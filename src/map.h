#include <stdbool.h>
#define MAX_Obs 102
CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY);
CP_Vector checkObsCollision(CP_Vector charPosition, float cWidth, float cHeight, float x, float y, float width, float height);
int checkProjectileMapCollision(CP_Vector bulletPosition, float minX, float maxX, float minY, float maxY);
bool checkProjectileObsCollision(CP_Vector bulletPosition, float bulletWidth, float bulletHeight, float x, float y, float width, float height);
typedef struct Rect
{
	float x;
	float y;
	float width;
	float height;
	CP_Image spriteImage;
} Rect;
typedef struct Obstruction
{
	Rect rec_block[MAX_Obs];
} Obstruction;
Rect SetRect_(float x, float y, float width, float height);
const int obstructionCount;
