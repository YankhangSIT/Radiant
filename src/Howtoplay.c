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
#include "stdio.h"
#include "utils.h"
#include "movement.h"
#include "combat.h"
#include "mainmenu.h"
#include "math.h"
#include "level1.h"
#include "spawn.h"
#include "map.h"
#include <stdbool.h>
#include <stdlib.h>
#include "button.h"
#include "gameOverpage.h"
#include "global.h"
#include "sound.h"

struct Character playerGun;
struct Character playerSword;

// Sprite Image
CP_Image gunPlayer;
CP_Image swordPlayer;
CP_Image health;
CP_Image energy;
CP_Image immunity;
CP_Image energybuff;
CP_Image shield;

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
	buttonClickSound = CP_Sound_Load("Assets/buttonClick.wav");
	health = CP_Image_Load("Assets/healthDrop.png");
	energy = CP_Image_Load("Assets/batteryDrop.png");
	immunity = CP_Image_Load("Assets/Unlimited_Health_Mode.png");
	energybuff = CP_Image_Load("Assets/Unlimited_Energy_Mode.png");
	shield = CP_Image_Load("Assets/Shield_Drop.png");

	//// player type gun
	//if (playerNum == 1)
	//{
	//	character.playerSprite = gunPlayer;
	//	character.width = (float)CP_Image_GetWidth(gunPlayer);
	//	character.height = (float)CP_Image_GetHeight(gunPlayer);
	//}

	//// player type sword
	//if (playerNum == 2)
	//{
	//	character.playerSprite = swordPlayer;
	//	character.width = (float)CP_Image_GetWidth(swordPlayer);
	//	character.height = (float)CP_Image_GetHeight(swordPlayer);
	//	canShoot = 0;
	//}

	//gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	//swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");
}

