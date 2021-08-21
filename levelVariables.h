#include "include/raylib.h"
#include "camera.h"
#include "levelStructs.h"
#pragma once

BoxCollider2D Col[15];
BoxCollider2D ladderCol[2];

TextBox levelText[2];

PhysicsObject crate[2];

int levelTexts;
int levelCol;
//int levelID;
int ladderNum;
int objectCol;
bool isLever;
bool isDoor;
bool disableCam;

Vector2 startingPos;

s_Camera camera;