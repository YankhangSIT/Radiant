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
int x = 100, a = 60;
// Sprite Image
CP_Image gunPlayer;
CP_Image swordPlayer;
CP_Image health;
CP_Image energy;
CP_Image immunity;
CP_Image energybuff;
CP_Image shield;
CP_Image mouse;
CP_Font Acme, Abril;
void how_To_play_Init(void)
{
	// CP_System_FullscreenAdvanced(1920, 1080);
	CP_System_SetWindowSize(1920, 1080);
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
	mouse = CP_Image_Load("Assets/Mouse.png");
	buttonClickSound = CP_Sound_Load("Assets/buttonClick.wav");
	nextState = 0.f;
	startCount = FALSE;
	//// player type gun
	// if (playerNum == 1)
	//{
	//	character.playerSprite = gunPlayer;
	//	character.width = (float)CP_Image_GetWidth(gunPlayer);
	//	character.height = (float)CP_Image_GetHeight(gunPlayer);
	// }

	//// player type sword
	// if (playerNum == 2)
	//{
	//	character.playerSprite = swordPlayer;
	//	character.width = (float)CP_Image_GetWidth(swordPlayer);
	//	character.height = (float)CP_Image_GetHeight(swordPlayer);
	//	canShoot = 0;
	// }

	// gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	// swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");
}

