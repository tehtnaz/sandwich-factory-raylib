#include "../../include/raylib.h"
#pragma once

typedef struct {
    int x;
    int y;
    int sizeX;
    int sizeY;
    bool trigger;
    bool ladder;
    bool enabled;
}BoxCollider2D;

BoxCollider2D Col[15];
BoxCollider2D ladderCol[2];

struct TextBox{
    int x;
    int y;
    int size;
    char text[40];
    Color colour;
}levelText[2];

typedef struct{
    Vector2 position;
    int sizeX;
    int sizeY;
    Vector2 velocity;
    bool trigger;
    bool enabled;
    bool isTouchingPlayer;
}PhysicsObject;

PhysicsObject crate[2];

int levelTexts;
int levelCol;
int levelID;
int ladderNum;
int objectCol;
bool isLever;
bool isDoor;

Vector2 startingPos;