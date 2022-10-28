#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "movement.h"
#include "mainmenu.h"
#include "math.h"
#include "carlevel.h"
#include <stdlib.h>
#define PI (3.141592653589793)
#define SIZE (50)
#define SPAWNSIZE (5)
#define FALSE (0)
#define TRUE (1)
//define struct for character
struct Character {
	CP_Vector Pos;
	CP_Color Color;
} character;

struct Enemy {
	CP_Vector pos;
	CP_Color Color;
	CP_Image enemySprite;
	float Height;
	float Width;
	float Direction;
	float Speed;
};

CP_Image gunPlayer;
CP_Image swordPlayer;
struct Enemy enemy1[SIZE];
struct Enemy enemy;
CP_Vector spawnPositions[SPAWNSIZE];
CP_Vector spawnPositions2[SPAWNSIZE];
CP_Vector spawnPositions3[SPAWNSIZE];
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

	enemy.enemySprite = CP_Image_Load("../Assets/testEnemy.png");
	

	gunPlayer = CP_Image_Load("../Assets/player1.png");
	swordPlayer = CP_Image_Load("../Assets/player2.png");
	srand(1);
	//randFloat(wHeight / 3, wHeight)

	for (int i = 0; i < SPAWNSIZE; ++i)
	{
		
		spawnPositions[i] = CP_Vector_Set(randFloat(wWidth / 8, wWidth), wHeight / 7);
		enemy1[i].pos.x = spawnPositions[i].x;
		enemy1[i].pos.y = spawnPositions[i].y;
	//	printf("Spawn: %f %f\n", spawnPositions[i].x, spawnPositions[i].y);
	//	printf("Spawn Enemy: %f %f\n", enemy1[i].pos.x, enemy1[i].pos.y);
		
				
	}

	for (int i = 0; i < SPAWNSIZE; ++i)
	{
		spawnPositions2[i] = CP_Vector_Set(wWidth / 8, randFloat(wHeight, wHeight / 7));
		enemy1[5+i].pos.x = spawnPositions2[i].x;
		enemy1[5+i].pos.y = spawnPositions2[i].y;
		//printf("Spawn Enemy: %f %f\n", enemy1[i].pos.x , enemy1[i].pos.y) ;
		
	}

	for (int i = 0; i < SPAWNSIZE; ++i)
	{
		spawnPositions3[i] = CP_Vector_Set(wWidth -50, randFloat(wHeight, wHeight / 7));
		enemy1[9+i].pos.x = spawnPositions3[i].x;
		enemy1[9+i].pos.y = spawnPositions3[i].y;

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
		// @DARREN PLEASE CHANGE THIS SO THAT THE ENEMY.POS IS INTIATED IN THE INIT() AND NOT UPDATE() SO THE ENEMIES WILL MOVE TOWARDS THE CHARACTER.
		for (int i = 0; i < SPAWNSIZE; i++)
		{
			CP_Image_Draw(enemy.enemySprite, enemy1[i].pos.x, enemy1[i].pos.y, CP_Image_GetWidth(enemy.enemySprite), CP_Image_GetHeight(enemy.enemySprite), 255);
			enemy1[i].pos = enemyMovement(character.Pos, enemy1[i].pos);
		}

		

		for (int i = 0; i < SPAWNSIZE; i++)
		{
			
			CP_Image_Draw(enemy.enemySprite, enemy1[5+i].pos.x, enemy1[5+i].pos.y, CP_Image_GetWidth(enemy.enemySprite), CP_Image_GetHeight(enemy.enemySprite), 255);
			enemy1[5+i].pos = enemyMovement(character.Pos, enemy1[5+i].pos);
		}

		//

		for (int i = 0; i < SPAWNSIZE; i++)
		{			
			CP_Image_Draw(enemy.enemySprite, enemy1[9+i].pos.x, enemy1[9+i].pos.y, CP_Image_GetWidth(enemy.enemySprite), CP_Image_GetHeight(enemy.enemySprite), 255);
			enemy1[9 + i].pos = enemyMovement(character.Pos, enemy1[9 + i].pos);
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
		//enemy1[i].pos = enemyMovement(character.Pos, enemy1[i].pos);

		//check where character going out of bounds
		character.Pos = checkMapCollision(character.Pos, 0, wWidth, 0 , wHeight);
		//CP_Vector vectorBetween = checkEnemyCollision(enemy1[1].pos, enemy1[2].pos, 100.f);
		//enemy1[2].pos.x = enemy1[2].pos.x * (vectorBetween.x * 0.5);
		//enemy1[2].pos.y = enemy1[2].pos.y * (vectorBetween.y * 0.5);
		//enemy1[1].pos.x = enemy1[1].pos.x * (vectorBetween.x * -0.5); 
		//enemy1[1].pos.y = enemy1[1].pos.y * (vectorBetween.y * -0.5);
	}
}

void Car_Level_Exit()
{

}
