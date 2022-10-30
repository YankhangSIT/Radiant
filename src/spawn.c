#include "spawn.h"
#include "cprocessing.h"
#include <stdlib.h>

float randFloat(float low, float high)
{
	return ((float)rand() / (float)RAND_MAX) * (high - low) + low;
}


void spawnEnemies( struct Enemy *enemies, int spawnSize, CP_Vector *spawnPositions, int wWidth, int wHeight)
{
	for (int i = 0; i < spawnSize; ++i)
	{
		// set spawn positions for the 5 enemies in spawnPositions array index 0
		//which represents the top row enemies spawn positions
		spawnPositions[i + 0 * spawnSize] = CP_Vector_Set(randFloat(wWidth / 8, wWidth), wHeight / 7);
		enemies[i].pos.x = spawnPositions[i + 0 * spawnSize].x;
		enemies[i].pos.y = spawnPositions[i + 0 * spawnSize].y;
	}

	for (int i = 0; i < spawnSize; ++i)
	{
		// set spawn positions for the 5 enemies in spawnPositions array index 1
		//which represents the left column enemies spawn position
		spawnPositions[i + 1 * spawnSize] = CP_Vector_Set(wWidth / 8, randFloat(wHeight, wHeight / 7));
		enemies[5 + i].pos.x = spawnPositions[i + 1 * spawnSize].x;
		enemies[5 + i].pos.y = spawnPositions[i + 1 * spawnSize].y;
	}

	for (int i = 0; i < spawnSize; ++i)
	{
		// set spawn positions for the 5 enemies in spawnPositions array index 1
		//which represents the right column enemies spawn position
		spawnPositions[i + 2* spawnSize] = CP_Vector_Set(wWidth - 50, randFloat(wHeight, wHeight / 7));
		enemies[10 + i].pos.x = spawnPositions[i + 2 * spawnSize].x;
		enemies[10 + i].pos.y = spawnPositions[i + 2 * spawnSize].y;

	}
}
