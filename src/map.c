//---------------------------------------------------------
// file:	map.c
// author:	Koh Yan Khang, Wei Jingsong
// email:	yankhang.k@digipen.edu, jingsong.wei@digipen.edu
// brief:	Includes code for the collision detection for character
// and enemey with obstruction.
// 
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "level1.h"
#include "map.h"
//Max obstrtuction object count for each level
const int obstructionCount1 = MAX_Obs1;
const int obstructionCount2 = MAX_Obs2;
const int obstructionCount3 = MAX_Obs3;
const int obstructionCount4 = MAX_Obs4;
//Obstruction initialisation
Rect SetRect_(float x, float y, float width, float height, CP_Image sprite)
{
	Rect rec;
	rec.x = x;
	rec.y = y;
	rec.width = width;
	rec.height = height;
	rec.spriteImage = sprite;

	return rec;
}
//Character movement out of screen window bounds detection
CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY)
{
	if (charPosition.x <= minX)
	{
		charPosition.x = minX;
	}
	else if (charPosition.x >= maxX)
	{
		charPosition.x = maxX;
	}
	if (charPosition.y <= minY)
	{
		charPosition.y = minY;
	}
	else if (charPosition.y >= maxY)
	{
		charPosition.y = maxY;
	}
	return charPosition;
}
//Projectiles out of scrren window bounds detection
int checkProjectileMapCollision(CP_Vector bulletPosition, float minX, float maxX, float minY, float maxY)
{
	if (bulletPosition.x <= minX)
	{
		return 1;
	}
	else if (bulletPosition.x >= maxX)
	{
		return 1;
	}
	else if (bulletPosition.y <= minY)
	{
		return 1;
	}
	else if (bulletPosition.y >= maxY)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//Projectiles and obstruction collision detection
bool checkProjectileObsCollision(CP_Vector bulletPosition, float bulletWidth, float bulletHeight, float x, float y, float width, float height)
{
	if (bulletPosition.x + bulletWidth / 2 > x - width / 2 && bulletPosition.x - bulletWidth / 2 < x + width / 2 && bulletPosition.y + bulletHeight / 2 > y - height / 2 && bulletPosition.y - bulletHeight / 2 < y + height / 2)
	{
		return true;
	}
	return false;
}
//Character and enemey movement collision with obstruction detection
CP_Vector checkObsCollision(CP_Vector charPosition, float cWidth, float cHeight, float x, float y, float width, float height)
{
	if (charPosition.x + cWidth / 2 > x - width / 2 && charPosition.x - cWidth / 2 < x + width / 2 && charPosition.y + cHeight / 2 > y - height / 2 && charPosition.y - cHeight / 2 < y + height / 2)
	{
		float deltaLeft = 100;
		float deltaRight = 100;
		float deltaUp = 100;
		float deltaDown = 100;
		if (fabsf(charPosition.x - (x - width / 2)) > fabsf(charPosition.x - (x + width / 2)))
		{
			deltaRight = (width + cWidth) - ((charPosition.x + cWidth / 2) - (x - width / 2));
		}
		if (fabsf(charPosition.x - (x - width / 2)) < fabsf(charPosition.x - (x + width / 2)))
		{
			deltaLeft = (width + cWidth) - ((x + width / 2) - (charPosition.x - cWidth / 2));
		}
		if (fabsf(charPosition.y - (y - height / 2)) > fabsf(charPosition.y - (y + height / 2)))
		{
			deltaDown = (height + cHeight) - ((charPosition.y + cHeight / 2) - (y - height / 2));
		}
		if (fabsf(charPosition.y - (y - height / 2)) < fabsf(charPosition.y - (y + height / 2)))
		{
			deltaUp = (height + cHeight) - ((y + height / 2) - (charPosition.y - cHeight / 2));
		}

		if (fabsf(deltaRight) < fabsf(deltaLeft) && fabsf(deltaRight) < fabsf(deltaDown) && fabsf(deltaRight) < fabsf(deltaUp))
		{
			charPosition.x = (x + width / 2) + cWidth / 2;
		}
		if (fabsf(deltaLeft) < fabsf(deltaRight) && fabsf(deltaLeft) < fabsf(deltaDown) && fabsf(deltaLeft) < fabsf(deltaUp))
		{
			charPosition.x = (x - width / 2) - cWidth / 2;
		}
		if (fabsf(deltaDown) < fabsf(deltaLeft) && fabsf(deltaDown) < fabsf(deltaRight) && fabsf(deltaDown) < fabsf(deltaUp))
		{
			charPosition.y = (y + height / 2) + cHeight / 2;
		}
		if (fabsf(deltaUp) < fabsf(deltaLeft) && fabsf(deltaUp) < fabsf(deltaDown) && fabsf(deltaUp) < fabsf(deltaRight))
		{
			charPosition.y = (y - height / 2) - cHeight / 2;
		}
	}
	return charPosition;
}
