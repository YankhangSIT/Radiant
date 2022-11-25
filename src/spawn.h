#pragma once
/*Darren Lua Spawn Header*/
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
	float height;
	float width;
	float speed;
	int health;
	int id;
	float takeDamage;
	int maxHealth;
};

// Drop struct with all the variables needed for the drop
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
struct ButtonStruct
{
	CP_Vector pos;
	float width;
	float height;
};

struct ButtonStruct nextLevel;
struct ButtonStruct resumeButton;
struct ButtonStruct restartButton;
struct ButtonStruct menuButton;
struct ButtonStruct exitLevelButton;


// Bullet struct with the variables needed
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
	int isSpawn;
	float bulletSpeed;
	float startBulletSpeed;
	float width;
	float height;
};

// spawn timer of enemies
float spawnTimer;
float startSpawnTimer;

int isCompleted;
int spawnIndex;

//Declarations for enemies
struct Enemy enemies[SIZE];
struct Enemy enemy;

// declarations needed for the bullets
struct Bullet bullet;
struct Bullet bulletArray[SIZE];

//Declarations needed for the boss bullets
struct Bullet bossBullet;
struct Bullet bossBulletArray[SIZE];
struct Bullet bossBulletArray2[SIZE];
struct Bullet bossBulletArray3[SIZE];
struct Enemy boss;
//Bullet Attack Speed Timer
float bossShootTimer;
float startBossShootTimer;

float bossShootTimer2;
float startBossShootTimer2;

float bossShootTimer3;
float startBossShootTimer3;

/*Boss change attack Timer and for Boss attack rotation*/
float changeAttackTimer;
float startChangeTimer;
int attackMode;
float directionAngle;
float rotationSpeed;
int bossChangeAttack;

/*Boss Bullet Indexes for the three array*/
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
CP_Vector dropPositions;

float shieldedDuration;
float unlimitedEnergyDuration;

// Image Sprites
CP_Image enemySprite1;
CP_Image enemySprite2;
CP_Image damagedSprite1;
CP_Image damagedSprite2;
CP_Image bossBulletSprite1;
CP_Image bossBulletSprite2;


CP_Image char_health; /// changed from dropHealthSprite
CP_Image char_energy; /// added
CP_Image dropShieldSprite;
CP_Image dropEnergySprite;
CP_Image shielded;
CP_Image unlimitedEnergy;
CP_Image bossSprite;

/*Enemy ID*/
unsigned int randomId;

//min and sec counter
int min;
float sec;
// survive condition
int surviveMin;
// win condition boolean
int win;
int lose;
int previousLevelPoints;

/*Declaration of change enemy spawn timer with the different direction/spawn position as int value*/
float changeSpawnTimer;
float startSpawnChangeTimer;
int direction;

float pauseElapsedTime;

/*Boss Health Bar*/
float hpBarCurrLengthX;
float hpbarOriginalX;
float bossHealthScale;

void clear(void);
void spawnItem(struct Enemy* enemies, struct Drop* itemDrop, CP_Image dropShieldSprite, CP_Image dropEnergySprite, int* dropIndex, int enemyIndex,int lowRange,int highLimit);



