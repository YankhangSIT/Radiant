#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "mainmenu.h"
#include "math.h"

#define PI (3.141592653589793)

//define struct for car
struct Car {
	CP_Vector Pos;
	CP_Color Color;
	float Direction;
}; struct Car cars[3]; //make an array to store the 3 cars (red, green, blue)

typedef struct Enemy{
	CP_Vector pos;
	CP_Color Color;
	float height;
	float width;
	float direction;
	float speed;
}Enemy;



//pre-define speed and i
float speed = 350.0;
int i = -1;

void Car_Level_Init()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();

	//set window size and center it
	CP_System_SetWindowSize(wWidth, wHeight);

	//set position, colour and direction of the three cars (red, green, blue)
	cars[0].Pos = CP_Vector_Set(100.0f, 100.0f);
	cars[0].Color = CP_Color_Create(255, 0, 0, 255);
	cars[0].Direction = 0.0f;

	cars[1].Pos = CP_Vector_Set(300.0f, 100.0f);
	cars[1].Color = CP_Color_Create(0, 255, 0, 255);
	cars[1].Direction = 0.0f;

	cars[2].Pos = CP_Vector_Set(200.0f, 200.0f);
	cars[2].Color = CP_Color_Create(0, 0, 255, 255);
	cars[2].Direction = 0.0f;
}

void Car_Level_Update()
{
	//esc to close game
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//draw circles
	for (int x = 0; x < 3; x++) {
		CP_Settings_Fill(cars[x].Color);
		CP_Graphics_DrawCircle(cars[x].Pos.x, cars[x].Pos.y, 70.0f);
	}

	// draw triangles
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	for (int x = 0; x < 3; x++) {
		CP_Graphics_DrawTriangleAdvanced(cars[x].Pos.x + 35.0f, cars[x].Pos.y,
			cars[x].Pos.x - 20.0f, cars[x].Pos.y + 25.0f,
			cars[x].Pos.x - 20.0f, cars[x].Pos.y - 25.0f,
			cars[x].Direction);
	}

	//select car with mouse click
	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		for (int x = 0; x < 3; x++)
			if (IsCircleClicked(cars[x].Pos.x, cars[x].Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
				i = x;
			}
	}

	//using selected car, turn it left and right with A and D, move it forwards and backwards with W and S
	float dtSpeed = speed * CP_System_GetDt(); //define dt speed (350 units per second)
	CP_Vector direction = AngleToVector(cars[i].Direction * (PI / 180.0)); //change my direction angle to a vector
	CP_Vector norm = CP_Vector_Normalize(direction); //normalize my vector

	if (CP_Input_KeyDown(KEY_A)) {
		if (cars[i].Direction > 0) {
			cars[i].Direction -= 150 * CP_System_GetDt();
		}
		else {
			cars[i].Direction = 359; //prevent the angle from going <0 (0-359)
		}
	}
	else if (CP_Input_KeyDown(KEY_D)) {
		if (cars[i].Direction < 359) {
			cars[i].Direction += 150 * CP_System_GetDt();
		}
		else {
			cars[i].Direction = 0; //prevent the angle from going >359
		}
	}
	if (CP_Input_KeyDown(KEY_W)) {
		cars[i].Pos = CP_Vector_Add(cars[i].Pos, CP_Vector_Scale(norm, dtSpeed));
	}
	else if (CP_Input_KeyDown(KEY_S)) {
		cars[i].Pos = CP_Vector_Subtract(cars[i].Pos, CP_Vector_Scale(norm, dtSpeed));
	}
}

void Car_Level_Exit()
{

}
