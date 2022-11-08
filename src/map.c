#include <stdio.h>
#include "cprocessing.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "level1.h"
#include "map.h"

Rect SetRect_(float x, float y, float width, float height)
{
	Rect rec;
	rec.x = x;
	rec.y = y;
	rec.width = width;
	rec.height = height;
	return rec;
}

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

int checkProjectileMapCollision(CP_Vector bulletPosition, float minX, float maxX, float minY, float maxY)
{
	if (bulletPosition.x <= minX)
	{
		return 1;
	}
	else if (bulletPosition.x >= maxX)
	{
		return 1;
	}
	else if (bulletPosition.y <= minY)
	{
		return 1;
	}
	else if (bulletPosition.y >= maxY)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

CP_Vector checkObsCollision(CP_Vector charPosition, float cWidth, float cHeight, float x, float y, float width, float height)
{
	if (charPosition.x + cWidth / 2 > x - width / 2 && charPosition.x - cWidth / 2 < x + width / 2 && charPosition.y + cHeight / 2 > y - height / 2 && charPosition.y - cHeight / 2 < y + height / 2)
	{
		float collideWidth = 0.0f;
		float collideHeight = 0.0f;
		if (fabsf(charPosition.x - (x - width / 2)) > fabsf(charPosition.x - (x + width / 2)))
		{
			collideWidth = (charPosition.x + cWidth / 2) - (x - width / 2);
			printf("collide from right collided width is %f\n", collideWidth);
		}
		if (fabsf(charPosition.x - (x - width / 2)) < fabsf(charPosition.x - (x + width / 2)))
		{
			collideWidth = (x + width / 2) - (charPosition.x - cWidth / 2);
			printf("collide from left collided width is %f\n", collideWidth);
		}
		if (fabsf(charPosition.y - (y - height / 2)) > fabsf(charPosition.y - (y + height / 2)))
		{
			collideHeight = (charPosition.y + cHeight / 2) - (y - height / 2);
			printf("collide from bottom collided height is %f\n", collideHeight);
		}
		if (fabsf(charPosition.y - (y - height / 2)) < fabsf(charPosition.y - (y + height / 2)))
		{
			collideHeight = (y + height / 2) - (charPosition.y - cHeight / 2);
			printf("collide from top collided height is %f\n", collideHeight);
		}

		if (fabsf(charPosition.x - (x - width / 2)) > fabsf(charPosition.x - (x + width / 2)) && collideWidth > collideHeight)
		{
			// charPosition.x += (width + cWidth) - collideWidth;
			charPosition.x = (x + width / 2) + cWidth / 2;
		}
		if (fabsf(charPosition.x - (x - width / 2)) < fabsf(charPosition.x - (x + width / 2)) && collideWidth > collideHeight)
		{
			charPosition.x = (x - width / 2) - cWidth / 2;
		}
		if (fabsf(charPosition.y - (y - height / 2)) > fabsf(charPosition.y - (y + height / 2)) && collideHeight > collideWidth)
		{
			charPosition.y = (y + height / 2) + cHeight / 2;
		}
		if (fabsf(charPosition.y - (y - height / 2)) < fabsf(charPosition.y - (y + height / 2)) && collideHeight > collideWidth)
		{
			charPosition.y = (y - height / 2) - cHeight / 2;
		}
	}
	return charPosition;
}
