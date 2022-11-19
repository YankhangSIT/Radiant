CP_Vector charMovement(CP_Vector charPosition, float charSpeed);
CP_Image charImageMelee(CP_Image charImage, CP_Vector charPosition, int *characterFacing);
CP_Image charImageRanged(CP_Image charImage, CP_Vector charPosition);
CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition, float enemySpeed);
float toDisplace(CP_Vector enemy1Pos, CP_Vector enemy2Pos, float radius);

struct Character
{
	CP_Image playerSprite;
	CP_Vector Pos;
	float height;
	float width;
	float speed;
	int playerType;
	int health;
	int energy;
	int invulState;
	int transparency;
	int shieldedState;
	int unlimitedEnergyState;
} character;
// CP_Vector checkEnemyCollision(CP_Vector enemy1Position, CP_Vector enemy2Position, float buffer);