void how_To_play_Update()
{
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	float xWidth = (float)CP_System_GetWindowWidth();
	float xHeight = (float)CP_System_GetWindowHeight();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f, xHeight / 2.0f - 100, 800, 750);

	CP_Settings_Fill(CP_Color_Create(139, 0, 0, 255));
	CP_Font_Set(Acme);
	CP_Font_DrawText("How to play:", xWidth / 2.0f, xHeight / 2.0f - 400);
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("Controls:", xWidth / 2.0f - 650, xHeight / 2.0f - 400);
	CP_Font_Set(Abril);

	//WASD Movement guide:
	//W
	CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 300, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("W", xWidth / 2.0f - 800, xHeight / 2.0f - 300);
	if (CP_Input_KeyDown(KEY_W) || IsAreaClicked(xWidth / 2.0f - 800, xHeight / 2.0f - 300, 75, 75, mouseClickPos.x, mouseClickPos.y)) {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 300, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("W", xWidth / 2.0f - 800, xHeight / 2.0f - 302);
	}

	//A 
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 210, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("S", xWidth / 2.0f - 800, xHeight / 2.0f - 210);
	if (CP_Input_KeyDown(KEY_S) || IsAreaClicked(xWidth / 2.0f - 800, xHeight / 2.0f - 210, 75, 75, mouseClickPos.x, mouseClickPos.y)){
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 210, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("S", xWidth / 2.0f - 800, xHeight / 2.0f - 208);
	}

	//S
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f - 890, xHeight / 2.0f - 210, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("A", xWidth / 2.0f - 890, xHeight / 2.0f - 210);
	if (CP_Input_KeyDown(KEY_A) || IsAreaClicked(xWidth / 2.0f - 890, xHeight / 2.0f - 210, 75, 75, mouseClickPos.x, mouseClickPos.y)) {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 890, xHeight / 2.0f - 210, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("A", xWidth / 2.0f - 892, xHeight / 2.0f - 210);
	}

	//D
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f - 710, xHeight / 2.0f - 210, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("D", xWidth / 2.0f - 710, xHeight / 2.0f - 210);
	if (CP_Input_KeyDown(KEY_D) || IsAreaClicked(xWidth / 2.0f - 710, xHeight / 2.0f - 210, 75, 75, mouseClickPos.x, mouseClickPos.y)) {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 710, xHeight / 2.0f - 210, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("D", xWidth / 2.0f - 708, xHeight / 2.0f - 210);
	}


	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	// Teach user how to play
	CP_Font_DrawText("1) You are to stay ALIVE for 1 minute.", xWidth / 2.0f - 155 , xHeight / 2.0f - 330);
	CP_Font_DrawText("2) Eliminate as many mobs as possible.", xWidth / 2.0f - 150, xHeight / 2.0f - 280);
	CP_Font_DrawText("3) Points are awarded for each boss/mobs killed.", xWidth / 2.0f - 90, xHeight / 2.0f - 230);
	CP_Font_DrawText("4) There are 4 stages, advance till the final stage with final boss. ", xWidth / 2.0f +3, xHeight / 2.0f - 180);
	CP_Font_DrawText("5) Energy is consumed ONLY if you attack!", xWidth / 2.0f - 125, xHeight / 2.0f - 130);
	CP_Font_DrawText("6) There will be no self health regeneration", xWidth / 2.0f - 120, xHeight / 2.0f - 80);

	// Item drop guide
	CP_Settings_Fill(CP_Color_Create(139, 0, 0, 255));
	CP_Font_Set(Acme);
	CP_Font_DrawText("Item Drop Guide:", xWidth / 2.0f, xHeight / 2.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_Set(Abril);
	CP_Font_DrawText("Health, Energy & Shield Bars", xWidth / 2.0f - 195, xHeight / 2.0f + 70);
	CP_Image_Draw(health, xWidth / 2.0f + 10 , xHeight / 2.0f + 70, (float)CP_Image_GetWidth(health), (float)CP_Image_GetHeight(health), 255);
	CP_Image_Draw(energy, xWidth / 2.0f + 70, xHeight / 2.0f + 70, (float)CP_Image_GetWidth(energy), (float)CP_Image_GetHeight(energy), 255);
	CP_Image_Draw(shield, xWidth / 2.0f + 130, xHeight / 2.0f + 70, (float)CP_Image_GetWidth(shield), (float)CP_Image_GetHeight(shield), 255);

	CP_Font_DrawText("Power Ups: - Immunity for 3 seconds", xWidth / 2.0f - 150, xHeight / 2.0f + 120);
	CP_Image_Draw(immunity, xWidth / 2.0f + 220, xHeight / 2.0f + 100, (float)CP_Image_GetWidth(immunity), (float)CP_Image_GetHeight(immunity), 255);
	CP_Font_DrawText("- Unlimited attacks for 3 seconds", xWidth / 2.0f - 33 , xHeight / 2.0f + 170);
	CP_Image_Draw(energybuff, xWidth / 2.0f + 330, xHeight / 2.0f + 150, (float)CP_Image_GetWidth(energybuff), (float)CP_Image_GetHeight(energybuff), 255);

	// Prompt user to click 'enter' to proceed to game
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f + 180, xHeight / 2.0f + 240, 200, 45);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Continue", xWidth / 2.0f + 180, xHeight / 2.0f + 240);

	
	if (IsAreaClicked(xWidth / 2.0f + 180, xHeight / 2.0f + 240, 200, 45, mouseClickPos.x, mouseClickPos.y) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f + 180, xHeight / 2.0f + 240, 220, 55);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Continue", xWidth / 2.0f + 180, xHeight / 2.0f + 236);
	}

	// Press Enter to proceed to next page
	if (CP_Input_KeyDown(KEY_ENTER))
	{
		// CP_Engine_SetNextGameState(level_4_Init, level_4_Update, level_4_Exit);
		CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
		
		CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
	}
	// Alternatively, click the area to proceed to next page.
	if (CP_Input_MouseClicked())
	{
		
		if (IsAreaClicked(xWidth / 2.0f + 180, xHeight / 2.0f + 240, 200, 45, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			// CP_Engine_SetNextGameState(level_4_Init, level_4_Update, level_4_Exit);
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
		}
	}
}

void how_To_play_Exit()
{
	CP_Sound_Free(&buttonClickSound);
}
