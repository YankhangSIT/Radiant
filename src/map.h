//---------------------------------------------------------
// file:	map.h
// author:	Koh Yan Khang, Wei Jingsong
// email:	yankhang.k@digipen.edu, jingsong.wei@digipen.edu
// brief:	Includes code for the collision detection for character
// and enemey with obstruction.
//
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#include <stdbool.h>
#include "cprocessing.h"
#define MAX_Obs1 66
#define MAX_Obs2 98
#define MAX_Obs3 133
#define MAX_Obs4 135
CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY);
CP_Vector checkObsCollision(CP_Vector charPosition, float cWidth, float cHeight, float x, float y, float width, float height);
int checkProjectileMapCollision(CP_Vector bulletPosition, float minX, float maxX, float minY, float maxY);
bool checkProjectileObsCollision(CP_Vector bulletPosition, float bulletWidth, float bulletHeight, float x, float y, float width, float height);
typedef struct Rect
{
	float x;
	float y;
	float width;
	float height;
	CP_Image spriteImage;
} Rect;
typedef struct Obstruction
{
	Rect rec_block[MAX_Obs4];
} Obstruction;
Rect SetRect_(float x, float y, float width, float height, CP_Image sprite);
const int obstructionCount1;
const int obstructionCount2;
const int obstructionCount3;
const int obstructionCount4;
CP_Image map_background;
CP_Image obstruction1;
CP_Image obstruction2;
CP_Image obstruction3;
CP_Image obstruction4;
CP_Image obstruction5;
CP_Image obstruction6;
CP_Image obstruction7;
CP_Image obstruction8;
CP_Image obstruction9;
CP_Image obstruction10;
Obstruction obs;
float obsWidth1;
float obsHeight1;
float obsWidth2;
float obsHeight2;
float obsWidth3;
float obsHeight3;
float obsWidth4;
float obsHeight4;
float obsWidth5;
float obsHeight5;
float obsWidth6;
float obsHeight6;
float obsWidth7;
float obsHeight7;
float obsWidth8;
float obsHeight8;
float obsWidth9;
float obsHeight9;
float obsWidth10;
float obsHeight10;