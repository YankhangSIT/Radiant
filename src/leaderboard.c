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
#include "sound.h"
#include <stdlib.h>

float TimeElapsed;
FILE* leaderboard = NULL;

struct account {
	char username[12];
	int points;
};
struct account points[30];
char username[12];

int i = 0;
int z = 0;

int compare_function(const void* a, const void* b)
{
	struct account lhs = *(struct account*)a;
	struct account rhs = *(struct account*)b;
	if (lhs.points < rhs.points)return 1;
	if (lhs.points > rhs.points)return -1;
	return 0;
}

void leaderboard_init() {

	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);

}

void leaderboard_update() {
	float gWidth = (float)CP_System_GetWindowWidth();
	float gHeight = (float)CP_System_GetWindowHeight();
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("Enter Username[MAX12ALPHABETS]: ", gWidth / 2.0f - 130, gHeight / 2.0f - 400);

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


		//save leaderboard score to txt file with append+, if use w+ will overwirte the original content
		fopen_s(&leaderboard, "Assets/leaderboard.txt", "a+");
		if (leaderboard != NULL) {
			fprintf(leaderboard, "%s", username);
			fprintf(leaderboard, " %d", 100);
			fprintf(leaderboard, "\n");
			
			fclose(leaderboard);
		}

		
	}

	//read and sort
	fopen_s(&leaderboard, "Assets/leaderboard.txt", "r");
	z = 0;
	if (leaderboard != NULL) {
		while (z < 30 && !feof(leaderboard)) {
#pragma warning(disable : 4996)
			if (fscanf(leaderboard, "%s %d", &points[z].username, &points[z].points) != 2)
			{
				break;
			}
			z++;
		}
		fclose(leaderboard);

		qsort(points,z, sizeof(struct account), compare_function);

		//for (int k = 0; k < a; k++) {
		//	for (int j = k + 1; j < a; j++) {
		//		if (points[i].points > points[j].points) {
		//			struct account temp = points[j];
		//			points[j] = points[i];
		//			points[i] = temp;
		//		}
		//	}
		//}
	}

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(gWidth / 2.0f, gHeight / 2.0f + 100, 750, 500);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("LEADERBOARD", gWidth / 2.0f, gHeight / 2.0f  - 100);


	for (int q = 0; q < z; q++)
	{
		if (q >= 10)break;
		char temp_str[50];
		sprintf(temp_str, "%s %d", points[q].username, points[q].points);
		CP_Font_DrawText(temp_str, gWidth / 2.0f, gHeight / 2.0f + 40 * q - 50);
	}

	Button("Continue", gWidth / 2.0f + 720, gHeight / 2.0f + 450, gWidth / 2.0f + 720, gHeight / 2.0f + 450, 180, 80, 0, 255, 0, 0, 0, 0, 255);
	CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (IsAreaClicked(gWidth / 2.0f + 700, gHeight / 2.0f + 450, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
	{
		Button("Continue", gWidth / 2.0f + 720, gHeight / 2.0f + 450, gWidth / 2.0f + 716, gHeight / 2.0f + 450, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
				startCount = TRUE;
		}
	}
}

void leaderboard_exit() {

}