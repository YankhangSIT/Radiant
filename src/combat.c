#include "cprocessing.h"
#include "math.h"
#include "stdio.h"

int checkDamage(CP_Vector charPosition, float charWidth, float charHeight, CP_Vector enemyPosition, float enemyWidth, float enemyHeight)
{
	if (charPosition.x < enemyPosition.x + enemyWidth &&
		charPosition.x + charWidth > enemyPosition.x &&
		charPosition.y < enemyPosition.y + enemyHeight &&
		charHeight + enemyPosition.y > enemyPosition.y) {
		return 1;
	}
	else {
		return 0;
	}
}

int takeDamage(int charHealth) {
	return charHealth - 1;
}