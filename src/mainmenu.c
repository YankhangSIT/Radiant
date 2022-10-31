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

int panelDisplay = 0;
CP_Image gunPlayer;
CP_Image swordPlayer;
//CP_Image digipen;

float TimeElapsed;
extern int playerNum = 0;
void Main_Menu_Init()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();
	
	gunPlayer = CP_Image_Load("Assets/player1.png");
	swordPlayer = CP_Image_Load("Assets/player2.png");

	//align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);
}




void Main_Menu_Update()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();


	////Buffer time for splashscreen image & cursor creation
	//TimeElapsed += CP_System_GetDt();
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	//CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);

	//float alphatime = 2;
	//if (TimeElapsed >= alphatime)
	//{
	//	TimeElapsed = 0;
	//}
	//float resulttime = (TimeElapsed / alphatime) * 255;
	//CP_Image_Draw(digipen, 0, 0, CP_Image_GetWidth(digipen), CP_Image_GetHeight(digipen), (int)resulttime);

		//Play Button
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Play", wWidth / 2.0f, wHeight / 2.0f - 100);

		//Settings Button
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Settings", wWidth / 2.0f, wHeight / 2.0f + 200);

		//Exit Button
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Exit", wWidth / 2.0f, wHeight / 2.0f + 50);

		//If click "Play" Button
	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1) {
			
			panelDisplay = 1;
					
		} 
		//else if click "Exit" button
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1) {
			CP_Engine_Terminate();
		}

		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1) {
			//CP_Engine_SetNextGameState(Settings_Init, Settings_Update, Settings_Exit);
		}

		if (IsAreaClicked(wWidth / 2.0f - 100, wHeight / 2.0f, CP_Image_GetWidth(gunPlayer), CP_Image_GetHeight(gunPlayer), mouseClickPos.x, mouseClickPos.y) == 1)
		{
			playerNum = 1;
			CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
			panelDisplay = 0;

		}

		if (IsAreaClicked(wWidth / 2.0f + 100, wHeight / 2.0f, CP_Image_GetWidth(swordPlayer), CP_Image_GetHeight(swordPlayer), mouseClickPos.x, mouseClickPos.y) == 1)
		{
			playerNum = 2;
			CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
			panelDisplay = 0;
		}
	}


	if (panelDisplay == 1)
	{
		
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 500, 500);
		
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Choose your character", wWidth / 2.0f, wHeight / 2.0f - 300);
		CP_Image_Draw(gunPlayer, wWidth /2.0f -100 , wHeight / 2.0f, CP_Image_GetWidth(gunPlayer), CP_Image_GetHeight(gunPlayer), 255);
		CP_Image_Draw(swordPlayer, wWidth / 2.0f +100, wHeight / 2.0f, CP_Image_GetWidth(swordPlayer), CP_Image_GetHeight(swordPlayer), 255);
	
	}
}

void Main_Menu_Exit()
{

}
