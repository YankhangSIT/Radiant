//---------------------------------------------------------
// file:	spawn.c
// author:	Lua Wei Xiang Darren
// email:	 weixiangdarren.lua@digipen.edu
// brief:	Includes code for the first level of the game, with only one type of monster
//
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "spawn.h"
#include "cprocessing.h"
#include <stdlib.h>
#include "global.h"
/*Darren Lua Source File*/

struct Bullet bullet;
struct Bullet bulletArray[SIZE];

int bulletSpawnIndex = 0;
int firstShoot = 0;
int canShoot = 0;
float delayShootTime = 0;
float delayShootStart = 0;
CP_Vector spawnPosition;
struct Enemy enemies[SIZE];
struct Enemy enemy;
struct Drop itemDrop[SIZE];
struct Drop healthDrop;
int dropIndex = 0;
CP_Vector itemSpawn;
int firstDrop = 0;
CP_Image enemySprite1;
CP_Image enemySprite2;
int min = 0;
float sec = 0;
int surviveMin = 1;
// win condition boolean
int win = 0;
float spawnTimer = 0.f;
int lose = 0;


/*To clear the array*/
void clear()
{
	memset(enemies, 0, sizeof(enemies));
	memset(bulletArray, 0 ,sizeof(bulletArray));
	memset(itemDrop, 0, sizeof(itemDrop));
	memset(bossBulletArray, 0, sizeof(bossBulletArray));
	memset(bossBulletArray2, 0, sizeof(bossBulletArray2));
	memset(bossBulletArray3, 0, sizeof(bossBulletArray3));
}

void spawnItem(struct Enemy* enemies, struct Drop* itemDrop , CP_Image dropShieldSprite, CP_Image dropEnergySprite, int* dropIndex, int enemyIndex,int lowRange, int highRange)
{
	// randomize spawn rate from l to 4 meaning 1 in 4 chance of spawn
	unsigned int randomRate = CP_Random_RangeInt(lowRange, highRange);
	// randomly set drop id between 1 or 2
	unsigned int dropId = CP_Random_RangeInt(1, 2);
	//set drop Id and drop boolean to true
	itemDrop[*dropIndex].itemId = dropId;
	itemDrop[*dropIndex].dropTrue = 1;
	if (randomRate == 2)
	{
		// check item drop's id by the spawn index of the drop
		if (itemDrop[*dropIndex].itemId == 1)
		{
			// if item's id is 1 set the item's dropSprite to the dropHealthSprite
			itemDrop[*dropIndex].dropSprite = dropShieldSprite;
			// set the width and height to the respective sprite
			itemDrop[*dropIndex].width = (float)CP_Image_GetWidth(itemDrop[(int)*dropIndex].dropSprite);
			itemDrop[*dropIndex].height = (float)CP_Image_GetHeight(itemDrop[(int)*dropIndex].dropSprite);
		}
		else if (itemDrop[*dropIndex].itemId == 2)
		{
			// if item's id is 2 set the item's dropSprite to the dropEnergySprite
			itemDrop[*dropIndex].dropSprite = dropEnergySprite;
			// set the width and height to the respective sprite
			itemDrop[*dropIndex].width = (float)CP_Image_GetWidth(itemDrop[(int)*dropIndex].dropSprite);
			itemDrop[*dropIndex].height = (float)CP_Image_GetHeight(itemDrop[(int)*dropIndex].dropSprite);
		}
		// set item with the drop index to the enemy coordinate
		itemDrop[*dropIndex].pos.x = enemies[enemyIndex].pos.x;
		itemDrop[*dropIndex].pos.y = enemies[enemyIndex].pos.y;
		/*Increment drop index*/
		++*dropIndex;
	}
}