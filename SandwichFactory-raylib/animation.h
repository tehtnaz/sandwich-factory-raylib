#include "include/raylib.h"
#include <stdio.h>
#pragma once
typedef struct{
    int frameCount; //Essentially the point in the array where it returns to zero (because the array size is static) but yes it's the number of frames
    Texture2D frames[20];
    int fps; //Instead of the rendered fps, use whatever you like!
    bool isAnimating;
    int currentFrame;
    float frameBuffer; //Used in main.c to tell how many frames have gone between each switch
    bool allowSnap;
}Animation;

typedef struct{
    Texture2D frames[2];
    int fps;
    bool isAnimating;
    int currentFrame;
}SwitchAnimation;

Animation assignProperties(int currentFrame, int fps, bool isAnimating, int frameCount, bool allowsnap){
    Animation temp;
    temp.frameCount = frameCount;
    temp.fps = fps;
    temp.isAnimating = isAnimating;
    temp.currentFrame = currentFrame;
    temp.frameBuffer = 0;
    temp.allowSnap = allowsnap;
    return temp;
}

Animation getFromFolder(Animation input, char path[40]){
    Animation temp = input;
    char str[45];
    for(int i = 0; i < input.frameCount; i++){
        sprintf(str, "%s%d.png", path, i);
        temp.frames[i] = LoadTexture(str);
    }
    return temp;
}

SwitchAnimation switchAssignProperties(int currentFrame, int fps, bool isAnimation){
    SwitchAnimation temp;
    temp.fps = fps;
    temp.isAnimating = isAnimation;
    temp.currentFrame = currentFrame;
    return temp;
}

SwitchAnimation switchGetFromFolder(SwitchAnimation input, char path[40]){
    SwitchAnimation temp = input;
    char str[45];
    sprintf(str, "%s0.png", path);
    temp.frames[0] = LoadTexture(str);
    sprintf(str, "%s1.png", path);
    temp.frames[1] = LoadTexture(str);
    return temp;
}

Animation cycleAnimation(Animation input, float screenfps){
    Animation temp = input;

    temp.frameBuffer += temp.fps / screenfps;
    
    if((float)screenfps / temp.fps - 1 < 0){
        while(temp.frameBuffer >= 1){
            temp.frameBuffer--;
            if(temp.allowSnap || (temp.currentFrame != temp.frameCount - 1 && !temp.allowSnap)){
                temp.currentFrame++;
            }
        }
    }else{
        if(temp.frameBuffer >= 1){
            temp.frameBuffer--;
            temp.currentFrame++;
        }
    }

    if(temp.currentFrame > temp.frameCount - 1 && temp.allowSnap){
        temp.currentFrame = 0;
    }
    return temp;
}

Animation cycleAnimationBackwards(Animation input, float screenfps){
    Animation temp = input;

    temp.frameBuffer += temp.fps / screenfps;

    if((float)screenfps / temp.fps - 1 < 0){
        while(temp.frameBuffer >= 1){
            temp.frameBuffer--; 
            if(temp.allowSnap || (temp.currentFrame != 0 && !temp.allowSnap)){
                temp.currentFrame--;
            }
        }
    }else{
        if(temp.frameBuffer >= 1){
            temp.frameBuffer--;
            temp.currentFrame--;
        }
    }

    if(temp.currentFrame < 0 && temp.allowSnap){
        temp.currentFrame = temp.frameCount - 1;
    }
    return temp;
}