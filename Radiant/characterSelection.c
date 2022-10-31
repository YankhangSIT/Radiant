#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "stdio.h"
#include "splashScreen.h"
#include "mainmenu.h"

CP_Image gunPlayer;
CP_Image swordPlayer;

int panelDisplay = 0;
extern int playerNum = 0;
void characer_Selection_init()
{
	gunPlayer = CP_Image_Load("Assets/player1.png");
	swordPlayer = CP_Image_Load("Assets/player2.png");
}

void characer_Selection_Update(float wWidth, float wHeight)
{
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 500, 500);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Choose your character", wWidth / 2.0f, wHeight / 2.0f - 300);
	CP_Image_Draw(gunPlayer, wWidth / 2.0f - 100, wHeight / 2.0f, CP_Image_GetWidth(gunPlayer), CP_Image_GetHeight(gunPlayer), 255);
	CP_Image_Draw(swordPlayer, wWidth / 2.0f + 100, wHeight / 2.0f, CP_Image_GetWidth(swordPlayer), CP_Image_GetHeight(swordPlayer), 255);

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

void characer_Selection_Exit()
{


}