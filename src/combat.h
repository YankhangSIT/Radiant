typedef struct Sword
{
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float degrees;
}Sword;
int checkDamage(CP_Vector charPosition, float charWidth, float charHeight, CP_Vector enemyPosition, float enemyWidth, float enemyHeight);
//CP_Vector checkEnemyCollision(CP_Vector enemy1Position, CP_Vector enemy2Position, float buffer);
int takeDamage(int charHealth);
Sword SetSword(float x1, float y1, float x2, float y2, float x3, float y3, float degree);
Sword UpdateSwordSwing(Sword tri, CP_Vector charPosition, float cWidth, float cHeight);
