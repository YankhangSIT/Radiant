#pragma once

#include "cprocessing.h"
#include "math.h"
#include "stdio.h"
#include "level1.h"
#include "level2.h"

struct Enemy {
	CP_Vector pos;
	CP_Color Color;
	CP_Image enemySprite;
	float radius;
	float height;
	float width;
	float Direction;
	float speed;
	int isDead;
	int health;
	int id;


};

struct Drop
{
	CP_Vector pos;
	CP_Image dropSprite;
	float width;
	float height;
	int itemId;
	float dropDespawnTimer;
	float dropDespawnStartTimer;
	int dropTrue;
};

struct Button
{
	CP_Vector pos;
	float width;
	float height;
};

struct Bullet
{

	CP_Vector shootPosition;
	CP_Vector bulletPos;
	CP_Image bulletSprite;
	CP_Vector acceleration;
	CP_Vector directionBullet;
	CP_Vector normalizedDirection;
	float bulletSpeed;
	float width;
	float height;
	float direction;

	int isAlive;
};


float spawnTimer;
float startSpawnTimer;

int isCompleted;
int spawnIndex;

// Bullet Struct Contains all the properties of the bullet
struct Enemy enemies[SIZE];
struct Enemy enemy;

struct Bullet bullet;
struct Bullet bulletArray[SIZE];

int bulletSpawnIndex;
int firstShoot;
int canShoot;
float delayShootTime;
float delayShootStart;
CP_Vector spawnPosition;

struct Drop itemDrop[SIZE];
struct Drop healthDrop;
int dropIndex;
CP_Vector itemSpawn;
int firstDrop;
CP_Image enemySprite1;
CP_Image enemySprite2;
unsigned int randomId;
CP_Image dropHealthSprite;
CP_Image dropEnergySprite;
CP_Vector dropPositions;

int min;
float sec;
// survive condition
int surviveMin;
// win condition boolean
int win;
//float spawnTimer = 0.f;
int lose;

void clear(void);


//void spawnEnemies(struct Enemy* enemies, int spawnSize, CP_Vector* spawnPositions, int wWidth, int wHeight);

