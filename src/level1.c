#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "movement.h"
#include "combat.h"
#include "mainmenu.h"
#include "math.h"
#include "level1.h"
#include "spawn.h"
#include "map.h"

#include<stdbool.h>
#include<stdlib.h>
#define PI (3.141592653589793)
#define SIZE (1000)
//#define SPAWNSIZE (5)
#define FALSE (0)
#define TRUE (1)
#define SPAWNSIZE (5)
#define SPAWNINDEX (4)
#define MAX_LENGTH (100)
//define struct for character
struct Character {
	CP_Vector Pos;
	//CP_Color Color;
	float height;
	float width;
	CP_Image playerSprite;
	int playerType;
	int health;
	int energy;
	int invulState;
} character;

struct Character playerGun;
struct Character playerSword;

//Sprite Image
CP_Image gunPlayer;
CP_Image swordPlayer;

//
struct Enemy enemies[SIZE];
struct Enemy enemy;
CP_Vector spawnPositions[SPAWNINDEX][SPAWNSIZE];
//CP_Vector spawnPosition[];
//
int isPaused;


//extern int playerNum = 0;
//pre-define speed and i
//float speed = 210.0;
//float enemySpeed = 100.0;
int i = -1;
float elapsedTime;
float invulElapsedTime;
float energyRechargeTime;
float stunnedElapsedTime;
int healthChange;
float wWidth = 0;
float wHeight = 0;

//obstruction obj in map.h
Obstruction obs;
//triangle area for sword swing
Sword swordSwingArea;

// string array to use for text display
char timeString[MAX_LENGTH];
char characterHealthDisplay[MAX_LENGTH];
char characterEnergyDisplay[MAX_LENGTH];
// time variables
int min = 0;
float sec = 0;
// survive condition
int surviveMin = 1;
// win condition boolean
int win = 0;
float spawnTimer = 0.7f;
float startSpawnTimer;

int isCompleted = 0;
int spawnIndex = 0;
//Bullet Struct Contains all the properties of the bullet
struct Bullet {

	CP_Vector shootPosition;
	CP_Vector bulletPos;
	CP_Image bulletSprite;
	CP_Vector acceleration;
	CP_Vector directionBullet;
	float bulletSpeed;
	float width;
	float height;
};
struct Bullet bullet;


CP_Vector spawnPosition;
//float shootDirection;
void level_1_Init()
{
	CP_System_Fullscreen();
	bullet.bulletSpeed = 10;
	startSpawnTimer = spawnTimer;
	elapsedTime = 0;
	sec = 0;
	min = 0;
	spawnIndex = 0;
	//Set window width and height to variables
	wWidth = CP_System_GetWindowWidth();
	wHeight = CP_System_GetWindowHeight();

	//
	bullet.bulletSprite = CP_Image_Load("Assets/playerBullet.png");
	enemy.enemySprite = CP_Image_Load("Assets/testEnemy.png");
	enemy.radius = 39;
	bullet.width = CP_Image_GetWidth(bullet.bulletSprite);
	bullet.height = CP_Image_GetWidth(bullet.bulletSprite);
	//player sprite
	gunPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/player2.png");

	//enemy spawn 
	spawnPosition = CP_Vector_Set(0, 0);
	enemies[spawnIndex].pos.x = spawnPosition.x;
	enemies[spawnIndex].pos.y = spawnPosition.y;
	//enemy width and height
	enemy.width = CP_Image_GetWidth(enemy.enemySprite);
	enemy.height = CP_Image_GetHeight(enemy.enemySprite);

	// player type gun
	if (playerNum == 1)
	{
		character.playerSprite = gunPlayer;
		character.width = CP_Image_GetWidth(gunPlayer);
		character.height = CP_Image_GetWidth(gunPlayer);
	}

	// player type sword
	if (playerNum == 2)
	{
		character.playerSprite = swordPlayer;
		character.width = CP_Image_GetWidth(swordPlayer);
		character.height = CP_Image_GetWidth(swordPlayer);
	}
	//set position, colour and direction of the three cars (red, green, blue)
	character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	character.health = 5; // start with 5 hp
	character.energy = 5; // start with 5 energy
	character.invulState = 0; // start not invul
	invulElapsedTime = 0; // timer for invul
	energyRechargeTime = 0; // timer for energyRecharge
	stunnedElapsedTime = 0;

	//bullet start shoot spawn position
	bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2 + 20, character.Pos.y + character.health/2);
	isPaused = FALSE;


	//windowResolution = SetResolution(1920,1080);
	//  CP_System_SetWindowSize(windowResolution.width, windowResolution.height);
	//

	//initiate obstruction
	srand(56423);
	for (int i = 0; i < 3; i++) {
		float x = rand() % (int)((wWidth / 3 + 1) + (wWidth / 3));
		float y = rand() % (int)((wHeight / 3 + 1) + (wHeight / 3));
		obs.rec_block[i] = SetRect_(x, y, 100.f, 100.f);
	}

	swordSwingArea = SetSword(character.Pos.x, character.Pos.y, character.Pos.x + 80.f, character.Pos.y -80.f, character.Pos.x + 80.f, character.Pos.y + 80.f, 360.f);
}

