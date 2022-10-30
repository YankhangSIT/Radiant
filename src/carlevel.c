#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "movement.h"
#include "mainmenu.h"
#include "math.h"
#include "carlevel.h"
#include <stdlib.h>
#include "spawn.h"
#define PI (3.141592653589793)
#define SIZE (50)
//#define SPAWNSIZE (5)
#define FALSE (0)
#define TRUE (1)
#define SPAWNSIZE (5)
#define SPAWNINDEX (4)

//define struct for character
struct Character {
	CP_Vector Pos;
	CP_Color Color;
} character;


//Sprite Image
CP_Image gunPlayer;
CP_Image swordPlayer;

//
struct Enemy enemies[SIZE];
struct Enemy enemy;
CP_Vector spawnPositions[SPAWNINDEX][SPAWNSIZE];
//
int isPaused;


//extern int playerNum = 0;
//pre-define speed and i
//float speed = 210.0;
//float enemySpeed = 100.0;
int i = -1;
float elapsedTime;
float wWidth = 0;
float wHeight = 0;

float randFloat(float low, float high)
{
	return ((float)rand() / (float)RAND_MAX) * (high - low) + low;
}

void Car_Level_Init()
{
	//Set window width and height to variables
	wWidth = CP_System_GetWindowWidth();
	wHeight = CP_System_GetWindowHeight();

	enemy.enemySprite = CP_Image_Load("Assets/testEnemy.png");
	enemy.radius = 39;
	

	gunPlayer = CP_Image_Load("Assets/player1.png");
	swordPlayer = CP_Image_Load("Assets/player2.png");
	srand(1);
	//spawnEnemies(enemies, SPAWNSIZE, spawnPositions);

	for (int i = 0; i < SPAWNSIZE; ++i)
	{
		// set spawn positions for the 5 enemies in spawnPositions array index 0
		//which represents the top row enemies spawn positions
		spawnPositions[0][i] = CP_Vector_Set(randFloat(wWidth / 8, wWidth), wHeight / 7);
		enemies[i].pos.x = spawnPositions[0][i].x;
		enemies[i].pos.y = spawnPositions[0][i].y;				
	}

	for (int i = 0; i < SPAWNSIZE; ++i)
	{
		// set spawn positions for the 5 enemies in spawnPositions array index 1
		//which represents the left column enemies spawn position
		spawnPositions[1][i] = CP_Vector_Set(wWidth / 8, randFloat(wHeight, wHeight / 7));
		enemies[5+i].pos.x = spawnPositions[1][i].x;
		enemies[5+i].pos.y = spawnPositions[1][i].y;	
	}

	for (int i = 0; i < SPAWNSIZE; ++i)
	{
		// set spawn positions for the 5 enemies in spawnPositions array index 2
		//which represents the right column enemies spawn position
		spawnPositions[2][i] = CP_Vector_Set(wWidth -50, randFloat(wHeight, wHeight / 7));
		enemies[10+i].pos.x = spawnPositions[2][i].x;
		enemies[10+i].pos.y = spawnPositions[2][i].y;

	}

	/*for (int i = 0; i < SPAWNSIZE; i++)
	{
		spawnPositions[i] = CP_Vector_Set(wWidth /4, randFloat(wHeight ,wHeight / 7));
	}*/


	//set window size and center it
	CP_System_SetWindowSize(wWidth, wHeight);
	//enemy1.pos = CP_Vector_Set(0, wHeight / 5);
	//set position, colour and direction of the three cars (red, green, blue)
	character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	//Character.Color = CP_Color_Create(255, 0, 0, 255);
	//Char.Direction = 0.0f;

	//enemy1.Pos = CP_Vector_Set(50, 50);

	isPaused = FALSE;
}

