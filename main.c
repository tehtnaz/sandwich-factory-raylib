#include "animation.h"
#include <stdio.h>
#include "checkColliders.h"
#include "loadNew.h"
#include "velocity.h"

/* TODO LIST!! (Top to bottom)
* Allow for crates to give velocity to one another
* Side scrolling
* Ladders (setup for collision checking done, physics manipulation still need to be done)
* Disappearing walls / portals
* Multiple lever instance possibility
* Multiple portal instance ppossibility
*/



int main(void){
    //initialize variables
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int screenFPS = 60;
    Vector2 bgPosition;
        bgPosition.x = 0;
        bgPosition.y = 0;
    char str[40];
    void prepareLevel();

    //image related variables
    const int resolutionMultiplier = screenWidth / 240;
    Texture2D level;
    Texture2D player;
    Texture2D player_flipped;
    Texture2D crateImage;

    //load colliders and resize starting position and declare which level we start with
    int selectedLevel = 0;
    const int maxLevel = 2;
    loadNew(selectedLevel);

    //game related variables
    const float characterSpeed = 96 / 2.25f * resolutionMultiplier;
    const float gravity = -9.81f * 1.5f * resolutionMultiplier / 8;
    const float jumpHeight = 490.5f * resolutionMultiplier / 8;
    const float frictionCoefficient = 0.98f;
    float velocity = 0.00f;
    bool isTouchingCrate;
    bool ColliderDebugMode = false;
    bool player_flipX = false;
    bool CrateDebugMode = false;
    bool showVelocity = false;
    int ShowCollider = 0;
    Vector2 playerPos;



    //start raylib
    InitWindow(screenWidth, screenHeight, "Sandwich Factory");
    InitAudioDevice();
    SetTargetFPS(screenFPS);

    //prepare level variables
    prepareLevel(resolutionMultiplier, &playerPos, startingPos, selectedLevel, &level, str);

    //load images
    Animation background;
    background = assignProperties(0, 1, true, 10);
    background.fps = 10;

    background.frameBuffer = 0;
    background = getFromFolder(background, "resources/background/");

    Animation door;
    door = assignProperties(0, 10, false, 12);
    door = getFromFolder(door, "resources/objects/door/");
    bool door_isClosed = true;

    SwitchAnimation lever;
    lever = switchAssignProperties(0, 10, false);
    lever = switchGetFromFolder(lever, "resources/objects/lever/");

    player = LoadTexture("resources/objects/player.png");
    player_flipped = LoadTexture("resources/objects/player_flip.png");

    Animation ladder;
    ladder = assignProperties(0, 0, false, 7);
    ladder = getFromFolder(ladder, "resources/objects/ladder/");

    crateImage = LoadTexture("resources/objects/crate.png");

    //load sounds

    Sound door_open;
    door_open = LoadSound("resources/sounds/door/open.wav");
    Sound door_close;
    door_close = LoadSound("resources/sounds/door/close.wav");

    Sound portal;
    portal = LoadSound("resources/sounds/portal.wav");

    Sound soundtrack;
    soundtrack = LoadSound("resources/sounds/soundtrack/menu.wav");
    SetSoundVolume(soundtrack, 0.5f);

    //sprite size Vec2 definition
    Vector2 playerSize;
    playerSize.x = player.width * resolutionMultiplier;
    playerSize.y = player.height * resolutionMultiplier;

    if(!IsWindowFullscreen()){
        //ToggleFullscreen(); 
    }
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }

        if(!IsSoundPlaying(soundtrack)){
            PlaySound(soundtrack);
        }

        //Cycle anims
        background = cycleAnimation(background, screenFPS);
        if(door.isAnimating && door_isClosed == true){
            door = cycleAnimation(door, screenFPS/ 10);
            printf("door is animating (opening)\n");
            if(door.currentFrame == door.frameCount - 1){
                printf("opeinging animationg ended\n");
                door.isAnimating = false;
                door_isClosed = false;
                Col[levelCol + 1].enabled = false;
            }
        }else if(door.isAnimating && door_isClosed == false){
            door = cycleAnimationBackwards(door, screenFPS / 10);
            printf("door is animating (closing)\n");
            if(door.currentFrame == 0){
                printf("closing animation ended\n");
                door.isAnimating = false;
                door_isClosed = true;
                Col[levelCol + 1].enabled = true;
            }
        }

        //Prepare collision check
        float self[4];
        self[0] = playerPos.x;
        self[1] = playerPos.y;
        self[2] = playerSize.x;
        self[3] = playerSize.y;
        CollisionInfo collision = checkAllColliders(self, true);

        if(collision.down == true){
            velocity = 0;
            if(collision.floor <= levelCol - 1){
                playerPos.y = Col[collision.floor].y - playerSize.y + 0.1f;
            }
        }

        //Movement
        if((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)) && collision.up == false && collision.down == true){
            velocity += jumpHeight;
            //jump
        }
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
            //left
            player_flipX = true;
            if(collision.left == false){
                playerPos.x -= characterSpeed * (1.0f/(float)screenFPS);
            }
        }
        if(IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)){
            //right
            player_flipX = false;
            if(collision.right == false){
                playerPos.x += characterSpeed * (1.0f/(float)screenFPS);
            }
        }

        //Interact
        if(IsKeyPressed(KEY_E) && collision.inTrigger){
            //interact with lever
            if(lever.currentFrame == 0){
                lever.currentFrame = 1;
            }else{
                lever.currentFrame = 0;
            }
            door.isAnimating = true;
            printf("door should be animating %d\n", door_isClosed);
            if(door_isClosed){
                PlaySound(door_open);
            }else{
                PlaySound(door_close);
            }
        }
        //Reset
        if(playerPos.y > screenHeight || IsKeyPressed(KEY_R)){
            playerPos = startingPos;
        }
        if(playerPos.x > screenWidth){
            selectedLevel++;
            if(selectedLevel > maxLevel){
                printf("Error: Cannot load level above specified maximum (%d is too large for %d)\n", selectedLevel, maxLevel);
                playerPos = startingPos;
                CloseWindow();
                return 0;
            }else{
                loadNew(selectedLevel);
                prepareLevel(resolutionMultiplier, &playerPos, startingPos, selectedLevel, &level, str);
            }
        }

        //Skip level
        if(IsKeyPressed(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_TAB)){
            selectedLevel++;
            if(selectedLevel > maxLevel){
                printf("Error: Cannot load level above specified maximum (%d is too large for %d)\n", selectedLevel, maxLevel);
                playerPos = startingPos;
                CloseWindow();
                return 0;
            }else{
                loadNew(selectedLevel);
                prepareLevel(resolutionMultiplier, &playerPos, startingPos, selectedLevel, &level, str);
            }
        }

        //Velocity management
        if((velocity <= 0 && collision.down == false) || velocity > 0){
            velocity += gravity;
            if(!(velocity > 0 && collision.up == true)){
                playerPos.y -= velocity * (1/(float)screenFPS);
            }else{
                velocity = 0;
            }
        }

        //Manage crate collisions
        Vector2 inputVelocity;
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
            inputVelocity.x = -characterSpeed;
        }
        if(IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)){
            inputVelocity.x = characterSpeed;
        }
        if(((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D))) || !((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) || (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)))){
            inputVelocity.x = 0;
        }
        inputVelocity.y = velocity;
        crate[0] = updateObject(crate[0], playerPos, playerSize, inputVelocity, frictionCoefficient, screenFPS, gravity, 0, player_flipX, resolutionMultiplier);
        crate[1] = updateObject(crate[1], playerPos, playerSize, inputVelocity, frictionCoefficient, screenFPS, gravity, 1, player_flipX, resolutionMultiplier);

        //printf("fard - %f", inputVelocity.x);

        /*
        * Debug Section extra info
        * 0 = None
        * 1 = Left (Red)
        * 2 = Right (Green)
        * 3 = Up (Blue)
        * 4 = Down (Yellow)
        */
        if(IsKeyPressed(KEY_F1)){
            ColliderDebugMode = !ColliderDebugMode;
        }
        if(IsKeyPressed(KEY_F2)){
            CrateDebugMode = !CrateDebugMode;
        }
        if(IsKeyPressed(KEY_F3)){
            showVelocity = !showVelocity;
        }
        if(IsKeyPressed(KEY_F4)){
            if(ShowCollider > 0){
                ShowCollider = 0;
            }else{
                ShowCollider = 1;
            }
        }
        if(IsKeyPressed(KEY_TAB) && ShowCollider > 0){
            if(ShowCollider > levelCol){
                ShowCollider = 1;
            }else{
                ShowCollider++;
            }
        }
            
        BeginDrawing();
        ClearBackground(RAYWHITE);
            //Background
            DrawTextureEx(background.frames[background.currentFrame], bgPosition, 0, 6, WHITE);

            //Ladders
            Vector2 tempVector;
            for(int i = 0; i < ladderNum; i++){
                tempVector.x = ladderCol[i].x;
                tempVector.y = ladderCol[i].y;
                for(int i = 0; i < ladderCol[i].sizeY / 3; i++){
                    DrawTextureEx(ladder.frames[GetRandomValue(0, ladder.frameCount - 1)], tempVector, 0, resolutionMultiplier, WHITE);
                    tempVector.y += 3 * resolutionMultiplier;
                }
            }

            //Level + Text
            DrawTextureEx(level, bgPosition, 0, resolutionMultiplier, WHITE);
            for(int i = 0; i < levelTexts; i++){
                DrawText(levelText[i].text, levelText[i].x, levelText[i].y, levelText[i].size, levelText[i].colour);
            }

            //Objects in level
            if(isLever){
                tempVector.x = Col[levelCol].x;
                tempVector.y = Col[levelCol].y;
                DrawTextureEx(lever.frames[lever.currentFrame], tempVector, 0, resolutionMultiplier, WHITE);
            }
            if(isDoor){
                tempVector.x = Col[levelCol + 1].x;
                tempVector.y = Col[levelCol + 1].y;
                DrawTextureEx(door.frames[door.currentFrame], tempVector, 0, resolutionMultiplier, WHITE);
            }
            if(objectCol > 0){
                for(int i = 0; i < objectCol; i++){
                    DrawTextureEx(crateImage, crate[i].position, 0, resolutionMultiplier, WHITE);
                }
            }

            //Player
            if(player_flipX){
                DrawTextureEx(player_flipped, playerPos, 0, resolutionMultiplier, WHITE);
            }else{
                DrawTextureEx(player, playerPos, 0, resolutionMultiplier, WHITE);
            }

            //Debug related
            if(ColliderDebugMode){
                DrawRectangle(playerPos.x, playerPos.y, playerSize.x, playerSize.y, PINK);
                int colsToResize = levelCol;
                if(isLever) colsToResize++;
                if(isDoor) colsToResize++;
                for(int i = 0; i < colsToResize; i++){
                    switch(collision.colsTouched[i]){
                        case 0:
                            DrawRectangle(Col[i].x, Col[i].y, Col[i].sizeX, Col[i].sizeY, WHITE);
                            break;
                        case 1:
                            DrawRectangle(Col[i].x, Col[i].y, Col[i].sizeX, Col[i].sizeY, RED);
                            break;
                        case 2:
                            DrawRectangle(Col[i].x, Col[i].y, Col[i].sizeX, Col[i].sizeY, GREEN);
                            break;
                        case 3:
                            DrawRectangle(Col[i].x, Col[i].y, Col[i].sizeX, Col[i].sizeY, BLUE);
                            break;
                        case 4:
                            DrawRectangle(Col[i].x, Col[i].y, Col[i].sizeX, Col[i].sizeY, YELLOW);
                            break;
                        case 5:
                            DrawRectangle(Col[i].x, Col[i].y, Col[i].sizeX, Col[i].sizeY, BROWN);
                            break;
                    }
                }
            }
            /*if(true){
                if(objCollision.left){
                    DrawRectangle(playerPos.x, playerPos.y, 4, playerSize.y, PURPLE);
                }
                if(objCollision.right){
                    DrawRectangle(playerPos.x + playerSize.x, playerPos.y, 4, playerSize.y, PURPLE);
                }
                if(objCollision.up){
                    DrawRectangle(playerPos.x, playerPos.y, playerSize.x, 4, PURPLE);
                }
                if(objCollision.down){
                    DrawRectangle(playerPos.x, playerPos.y + playerSize.y, playerSize.x + 4, 4, PURPLE);
                }
            }*/
            /*if(IsKeyPressed(KEY_F2)){
                DrawRectangle(playerPos.x, playerPos.y, playerSize.x, playerSize.y, PURPLE);
            }*/
            if(showVelocity){
                sprintf(str, "%f", velocity);
                DrawText(str, 0, 50, 100, WHITE);
            }
            if(ShowCollider > 0){
                DrawRectangle(Col[ShowCollider - 1].x, Col[ShowCollider - 1].y, Col[ShowCollider - 1].sizeX, Col[ShowCollider - 1].sizeY, GREEN);
                sprintf(str, "%f", playerPos.y + playerSize.y);
                DrawText(str, 0, 0, 100, GREEN);
                sprintf(str, "%d", Col[ShowCollider - 1].y);
                DrawText(str, 0, 100, 100, GREEN);
                sprintf(str, "%d", Col[ShowCollider - 1].y + Col[ShowCollider - 1].sizeY);
                DrawText(str, 0, 200, 100, GREEN);
            }
            if(CrateDebugMode){
                sprintf(str, "%f", crate[0].velocity.x);
                DrawText(str, 0, 0, 100, RED);
                sprintf(str, "%f", inputVelocity.x);
                DrawText(str, 0, 100, 100, RED);
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void prepareLevel(int resolutionMultiplier, Vector2* playerPos, Vector2 startingPos, int selectedLevel, Texture2D* level, char str[40]){
    //load level image
    sprintf(str, "resources/levels/%d.png", selectedLevel + 1);
    *level = LoadTexture(str);

    //resize Colliders according to resolution
    int colsToResize = levelCol;
    if(isLever) colsToResize++;
    if(isDoor) colsToResize++;
    for(int i = 0; i < colsToResize; i++){
        Col[i].x *= resolutionMultiplier;
        Col[i].y *= resolutionMultiplier;
        Col[i].sizeX *= resolutionMultiplier;
        Col[i].sizeY *= resolutionMultiplier;
        printf("%d\n",Col[i].x + Col[i].sizeX);
    }
    //resize levelText according to resolution
    
    for(int i = 0; i < levelTexts; i++){
        levelText[i].x *= resolutionMultiplier;
        levelText[i].y *= resolutionMultiplier;
        levelText[i].size *= resolutionMultiplier;
    }
    Vector2 tempPos = startingPos;
    tempPos.x *= resolutionMultiplier;
    tempPos.y *= resolutionMultiplier;
    *playerPos = tempPos;

    for(int i = 0; i < objectCol; i++){
        crate[i].position.x *= resolutionMultiplier;
        crate[i].position.y *= resolutionMultiplier;
        crate[i].sizeX *= resolutionMultiplier;
        crate[i].sizeY *= resolutionMultiplier;
        crate[i].velocity.x = 0;
        crate[i].velocity.y = 0;
    }
}
    