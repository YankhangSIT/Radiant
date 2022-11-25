//---------------------------------------------------------
// file:	movement.c
// author:	Koh Yan Khang
// email:	yankhang.k@digipen.edu
// brief:	Includes code for the movement mechanics (char and enemy) of the game, including collision tech between enemies, image rendering when character changes direction.
// 
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "math.h"
#include "stdio.h"

CP_Vector charMovement(CP_Vector charPosition, float charSpeed)
{
	float dtSpeed = charSpeed * CP_System_GetDt(); // CHARACTER SPEED IS 210 UNITS PER SECOND

	if (CP_Input_KeyDown(KEY_A))
	{
		charPosition.x -= dtSpeed;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		charPosition.x += dtSpeed;
	}
	if (CP_Input_KeyDown(KEY_W))
	{
		charPosition.y -= dtSpeed;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		charPosition.y += dtSpeed;
	}
	return charPosition;
}

CP_Image charImageMelee(CP_Image charImage, CP_Vector charPosition, int *characterFacing)
{
	if (CP_Input_GetMouseX() < charPosition.x)
	{
		charImage = CP_Image_Load("Assets/melee_char_facing_left.png");
		*characterFacing = 0;
	}
	else if (CP_Input_GetMouseX() > charPosition.x)
	{
		charImage = CP_Image_Load("Assets/melee_char_facing_right.png");
		*characterFacing = 1;
	}
	return charImage;
}

CP_Image charImageRanged(CP_Image charImage, CP_Vector charPosition)
{
	if (CP_Input_GetMouseX() < charPosition.x)
	{
		charImage = CP_Image_Load("Assets/ranged_char_facing_left.png");
	}
	else if (CP_Input_GetMouseX() > charPosition.x)
	{
		charImage = CP_Image_Load("Assets/ranged_char_facing_right.png");
	}
	return charImage;
}

CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition, float enemySpeed)
{
	float dtEnemySpeed = enemySpeed * CP_System_GetDt(); // ENEMY SPEED IS 100 UNITS PER SECOND

	CP_Vector directionNorm = CP_Vector_Normalize(CP_Vector_Subtract(charPosition, enemyPosition));

	enemyPosition = CP_Vector_Add(enemyPosition, CP_Vector_Scale(directionNorm, dtEnemySpeed));

	return enemyPosition;
}



