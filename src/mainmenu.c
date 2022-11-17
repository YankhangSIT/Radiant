/*!
@file mainmenu.c
@author Koh Yan Khang (yankhang.k)
@course csd1401f22
@section b
@CarSelectGame
@date 28/09/2022
*/
/*______________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "stdio.h"
#include "splashScreen.h"
#include "characterSelect.h"
#include "win.h"
#include "button.h"
#include "gameOverpage.h"

int panelDisplay = 0;

float TimeElapsed;
CP_Font Alclonia;
CP_Image main_menu;
float wWidth;
float wHeight;
void Main_Menu_Init()
{

	CP_System_Fullscreen();
	CP_Settings_RectMode(CP_POSITION_CENTER);
	Alclonia = CP_Font_Load("Assets/Alclonia_Regular.ttf");
	main_menu = CP_Image_Load("Assets/Main_menu.jpg");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	/*CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP)*/;

	// align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);
	wWidth = (float) CP_System_GetWindowWidth();
	wHeight = (float) CP_System_GetWindowHeight();
}

void Main_Menu_Update()
{
	// Set window width and height to variables

	// Set background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(main_menu, wWidth / 2.0f, wHeight / 2.0f, (float) CP_Image_GetWidth(main_menu), (float) CP_Image_GetHeight(main_menu), 255);

	// Set font
	CP_Font_Set(Alclonia);

	CP_Settings_RectMode(CP_POSITION_CENTER);

	// Play Button
	Button("Play", wWidth / 2.f, wHeight / 2.f - 100, wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);

	// Settings Button
	Button("Settings", wWidth / 2.0f, wHeight / 2.0f + 50, wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);

	// Exit Button
	Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 200, wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);

	// If click "Play" Button
	if (CP_Input_MouseClicked())
	{
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{

			panelDisplay = 1;
			CP_Engine_SetNextGameState(character_Select_Init, character_Select_Update, character_Select_Exit);
		}
		// else if click "Exit" button
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_Terminate();
		}

		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			// CP_Engine_SetNextGameState(Settings_Init, Settings_Update, Settings_Exit);
		}
	}
}

void Main_Menu_Exit()
{
	CP_Image_Free(&main_menu);
}