void Car_Level_Update()
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 500, 1000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Paused", wWidth / 2.0f, wHeight / 2.0f - 300);


		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Resume", wWidth / 2.0f, wHeight / 2.0f - 200);

		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Restart", wWidth / 2.0f, wHeight / 2.0f - 50);

		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f +100 , 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Menu", wWidth / 2.0f, wHeight / 2.0f +100);

		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f +250, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Exit", wWidth / 2.0f, wHeight / 2.0f +250);


		isPaused = !isPaused;

	}

	if (CP_Input_MouseClicked() && isPaused)
	{
		
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			isPaused = !isPaused;
		}
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			isPaused = !isPaused;
			Car_Level_Init();
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f +250, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_Terminate();
		}

	}

	if (!isPaused)
	{ 
		//Spawn Enemies in the spawn positions defined by array index 0
		for (int i = 0; i < SPAWNSIZE; i++)
		{
			CP_Image_Draw(enemy.enemySprite, enemies[i].pos.x, enemies[i].pos.y, CP_Image_GetWidth(enemy.enemySprite), CP_Image_GetHeight(enemy.enemySprite), 255);
			enemies[i].pos = enemyMovement(character.Pos, enemies[i].pos);
		}
	
		//Spawn Enemies in the spawn positions defined by array index 1
		for (int i = 0; i < SPAWNSIZE; i++)
		{
			
			CP_Image_Draw(enemy.enemySprite, enemies[5+i].pos.x, enemies[5+i].pos.y, CP_Image_GetWidth(enemy.enemySprite), CP_Image_GetHeight(enemy.enemySprite), 255);
			enemies[5+i].pos = enemyMovement(character.Pos, enemies[5+i].pos);
		}

		
		//Spawn Enemies in the spawn positions defined by array index 2
		for (int i = 0; i < SPAWNSIZE; i++)
		{			
			CP_Image_Draw(enemy.enemySprite, enemies[10+i].pos.x, enemies[10+i].pos.y, CP_Image_GetWidth(enemy.enemySprite), CP_Image_GetHeight(enemy.enemySprite), 255);
			enemies[10 + i].pos = enemyMovement(character.Pos, enemies[10+i].pos);
		}
		

		if (playerNum == 1)
		{
			CP_Image_Draw(gunPlayer, character.Pos.x, character.Pos.y, CP_Image_GetWidth(gunPlayer), CP_Image_GetHeight(gunPlayer), 255);
		}

		if (playerNum == 2)
		{
			CP_Image_Draw(swordPlayer, character.Pos.x, character.Pos.y, CP_Image_GetWidth(swordPlayer), CP_Image_GetHeight(swordPlayer), 255);
		}

		//CLEAR BACKGROUND
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
		// updates character's positon based off WASD inputs. Function defined in movement.c
		character.Pos = charMovement(character.Pos);
		// updates enemy's positon based off character's position. Function defined in movement.c
		// enemy1[i].pos = enemyMovement(character.Pos, enemy1[i].pos);

		// check where character going out of bounds
		character.Pos = checkMapCollision(character.Pos, 0, wWidth, 0 , wHeight);

		// enemy obstruction
		for (int i = 0; i < (SPAWNSIZE * 3); ++i) {
			for (int j = 0; j < (SPAWNSIZE * 3); ++j) {
				if (i == j) continue;
				float xDistance = enemy1[i].pos.x - enemy1[j].pos.x;
				float yDistance = enemy1[i].pos.y - enemy1[j].pos.y;
				float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
				float toDisplace = 0.5 * distance - (enemy.radius * 2);

				if (distance < enemy.radius * 2) {
					float toDisplace = 0.5 * (distance - (enemy.radius * 2));
					enemy1[i].pos.x -= toDisplace * (xDistance) / distance;
					enemy1[i].pos.y -= toDisplace * (yDistance) / distance;

					enemy1[j].pos.x += toDisplace * (xDistance) / distance;
					enemy1[j].pos.y += toDisplace * (yDistance) / distance;
				
				}
			}
		}	
	}
}

void Car_Level_Exit()
{

}
