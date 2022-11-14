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
int checkDamage(CP_Vector charPosition, float charWidth, float charHeight, CP_Vector enemyPosition, float enemyWidth, float enemyHeight)
{
	if (charPosition.x < enemyPosition.x + enemyWidth &&
		charPosition.x + charWidth > enemyPosition.x &&
		charPosition.y < enemyPosition.y + enemyHeight &&
		charHeight + enemyPosition.y > enemyPosition.y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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

		sword.x = charPosition.x - cWidth / 2;
	}
	if (charDirection == right)
	{
		sword.x = charPosition.x + cWidth / 2;
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