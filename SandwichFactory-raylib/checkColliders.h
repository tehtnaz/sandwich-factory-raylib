#include "resources/levels/1.h"
#include "resources/levels/2.h"
#include "resources/levels/3.h"
#include "resources/levels/4.h"
#include "abs.h"
#include "checkColliders_Float.h"
#pragma once
/*
*  0 = x Position
*  1 = y Position
*  2 = size X
*  3 = size Y
*/

bool up(int box[4], float self[4]){
    if((self[1] < box[1] + box[3] && self[1] > box[1]) || self[1] == box[1]){
        return true;
    }else{
        return false;
    }
}
bool left(int box[4], float self[4]){
    if(self[0] < box[0] + box[2] && self[0] > box[0]){
        return true;
    }else{
        return false;
    }
}
bool right(int box[4], float self[4]){
    if(self[0] + self[2] > box[0] && self[0] + self[2] < box[0] + box[2]){
        return true;
    }else{
        return false;
    }
}
bool down(int box[4], float self[4]){
    if((self[1] + self[3] > box[1] && self[1] + self[3] < box[1] + box[3]) || self[1] + self[3] == box[1] + box[3]){
        return true;
    }else{
        return false;
    }
}


bool betweenX(int box[4], float self[4]){
    if(self[0] > box[0] && self[0] + self[2] < box[0] + box[2]){
        return true;
    }else{
        return false;
    }
}
bool betweenY(int box[4], float self[4]){
    if(self[1] > box[1] && self[1] + self[3] < box[1] + box[3]){
        return true;
    }else{
        return false;
    }
}

bool objectBetweenX(int box[4], float self[4]){
    if(box[0] > self[0] && box[0] + box[2] < self[0] + self[2]){
        return true;
    }else{
        return false;
    }
}
bool objectBetweenY(int box[4], float self[4]){
    if(box[1] > self[1] && box[1] + box[3] < self[1] + self[3]){
        return true;
    }else{
        return false;
    }
}

bool botLeftEdgeCheck(int box[4], float self[4]){
    int distanceY = self[1] + self[3] - box[1];
    int distanceX = box[0] + box[2] - self[0];
    if(distanceX < distanceY){
        //horizontal collision
        return true;
    }else{
        //vertical collision
        return false;
    }
}
bool botRightEdgeCheck(int box[4], float self[4]){
    int distanceY = self[1] + self[3] - box[1];
    int distanceX = self[0] + self[2] - box[0];
    if(distanceX < distanceY){
        //horizontal collision
        return true;
    }else{
        //vertical collision
        return false;
    }
}
bool topLeftEdgeCheck(int box[4], float self[4]){
    int distanceY = box[1] + box[3] - self[1];
    int distanceX = box[0] + box[2] - self[0];
    if(distanceX < distanceY){
        //horizontal collision
        return true;
    }else{
        //vertical collision
        return false;
    }
}
bool topRightEdgeCheck(int box[4], float self[4]){
    int distanceY = box[1] + box[3] - self[1];
    int distanceX = self[0] + self[2] - box[0];
    if(distanceX < distanceY){
        //horizontal collision
        return true;
    }else{
        //vertical collision
        return false;
    }
}

/*
* Return value = direction of collision
* Return value definitions:
* 0 = None
* 1 = Left
* 2 = Right
* 3 = Up
* 4 = Down
*/

/*
*  0 = x Position
*  1 = y Position
*  2 = size X
*  3 = size Y
*/
int checkCollider(int box[4], float self[4], bool trigger, bool enabled, bool ladder){
    if(enabled == false){
        return 0;
    }

    if(betweenX(box, self) || objectBetweenX(box, self)){
        //printf("X %d    ", id);
        if(up(box, self)){
            if(trigger) {
                return 5;
            }
            if(ladder) {
                return 6;
            }
            return 3;
        }else if(down(box, self)){
            if(trigger) {
                return 5;
            }
            if(ladder) {
                return 6;
            }
            return 4;
        }
    }else if (betweenY(box, self) || objectBetweenY(box, self)){
        //printf("Y %d    ", id);
        if(left(box, self)){
            if(trigger) {
                return 5;
            }
            if(ladder) {
                return 6;
            }
            return 1;
        }else if(right(box, self)){
            if(trigger) {
                return 5;
            }
            if(ladder) {
                return 6;
            }
            return 2;
        }
    }else{
        if(left(box, self) && (up(box, self) || down(box, self))){
            if(trigger) {
                return 5;
            }
            if(ladder) {
                return 6;
            }

            if(up(box, self)){
                //True = horizontal
                //False = vertical

                if(topLeftEdgeCheck(box, self)){
                    return 1;
                }else{
                    return 3;
                }
            }else{
                if(botLeftEdgeCheck(box, self)){
                    return 1;
                }else{
                    return 4;
                }
            }
        }
        if(right(box, self) && (up(box, self) || down(box, self))){
            if(trigger) {
                return 5;
            }
            if(ladder) {
                return 6;
            }

            if(up(box, self)){
                //True = horizontal
                //False = vertical
                if(topRightEdgeCheck(box, self)){
                    return 2;
                }else{
                    return 3;
                }
            }else{
                if(botRightEdgeCheck(box, self)){
                    return 2;
                }else{
                    return 4;
                }
            }
        }
    }
    return 0;
}

