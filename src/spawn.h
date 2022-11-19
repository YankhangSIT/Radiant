#pragma once

#include "cprocessing.h"
#include "math.h"
#include "stdio.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "global.h"

// enemy struct with all the properties needed for the enemy
struct Enemy {
	CP_Vector pos;
	CP_Image enemySprite;	
	float radius;
	float height;
	float width;
	float speed;
	int health;
	int id;
	float takeDamage;
};
//
//struct Boss
//{
//	CP_Vector pos;
//	CP_Image bossSprite;
//	float height;
//	float width;
//	float speed;
//	int health;
//	float takeDamage;
//};

// enemy struct with all the properties needed for the drop
struct Drop
{
	CP_Vector pos;
	CP_Image dropSprite;
	float width;
	float height;
	int itemId;
	int dropTrue;
};

// Button struct
struct Button
{
	CP_Vector pos;
	float width;
	float height;
};

// Bullet struct with the properties needed
struct Bullet
{
	CP_Vector shootPosition;
	CP_Vector shootPosition2;
	CP_Vector shootPosition3;
	CP_Vector bulletPos;
	CP_Image bulletSprite;
	CP_Vector acceleration;
	CP_Vector directionBullet;
	CP_Vector normalizedDirection;
	float bulletSpeed;
	float width;
	float height;
};

// spawn timer of enemies
float spawnTimer;
float startSpawnTimer;

int isCompleted;
int spawnIndex;

// Bullet Struct Contains all the properties of the bullet
struct Enemy enemies[SIZE];
struct Enemy enemy;

// declarations needed for the bullet 
struct Bullet bullet;
struct Bullet bulletArray[SIZE];

struct Bullet bossBullet;
struct Bullet bossBulletArray[SIZE];
struct Bullet bossBulletArray2[SIZE];
struct Bullet bossBulletArray3[SIZE];
struct Enemy boss;
float bossShootTimer;
float startBossShootTimer;
int bossShoot;
int bossBulletIndex;
int bossBulletIndex2;
int bossBulletIndex3;


int bulletSpawnIndex;
int firstShoot;
int canShoot;
float delayShootTime;
float delayShootStart;
CP_Vector spawnPosition;

// declarations needed for drops
struct Drop itemDrop[SIZE];
struct Drop healthDrop;
int dropIndex;
CP_Vector itemSpawn;
int firstDrop;
CP_Vector dropPositions;

float shieldDuration;
float unlimitedEnergyDuration;

// Image Sprites
CP_Image enemySprite1;
CP_Image enemySprite2;
CP_Image damagedSprite1;
CP_Image damagedSprite2;
CP_Image char_health; /// changed from dropHealthSprite
CP_Image char_energy; /// added
CP_Image dropShieldSprite;
CP_Image dropEnergySprite;
CP_Image bossSprite;
unsigned int randomId;

//min and sec counter
int min;
float sec;
// survive condition
int surviveMin;
// win condition boolean
int win;
//float spawnTimer = 0.f;
int lose;
float changeSpawnTimer;
float startSpawnChangeTimer;
int direction;
void clear(void);


//void spawnEnemies(struct Enemy* enemies, int spawnSize, CP_Vector* spawnPositions, int wWidth, int wHeight);

