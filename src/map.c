#include <stdio.h>
#include "cprocessing.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "level1.h"
#include "map.h"

Triangle SetTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float degree)
{
	Triangle tri;
	tri.x1 = x1;
	tri.y1 = y1;
	tri.x2 = x2;
	tri.y2 = y2;
	tri.x3 = x3;
	tri.y3 = y3;
	tri.degrees = degree;
	return tri;
}
Circle SetCircle(float x, float y, float diameter, int clicked)
{
	Circle cir;
	cir.x = x;
	cir.y = y;
	cir.diameter = diameter;
	cir.clicked = clicked;
	return cir;
}
Rect SetRect_(float x, float y, float width, float height)
{
	Rect rec;
	rec.x = x;
	rec.y = y;
	rec.width = width;
	rec.height = height;
	return rec;
}
// typedef struct Resolution
//{
//	int width;
//	int height;
// }Resolution;
// static Resolution SetResolution(int width, int height) {
//	Resolution res;
//	res.width = width;
//	res.height = height;
//	return res;
// }Resolution windowResolution;

CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY)
{
	if (charPosition.x <= minX)
	{
		charPosition.x = minX;
	}
	else if (charPosition.x >= maxX)
	{
		charPosition.x = maxX;
	}
	if (charPosition.y <= minY)
	{
		charPosition.y = minY;
	}
	else if (charPosition.y >= maxY)
	{
		charPosition.y = maxY;
	}
	return charPosition;
}
CP_Vector checkObsCollision(CP_Vector charPosition, float cWidth, float cHeight, float x, float y, float width, float height)
{
	// float speed = 500.0;
	// float dtSpeed = speed * CP_System_GetDt();

	if (charPosition.x + cWidth / 2 >= x - width / 2 && charPosition.x - cWidth / 2 <= x + width / 2 && charPosition.y + cHeight / 2 >= y - height / 2 && charPosition.y - cHeight / 2 <= y + height / 2)
	{
		if (CP_Input_KeyDown(KEY_A) && fabsf(charPosition.x - (x - width / 2)) > fabsf(charPosition.x - (x + width / 2)))
		{
			charPosition.x = (x + width / 2) + cWidth / 2;
		}
		if (CP_Input_KeyDown(KEY_D) && fabsf(charPosition.x - (x - width / 2)) < fabsf(charPosition.x - (x + width / 2)))
		{
			charPosition.x = (x - width / 2) - cWidth / 2;
		}
		if (CP_Input_KeyDown(KEY_W) && fabsf(charPosition.y - (y - height / 2)) > fabsf(charPosition.y - (y + height / 2)))
		{
			charPosition.y = (y + height / 2) + cHeight / 2;
		}
		if (CP_Input_KeyDown(KEY_S) && fabsf(charPosition.y - (y - height)) < fabsf(charPosition.y - (y + height / 2)))
		{
			charPosition.y = (y - height / 2) - cHeight / 2;
		}
	}
	return charPosition;
}
