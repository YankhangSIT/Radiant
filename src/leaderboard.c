#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#define __STDC_WANT_LIB_EXT1__1
#include "stdio.h"
#include "splashScreen.h"
#include "mainmenu.h"
#include "loadingScreen.h"
#include "gameOverPage.h"
#include "button.h"
#include "characterSelect.h"


CP_Image win;
float TimeElapsed;
FILE* leaderboard = NULL;
char username[12] = { '/0' };

int points[];
int i = 0;

void leaderboard_init() {

	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);

	fopen(leaderboard, "r");
}

void leaderboard_update() {
	float gWidth = (float)CP_System_GetWindowWidth();
	float gHeight = (float)CP_System_GetWindowHeight();
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("Enter Username[MAX12CHARACTERS]: ", gWidth / 2.0f - 130, gHeight / 2.0f - 400 );
	
	if (i < 12) {

		if (CP_Input_KeyTriggered(KEY_A)) {
			username[i] = 'A';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_B)) {
			username[i] = 'B';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_C)) {
			username[i] = 'C';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_D)) {
			username[i] = 'D';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_E)) {
			username[i] = 'E';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_F)) {
			username[i] = 'F';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_G)) {
			username[i] = 'G';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_H)) {
			username[i] = 'H';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_I)) {
			username[i] = 'I';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_J)) {
			username[i] = 'J';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_K)) {
			username[i] = 'K';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_L)) {
			username[i] = 'L';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_M)) {
			username[i] = 'M';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_N)) {
			username[i] = 'N';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_O)) {
			username[i] = 'O';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_P)) {
			username[i] = 'P';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_Q)) {
			username[i] = 'Q';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_R)) {
			username[i] = 'R';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_S)) {
			username[i] = 'S';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_T)) {
			username[i] = 'T';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_U)) {
			username[i] = 'U';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_V)) {
			username[i] = 'V';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_W)) {
			username[i] = 'W';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_X)) {
			username[i] = 'X';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_Y)) {
			username[i] = 'Y';
			i++;
		}
		if (CP_Input_KeyTriggered(KEY_Z)) {
			username[i] = 'Z';
			i++;
		}
	}
	if (CP_Input_KeyTriggered(KEY_BACKSPACE)) {
		--i;
		username[i] = ' ';
	}
	CP_Font_DrawText(username, gWidth / 2.0f + 250, gHeight / 2.0f - 400);
	

	if (CP_Input_KeyTriggered(KEY_ENTER)) {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(gWidth / 2.0f, gHeight / 2.0f + 100, 750, 500);
		//sort array here
		
		
		fopen_s(&leaderboard,"Assets/leaderboard.txt", "w+");
		if (leaderboard != NULL) {
			fputs(username, leaderboard);
			//Prompt the leaderboard to display with the updated file data.
			
			/*	while(fgets(username, i, leaderboard){
					for(int j = 0; j < 10; j++){
						fprintf(stdout, "%c")*/
			fclose(leaderboard);
		}



	}

}

void leaderboard_exit() {
	
}