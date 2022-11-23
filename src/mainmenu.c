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
#include "sound.h"
#include "credits.h"

int panelDisplay = 0;
float elapsedTime;
int startCount;
float nextState;
int exitCount;
float exitSec;
float TimeElapsed;
CP_Font Alclonia;
CP_Image main_menu;
float wWidth;
float wHeight;
int isPaused;
void Main_Menu_Init()
{

	// clear();
	// CP_System_Fullscreen();
	CP_System_SetWindowSize(1920, 1080);
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
	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();
	buttonClickSound = CP_Sound_Load("Assets/buttonClick.wav");
	backgroundMusic = CP_Sound_Load("Assets/background.wav");
	nextState = 0.f;
	startCount = FALSE;
	exitCount = FALSE;
	exitSec = 0.f;
	isPaused = FALSE;
}

void Main_Menu_Update()
{
	if (!isPaused)
	{
		// delay call next game state by 0.1 sec to register the button sound
		elapsedTime = CP_System_GetDt();
		if (startCount)
			nextState += elapsedTime;
		if (nextState > 0.2)
			CP_Engine_SetNextGameState(character_Select_Init, character_Select_Update, character_Select_Exit);
		if (exitCount)
			exitSec += elapsedTime;
		if (exitSec > 0.2)
			CP_Engine_Terminate();
		// Set background music
		CP_Sound_PlayAdvanced(backgroundMusic, 0.1f, 0.5f, TRUE, CP_SOUND_GROUP_1);

		// Set background
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Image_Draw(main_menu, wWidth / 2.0f, wHeight / 2.0f, (float)CP_Image_GetWidth(main_menu), (float)CP_Image_GetHeight(main_menu), 255);

		// Set font
		CP_Font_Set(Alclonia);

		CP_Settings_RectMode(CP_POSITION_CENTER);

		// Play Button
		Button("Play", wWidth / 2.f, wHeight / 2.f - 100, wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		// volume ettings Button
		Button("Sound", wWidth / 2.0f, wHeight / 2.0f + 50, wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		// Exit Button
		Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 200, wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		// Credits Button
		Button("Credits", wWidth / 2.0f + 700, wHeight / 2.0f + 450, wWidth / 2.0f + 700, wHeight / 2.0f + 450, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		// If click "Play" Button
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Play", wWidth / 2.f, wHeight / 2.f - 100, wWidth / 2.0f, wHeight / 2.0f - 96, 220, 100, 0, 255, 0, 0, 0, 0, 255);

			if (CP_Input_MouseClicked())
			{

				if (IsAreaClicked(wWidth / 2.0f - 30, wHeight / 2.0f - 130, 210, 110, mouseClickPos.x, mouseClickPos.y) == 1)
				{
					if (!nextState)
						startCount = TRUE;
					panelDisplay = 1;
					CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				}
			}
		}

		// else if click "Exit" button
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 200, wWidth / 2.0f, wHeight / 2.0f + 196, 220, 100, 0, 255, 0, 0, 0, 0, 255);
			if (CP_Input_MouseClicked())
			{
				if (!exitSec)
					exitCount = TRUE;
				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			}
		}
		// volume settings
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			if (CP_Input_MouseClicked())
			{
				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				isPaused = !isPaused;
			}
		}
		else if (IsAreaClicked(wWidth / 2.0f + 700, wHeight / 2.0f + 450, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Credits", wWidth / 2.0f + 700, wHeight / 2.0f + 450, wWidth / 2.0f + 696, wHeight / 2.0f + 450, 220, 100, 0, 255, 0, 0, 0, 0, 255);
			if (CP_Input_MouseClicked())
			{
				CP_Engine_SetNextGameState(Credits_Init, Credits_Update, Credits_Exit);
			}
		}
	}

	if (isPaused)
	{
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 500, 1000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Volume settings", wWidth / 2.0f, wHeight / 2.0f - 300);

		CP_Font_DrawText("Background music", wWidth / 2.0f, wHeight / 2.0f - 600);

		TriButton("", wWidth / 2.0f - 200, wHeight / 2.0f - 200, wWidth / 2.0f, wHeight / 2.0f, wWidth / 2.0f + 200, wHeight / 2.0f + 200, 360, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		Button("Back", wWidth / 2.0f, wHeight / 2.0f + 200, wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 200, 200, 180, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			if (CP_Input_MouseClicked())
			{
				if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 200, 200, 180, mouseClickPos.x, mouseClickPos.y) == 1)
				{
					isPaused = !isPaused;
				}
			}
		}
	}
}

void Main_Menu_Exit()
{
	CP_Image_Free(&main_menu);
	CP_Sound_Free(&buttonClickSound);
	CP_Sound_Free(&backgroundMusic);
}
