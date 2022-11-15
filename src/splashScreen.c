#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "stdio.h"
#include "splashScreen.h"
#include "mainmenu.h"
#include "loadingScreen.h"
//
CP_Image digipen;
float TimeElapsed;
int fadeout = FALSE;
void splash_screen_init()
{
	// Set TimeElapsed to float 0
	// Load your image
	// Position your image to the corner of top left
	// Set the size according to your image size.
	TimeElapsed = 0.0f;
	digipen = CP_Image_Load("Assets/DigiPen_BLACK.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_Fullscreen();
	CP_Settings_RectMode(CP_POSITION_CENTER);
}
//
void splash_screen_update(void)
{
	// Buffer time for splashscreen image & cursor creation
	TimeElapsed += CP_System_GetDt();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	float alphatime = 3;
	float resulttime = (TimeElapsed / alphatime) * 255; // Fade in formula

	if (fadeout == TRUE)
	{
		resulttime = 255 - (TimeElapsed / alphatime) * 255; // Fade out formula
		if (TimeElapsed >= alphatime) {
			CP_Engine_SetNextGameState(loading_Screen_Init, loading_Screen_Update, loading_Screen_Exit);
		}
	}

	if (TimeElapsed >= alphatime)
	{
		TimeElapsed = 0;
		fadeout = TRUE;
		alphatime = 3;
	}

	
	CP_Image_Draw(digipen, 0, 0, (float) CP_Image_GetWidth(digipen), (float)CP_Image_GetHeight(digipen), (int)resulttime); // Draw splashscreen image
}
void splash_screen_exit(void)
{
	// Image would be free from the memory running.
	CP_Image_Free(&digipen);
}