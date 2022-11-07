//#include "cprocessing.h"
//#include "utils.h"
//#include "level1.h"
//#include "stdio.h"
//#include "splashScreen.h"
//#include "mainmenu.h"
//#include "loadingScreen.h"
//
//
//CP_Image game_Title;
//float TimeElapsed;
//float loadingBar = 0;
//
//void loading_Screen_Init()
//{
//	//Set TimeElapsed to float 0
//	//Load your image
//	//Position your image to the corner of top left
//	//Set the size according to your image size.
//	TimeElapsed = 0.0f;
//	game_Title = CP_Image_Load("./Assets/Game_Titlee.png");
//	
//	CP_Settings_ImageMode(CP_POSITION_CENTER);
//	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
//	CP_System_Fullscreen();
//	CP_Settings_RectMode(CP_POSITION_CENTER);
//
//	CP_Settings_TextSize(35.0f);
//}
//
//void loading_Screen_Update(void)
//{
//	float aWidth = CP_System_GetWindowWidth();
//	float aHeight = CP_System_GetWindowHeight();
//	const float loadingTime = 4.0f;
//	char loadingPercentage[10];
//	float loadingPercentagef = (TimeElapsed / (loadingTime - 0.5)) * 100;
//	snprintf(loadingPercentage , sizeof(loadingPercentage), "%d", (int)loadingPercentagef);
//	//Buffer time for loading screen
//	TimeElapsed += CP_System_GetDt();
//
//	if (TimeElapsed > loadingTime) {
//		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
//	}
//	if (TimeElapsed < loadingTime - 0.5) {
//		loadingBar = (TimeElapsed / loadingTime) * aWidth / 2.0f;
//	}
//
//	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
//
//	CP_Image_Draw(game_Title, aWidth/ 4.0f + 125, (aHeight / 2.0f - 100), CP_Image_GetWidth(game_Title), CP_Image_GetHeight(game_Title), 255);
//
//	//Loading Bar creation
//	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//	CP_Graphics_DrawRect(aWidth / 2.0f, aHeight / 2.0f + 100, loadingBar, 100);
//	
//	//Loading Screen percentage (%) creation
//	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//	CP_Font_DrawText(loadingPercentage, aWidth / 2.0f - 30, aHeight / 2.0f + 100);
//
//	
//}
//void loading_Screen_Exit(void)
//{
//	CP_Image_Free(&game_Title);
//	
//}
//	