#define STRING_LENGTH (50)
#include "stdio.h"
#include "cprocessing.h"
#include "button.h"

char string[STRING_LENGTH];

void Button(char *string, float posX, float posY, float txtPosX, float txtPosY, int width, int height, int colorRed, int colorBlue, int colourGreen, int textRed, int textBlue, int textGreen, int alpha)
{
	// CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawRect((float)posX, (float)posY, (float)width, (float)height);
	CP_Settings_Fill(CP_Color_Create(textRed, textBlue, textGreen, alpha));
	CP_Font_DrawText(string, txtPosX, txtPosY);
}
void TriButton(float posX1, float posY1, float posX2, float posY2, float posX3, float posY3, float degree, float txtPosX, float txtPosY, int colorRed, int colorBlue, int colourGreen, int textRed, int textBlue, int textGreen, int alpha)
{
	// CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawTriangleAdvanced(posX1, posY1, posX2, posY2, posX3, posY3, degree);
	CP_Settings_Fill(CP_Color_Create(textRed, textBlue, textGreen, alpha));
	CP_Font_DrawText(string, txtPosX, txtPosY);
}
void sliderBox(float posX, float posY, int width, int height, int colorRed, int colorBlue, int colourGreen, int alpha)
{
	// CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawRect((float)posX, (float)posY, (float)width, (float)height);
}
void sliderBar(float posX, float posY, int width, int height, int colorRed, int colorBlue, int colourGreen, int alpha)
{
	// CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(colorRed, colorBlue, colourGreen, alpha));
	CP_Graphics_DrawRect((float)posX, (float)posY, (float)width, (float)height);
}