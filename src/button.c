#define STRING_LENGTH (50)
#include "stdio.h"
#include "cprocessing.h"
#include "button.h"

char string[STRING_LENGTH];



void Button(char *string,float posX,float posY, float txtPosX, float txtPosY, int width, int height, int colorRed, int colorBlue, int colourGreen, int textRed, int textBlue, int textGreen,int alpha)
{
	//CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawRect(posX, posY, width, height);
	CP_Settings_Fill(CP_Color_Create(textRed, textBlue, textGreen, alpha));
	CP_Font_DrawText(string, txtPosX, txtPosY);
}