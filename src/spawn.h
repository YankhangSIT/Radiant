#include "cprocessing.h"
#include "math.h"
#include "stdio.h"


struct Enemy {
	CP_Vector pos;
	CP_Color Color;
	CP_Image enemySprite;
	float radius;
	float height;
	float width;
	float Direction;
	float Speed;
	int isDead;

};



void spawnEnemies(struct Enemy* enemies, int spawnSize, CP_Vector* spawnPositions, int wWidth, int wHeight);

