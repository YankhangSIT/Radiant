/*!
@file mainmenu.c
@author Koh Yan Khang (yankhang.k)
@course csd1401f22
@section b
@CarSelectGame
@date 28/09/2022
*//*______________________________________________________________________*/


#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "stdio.h"
#include "splashScreen.h"
#include "characterSelect.h"
#include "mainmenu.h"
#include "Howtoplay.h"

CP_Image gunPlayer;
CP_Image swordPlayer;

extern int playerNum = 0;
float zWidth;
float zHeight;
void character_Select_Init()
{
	gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");

	//align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);
	zWidth = CP_System_GetWindowWidth();
	zHeight = CP_System_GetWindowHeight();
}




void character_Select_Update()
{
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

		// Create rectangle 

		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(zWidth / 2.0f, zHeight / 2.0f , 700, 700);

		// Set up the character select screen 
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Choose your character", zWidth / 2.0f, zHeight / 2.0f - 200);
		CP_Image_Draw(gunPlayer, zWidth / 2.0f - 100, zHeight / 2.0f, CP_Image_GetWidth(gunPlayer), CP_Image_GetHeight(gunPlayer), 255);
		CP_Image_Draw(swordPlayer, zWidth / 2.0f + 100, zHeight / 2.0f, CP_Image_GetWidth(swordPlayer), CP_Image_GetHeight(swordPlayer), 255);
	
		//Pick the character, then proceed to Howtoplay page.
		if (CP_Input_MouseClicked()) {
			CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
			
				if (IsAreaClicked(zWidth / 2.0f - 100, zHeight / 2.0f, CP_Image_GetWidth(gunPlayer) + 10, CP_Image_GetHeight(gunPlayer) + 10 , mouseClickPos.x, mouseClickPos.y) == 1)
				{
					playerNum = 1;
					CP_Engine_SetNextGameState(how_To_play_Init, how_To_play_Update, how_To_play_Exit);
					/*panelDisplay = 0;*/
				}

				if (IsAreaClicked(zWidth / 2.0f + 100, zHeight / 2.0f, CP_Image_GetWidth(swordPlayer) +10, CP_Image_GetHeight(swordPlayer) + 10 , mouseClickPos.x, mouseClickPos.y) == 1)
				{
					playerNum = 2;
					CP_Engine_SetNextGameState(how_To_play_Init, how_To_play_Update, how_To_play_Exit);
					/*	panelDisplay = 0;*/
				}
			}
		
}

void character_Select_Exit()
{

}
