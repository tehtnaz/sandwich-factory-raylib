#pragma once
#include "resources/levels/levelStructs.h"
#include "checkColliders.h"
#include "checkColliders_Float.h"

/*
* 0 = None
* 1 = Left
* 2 = Right
* 3 = Up
* 4 = Down
* 5 = Trigger
*/

bool isTouchingPlayer(PhysicsObject input, Vector2 playerPosition, Vector2 playerSize, int resMultiplier){
    float self[4];
    self[0] = input.position.x;
    self[1] = input.position.y;
    self[2] = input.sizeX;
    self[3] = input.sizeY;
    float box[4];
    box[0] = playerPosition.x - (resMultiplier * 2);
    box[1] = playerPosition.y + resMultiplier;
    box[2] = playerSize.x + (resMultiplier * 4);
    box[3] = playerSize.y - (resMultiplier * 2);
    int result = f_checkCollider(box, self, false, true);
    if(result == 0){
        return false;
    }else{
        return true;
    }

}

PhysicsObject updateObject(PhysicsObject input, Vector2 playerPosition, Vector2 playerSize, Vector2 playerVelocity, float friction, int screenFPS, float gravity, int crateID, bool flipX, int resMultiplier){
    
    PhysicsObject temp = input;
    float fpsMultiplier = (1.0f/(float)screenFPS);

    //Friction
    temp.velocity.x = temp.velocity.x * (friction / screenFPS) * 60;

    //Check against level colliders
    float self[4];
    self[0] = input.position.x;
    self[1] = input.position.y;
    self[2] = input.sizeX;
    self[3] = input.sizeY;
    CollisionInfo objCollision = checkAllColliders(self, false);
    objCollision = checkObjects(objCollision, self, crateID);

    //Check against given player
    float box[4];
    box[0] = playerPosition.x;
    box[1] = playerPosition.y;
    box[2] = playerSize.x;
    box[3] = playerSize.y;
    int result = f_checkCollider(box, self, false, true);
    //printf("%d\n", result);
    if(result == 1){
        objCollision.left = true;
        //if(!objCollision.right) temp.position.x += 1;
        temp.velocity.x = playerVelocity.x;
    }
    if(result == 2){
        objCollision.right = true;
        //if(!objCollision.left) temp.position.x -= 1;
        temp.velocity.x = playerVelocity.x;
    }
    if(result == 3){
        objCollision.up = true;
    }
    if(result == 4){
        objCollision.down = true;
    }
    if(result == 0){
        temp.isTouchingPlayer = false;
    }else{
        temp.isTouchingPlayer = true;
    }

    if(IsKeyDown(KEY_E) && isTouchingPlayer(temp, playerPosition, playerSize, resMultiplier)){
        temp.velocity.x = playerVelocity.x;
        temp.velocity.y = -playerVelocity.y;
    }

    //Change velocity based on collision
    if(!objCollision.down){
        temp.velocity.y -= gravity;
    }

    if((objCollision.down && temp.velocity.y > 0) || (objCollision.up && temp.velocity.y < 0)){
        
        temp.velocity.y = 0;
        //if (objCollision.down && temp.velocity.y > 0) temp.position.y = Col[objCollision.floor].y - temp.sizeY + 0.1f;
    }
    if((objCollision.left && temp.velocity.x < 0) || (objCollision.right && temp.velocity.x > 0)){
        temp.velocity.x = 0;
    }

    //Update Velocity
    temp.position.x += temp.velocity.x * fpsMultiplier;
    temp.position.y += temp.velocity.y * fpsMultiplier;

    //printf("x = %f\n", temp.velocity.x);
    //printf("y = %f\n", temp.velocity.y);
    //printf("touch = %d\n", temp.isTouchingPlayer);
    return temp;
}