#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "stdio.h"
#include "splashScreen.h"
#include "mainmenu.h"
#include "loadingScreen.h"
#include "gameOverPage.h"
#include "button.h"
#include "characterSelect.h"


CP_Image winImage;
float TimeElapsed;

void win_init() {
	CP_System_Fullscreen();
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);


	winImage = CP_Image_Load("Assets/victory.png");
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);
}

void win_update() {
	float gWidth = (float)CP_System_GetWindowWidth();
	float gHeight = (float)CP_System_GetWindowHeight();
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());


	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	// Buffer time for splashscreen image & cursor creation
	TimeElapsed += CP_System_GetDt();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	float alphatime = 2;
	if (TimeElapsed >= alphatime + 1)
	{
		TimeElapsed = 0;

	}

	float resulttime = (TimeElapsed / alphatime) * 255;
	CP_Image_Draw(winImage, gWidth / 2.0f , (gHeight / 2.0f - 300), (float)CP_Image_GetWidth(winImage), (float)CP_Image_GetHeight(winImage), (int)resulttime);

	Button("Next", gWidth / 2.0f, gHeight / 2.0f - 50, gWidth / 2.0f, gHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);

	if (IsAreaClicked(gWidth / 2.0f, gHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
	{
		Button("Next", gWidth / 2.0f, gHeight / 2.0f - 50, gWidth / 2.0f, gHeight / 2.0f - 47, 190, 90, 0, 255, 0, 0, 0, 0, 255);
	}

	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(gWidth / 2.0f, gHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			/*CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Enter your username: ", gWidth / 2.0f , gHeight / 2.0f-500);*/
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}

}

void win_exit() {
	// Image would be free from the memory running.
	CP_Image_Free(&winImage);
}