#include "include/raylib.h"
#pragma once

Vector2 addVec2(Vector2 input, Vector2 input2){
    Vector2 temp = input;
    temp.x += input2.x;
    temp.y += input2.y;
    return temp;
}

Vector2 subVec2(Vector2 input, Vector2 input2){
    Vector2 temp = input;
    temp.x -= input2.x;
    temp.y -= input2.y;
    return temp;
}

Vector2 negVec2(Vector2 input){
    Vector2 temp = input;
    temp.x = -input.x;
    temp.y = -input.y;
    return temp;
}

Vector2 addNewVec2(Vector2 input, float inX, float inY){
    Vector2 temp = input;
    temp.x += inX;
    temp.y += inY;
    return temp;
}

Vector2 newVec2(float inX, float inY){
    Vector2 temp;
    temp.x = inX;
    temp.y = inY;
    return temp;
}

//Linear interpolation (Lerp)
//lerpAmount changes the input a certain percentage of the distance of the input to the destination

//Broken. Pls fix
Vector2 lerpVec2(Vector2 input, float destX, float destY, float lerpAmount){
    Vector2 temp = input;
    if(lerpAmount == 0){
        printf("WARNING: lerpAmount has been set to zero!\n");
    }

    /*if(destX > temp.x){
        printf("%f += %f - %f * %f;", temp.x, destX, temp.x, lerpAmount);
        temp.x += (destX - temp.x) * lerpAmount;
        printf("%f;", temp.x);
        printf("x = Greater\n");
    }else{
        printf("%f -= %f - %f * %f;", temp.x, destX, temp.x, lerpAmount);
        temp.x += (destX - temp.x) * lerpAmount;
        printf("%f;", temp.x);
        printf("x = Lesser\n");
    }*/
    temp.x += (destX - temp.x) * lerpAmount;

    /*if(destY > temp.y){
        printf("%f += %f - %f * %f;", temp.y, destY, temp.y, lerpAmount);
        temp.y += (destY - temp.y) * lerpAmount;
        printf("%f;", temp.y);
        printf("y = Greater\n");
    }
    else{
        printf("%f -= %f - %f * %f;", temp.y, destY, temp.y, lerpAmount);
        temp.y += (destY - temp.y) * lerpAmount;
        printf("%f;", temp.y);
        printf("y = Lesser\n");
    }*/
    temp.y += (destY - temp.y) * lerpAmount;
    printf("%f;%f;\n", temp.x, temp.y);

    return temp;
}