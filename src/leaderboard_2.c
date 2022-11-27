/#include "cprocessing.h"
//#include "utils.h"
//#include "level1.h"
//#include "level2.h"
//#include "level3.h"
//#include "level4.h"
//#define __STDC_WANT_LIB_EXT1__1
//#include "stdio.h"
//#include "splashScreen.h"
//#include "mainmenu.h"
//#include "loadingScreen.h"
//#include "gameOverPage.h"
//#include "button.h"
//#include "characterSelect.h"
//#include "leaderboard.h"
//
//
////union account {
////	char username[12] = { '/0' };
////	int points[];
////};
////struct user1;
//
//
//
//void leaderboard_2_init() {
//
//	CP_System_SetWindowSize(1920, 1080);
//	CP_Settings_ImageMode(CP_POSITION_CENTER);
//	CP_Settings_RectMode(CP_POSITION_CENTER);
//
//	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
//	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
//	CP_Settings_TextAlignment(horizontal, vertical);
//	CP_Settings_TextSize(35.0f);
//
//}
//
//void leaderboard_2_update() {
//	float gWidth = (float)CP_System_GetWindowWidth();
//	float gHeight = (float)CP_System_GetWindowHeight();
//	
//	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
//	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//	CP_Graphics_DrawRect(gWidth / 2.0f, gHeight / 2.0f + 100, 750, 500);
//	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//	CP_Font_DrawText("LEADERBOARD", gWidth / 2.0f, gHeight / 2.0f - 100);
//
//	//fopen_s(&leaderboard, "Assets/leaderboard.txt", "r");
//	//if (leaderboard != NULL) {
//	//	
//	//	CP_Font_DrawText(username, gWidth / 2.0f, gHeight / 2.0f - 80);
//	//}
//}
//
//void leaderboard_2_exit() {
//
//}