#include <stdbool.h>
typedef struct Sword
{
	float x;
	float y;
	float width;
	float height;
} Sword;
int checkDamage(CP_Vector charPosition, float charWidth, float charHeight, CP_Vector enemyPosition, float enemyWidth, float enemyHeight);
// CP_Vector checkEnemyCollision(CP_Vector enemy1Position, CP_Vector enemy2Position, float buffer);
int takeDamage(int charHealth);
Sword SetSword(float x, float y, float width, float height);
Sword UpdateSwordSwing(Sword sword, CP_Vector charPosition, float cWidth, float cHeight);
bool swordSwingEnemey(Sword sword, CP_Vector enemyPosition, float enemyRaduis);
