#include "animation.h"
#include <stdio.h>
#include "checkColliders.h"
#include "loadNew.h"
#include "velocity.h"
#include "vector2pp.h"
#include "dataHandling.h"
#include "exponent.h"
#include "levelVariables.h"

/* TODO LIST!! (Top to bottom)s

* VECTOR 2 READING FROM PHYSICS OBJECTS IS BROKEN!!!
* Custom level mode
* Ladders (setup for collision checking done, physics manipulation still need to be done)
* Allow for crates to give velocity to one another
* Disappearing walls / portals
* Multiple lever instance possibility
* Multiple portal instance ppossibility
* Side scrolling - Only if you want to do the original scrolling
*/

/* BUGS
* At low frame rates, you cannot grab crates from the side but can from the top
*/


int main(void){
    //ask for resolution and fps
    int screenWidth;
    int screenHeight;
    int screenFPS;
    char str[40];

    Vector2 test;
    /*float test_output[16];
    for(int i = 0; i < 16; i++){
        test_output[i] = false;
    }
    
    for(int i = 0; i < 16; i++){
        printf("%d;", test_output[i]);
    }*/
    //printf("%d\n", parseInt("130;8492749274", 9));
    //test = readVector2("(1029,10983)");
    //printf("%f,%f\n", test.x, test.y);
    //test = readVector2Float("(92.133,3108.1)");
    //printf("%f,%f\n", test.x, test.y);
    char levelImagePath[64];
    disableCam = false;
    //printf("%d\n", readFileSF("level01.sandwich", true, &isDoor, &isLever, levelImagePath, &disableCam, &startingPos, &camera, Col, ladderCol, levelText, crate, &levelTexts, &levelCol, &ladderNum, &objectCol));
    loadNew(2, false, levelImagePath);
    /*//printf("hello6");
    printf("(%f,%f),(%f,%f),(%f,%f),%d,%f\n", camera.position.x, camera.position.y, camera.maxCamera.x, camera.maxCamera.y, camera.minCamera.x, camera.minCamera.y, camera.smoothingEnabled, camera.smoothing);
    //parseInt("99999999;", 10);
    printf("%s---\n", levelImagePath);
    printf("%d, %d, %d, %d, %d, %d\n", Col[0].x, Col[0].y, Col[0].sizeX, Col[0].sizeY, Col[0].trigger, Col[0].enabled);
    printf("%d, %d, %d, %d, %d, %d\n", Col[1].x, Col[1].y, Col[1].sizeX, Col[1].sizeY, Col[1].trigger, Col[1].enabled);

    printf("%d, %d, %d, %d, %d, %d\n", ladderCol[0].x, ladderCol[0].y, ladderCol[0].sizeX, ladderCol[0].sizeY, ladderCol[0].trigger, ladderCol[0].enabled);
    printf("%d, %d, %d, %d, %d, %d\n", ladderCol[1].x, ladderCol[1].y, ladderCol[1].sizeX, ladderCol[1].sizeY, ladderCol[1].trigger, ladderCol[1].enabled);
*/
    printf("%f, %f, %d, %d, %d, %d\n", crate[0].position.x, crate[0].position.y, crate[0].sizeX, crate[0].sizeY, crate[0].trigger, crate[0].enabled);
    printf("%f, %f, %d, %d, %d, %d\n", crate[1].position.x, crate[1].position.y, crate[1].sizeX, crate[1].sizeY, crate[1].trigger, crate[1].enabled);
/*
    //Color parsed = parseColor("(255,12,55,93)", 12);
    //printf("%d, %d, %d, %d\n", parsed.r, parsed.g, parsed.b, parsed.a);

    printf("\n%d, %d, %d, %s, (%d, %d, %d, %d)\n", levelText[0].x, levelText[0].y, levelText[0].size, levelText[0].text, levelText[0].colour.r, levelText[0].colour.g, levelText[0].colour.b, levelText[0].colour.a);
    printf("%d, %d, %d, %s, (%d, %d, %d, %d)\n", levelText[1].x, levelText[1].y, levelText[1].size, levelText[1].text, levelText[1].colour.r, levelText[1].colour.g, levelText[1].colour.b, levelText[1].colour.a);
    //printf();

    printf("dc: %d, spx: %f, spy: %f\n", disableCam, startingPos.x, startingPos.y);*/

    printf("Enter Resolution (recommended: 135, 270, 540, 1080): ");
    scanf("%d", &screenHeight);
    screenWidth = (float)screenHeight / 9.00f * 16.00f;

    printf("Enter desired FPS: ");
    scanf("%d", &screenFPS);

    //initialize variables
    Vector2 bgPosition;
        bgPosition.x = 0;
        bgPosition.y = 0;
    void prepareLevel();

    //image related variables
    const int resolutionMultiplier = screenWidth / 240;
    const int backgroundResMultiplier = screenWidth / 320;
    Texture2D level;

    //load colliders and resize starting position and declare which level we start with
    int selectedLevel = 0;
    const int maxLevel = 3;
    printf("Type 0 for the regular levels and 1 for a custom level: ");
    int customLevel = 2;
    while(customLevel != 0 && customLevel != 1){
        scanf("%d", &customLevel);
        if(customLevel != 0 && customLevel != 1){
            printf("Enter 0 or 1\n");
        }
    }
    if(customLevel == 0){
        loadNew(selectedLevel, false, levelImagePath);
    }else{
        loadNew(selectedLevel, true, levelImagePath);
    }

    //game related variables
    const float characterSpeed = 96 / 2.25f * resolutionMultiplier;
    const float gravity = -9.81f * 1.5f * resolutionMultiplier / 8;
    const float jumpHeight = 490.5f * resolutionMultiplier / 8;
    const float frictionCoefficient = 1.05f;
    float velocity = 0.00f;
    //bool isTouchingCrate;
    bool ColliderDebugMode = false;
    bool player_flipX = false;
    bool CrateDebugMode = false;
    bool showVelocity = false;
    int ShowCollider = 0;
    Vector2 playerPos;
    test.x = 100;
    test.y = 100;


    //start raylib
    InitWindow(screenWidth, screenHeight, "Sandwich Factory");
    InitAudioDevice();
    SetTargetFPS(screenFPS);

    //prepare level variables
    prepareLevel(resolutionMultiplier, &playerPos, startingPos, selectedLevel, &level, str);

    //load images
    Animation background;
    background = assignProperties(0, 10, true, 10, true);

    background.frameBuffer = 0;
    background = getFromFolder(background, "resources/background/");

    Animation door;
    door = assignProperties(0, 60, false, 12, false);
    door = getFromFolder(door, "resources/objects/door/");
    bool door_isClosed = true;

    SwitchAnimation lever;
    lever = switchAssignProperties(0, 10, false);
    lever = switchGetFromFolder(lever, "resources/objects/lever/");

    Texture2D player = LoadTexture("resources/objects/player.png");
    Texture2D player_flipped = LoadTexture("resources/objects/player_flip.png");

    Animation ladder;
    ladder = assignProperties(0, 0, false, 7, true);
    ladder = getFromFolder(ladder, "resources/objects/ladder/");

    Texture2D crateImage = LoadTexture("resources/objects/crate.png");

    //load sounds

    Sound door_open;
    door_open = LoadSound("resources/sounds/door/open.wav");
    Sound door_close;
    door_close = LoadSound("resources/sounds/door/close.wav");

    //Sound portal;
    //portal = LoadSound("resources/sounds/portal.wav");

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
            door = cycleAnimation(door, screenFPS);
            printf("door is animating (opening)\n");
            if(door.currentFrame == door.frameCount - 1){
                printf("opeinging animationg ended\n");
                door.isAnimating = false;
                door_isClosed = false;
                Col[levelCol + 1].enabled = false;
            }
        }else if(door.isAnimating && door_isClosed == false){
            door = cycleAnimationBackwards(door, screenFPS);
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
        if(collision.inLadder == true){
            
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
                printf("Attemping to load level %d because posX: %f > width: %d\n", selectedLevel, playerPos.x, screenWidth);
                if(loadNew(selectedLevel, false, levelImagePath) == 0){
                    printf("Succesfully loaded\n");
                }
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
                printf("Attemping to load level %d because posX: %f > width: %d\n", selectedLevel, playerPos.x, screenWidth);
                if(loadNew(selectedLevel, false, levelImagePath) == 0){
                    printf("Succesfully loaded\n");
                }
                prepareLevel(resolutionMultiplier, &playerPos, startingPos, selectedLevel, &level, str);
            }
        }

        //Velocity management
        if((velocity <= 0 && collision.down == false) || velocity > 0){
            velocity += gravity / (screenFPS / 60.00f);
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

        //Change camera position
        Vector2 camInput = addNewVec2(negVec2(playerPos), screenWidth / 2.00f, screenHeight / 2.00f);
        if(!disableCam && camera.smoothingEnabled){
            camera = lerpCamera(camera, camInput.x, camInput.y);
        }
        

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
        
        if(IsKeyPressed(KEY_F10)){
            test = lerpVec2(test, 50, 50, 0.25f);
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
            DrawTextureEx(background.frames[background.currentFrame], bgPosition, 0, backgroundResMultiplier, WHITE);

            Vector2 tempVector;

            //Level + Text
            DrawTextureEx(level, addVec2(bgPosition, camera.position), 0, resolutionMultiplier, WHITE);
            for(int i = 0; i < levelTexts; i++){
                DrawText(levelText[i].text, levelText[i].x + camera.position.x, levelText[i].y + camera.position.y, levelText[i].size, levelText[i].colour);
            }

            //Objects in level
            if(isLever){
                tempVector.x = Col[levelCol].x;
                tempVector.y = Col[levelCol].y;
                DrawTextureEx(lever.frames[lever.currentFrame], addVec2(tempVector, camera.position), 0, resolutionMultiplier, WHITE);
            }
            if(isDoor){
                tempVector.x = Col[levelCol + 1].x;
                tempVector.y = Col[levelCol + 1].y;
                DrawTextureEx(door.frames[door.currentFrame], addVec2(tempVector, camera.position), 0, resolutionMultiplier, WHITE);
            }
            if(objectCol > 0){
                for(int i = 0; i < objectCol; i++){
                    DrawTextureEx(crateImage, addVec2(crate[i].position, camera.position), 0, resolutionMultiplier, WHITE);
                }
            }

            //Ladders
            
            for(int i = 0; i < ladderNum; i++){
                printf("%d;", ladderCol[i].x);
                printf("%d;", ladderCol[i].y);
                tempVector.x = ladderCol[i].x;
                tempVector.y = ladderCol[i].y;
                for(int i = 0; i < (float)ladderCol[i].sizeY / 3.00f; i++){
                    //printf(";fard");
                    //printf("%d", ladderCol[i].sizeY / 3);
                    //printf(";%d", i);
                    //printf("!%d!", i < ladderCol[i].sizeY / 3);
                    printf("%d;", ladder.frames[0].height);
                    printf("%d;", ladder.frames[0].width);
                    printf("!");
                    DrawTextureEx(ladder.frames[0], tempVector, 0, resolutionMultiplier, WHITE);
                    tempVector.y += 3 * resolutionMultiplier;
                    printf("%d", i);
                    //GetRandomValue(0, ladder.frameCount - 1)
                }
                DrawRectangle(ladderCol[i].x, ladderCol[i].y, ladderCol[i].sizeX, 1, WHITE);
                printf("\n");
            }

            //Player
            if(player_flipX){
                DrawTextureEx(player_flipped, addVec2(playerPos, camera.position), 0, resolutionMultiplier, WHITE);
            }else{
                DrawTextureEx(player, addVec2(playerPos, camera.position), 0, resolutionMultiplier, WHITE);
            }

            //Debug related - DOES NOT FOLLOW CAM!!
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
    printf("Attemping to load image: %s\n", str);
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

    //resize ladders

    for(int i = 0; i < ladderNum; i++){
        ladderCol[i].x *= resolutionMultiplier;
        ladderCol[i].y *= resolutionMultiplier;
        ladderCol[i].sizeX *= resolutionMultiplier;
        ladderCol[i].sizeY *= resolutionMultiplier;
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

    camera.position.x = 0;
    camera.position.y = 0;

    if(disableCam){
        camera.maxCamera.x = 0;
        camera.maxCamera.y = 0;
        camera.minCamera.x = 0;
        camera.minCamera.y = 0;
        camera.smoothingEnabled = false;
    }
}
    