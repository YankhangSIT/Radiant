#include "cprocessing.h"
#include "math.h"
#include "stdio.h"


struct Enemy {
	CP_Vector pos;
	CP_Color Color;
	CP_Image enemySprite;
	float radius;
	float Height;
	float Width;
	float Direction;
	float Speed;

};



void spawnEnemies(struct Enemy *enemies, int size, CP_Vector spawnPositions[]);

