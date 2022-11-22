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
#include "utils.h"
#include "level1.h"
#include "stdio.h"
#include "splashScreen.h"
#include "characterSelect.h"
#include "win.h"
#include "button.h"
#include "gameOverpage.h"
#include "sound.h"

float TimeElapsed;
CP_Font Alclonia;
CP_Image enter;
float wWidth;
float wHeight;
void Credits_3_Init()
{

	// clear();
	CP_System_Fullscreen();
	CP_Settings_RectMode(CP_POSITION_CENTER);
	Alclonia = CP_Font_Load("Assets/Alclonia_Regular.ttf");
	enter = CP_Image_Load("Assets/credits.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	/*CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP)*/;

	// align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);

	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();
}

void Credits_3_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	float alphatime = 2;
	if (TimeElapsed >= alphatime + 1)
	{
		TimeElapsed = 0;
	}
	CP_Image_Draw(enter, wWidth / 2.0f + 600, wHeight / 2.0f + 500, 550, 50, 255);

	CP_Settings_Fill(CP_Color_Create(255, 250, 250, 255));
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("Created at", wWidth / 2.0f, wHeight / 2.0f - 450);
	CP_Font_DrawText("DigiPen Institute of Technology Singapore", wWidth / 2.0f, wHeight / 2.0f - 390);

	CP_Settings_TextSize(70.f);
	CP_Font_DrawText("PRESIDENT", wWidth / 2.0f, wHeight / 2.0f - 210);
	CP_Settings_TextSize(60.f);
	CP_Font_DrawText("CLAUDE COMAIR", wWidth / 2.0f, wHeight / 2.0f - 150);

	CP_Settings_TextSize(70.f);
	CP_Font_DrawText("EXCUTIVES", wWidth / 2.0f, wHeight / 2.0f + 30);

	CP_Settings_TextSize(60.0f);
	CP_Font_DrawText("JASON CHU     SAMIR ABOU SAMRA     MICHELE COMAIR", wWidth / 2.0f, wHeight / 2.0f + 100);
	CP_Font_DrawText("PRASANNA GHALI     ANGELA KUGLER     ERIK MOHRMANN", wWidth / 2.0f, wHeight / 2.0f + 150);
	CP_Font_DrawText("BENJAMIN ELLINGER     MELVIN GONSALVEZ     RAYMOND YAN", wWidth / 2.0f, wHeight / 2.0f + 200);
	CP_Font_DrawText("CHRISTOPHER COMAIR    JOHN BAUER     JOHNNY DEEK", wWidth / 2.0f, wHeight / 2.0f + 250);
	CP_Font_DrawText("MICHAEL GATS     CHARLES DUBA", wWidth / 2.0f, wHeight / 2.0f + 300);

	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("WWW.DIGIPEN.EDU", wWidth / 2.0f, wHeight / 2.0f + 400);
	CP_Font_DrawText("All content 20XX DigiPen Institute of Technology Singapore. All Rights Reserved", wWidth / 2.0f, wHeight / 2.0f + 450);

	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Credits_3_Exit()
{
}
