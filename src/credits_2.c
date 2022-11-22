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
#include "credits_3.h"


float TimeElapsed;
CP_Font Alclonia;
CP_Image enter;
float wWidth;
float wHeight;
void Credits_2_Init()
{

	//clear();
	CP_System_Fullscreen();
	CP_Settings_RectMode(CP_POSITION_CENTER);
	Alclonia = CP_Font_Load("Assets/Alclonia_Regular.ttf");
	enter = CP_Image_Load("Assets/credits.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	/*CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP)*/;

	// align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	
	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();
	credits = CP_Sound_Load("Assets/credits.wav");

}

void Credits_2_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Sound_PlayAdvanced(credits, 1.0f, 0.5f, TRUE, CP_SOUND_GROUP_1);
	
	CP_Image_Draw(enter, wWidth / 2.0f + 600, wHeight / 2.0f + 500, 550, 50, 255);


	CP_Settings_Fill(CP_Color_Create(247, 162, 51, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("GRAPHICS PROGRAMMER", wWidth / 2.0f , wHeight / 2.0f - 500);
	CP_Font_DrawText("LEVEL DESIGNER", wWidth / 2.0f , wHeight / 2.0f - 400);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Darren Lua", wWidth / 2.0f , wHeight / 2.0f - 350);
	CP_Font_DrawText("Koh Yan Khang", wWidth / 2.0f , wHeight / 2.0f - 310);
	CP_Settings_Fill(CP_Color_Create(247, 162, 51, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("MAP ARTIST AND USER-INTERFACE", wWidth / 2.0f, wHeight / 2.0f - 230);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Seah Sheng Rong Donovan", wWidth / 2.0f, wHeight / 2.0f - 180);
	CP_Font_DrawText("Wei Jing Song", wWidth / 2.0f, wHeight / 2.0f - 140);

	CP_Settings_Fill(CP_Color_Create(247, 162, 51, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("ART DESIGN & AUDIO LEAD", wWidth / 2.0f, wHeight / 2.0f - 60);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Seah Sheng Rong Donovan", wWidth / 2.0f, wHeight / 2.0f - 10);
	CP_Font_DrawText("Wei Jing Song", wWidth / 2.0f, wHeight / 2.0f + 30);
	CP_Font_DrawText("Darren Lua", wWidth / 2.0f, wHeight / 2.0f + 70);
	CP_Font_DrawText("Koh Yan Khang", wWidth / 2.0f, wHeight / 2.0f + 110);


	CP_Settings_Fill(CP_Color_Create(247, 162, 51, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("SPECIAL THANKS TO: ", wWidth / 2.0f, wHeight / 2.0f + 400);
	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(45.0f);
	CP_Font_DrawText("Teaching Assistants & Lecturers", wWidth / 2.0f, wHeight / 2.0f + 470);
	CP_Font_DrawText("Play Testers", wWidth / 2.0f, wHeight / 2.0f + 515);

	if (CP_Input_KeyTriggered(KEY_ENTER)) {
		CP_Engine_SetNextGameState(Credits_3_Init, Credits_3_Update,Credits_3_Exit);
	}


}

void Credits_2_Exit()
{
	
	
}