void level_1_Update()
{

	if (min == surviveMin)
	{
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 500, 1000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("You survived Level 1!", wWidth / 2.0f, wHeight / 2.0f - 300);


		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Next Level", wWidth / 2.0f, wHeight / 2.0f - 200);

		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Restart", wWidth / 2.0f, wHeight / 2.0f - 50);

		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Menu", wWidth / 2.0f, wHeight / 2.0f + 100);

		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Exit", wWidth / 2.0f, wHeight / 2.0f + 250);

		win = TRUE;
		isPaused = TRUE;
	}


	if (CP_Input_KeyTriggered(KEY_ESCAPE) && win == FALSE)
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
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Menu", wWidth / 2.0f, wHeight / 2.0f + 100);

		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Exit", wWidth / 2.0f, wHeight / 2.0f + 250);

		isPaused = !isPaused;

	}

	if (CP_Input_MouseClicked() && isPaused)
	{

		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			if (win == FALSE)
			{
				isPaused = !isPaused;
			}

		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			//isPaused = !isPaused;	
			if (isPaused == TRUE)
			{
				win = FALSE;
				level_1_Init();
				isPaused = FALSE;
			}


		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			CP_Engine_Terminate();
		}
	}

	if (!isPaused)
	{
		elapsedTime = CP_System_GetDt();
		sec += elapsedTime;

		if (sec >= 60)
		{
			sec = 0;
			min++;
		}

		spawnTimer -= elapsedTime;

		sprintf_s(timeString, MAX_LENGTH, "%d:%.2f", min, sec);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText(timeString, wWidth / 2.0f, wHeight / 2.0f - 300);

		//to display character health
		sprintf_s(characterHealthDisplay, MAX_LENGTH, "%d", character.health);
		CP_Font_DrawText("Health:", 200, 200);
		CP_Font_DrawText(characterHealthDisplay, 260, 200);

		//to display character energy
		sprintf_s(characterEnergyDisplay, MAX_LENGTH, "%d", character.energy);
		CP_Font_DrawText("Energy:", 200, 230);
		CP_Font_DrawText(characterEnergyDisplay, 260, 230);

		bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2 + 20, character.Pos.y + character.height / 2);

		if (character.energy > 0) {
			if (CP_Input_MouseClicked()) {
				CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
				bullet.directionBullet = CP_Vector_Subtract(mouseClickPos, bullet.shootPosition);
				bullet.bulletPos = bullet.shootPosition;

				// energy deplete function
				character.energy = energyDeplete(character.energy);
			}
		}
		
		bullet.acceleration = CP_Vector_Scale(bullet.directionBullet, bullet.bulletSpeed * elapsedTime);
		bullet.bulletPos = CP_Vector_Add(bullet.bulletPos, bullet.acceleration);
		CP_Image_Draw(bullet.bulletSprite, bullet.bulletPos.x, bullet.bulletPos.y, bullet.width, bullet.height, 255);


		if (min < surviveMin)//!isCompleted)
		{

			if (spawnTimer <= 0)
			{
				spawnPosition = CP_Vector_Set(CP_Random_RangeFloat(wWidth / 8, wWidth), wHeight / 7);
				enemies[spawnIndex].pos.x = spawnPosition.x;
				enemies[spawnIndex].pos.y = spawnPosition.y;
				spawnIndex++;
				spawnTimer = startSpawnTimer;
			}

		}
		
		//CP_Image_Draw(enemy.enemySprite, enemies[0].pos.x, enemies[0].pos.y, enemy.width, enemy.height, 255);
		//enemies[0].pos = enemyMovement(character.Pos, enemies[0].pos);


		for (int i = 0; i < spawnIndex; i++)
		{
			//Enemy Render
			CP_Image_Draw(enemy.enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemy.width, enemy.height, 255);
			enemies[i].pos = enemyMovement(character.Pos, enemies[i].pos);
		}

	
		// Player Render
		if (playerNum == 1)
		{
			CP_Image_Draw(gunPlayer, character.Pos.x, character.Pos.y, character.width, character.height, 255);
		}

		if (playerNum == 2)
		{
			CP_Image_Draw(swordPlayer, character.Pos.x, character.Pos.y, character.width, character.height, 255);
		}

		//CLEAR BACKGROUND
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

		//draw obstruction
		CP_Settings_Fill(CP_Color_Create(5, 50, 250, 255));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		for (int i = 0; i < 3; i++) {

			CP_Graphics_DrawRect(obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height);

		}
		//draw sword swing area
		swordSwingArea = UpdateSwordSwing(swordSwingArea, character.Pos , character.width, character.height);
		CP_Settings_Fill(CP_Color_Create(5, 50, 250, 255));
		CP_Graphics_DrawTriangleAdvanced(swordSwingArea.x1, swordSwingArea.y1, swordSwingArea.x2, swordSwingArea.y2, swordSwingArea.x3, swordSwingArea.y3, swordSwingArea.degrees);

		
		// updates enemy's positon based off character's position. Function defined in movement.c
		// enemy1[i].pos = enemyMovement(character.Pos, enemy1[i].pos);

			// check for obstructions
		for (int i = 0; i < 3; i++) {

			character.Pos = checkObsCollision(character.Pos, character.width, character.height, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height);

		}


		// check where character going out of bounds
		character.Pos = checkMapCollision(character.Pos, 0, wWidth - character.width, 0, wHeight - character.height);




		// enemy obstruction
		for (int i = 0; i < (spawnIndex); ++i) {
			for (int j = 0; j < (spawnIndex * 3); ++j) {
				if (i == j) continue;
				float xDistance = enemies[i].pos.x - enemies[j].pos.x;
				float yDistance = enemies[i].pos.y - enemies[j].pos.y;
				float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
				float toDisplace = 0.5 * distance - (enemy.radius * 2);

				if (distance < enemy.radius * 2) {
					float toDisplace = 0.5 * (distance - (enemy.radius * 2));
					enemies[i].pos.x -= toDisplace * (xDistance) / distance;
					enemies[i].pos.y -= toDisplace * (yDistance) / distance;

					enemies[j].pos.x += toDisplace * (xDistance) / distance;
					enemies[j].pos.y += toDisplace * (yDistance) / distance;

				}
			}
		}
		/*
		for (int i = 0; i < (spawnIndex); ++i) {
			for (int j = 0; j < (spawnIndex * 3); ++j) {
				if (i == j) continue;
				float xDistance = enemies[i].pos.x - enemies[j].pos.x;
				float yDistance = enemies[i].pos.y - enemies[j].pos.y;
				float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
				float toDisplace = 0.5 * distance - (enemy.radius * 2);

				if (distance < enemy.radius * 2) {
					float toDisplace = 0.5 * (distance - (enemy.radius * 2));
					enemies[i].pos.x -= toDisplace * (xDistance) / distance;
					enemies[i].pos.y -= toDisplace * (yDistance) / distance;

					enemies[j].pos.x += toDisplace * (xDistance) / distance;
					enemies[j].pos.y += toDisplace * (yDistance) / distance;

				}
			}
		}
		*/

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1) { // if not invul, check for damage (collision with mobs) every frame
			for (int i = 0; i < spawnIndex; i++)
			{
				if (checkDamage(character.Pos, character.width, character.height, enemies[i].pos, enemy.width, enemy.height) == 1) {
					if (healthChange == 0) {
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}

		}

		// if character is invulnerable, don't take damage
		if (character.invulState == 1) { // if invul, it will last for 2 seconds (2000 ms)
			invulElapsedTime += elapsedTime;

			if (invulElapsedTime >= 2) { // if invul for more than 2 seconds, go back to being vul
				character.invulState = 0;
				invulElapsedTime = 0;
			}
		}

		// updates character's positon based off WASD inputs. Function defined in movement.c
		if (character.energy > 0) {
			character.Pos = charMovement(character.Pos , gunPlayer); // character movement
			gunPlayer = charImage(gunPlayer); // changes character sprite based on which direction he is facing
		}

		if (character.energy < 5) {
			energyRechargeTime += elapsedTime;

			if (energyRechargeTime >= 3) { // if stunned for more than 2 seconds, go back to being unstunned
				++character.energy;
				energyRechargeTime = 0;
			}
		}
	}
}

void level_1_Exit()
{

}
