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

CP_Image gameOver;
float TimeElapsed;

void game_Over_page_init(void)
{
	//Set TimeElapsed to float 0
	//Load your image
	//Position your image to the corner of top left
	//Set the size according to your image size.
	CP_System_Fullscreen();
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// Set TimeElapsed to float 0
	// Load your image
	// Position your image to the corner of top left
	// Set the size according to your image size.
	TimeElapsed = 0.0f;
	gameOver = CP_Image_Load("Assets/Gameover.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_Fullscreen();
	CP_Settings_RectMode(CP_POSITION_CENTER);

	//Set text alignment and font size
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);

}

void game_Over_page_update(void)
{
	float pWidth = (float) CP_System_GetWindowWidth();
	float pHeight = (float) CP_System_GetWindowHeight();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));


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
	CP_Image_Draw(gameOver, pWidth / 4.0f + 100, (pHeight / 2.0f - 300), (float) CP_Image_GetWidth(gameOver), (float) CP_Image_GetHeight(gameOver), (int)resulttime);

	Button("Restart", pWidth / 2.0f, pHeight / 2.0f - 50, pWidth / 2.0f, pHeight / 2.0f - 50, 180, 80, 255, 0, 0, 0, 0, 0, 255);

	Button("Menu", pWidth / 2.0f, pHeight / 2.0f + 100, pWidth / 2.0f, pHeight / 2.0f + 100, 180, 80, 255, 0, 0, 0, 0, 0, 255);

	Button("Exit", pWidth / 2.0f, pHeight / 2.0f + 250, pWidth / 2.0f, pHeight / 2.0f + 250, 180, 80, 255, 0, 0, 0, 0, 0, 255);


	if (CP_Input_MouseClicked()) {

		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
			if (IsAreaClicked(pWidth / 2.0f, pHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
			{
				if (level == 1)
				{
					CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);
				}
				else if (level == 2)
				{
					CP_Engine_SetNextGameState(level_2_Init, level_2_Update, level_2_Exit);
				}
				else if (level == 3)
				{
					CP_Engine_SetNextGameState(level_3_Init, level_3_Update, level_3_Exit);
				}
				else if(level == 4)
				{
					CP_Engine_SetNextGameState(level_4_Init, level_4_Update, level_4_Exit);
				}



					
				//CP_Engine_SetNextGameState(level_1_Init, level_1_Update, level_1_Exit);

			}

		if (IsAreaClicked(pWidth / 2.0f, pHeight / 2.0f + 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}

		if (IsAreaClicked(pWidth / 2.0f, pHeight / 2.0f + 250, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_Terminate();
		}
	}
}
void game_Over_page_exit(void)
{
	// Image would be free from the memory running.
	CP_Image_Free(&gameOver);
	
}

