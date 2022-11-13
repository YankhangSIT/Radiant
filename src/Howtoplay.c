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
#include "mainmenu.h"
#include "Howtoplay.h"

CP_Font Acme, Abril;
void how_To_play_Init()
{

	Abril = CP_Font_Load("Assets/Abril_Fatface.ttf");
	Acme = CP_Font_Load("Assets/Acme_Regular.ttf");
	// align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	/*CP_TEXT_ALIGN_HORIZONTAL horizontal2 = CP_TEXT_ALIGN_H_LEFT;
	CP_TEXT_ALIGN_VERTICAL vertical2 = CP_TEXT_ALIGN_V_TOP;*/
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);
}

void how_To_play_Update()
{
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	float xWidth = CP_System_GetWindowWidth();
	float xHeight = CP_System_GetWindowHeight();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f, xHeight / 2.0f - 100, 750, 750);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_Set(Acme);
	CP_Font_DrawText("How to play:", xWidth / 2.0f, xHeight / 2.0f - 400);
	CP_Font_Set(Abril);

	// Teach user how to play
	CP_Font_DrawText("1) You are to stay ALIVE until the timer 1minute.", xWidth / 2.0f, xHeight / 2.0f - 330);
	CP_Font_DrawText("2) Eliminate as many mobs as possible.", xWidth / 2.0f, xHeight / 2.0f - 280);
	CP_Font_DrawText("3) Points are awarded for each boss/mobs killed.", xWidth / 2.0f, xHeight / 2.0f - 230);
	CP_Font_DrawText("4) There are 4 stages, advance till the final stage. ", xWidth / 2.0f, xHeight / 2.0f - 180);
	CP_Font_DrawText("5) Kill the final boss and win!", xWidth / 2.0f, xHeight / 2.0f - 130);
	CP_Font_DrawText("6) There will be no self health regeneration", xWidth / 2.0f, xHeight / 2.0f - 80);

	// Item drop guide
	CP_Font_Set(Acme);
	CP_Font_DrawText("Item Drop Guide:", xWidth / 2.0f, xHeight / 2.0f);
	CP_Font_Set(Abril);
	CP_Font_DrawText("- There are health/energy bars around the area", xWidth / 2.0f, xHeight / 2.0f + 70);
	CP_Font_DrawText("- There are different weapons around the area", xWidth / 2.0f, xHeight / 2.0f + 120);
	CP_Font_DrawText("- To take the items, simply walk over the it.", xWidth / 2.0f, xHeight / 2.0f + 170);

	// Prompt user to click 'enter' to proceed to game
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f + 175, xHeight / 2.0f + 240, 350, 45);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Press 'Enter' to continue", xWidth / 2.0f + 180, xHeight / 2.0 + 240);

	// Press Enter to proceed to next page
	if (CP_Input_KeyDown(KEY_ENTER))
	{
		CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
	}
	// Alternatively, click the area to proceed to next page.
	if (CP_Input_MouseClicked())
	{
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsAreaClicked(xWidth / 2.0f + 175, xHeight / 2.0f + 240, 350, 45, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
		}
	}
}

void how_To_play_Exit()
{
}
