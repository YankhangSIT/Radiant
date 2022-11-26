//---------------------------------------------------------
// file:	credits_2.c
// author:	Seah Sheng Rong Donovan
// email:	s.seah@digipen.edu
// brief:	credits page 1 (Roles & Credits)
// 
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

//header files
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
#include "credits_3.h"

float TimeElapsed;
CP_Font Alclonia;

float wWidth;
float wHeight;
void Credits_2_Init()
{

	CP_System_FullscreenAdvanced(1920, 1080);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	Alclonia = CP_Font_Load("Assets/Alclonia_Regular.ttf");

	CP_Settings_ImageMode(CP_POSITION_CENTER);

	// align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	buttonClickSound = CP_Sound_Load("Assets/buttonClick.wav");
	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();
	nextState = 0.f;
	startCount = FALSE;
}

void Credits_2_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	elapsedTime = CP_System_GetDt();
	if (startCount)
		nextState += elapsedTime;
	if (nextState > 0.2)
	{
		CP_Engine_SetNextGameState(Credits_3_Init, Credits_3_Update, Credits_3_Exit);
	}
	// Project credits
	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("DIRECTOR and PROGRAMMER", wWidth / 2.0f, wHeight / 2.0f - 400);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Koh Yan Khang", wWidth / 2.0f, wHeight / 2.0f - 350);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("PRODUCER and DESIGN LEAD", wWidth / 2.0f, wHeight / 2.0f - 250);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Wei Jing Song", wWidth / 2.0f, wHeight / 2.0f - 200);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("ENVIRONMENT ARTISTS and USER-INTERFACE", wWidth / 2.0f, wHeight / 2.0f - 100);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Seah Sheng Rong Donovan", wWidth / 2.0f, wHeight / 2.0f - 50);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("TECHNICAL LEAD", wWidth / 2.0f, wHeight / 2.0f + 50);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Lua Wei Xiang Darren", wWidth / 2.0f, wHeight / 2.0f + 100);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("SPECIAL THANKS TO: ", wWidth / 2.0f, wHeight / 2.0f + 200);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Professor Cheng Ding Xiang", wWidth / 2.0f, wHeight / 2.0f + 250);
	CP_Font_DrawText("Mr Gerald Wong", wWidth / 2.0f, wHeight / 2.0f + 300);
	CP_Font_DrawText("Teaching Assistants", wWidth / 2.0f, wHeight / 2.0f + 350);
	CP_Font_DrawText("Play Testers", wWidth / 2.0f, wHeight / 2.0f + 400);

	CP_Settings_TextSize(30.0f);
	Button("Continue", wWidth / 2.0f + 700, wHeight / 2.0f + 450, wWidth / 2.0f + 700, wHeight / 2.0f + 450, 180, 80, 0, 255, 0, 0, 0, 0, 255);
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (IsAreaClicked(wWidth / 2.0f + 700, wHeight / 2.0f + 450, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
	{
		Button("Continue", wWidth / 2.0f + 700, wHeight / 2.0f + 450, wWidth / 2.0f + 696, wHeight / 2.0f + 450, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		if (CP_Input_MouseClicked())
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
				startCount = TRUE;
		}
	}

	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		CP_Engine_SetNextGameState(Credits_3_Init, Credits_3_Update, Credits_3_Exit);
	}
}

void Credits_2_Exit()
{
	CP_Sound_Free(&buttonClickSound);
}
