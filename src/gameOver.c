#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "stdio.h"
#include "splashScreen.h"
#include "mainmenu.h"
#include "loadingScreen.h"
#include "gameOver.h"
#include "gameOverpage.h"

CP_Image gameOver;
float TimeElapsed;
void game_Over_init(void)
{
	//Set TimeElapsed to float 0
	//Load your image
	//Position your image to the corner of top left
	//Set the size according to your image size.
	TimeElapsed = 0.0f;
	gameOver = CP_Image_Load("./Assets/Gameover.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	 CP_System_Fullscreen();
	CP_Settings_RectMode(CP_POSITION_CENTER);

}

void game_Over_update(void)
{
	float gWidth = CP_System_GetWindowWidth();
	float gHeight = CP_System_GetWindowHeight();

	//Buffer time for splashscreen image & cursor creation
	TimeElapsed += CP_System_GetDt();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	float alphatime = 2;
	if (TimeElapsed >= alphatime)
	{
		TimeElapsed = 0;
		CP_Engine_SetNextGameState(game_Over_page_init, game_Over_page_update, game_Over_page_exit);
	}
	
		float resulttime = (TimeElapsed / alphatime) * 255;
		CP_Image_Draw(gameOver, gWidth / 4.0f + 100, (gHeight / 2.0f - 100), CP_Image_GetWidth(gameOver), CP_Image_GetHeight(gameOver), (int)resulttime);
		

}
void game_Over_exit(void)
{
	//Image would be free from the memory running.
	CP_Image_Free(&gameOver);
}

