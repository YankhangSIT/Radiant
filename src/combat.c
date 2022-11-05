#include "cprocessing.h"
#include "math.h"
#include "stdio.h"
#include "map.h"
#include "combat.h"

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

int energyDeplete(int charEnergy) {
	return charEnergy - 1;
}


int takeDamage(int charHealth) {
	return charHealth - 1;
}
Sword SetSword(float x1, float y1, float x2, float y2, float x3, float y3, float degree) {
	Sword tri;
	tri.x1 = x1;
	tri.y1 = y1;
	tri.x2 = x2;
	tri.y2 = y2;
	tri.x3 = x3;
	tri.y3 = y3;
	tri.degrees = degree;
	return tri;
}
Sword UpdateSwordSwing(Sword tri, CP_Vector charPosition, float cWidth, float cHeight ) {
	tri.x1 = charPosition.x + cWidth /2;
	tri.y1 = charPosition.y + cHeight /2;
	tri.x2 = tri.x1 + 80.f;
	tri.y2 = tri.y1 - 80.f;
	tri.x3 = tri.x1 + 80.f;
	tri.y3 = tri.y1 + 80.f;
	return tri;
}