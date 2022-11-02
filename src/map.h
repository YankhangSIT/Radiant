#include <stdbool.h>
CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY);
CP_Vector checkObsCollision(CP_Vector charPosition, float cWidth, float cHeight, float x, float y, float width, float height);
typedef struct Circle
{
	float x;
	float y;
	float diameter;
	int clicked;
}Circle;
typedef struct Triangle
{
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float degrees;
}Triangle;
typedef struct Rect
{
	float x;
	float y;
	float width;
	float height;
}Rect;
typedef struct Obstruction
{
	Circle cir_block[3];
	Triangle tri_block[3];
	Rect rec_block[3];
}Obstruction;
Triangle SetTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float degree);
Circle SetCircle(float x, float y, float diameter, int clicked);
Rect SetRect_(float x, float y, float width, float height);
