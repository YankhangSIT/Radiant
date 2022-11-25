//---------------------------------------------------------
// file:	spawn.c
// author:	Lua Wei Xiang Darren, Jing Song
// email:	 weixiangdarren.lua@digipen.edu , jingsong.wei@digipen.edu
// brief:	Contains the functions for buttons and slider
//
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------


#define STRING_LENGTH (50)
#include "stdio.h"
#include "cprocessing.h"
#include "button.h"

char string[STRING_LENGTH];
/*Darren Lua Button Code*/
void Button(char *string, float posX, float posY, float txtPosX, float txtPosY, float width, float height, int colorRed, int colorBlue, int colourGreen, int textRed, int textBlue, int textGreen, int alpha)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawRect(posX, posY, width, height);
	CP_Settings_Fill(CP_Color_Create(textRed, textBlue, textGreen, alpha));
	CP_Font_DrawText(string, txtPosX, txtPosY);
}

void TriButton(float posX1, float posY1, float posX2, float posY2, float posX3, float posY3, float degree, float txtPosX, float txtPosY, int colorRed, int colorBlue, int colourGreen, int textRed, int textBlue, int textGreen, int alpha)
{

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawTriangleAdvanced(posX1, posY1, posX2, posY2, posX3, posY3, degree);
	CP_Settings_Fill(CP_Color_Create(textRed, textBlue, textGreen, alpha));
	CP_Font_DrawText(string, txtPosX, txtPosY);
}
void sliderBox(float posX, float posY, int width, int height, int colorRed, int colorBlue, int colourGreen, int alpha)
{

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawRect((float)posX, (float)posY, (float)width, (float)height);
}
void sliderBar(float posX, float posY, int width, int height, int colorRed, int colorBlue, int colourGreen, int alpha)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawRect((float)posX, (float)posY, (float)width, (float)height);
}