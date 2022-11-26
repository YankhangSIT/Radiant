//---------------------------------------------------------
// file:	credits_3.c
// author:	Seah Sheng Rong Donovan
// email:	s.seah@digipen.edu
// brief:	Credits page 2 (credits to Digipen main body)
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

// header files
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
#include "credits_4.h"

float TimeElapsed;
CP_Font Alclonia;
float wWidth;
float wHeight;
void Credits_3_Init()
{

	// clear();
	// CP_System_SetWindowSize(1920, 1080);
	CP_System_FullscreenAdvanced(1920, 1080);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	Alclonia = CP_Font_Load("Assets/Alclonia_Regular.ttf");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	/*CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP)*/;

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

void Credits_3_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	elapsedTime = CP_System_GetDt();
	if (startCount)
		nextState += elapsedTime;
	if (nextState > 0.2)
	{
		CP_Engine_SetNextGameState(Credits_4_Init, Credits_4_Update, Credits_4_Exit);
	}

	float alphatime = 2;
	if (TimeElapsed >= alphatime + 1)
	{
		TimeElapsed = 0;
	}

	//Digipen main body 
	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(70.f);
	CP_Font_DrawText("CREATED AT", wWidth / 2.0f, wHeight / 2.0f - 450);
	CP_Settings_TextSize(60.f);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Font_DrawText("DigiPen Institute of Technology Singapore", wWidth / 2.0f, wHeight / 2.0f - 390);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(70.f);
	CP_Font_DrawText("PRESIDENT", wWidth / 2.0f, wHeight / 2.0f - 210);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("CLAUDE COMAIR", wWidth / 2.0f, wHeight / 2.0f - 150);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(70.f);
	CP_Font_DrawText("EXECUTIVES", wWidth / 2.0f, wHeight / 2.0f + 30);

	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(60.0f);
	CP_Font_DrawText("JASON CHU     SAMIR ABOU SAMRA     MICHELE COMAIR", wWidth / 2.0f, wHeight / 2.0f + 100);
	CP_Font_DrawText("PRASANNA GHALI     ANGELA KUGLER     ERIK MOHRMANN", wWidth / 2.0f, wHeight / 2.0f + 150);
	CP_Font_DrawText("BENJAMIN ELLINGER     MELVIN GONSALVEZ     RAYMOND YAN", wWidth / 2.0f, wHeight / 2.0f + 200);
	CP_Font_DrawText("CHRISTOPHER COMAIR    JOHN BAUER     JOHNNY DEEK", wWidth / 2.0f, wHeight / 2.0f + 250);
	CP_Font_DrawText("MICHAEL GATS     CHARLES DUBA", wWidth / 2.0f, wHeight / 2.0f + 300);

	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("WWW.DIGIPEN.EDU", wWidth / 2.0f, wHeight / 2.0f + 400);
	CP_Font_DrawText("All content 2022 DigiPen Institute of Technology Singapore. All Rights Reserved", wWidth / 2.0f, wHeight / 2.0f + 450);

	//Buttons
	Button("Continue", wWidth / 2.0f + 720, wHeight / 2.0f + 450, wWidth / 2.0f + 720, wHeight / 2.0f + 450, 180, 80, 0, 255, 0, 0, 0, 0, 255);
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (IsAreaClicked(wWidth / 2.0f + 700, wHeight / 2.0f + 450, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
	{
		Button("Continue", wWidth / 2.0f + 720, wHeight / 2.0f + 450, wWidth / 2.0f + 716, wHeight / 2.0f + 450, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		if (CP_Input_MouseClicked())
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
				startCount = TRUE;
		}
	}

	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		CP_Engine_SetNextGameState(Credits_4_Init, Credits_4_Update, Credits_4_Exit);
	}
}

void Credits_3_Exit()
{
	CP_Sound_Free(&buttonClickSound);
}