/*
* 0 = None
* 1 = Left
* 2 = Right
* 3 = Up
* 4 = Down
* 5 = Trigger
* 6 = ladder
*/
typedef struct {
    bool left;
    bool right;
    bool up;
    bool down;
    int colsTouched[14];
    //bool sidesTouched[4];
    int floor;
    bool inTrigger;
    bool inLadder;
}CollisionInfo;

//CollisionInfo objCollision;

CollisionInfo checkAllColliders(float self[4], bool checkObjects){
    CollisionInfo collision;
    //This will cause the use of more memory
    int box[4];
    float f_box[4];
    int result;

    collision.left = false;
    collision.right = false;
    collision.up = false;
    collision.down = false;
    collision.inTrigger = false;
    collision.inLadder = false;

    int colsToCheck = levelCol;
    //printf("%d\n", colsToCheck);
    if(isLever) colsToCheck++;
    if(isDoor) colsToCheck++;
    //printf("%d\n", colsToCheck);
    if(checkObjects && objectCol > 0 ) colsToCheck += objectCol;
    //printf("%d\n", colsToCheck);

    for(int i = 0; i < colsToCheck; i++){
        if(i > levelCol - 1 + isLever + isDoor){
            f_box[0] = crate[i - levelCol].position.x;
            f_box[1] = crate[i - levelCol].position.y;
            f_box[2] = crate[i - levelCol].sizeX;
            f_box[3] = crate[i - levelCol].sizeY;
            result = f_checkCollider(f_box, self, crate[i - levelCol].trigger, crate[i - levelCol].enabled);
            printf("checking obj: %d\n", i - levelCol);
        }else{
            box[0] = Col[i].x;
            box[1] = Col[i].y;
            box[2] = Col[i].sizeX;
            box[3] = Col[i].sizeY;
            result = checkCollider(box, self, Col[i].trigger, Col[i].enabled, Col[i].ladder);
        }
        if(result != 0){
            collision.colsTouched[i] = result;
            /*if(left(box,self)){
                collision.sidesTouched[0] = true;
            }
            if(right(box,self)){
                collision.sidesTouched[1] = true;
            }
            if(up(box, self)){
                collision.sidesTouched[2] = true;
            }
            if(down(box,self)){
                collision.sidesTouched[3] = true;
            }*/
        }
        if(result == 1){
            collision.left = true;
        }
        if(result == 2){
            collision.right = true;
        }
        if(result == 3){
            collision.up = true;
        }
        if(result == 4){
            collision.down = true;
            collision.floor = i;
        }
        if(result == 5){
            collision.inTrigger = true;
        }
        if(result == 6){
            collision.inLadder = true;
        }
        //printf("i = %d, trigger = %d, result = %d\n", i, Col[i].trigger, result);
    }
    return collision;
}

CollisionInfo checkObjects(CollisionInfo collision, float self[4], int selfObjID){

    //This will cause the use of more memory
    float f_box[4];
    int result;

    int colsToCheck = objectCol;
    //printf("%d\n", colsToCheck);

    for(int i = 0; i < colsToCheck; i++){

        f_box[0] = crate[i].position.x;
        f_box[1] = crate[i].position.y;
        f_box[2] = crate[i].sizeX;
        f_box[3] = crate[i].sizeY;

        if(i == selfObjID){
            result = 0;
        }else{
            result = f_checkCollider(f_box, self, crate[i].trigger, crate[i].enabled);
        }

        if(result != 0){
            collision.colsTouched[i] = result;
        }
        if(result == 1){
            collision.left = true;
            //crate[i].velocity.x = crate[selfObjID].velocity.x;
        }
        if(result == 2){
            collision.right = true;
            //crate[i].velocity.x = crate[selfObjID].velocity.x;
        }
        if(result == 3){
            collision.up = true;
        }
        if(result == 4){
            collision.down = true;
            collision.floor = i;
        }
        if(result == 5){
            collision.inTrigger = true;
        }
    }
    return collision;
}