void how_To_play_Update(void)
{
	// delay call next game state by 0.1 sec to register the button sound
	elapsedTime = CP_System_GetDt();
	if (startCount)
		nextState += elapsedTime;
	if (nextState > 0.2)
		// CP_Engine_SetNextGameState(level_4_Init, level_4_Update, level_4_Exit);
		CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);

	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	float xWidth = (float)CP_System_GetWindowWidth();
	float xHeight = (float)CP_System_GetWindowHeight();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f + 50, xHeight / 2.0f - 100 + x, 850, 850);

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_Set(Acme);
	CP_Font_DrawText("How to play:", xWidth / 2.0f + 50, xHeight / 2.0f - 400 + a);
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("Controls:", xWidth / 2.0f - 650, xHeight / 2.0f - 300 + x);
	CP_Font_Set(Abril);

	// WASD Movement guide:
	// W
	CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 150 + x, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("W", xWidth / 2.0f - 800, xHeight / 2.0f - 150 + x);
	if (CP_Input_KeyDown(KEY_W) || IsAreaClicked(xWidth / 2.0f - 800, xHeight / 2.0f - 150 + x, 75, 75, mouseClickPos.x, mouseClickPos.y))
	{
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 150 + x, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("W", xWidth / 2.0f - 800, xHeight / 2.0f - 152 + x);
	}

	// A
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 60 + x, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("S", xWidth / 2.0f - 800, xHeight / 2.0f - 60 + x);
	if (CP_Input_KeyDown(KEY_S) || IsAreaClicked(xWidth / 2.0f - 800, xHeight / 2.0f - 60 + x, 75, 75, mouseClickPos.x, mouseClickPos.y))
	{
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 800, xHeight / 2.0f - 60 + x, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("S", xWidth / 2.0f - 800, xHeight / 2.0f - 58 + x);
	}

	// S
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f - 890, xHeight / 2.0f - 60 + x, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("A", xWidth / 2.0f - 890, xHeight / 2.0f - 60 + x);
	if (CP_Input_KeyDown(KEY_A) || IsAreaClicked(xWidth / 2.0f - 890, xHeight / 2.0f - 60 + x, 75, 75, mouseClickPos.x, mouseClickPos.y))
	{
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 890, xHeight / 2.0f - 60 + x, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("A", xWidth / 2.0f - 892, xHeight / 2.0f - 60 + x);
	}

	// D
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f - 710, xHeight / 2.0f - 60 + x, 75, 75);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("D", xWidth / 2.0f - 710, xHeight / 2.0f - 60 + x);
	if (CP_Input_KeyDown(KEY_D) || IsAreaClicked(xWidth / 2.0f - 710, xHeight / 2.0f - 60 + x, 75, 75, mouseClickPos.x, mouseClickPos.y))
	{
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 710, xHeight / 2.0f - 60 + x, 85, 85);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("D", xWidth / 2.0f - 708, xHeight / 2.0f - 10 + x);
	}

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("Movement", xWidth / 2.0f - 790, xHeight / 2.0f + 20 + x);
	CP_Font_DrawText("Left Click to Attack", xWidth / 2.0f - 530, xHeight / 2.0f + 80 + x);

	// Clicking guide:
	CP_Image_Draw(mouse, xWidth / 2.0f - 530, xHeight / 2.0f - 100 + 100, 225, 320, 255);

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f - 585, xHeight / 2.0f - 210 + 100, 120, 100);
	}

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	// Teach user how to play
	CP_Font_DrawText("1) You are to stay ALIVE for 1 minute.", xWidth / 2.0f - 100, xHeight / 2.0f - 350 + a);
	CP_Font_DrawText("2) Eliminate as many mobs as possible.", xWidth / 2.0f - 95, xHeight / 2.0f - 300 + a);
	CP_Font_DrawText("3) Points are awarded for each boss/mobs killed.", xWidth / 2.0f - 35, xHeight / 2.0f - 250 + a);
	CP_Font_DrawText("4) There are 4 stages, advance till the final stage with final boss. ", xWidth / 2.0f + 58, xHeight / 2.0f - 200 + a);
	CP_Font_DrawText("5) Energy is consumed ONLY if you attack!", xWidth / 2.0f - 70, xHeight / 2.0f - 150 + a);
	CP_Font_DrawText("6) Character is STUNNED & unable to MOVE if energy ", xWidth / 2.0f, xHeight / 2.0f - 100 + a);
	CP_Font_DrawText("REACHES ZERO", xWidth / 2.0f - 193, xHeight / 2.0f - 70 + a);
	CP_Font_DrawText("7) There will be no self health regeneration", xWidth / 2.0f - 65, xHeight / 2.0f - 30 + a);

	// Item drop guide
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_Set(Acme);
	CP_Font_DrawText("Item Drop Guide:", xWidth / 2.0f + 50, xHeight / 2.0f + 20 + a);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_Set(Abril);
	CP_Font_DrawText("Power Ups: - Shield & Energy Icon", xWidth / 2.0f - 120, xHeight / 2.0f + 70 + a);

	CP_Image_Draw(shield, xWidth / 2.0f + 130, xHeight / 2.0f + 70 + a, (float)CP_Image_GetWidth(shield), (float)CP_Image_GetHeight(shield), 255);
	CP_Image_Draw(energy, xWidth / 2.0f + 190, xHeight / 2.0f + 70 + a, (float)CP_Image_GetWidth(energy), (float)CP_Image_GetHeight(energy), 255);

	CP_Font_DrawText("- Immunity for 3 seconds", xWidth / 2.0f - 35, xHeight / 2.0f + 120 + a);
	// CP_Image_Draw(immunity, xWidth / 2.0f + 270, xHeight / 2.0f + 150, (float)CP_Image_GetWidth(immunity), (float)CP_Image_GetHeight(immunity), 255);
	CP_Font_DrawText("- Unlimited attacks for 3 seconds", xWidth / 2.0f + 12, xHeight / 2.0f + 170 + a);
	// CP_Image_Draw(energybuff, xWidth / 2.0f + 380, xHeight / 2.0f + 150, (float)CP_Image_GetWidth(energybuff), (float)CP_Image_GetHeight(energybuff), 255);

	// Prompt user to click 'enter' to proceed to game
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRect(xWidth / 2.0f + 320, xHeight / 2.0f + 240 + x, 200, 90);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Continue", xWidth / 2.0f + 320, xHeight / 2.0f + 240 + x);

	if (IsAreaClicked(xWidth / 2.0f + 320, xHeight / 2.0f + 240 + x, 200, 90, mouseClickPos.x, mouseClickPos.y) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(xWidth / 2.0f + 320, xHeight / 2.0f + 240 + x, 220, 110);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Continue", xWidth / 2.0f + 320, xHeight / 2.0f + 236 + x);
	}

	// Press Enter to proceed to next page
	if (CP_Input_KeyDown(KEY_ENTER))
	{
		// CP_Engine_SetNextGameState(level_4_Init, level_4_Update, level_4_Exit);
		CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
		if (!nextState)
			startCount = TRUE;
		// CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
	}
	// Alternatively, click the area to proceed to next page.
	if (CP_Input_MouseClicked())
	{

		if (IsAreaClicked(xWidth / 2.0f + 320, xHeight / 2.0f + 240 + x, 200, 45, mouseClickPos.x, mouseClickPos.y) == 1)
		{

			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
				startCount = TRUE;
			// CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
			// CP_Engine_SetNextGameState(level_3_Init, level_3_Update, level_3_Exit);
			// CP_Engine_SetNextGameState(level_2_Init, level_2_Update, level_2_Exit);
		}
	}
}

void how_To_play_Exit(void)
{
	CP_Sound_Free(&buttonClickSound);
}
