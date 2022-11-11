#include "spawn.h"
#include "cprocessing.h"
#include <stdlib.h>
#include "global.h"
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
unsigned int randomId;

int min = 0;
float sec = 0;
int surviveMin = 1;
// win condition boolean
int win = 0;
//float spawnTimer = 0.f;
int lose;
struct Button nextLevel;
struct Button restart;
struct Button menu;
struct Button exitLevel;

void clear()
{
	memset(enemies, 0, sizeof(enemies));
}