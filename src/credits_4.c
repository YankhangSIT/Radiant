//---------------------------------------------------------
// file:	credits_4.c
// author:	Seah Sheng Rong Donovan
// email:	s.seah@digipen.edu
// brief:	Credits page 3 (Sound, image & font reference link)
// 
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

CP_Font Alclonia;
float wWidth;
float wHeight;
void Credits_4_Init()
{

	// clear();
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

void Credits_4_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	elapsedTime = CP_System_GetDt();
	if (startCount)
		nextState += elapsedTime;
	if (nextState > 0.2)
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	//Reference from web
	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("Sound System:", wWidth / 2.0f, wHeight / 2.0f - 460);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawText("mixkit Sound System 2022. All rights reserved - Made by Envato Elements", wWidth / 2.0f, wHeight / 2.0f - 420);
	CP_Font_DrawText("Website: www.mixkit.co", wWidth / 2.0f, wHeight / 2.0f - 380);
	CP_Font_DrawText("FreesoundLab Design by Pixelshell. Code by MTG (UPF) Some rights reserved.", wWidth / 2.0f, wHeight / 2.0f - 340);
	CP_Font_DrawText("Website: www.freesound.org", wWidth / 2.0f, wHeight / 2.0f - 300);
	CP_Font_DrawText("Proud Music Library - Music to be proud of | 1999 - 2022", wWidth / 2.0f, wHeight / 2.0f - 260);
	CP_Font_DrawText("Website: www.proudmusiclibrary.com/en/tag/end-credits", wWidth / 2.0f, wHeight / 2.0f - 220);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("Main Menu Background Art:", wWidth / 2.0f, wHeight / 2.0f - 120);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawText("freepikcompany Copyright 2010-2022 Freepik Company S.L All rights reserved", wWidth / 2.0f, wHeight / 2.0f - 80);
	CP_Font_DrawText("Website: www.freepik.com/free-photos-vectors/sci-fi-ui", wWidth / 2.0f, wHeight / 2.0f - 40);

	CP_Settings_Fill(CP_Color_Create(160, 32, 240, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("Softwares:", wWidth / 2.0f, wHeight / 2.0f + 60);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawText("Google fonts", wWidth / 2.0f, wHeight / 2.0f + 100);
	CP_Font_DrawText("Website: www.fonts.com/web-fonts/google", wWidth / 2.0f, wHeight / 2.0f + 140);
	CP_Font_DrawText("Fontmeme", wWidth / 2.0f, wHeight / 2.0f + 180);
	CP_Font_DrawText("Website: www.fontmeme.com/futuristic-fonts/", wWidth / 2.0f, wHeight / 2.0f + 220);
	CP_Font_DrawText("Piskel", wWidth / 2.0f, wHeight / 2.0f + 260);
	CP_Font_DrawText("Website: www.piskelapp.com/p/create/sprite", wWidth / 2.0f, wHeight / 2.0f + 300);
	CP_Font_DrawText("Microsoft PowerPoint", wWidth / 2.0f, wHeight / 2.0f + 340);
	CP_Font_DrawText("ClipChamp (Microsoft Store Application)", wWidth / 2.0f, wHeight / 2.0f + 380);

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
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Credits_4_Exit()
{
	CP_Sound_Free(&buttonClickSound);
}
