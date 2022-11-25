//---------------------------------------------------------
// file:	mainmenu.c
// author:	Lua Wei Xiang Darren, Jing Song , Seah Sheng Rong Donovan
// email:	weixiangdarren.lua@digipen.edu, jingsong.wei@digipen.edu, s.seah@digipen.edu
// brief:	Contains the code for main menu buttons such as Start Game, Options, Credits and Quit Game
//			the options code contains code for the sound adjustment slider
//
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

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
int startCount;
float TimeElapsed;
CP_Font Alclonia;
CP_Image main_menu;
float wWidth;
float wHeight;
int isPaused;
float mouseX1;
float mouseX2;
float sliderBoxX;
int playBackgroundMusic = 1;
void Main_Menu_Init()
{

	// clear();
	// CP_System_SetWindowSize(1920, 1080);
	CP_System_FullscreenAdvanced(1920, 1080);
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
	backgroundMusic = CP_Sound_Load("Assets/background.mp3");
	nextState = 0.f;
	startCount = FALSE;
	exitState = FALSE;
	creditState = FALSE;
	isPaused = FALSE;
	if (playBackgroundMusic)
	{
		CP_Sound_PlayAdvanced(backgroundMusic, 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_1);
		playBackgroundMusic = 0;
		*&backgroundVolume = 0.2f;
	}
	else
		CP_Sound_ResumeGroup(CP_SOUND_GROUP_1);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_1, *&backgroundVolume);
	mouseX1 = ((wWidth / 2 - 200) + CP_Sound_GetGroupVolume(CP_SOUND_GROUP_1) * 400);
	mouseX2 = ((wWidth / 2 - 200) + CP_Sound_GetGroupVolume(CP_SOUND_GROUP_0) * 400);
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
		{
			if (exitState)
				CP_Engine_Terminate();
			else if (creditState)
				CP_Engine_SetNextGameState(Credits_Init, Credits_Update, Credits_Exit);
			else
				CP_Engine_SetNextGameState(character_Select_Init, character_Select_Update, character_Select_Exit);
		}

		// Set background music
		// CP_Sound_PlayAdvanced(backgroundMusic, 0.5f, 1.0f, TRUE, CP_SOUND_GROUP_1);
		// Set background
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Image_Draw(main_menu, wWidth / 2.0f, wHeight / 2.0f, (float)CP_Image_GetWidth(main_menu), (float)CP_Image_GetHeight(main_menu), 255);

		// Set font
		CP_Font_Set(Alclonia);

		CP_Settings_RectMode(CP_POSITION_CENTER);

		// Play Button
		Button("Start Game", wWidth / 2.f, wHeight / 2.f - 100, wWidth / 2.0f, wHeight / 2.0f - 100, 220, 80, 0, 255, 0, 0, 0, 0, 255);

		// volume ettings Button
		Button("Options", wWidth / 2.0f, wHeight / 2.0f + 50, wWidth / 2.0f, wHeight / 2.0f + 50, 220, 80, 0, 255, 0, 0, 0, 0, 255);

		// Exit Button
		Button("Quit Game", wWidth / 2.0f, wHeight / 2.0f + 200, wWidth / 2.0f, wHeight / 2.0f + 200, 220, 80, 0, 255, 0, 0, 0, 0, 255);

		// Credits Button
		Button("Credits", wWidth / 2.0f + 700, wHeight / 2.0f + 450, wWidth / 2.0f + 700, wHeight / 2.0f + 450, 220, 80, 0, 255, 0, 0, 0, 0, 255);

		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		// If click "Play" Button
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Start Game", wWidth / 2.f, wHeight / 2.f - 100, wWidth / 2.0f, wHeight / 2.0f - 96, 260, 100, 0, 255, 0, 0, 0, 0, 255);

			if (CP_Input_MouseClicked())
			{

				if (IsAreaClicked(wWidth / 2.0f - 30, wHeight / 2.0f - 130, 210, 110, mouseClickPos.x, mouseClickPos.y) == 1)
				{

					panelDisplay = 1;
					CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					if (!nextState)
						startCount = TRUE;
				}
			}
		}

		// else if click "Exit" button
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Quit Game", wWidth / 2.0f, wHeight / 2.0f + 200, wWidth / 2.0f, wHeight / 2.0f + 196, 260, 100, 0, 255, 0, 0, 0, 0, 255);
			if (CP_Input_MouseClicked())
			{

				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				if (!nextState)
				{
					startCount = TRUE;
					exitState = TRUE;
				}
			}
		}
		// volume settings
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Options", wWidth / 2.0f, wHeight / 2.0f + 50, wWidth / 2.0f, wHeight / 2.0f + 46, 260, 100, 0, 255, 0, 0, 0, 0, 255);
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
				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				if (!nextState)
				{
					startCount = TRUE;
					creditState = TRUE;
				}
			}
		}
	}

	if (isPaused)
	{
		// Volume settings
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 500, 1000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Volume settings", wWidth / 2.0f, wHeight / 2.0f - 300);
		CP_Settings_TextSize(27.0f);
		CP_Font_DrawText("Background music", wWidth / 2.0f, wHeight / 2.0f - 140);
		CP_Font_DrawText("Sound effects", wWidth / 2.0f, wHeight / 2.0f + 60);
		CP_Settings_TextSize(35.0f);
		// background music volume adjustment
		sliderBar(wWidth / 2, wHeight / 2 - 100, 400, 10, 255, 255, 255, 255);
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) && IsAreaClicked(mouseX1, wHeight / 2 - 100, 800, 160, mouseClickPos.x, mouseClickPos.y) == 1)
		{

			mouseX1 = CP_Input_GetMouseX();
		}
		if (!(mouseX1 > wWidth / 2 + 200) && !(mouseX1 < wWidth / 2 - 200))
			sliderBox(mouseX1, wHeight / 2 - 100, 10, 20, 0, 0, 0, 255);
		else if (mouseX1 > wWidth / 2 + 200)
			sliderBox(wWidth / 2 + 200, wHeight / 2 - 100, 10, 20, 0, 0, 0, 255);
		else if (mouseX1 < wWidth / 2 - 200)
			sliderBox(wWidth / 2 - 200, wHeight / 2 - 100, 10, 20, 0, 0, 0, 255);
		*&backgroundVolume = (float)((mouseX1 - (wWidth / 2 - 200)) / 400);
		if (*&backgroundVolume > 1.f)
			*&backgroundVolume = 1.f;
		else if (*&backgroundVolume < 0)
			*&backgroundVolume = 0;
		CP_Sound_SetGroupVolume(CP_SOUND_GROUP_1, *&backgroundVolume);
		CP_Sound_SetGroupVolume(CP_SOUND_GROUP_2, *&backgroundVolume);
		mouseX1 = ((wWidth / 2 - 200) + *&backgroundVolume * 400);
		// SFX volume adjustment
		sliderBar(wWidth / 2, wHeight / 2 + 100, 400, 10, 255, 255, 255, 255);
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) && IsAreaClicked(mouseX2, wHeight / 2 + 100, 800, 160, mouseClickPos.x, mouseClickPos.y) == 1)
		{

			mouseX2 = CP_Input_GetMouseX();
		}
		if (!(mouseX2 > wWidth / 2 + 200) && !(mouseX2 < wWidth / 2 - 200))
			sliderBox(mouseX2, wHeight / 2 + 100, 10, 20, 0, 0, 0, 255);
		else if (mouseX2 > wWidth / 2 + 200)
			sliderBox(wWidth / 2 + 200, wHeight / 2 + 100, 10, 20, 0, 0, 0, 255);
		else if (mouseX2 < wWidth / 2 - 200)
			sliderBox(wWidth / 2 - 200, wHeight / 2 + 100, 10, 20, 0, 0, 0, 255);
		*&sfxVolume = (float)((mouseX2 - (wWidth / 2 - 200)) / 400);
		if (*&sfxVolume > 1.f)
			*&sfxVolume = 1.f;
		else if (*&sfxVolume < 0)
			*&sfxVolume = 0;
		mouseX2 = ((wWidth / 2 - 200) + *&sfxVolume * 400);
		CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, *&sfxVolume);
		Button("Back", wWidth / 2.0f, wHeight / 2.0f + 300, wWidth / 2.0f, wHeight / 2.0f + 300, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 300, 200, 180, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Back", wWidth / 2.0f, wHeight / 2.0f + 300, wWidth / 2.0f, wHeight / 2.0f + 296, 220, 100, 0, 255, 0, 0, 0, 0, 255);
			if (CP_Input_MouseClicked())
			{
				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				isPaused = !isPaused;
			}
		}
		if (CP_Input_KeyDown(KEY_ESCAPE))
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			isPaused = !isPaused;
		}
	}
}

void Main_Menu_Exit()
{
	CP_Image_Free(&main_menu);
	CP_Sound_Free(&buttonClickSound);
}
