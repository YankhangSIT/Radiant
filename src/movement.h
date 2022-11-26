CP_Vector charMovement(CP_Vector charPosition, float charSpeed);
CP_Image charImageMelee(CP_Image charImage, CP_Vector charPosition, int *characterFacing);
CP_Image charImageRanged(CP_Image charImage, CP_Vector charPosition);
CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition, float enemySpeed);


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
	int points;
} character;
