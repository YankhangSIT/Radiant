#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "mainmenu.h"
#include "math.h"

#define PI (3.141592653589793)
#define SIZE (2)
#define SPAWNSIZE (5)
#define FALSE (0)
#define TRUE (1)
//define struct for car
struct Character {
	CP_Vector Pos;
	CP_Color Color;
	//float Direction;
} Character; //struct Car cars[3]; //make an array to store the 3 cars (red, green, blue)

struct Enemy {
	CP_Vector pos;
	CP_Color Color;
	float height;
	float width;
	float direction;
	float speed;
};


struct Enemy enemies[SIZE];
CP_Vector spawnPositions[SPAWNSIZE];
int isPaused;

//pre-define speed and i
float speed = 210.0;
int i = -1;
float elapsedTime;

void Car_Level_Init()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();

	//set window size and center it
	CP_System_SetWindowSize(wWidth, wHeight);

	//set position, colour and direction of the three cars (red, green, blue)
	Character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	Character.Color = CP_Color_Create(255, 0, 0, 255);
	//Char.Direction = 0.0f;

	isPaused = FALSE;
}

void Car_Level_Update()
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		isPaused = isPaused;

	}

	//esc to close game
	/*if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}*/

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	/*draw circles
	for (int x = 0; x < 3; x++) {
		CP_Settings_Fill(cars[x].Color);
		CP_Graphics_DrawCircle(cars[x].Pos.x, cars[x].Pos.y, 70.0f);
	}
	*/

	CP_Settings_Fill(Character.Color);
	CP_Graphics_DrawCircle(Character.Pos.x, Character.Pos.y, 70.0f);

	/* draw triangles
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	for (int x = 0; x < 3; x++) {
		CP_Graphics_DrawTriangleAdvanced(cars[x].Pos.x + 35.0f, cars[x].Pos.y,
			cars[x].Pos.x - 20.0f, cars[x].Pos.y + 25.0f,
			cars[x].Pos.x - 20.0f, cars[x].Pos.y - 25.0f,
			cars[x].Direction);
	}
	*/

	/*select car with mouse click
	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		for (int x = 0; x < 3; x++)
			if (IsCircleClicked(cars[x].Pos.x, cars[x].Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
				i = x;
			}
	}
	*/

	//using selected car, turn it left and right with A and D, move it forwards and backwards with W and S

	//CP_Vector direction = AngleToVector(cars[i].Direction * (PI / 180.0)); //change my direction angle to a vector
	//CP_Vector norm = CP_Vector_Normalize(direction); //normalize my vector
	float dtSpeed = speed * CP_System_GetDt(); //define dt speed (350 units per second)

	if (CP_Input_KeyDown(KEY_A)) {
		Character.Pos.x -= dtSpeed;
	}
	else if (CP_Input_KeyDown(KEY_D)) {
		Character.Pos.x += dtSpeed;
	}
	if (CP_Input_KeyDown(KEY_W)) {
		Character.Pos.y -= dtSpeed;
	}
	else if (CP_Input_KeyDown(KEY_S)) {
		Character.Pos.y += dtSpeed;
	}
}

void Car_Level_Exit()
{

}
