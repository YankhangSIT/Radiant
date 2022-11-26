//---------------------------------------------------------
// file:	utils.c
// author:	Koh Yan Khang
// email:	yankhang.k@digipen.edu
// brief:	Includes code for the button mechanics to check area clicked in the game.
// 
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "math.h"
#include "stdio.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float minX = area_center_x - area_width / 2;
	float maxX = area_center_x + area_width / 2;

	float minY = area_center_y - area_height / 2;
	float maxY = area_center_y + area_height / 2;

	if ((minX <= click_x && click_x <= maxX) && (minY <= click_y && click_y <= maxY))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	CP_Vector circleCenter = CP_Vector_Set(circle_center_x, circle_center_y);
	CP_Vector clickPos = CP_Vector_Set(click_x, click_y);
	float radius = diameter / 2;
	float dist = CP_Vector_Distance(circleCenter, clickPos);

	if (dist <= radius)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

CP_Vector AngleToVector(float radian_angle)
{
	float xValue = (float) cos(radian_angle);
	float yValue = (float) sin(radian_angle);
	CP_Vector ret = CP_Vector_Set(xValue, yValue);
	return ret;
}

