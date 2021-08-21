#include "include/raylib.h"
#include "camera.h"
#pragma once

typedef struct {
    int x;
    int y;
    int sizeX;
    int sizeY;
    bool trigger;
    bool ladder; // private
    bool enabled;
}BoxCollider2D;

typedef struct TextBox{
    int x;
    int y;
    int size;
    char text[40];
    Color colour;
}TextBox;

typedef struct{
    Vector2 position;
    int sizeX;
    int sizeY;
    Vector2 velocity; // private
    bool trigger;
    bool enabled;
    bool isTouchingPlayer; // private
}PhysicsObject;