#include "cprocessing.h"
#include "math.h"
#include "stdio.h"
#include "map.h"
#include "combat.h"
#include <stdbool.h>
enum direction
{
	left,
	right
};
int charDirection = left;

int checkDamage(CP_Vector charPosition, float charWidth, float charHeight, CP_Vector enemyPosition, float radius)
{
	float testX = enemyPosition.x;
	float testY = enemyPosition.y;

	float rx = charPosition.x - charWidth / 2; // start from left of rect
	float ry = charPosition.y - charHeight / 2; // start from top of rect

	// check which edge of rect is closest to circle?
	if (enemyPosition.x < rx) testX = rx;      // test left edge
	else if (enemyPosition.x > rx + charWidth) testX = rx + charWidth;   // right edge
	if (enemyPosition.y < ry) testY = ry;      // top edge
	else if (enemyPosition.y > ry + charHeight) testY = ry + charHeight;   // bottom edge

	// get distance from closest edges
	float distX = enemyPosition.x - testX;
	float distY = enemyPosition.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision detected
	if (distance <= radius) {
		return 1;
	}
	return 0;
}

int energyDeplete(int charEnergy)
{
	return charEnergy - 1;
}

int takeDamage(int charHealth)
{
	return charHealth - 1;
}
Sword SetSword(float x, float y, float width, float height)
{
	Sword sword;
	sword.x = x;
	sword.y = y;
	sword.width = width;
	sword.height = height;
	return sword;
}
Sword UpdateSwordSwing(Sword sword, CP_Vector charPosition, float cWidth, float cHeight)
{
	if (CP_Input_GetMouseX() > charPosition.x)
	{
		charDirection = right;
	}
	else if (CP_Input_GetMouseX() < charPosition.x)
	{
		charDirection = left;
	}

	if (charDirection == left)
	{

		sword.x = charPosition.x - (cWidth * 3 / 2);
	}
	if (charDirection == right)
	{
		sword.x = charPosition.x + (cWidth * 3 / 2);
	}
	sword.y = charPosition.y;

	return sword;
}
bool swordSwingEnemey(Sword sword, CP_Vector enemyPosition, float enemyRaduis)
{

	if (enemyPosition.x + enemyRaduis > sword.x - sword.width / 2 && enemyPosition.x - enemyRaduis < sword.x + sword.width / 2 && enemyPosition.y + enemyRaduis > sword.y - sword.height && enemyPosition.y - enemyRaduis < sword.y + sword.height)
	{
		return true;
	}

	return false;
}