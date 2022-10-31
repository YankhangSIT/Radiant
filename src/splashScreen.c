#include "cprocessing.h"
#include "utils.h"
#include "level1.h"
#include "stdio.h"
#include "splashScreen.h"
#include "mainmenu.h"

CP_Image digipen;
float TimeElapsed;
void splash_screen_init(float wWidth, float wHeight)
{
	//Set TimeElapsed to float 0
	//Load your image
	//Position your image to the corner of top left
	//Set the size according to your image size.
	TimeElapsed = 0.0f;
	digipen = CP_Image_Load("./Assets/DigiPen_BLACK.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(wWidth * 2.5, wWidth * 2);

	//set window size and center it
	CP_System_SetWindowSize(wWidth * 2.5, wWidth * 2);
	CP_Settings_RectMode(CP_POSITION_CENTER);	

}

void splash_screen_update(void)
{
	//Buffer time for splashscreen image & cursor creation
	TimeElapsed += CP_System_GetDt();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);

	float alphatime = 2;
	if (TimeElapsed >= alphatime)
	{
		TimeElapsed = 0;
	}
	float resulttime = (TimeElapsed / alphatime) * 255;
	CP_Image_Draw(digipen, 0, 0, CP_Image_GetWidth(digipen), CP_Image_GetHeight(digipen), (int)resulttime);

	if (CP_Input_KeyDown(KEY_ENTER)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}
void splash_screen_exit(void)
{
	//Image would be free from the memory running.
	CP_Image_Free(&digipen);
}