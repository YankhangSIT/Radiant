//---------------------------------------------------------
// file:	credits.c
// author:	Seah Sheng Rong Donovan
// email:	s.seah@digipen.edu
// brief:	"splashscreen" of the credits
// 
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

//header files

#include "cprocessing.h"
#include "stdio.h"
#include "sound.h"
#include "credits_2.h"

float TimeElapsed;

CP_Image credits_title;
int fadeoutt = FALSE;
void Credits_Init()
{

	// Set TimeElapsed to float 0
	// Load your image
	// Position your image to the corner of top left
	// Set the size according to your image size.
	TimeElapsed = 0.0f;
	credits_title = CP_Image_Load("Assets/credits_title.PNG");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	// CP_System_SetWindowSize(1920, 1080);
	CP_System_FullscreenAdvanced(1920, 1080);
}

void Credits_Update()
{
	float wWidth = (float)CP_System_GetWindowWidth();
	float wHeight = (float)CP_System_GetWindowHeight();
	// Buffer time for credits title image
	TimeElapsed += CP_System_GetDt();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	float alphatime = 3;
	float resulttime = (TimeElapsed / alphatime) * 255; // Fade in formula

	if (fadeoutt == TRUE)
	{
		resulttime = 255 - (TimeElapsed / alphatime) * 255; // Fade out formula
		if (TimeElapsed >= alphatime)
		{
			CP_Engine_SetNextGameState(Credits_2_Init, Credits_2_Update, Credits_2_Exit);
		}
	}

	if (TimeElapsed >= alphatime)
	{
		TimeElapsed = 0;
		fadeoutt = TRUE;
		alphatime = 3;
	}
	CP_Image_Draw(credits_title, wWidth / 2.0f - 580, wHeight / 2.0f - 250, 1200, 500, (int)resulttime); // Draw Credits title image
}

void Credits_Exit()
{

	CP_Image_Free(&credits_title);
}
