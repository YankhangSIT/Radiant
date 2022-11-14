#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "movement.h"
#include "combat.h"
#include "mainmenu.h"
#include "math.h"
#include "level2.h"
#include "spawn.h"
#include "map.h"
#include <stdbool.h>
#include <stdlib.h>
#include "button.h"
#include "gameOverpage.h"
#include "global.h"

// define struct for character

/// CAN PUT IN .H FILE
struct Character playerGun;
struct Character playerSword;

// Sprite Image
CP_Image gunPlayer;
CP_Image swordPlayer;

/// CAN PUT IN .H FILE

int isPaused;
float elapsedTime;
float invulElapsedTime;
float energyRechargeTime;
float stunnedElapsedTime;
int healthChange;
float wWidth;
float wHeight;
/// WHY???
// int i = -1;

// obstruction obj in map.h
Obstruction obs;
// triangle area for sword swing
Sword swordSwingArea;
float swordSwingTime;
bool swingSword;
int *characterFacing;
CP_Image swordSwingSprite1;
CP_Image swordSwingSprite2;

// string array to use for text display
char timeString[MAX_LENGTH];
char characterHealthDisplay[MAX_LENGTH];
char characterEnergyDisplay[MAX_LENGTH];
// time variables

// Bullet Struct Contains all the properties of the bullet

CP_Image map_background;
void level_2_Init()
{
	CP_System_Fullscreen();
	delayShootTime = 0.1f;
	delayShootStart = delayShootTime;
	delayShootTime = delayShootStart;
	// CP_System_SetWindowSize(1000, 1000);
	bullet.bulletSpeed = 1000;
	spawnTimer = 1.f;
	startSpawnTimer = spawnTimer;
	bulletSpawnIndex = 0;
	elapsedTime = 0;
	surviveMin = 1;
	sec = 0;
	min = 0;
	firstDrop = 0;
	spawnIndex = 0;
	firstShoot = 0;
	dropIndex = 0;
	lose = 0;
	canShoot = 0;
	win = 0;
	;
	// Set window width and height to variables
	wWidth = CP_System_GetWindowWidth();
	wHeight = CP_System_GetWindowHeight();
	map_background = CP_Image_Load("Assets/map_background.png");
	/// CP_System_SetWindowSize(wWidth, wHeight);
	healthDrop.dropSprite = CP_Image_Load("Assets/healthDrop.png");
	bullet.bulletSprite = CP_Image_Load("Assets/playerBullet.png");
	// enemy.enemySprite = CP_Image_Load("Assets/enemy1.png");
	enemySprite1 = CP_Image_Load("Assets/enemy1.png");
	enemySprite2 = CP_Image_Load("Assets/Monster_2.png");
	damagedSprite1 = CP_Image_Load("Assets/enemy1Damaged.png");
	damagedSprite2 = CP_Image_Load("Assets/Monster_2_Damaged.png");
	dropHealthSprite = CP_Image_Load("Assets/healthDrop.png");
	dropEnergySprite = CP_Image_Load("Assets/batteryDrop.png");
	swordSwingSprite1 = CP_Image_Load("Assets/sword_swing.png");
	swordSwingSprite2 = CP_Image_Load("Assets/sword_swing2.png");

	enemy.radius = 39;
	bullet.width = CP_Image_GetWidth(bullet.bulletSprite);
	bullet.height = CP_Image_GetWidth(bullet.bulletSprite);
	// player sprite
	gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");

	// enemy spawn
	spawnPosition = CP_Vector_Set(0, 0);

	enemies[spawnIndex].pos.x = spawnPosition.x;
	enemies[spawnIndex].pos.y = spawnPosition.y;
	itemDrop[dropIndex].pos.x = spawnPosition.x;
	itemDrop[dropIndex].pos.y = spawnPosition.y;
	// enemy width and height
	// enemy.width = CP_Image_GetWidth(enemy.enemySprite);
	// enemy.height = CP_Image_GetHeight(enemy.enemySprite);
	enemy.speed = 70;
	healthDrop.width = CP_Image_GetWidth(healthDrop.dropSprite);
	healthDrop.height = CP_Image_GetHeight(healthDrop.dropSprite);

	// player type gun
	if (playerNum == 1)
	{
		character.playerSprite = gunPlayer;
		character.width = CP_Image_GetWidth(gunPlayer);
		character.height = CP_Image_GetHeight(gunPlayer);
		// canShoot = 1;
	}

	// player type sword
	if (playerNum == 2)
	{
		character.playerSprite = swordPlayer;
		character.width = CP_Image_GetWidth(swordPlayer);
		character.height = CP_Image_GetHeight(swordPlayer);
		canShoot = 0;
	}

	character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	character.health = 5;	  // start with 5 hp
	character.energy = 5;	  // start with 5 energy
	character.invulState = 0; // start not invul
	character.speed = 210;
	invulElapsedTime = 0;	// timer for invul
	energyRechargeTime = 0; // timer for energyRecharge
	stunnedElapsedTime = 0;

	// bullet start shoot spawn position
	bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2 + 20, character.Pos.y + character.health / 2);

	bulletArray[bulletSpawnIndex].bulletPos = bullet.shootPosition;

	isPaused = FALSE;
	printf("paused screen state init lv2 %d", isPaused);
	// initiate obstruction
	for (int i = 0, x = 0, y = 0; i < 6; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth / 4 + x, wHeight / 4 + y, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction1.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction1.png")), CP_Image_Load("Assets/obstruction1.png"));
		y += obs.rec_block[i].height;
		if (i == 2)
		{
			x = obs.rec_block[i].width;
			y = 0;
		}
	}
	// obstruction surrounding the jet
	obs.rec_block[6] = SetRect_(940, 277, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction3.png")) * 2, CP_Image_GetHeight(CP_Image_Load("Assets/obstruction3.png")), CP_Image_Load("Assets/obstruction3.png"));
	obs.rec_block[7] = SetRect_(1240, 277, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction3.png")) * 2, CP_Image_GetHeight(CP_Image_Load("Assets/obstruction3.png")), CP_Image_Load("Assets/obstruction3.png"));
	obs.rec_block[8] = SetRect_(990, 347, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction2.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction2.png")) * 2, CP_Image_Load("Assets/obstruction2.png"));
	obs.rec_block[9] = SetRect_(1090, 347, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction2.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction2.png")) * 2, CP_Image_Load("Assets/obstruction2.png"));
	obs.rec_block[10] = SetRect_(1190, 347, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction2.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction2.png")) * 2, CP_Image_Load("Assets/obstruction2.png"));
	obs.rec_block[11] = SetRect_(990, 207, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction2.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction2.png")) * 2, CP_Image_Load("Assets/obstruction2.png"));
	obs.rec_block[12] = SetRect_(1090, 207, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction2.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction2.png")) * 2, CP_Image_Load("Assets/obstruction2.png"));
	obs.rec_block[13] = SetRect_(1190, 207, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction2.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction2.png")) * 2, CP_Image_Load("Assets/obstruction2.png"));

	// obstruction surrounding the planet
	for (int i = 14, x = 195, y = 128; i < 32; i++)
	{
		obs.rec_block[i] = SetRect_(x, y, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction1.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction1.png")), CP_Image_Load("Assets/obstruction1.png"));
		x += 60;
		if (i == 22)
		{
			y = 667;
			x = 195;
		}
	}
	for (int i = 32, x = 128, y = 128; i < obstructionCount; i++)
	{
		obs.rec_block[i] = SetRect_(x, y, CP_Image_GetWidth(CP_Image_Load("Assets/obstruction1.png")), CP_Image_GetHeight(CP_Image_Load("Assets/obstruction1.png")), CP_Image_Load("Assets/obstruction1.png"));
		y += 60;
	}
	swordSwingArea = SetSword(character.Pos.x - (character.width * 3) / 2, character.Pos.y, character.width * 3, character.height * 2.5);
	swordSwingTime = 0;
	swingSword = false;
	characterFacing = 0;
}

void level_2_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (min == surviveMin || lose == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 500, 1000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		if (lose == 0)
		{
			CP_Font_DrawText("You survived Level 2!", wWidth / 2.0f, wHeight / 2.0f - 300);
			Button("Next level", wWidth / 2.0f, wHeight / 2.0f - 200, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);
			Button("Restart", wWidth / 2.0f, wHeight / 2.0f - 50, wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);

			Button("Menu", wWidth / 2.0f, wHeight / 2.0f + 100, wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);

			Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 250, wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		}
		else
		{

			CP_Engine_SetNextGameState(game_Over_page_init, game_Over_page_update, game_Over_page_exit);
			/*CP_Font_DrawText("You died!", wWidth / 2.0f, wHeight / 2.0f - 300);
			Button("Restart", wWidth / 2.0f, wHeight / 2.0f - 50, wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);

			Button("Menu", wWidth / 2.0f, wHeight / 2.0f + 50, wWidth / 2.0f, wHeight / 2.0f + 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);

			Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 200, wWidth / 2.0f, wHeight / 2.0f + 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		*/
		}

		// Button("Next level", wWidth / 2.0f, wHeight / 2.0f - 200, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		if (lose == 0)
		{
			win = TRUE;
		}
		isPaused = TRUE;
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE) && win == FALSE)
	{
		isPaused = !isPaused;
	}

	if (isPaused && win == FALSE)
	{
		printf("paused screen state  lv2 %d", isPaused);
		// CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 500, 1000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Paused", wWidth / 2.0f, wHeight / 2.0f - 300);

		Button("Resume", wWidth / 2.0f, wHeight / 2.0f - 200, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		//	Button("Resume", wWidth / 2.0f, wHeight / 2.0f - 200, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		Button("Restart", wWidth / 2.0f, wHeight / 2.0f - 50, wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		Button("Menu", wWidth / 2.0f, wHeight / 2.0f + 100, wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);

		Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 250, wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, 0, 255, 0, 0, 0, 0, 255);
	}

	if (CP_Input_MouseClicked() && isPaused)
	{

		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (lose == 0)
		{
			if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
			{
				if (win == FALSE)
				{
					delayShootTime = delayShootStart;

					isPaused = !isPaused;
				}
			}
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			// isPaused = !isPaused;
			if (isPaused == TRUE)
			{
				printf("paused state win lv2 %d", isPaused);
				win = FALSE;
				clear();
				level_2_Init();
			}
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			clear();
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			clear();
			CP_Engine_Terminate();
		}
	}

	if (!isPaused)
	{
		CP_Settings_ImageMode(CP_POSITION_CENTER);
		CP_Image_Draw(map_background, wWidth / 2.0f, wHeight / 2.0f, wWidth, wHeight, 255);
		elapsedTime = CP_System_GetDt();
		sec += elapsedTime;

		if (sec >= 60)
		{
			sec = 0;
			min++;
		}

		if (playerNum == 1)
		{
			canShoot = 0;
			if (delayShootTime > 0.f)
			{
				delayShootTime -= elapsedTime;
			}
			else if (delayShootTime < 0.f)
			{
				canShoot = 1;
			}
		}

		spawnTimer -= elapsedTime;

		sprintf_s(timeString, MAX_LENGTH, "%d:%.2f", min, sec);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText(timeString, wWidth / 2.0f, wHeight / 2.0f - 300);

		// to display character health
		sprintf_s(characterHealthDisplay, MAX_LENGTH, "%d", character.health);
		CP_Font_DrawText("Health:", 200, 200);
		CP_Font_DrawText(characterHealthDisplay, 260, 200);

		// to display character energy
		sprintf_s(characterEnergyDisplay, MAX_LENGTH, "%d", character.energy);
		CP_Font_DrawText("Energy:", 200, 230);
		CP_Font_DrawText(characterEnergyDisplay, 260, 230);

		// bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2 + 20, character.Pos.y + character.height / 2);
		bullet.shootPosition = CP_Vector_Set(character.Pos.x, character.Pos.y);

		if (character.energy > 0)
		{
			if (CP_Input_MouseClicked() && canShoot == 1)
			{
				CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
				if (firstShoot == 1)
				{
					++bulletSpawnIndex;
				}
				bulletArray[bulletSpawnIndex].directionBullet = CP_Vector_Subtract(mouseClickPos, bullet.shootPosition);
				bulletArray[bulletSpawnIndex].bulletPos = bullet.shootPosition;
				bulletArray[bulletSpawnIndex].normalizedDirection = CP_Vector_Normalize(bulletArray[bulletSpawnIndex].directionBullet);
				firstShoot = 1;

				// energy deplete function
				character.energy = energyDeplete(character.energy);
			}
		}

		for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
		{
			bulletArray[i].acceleration = CP_Vector_Scale(bulletArray[i].normalizedDirection, bullet.bulletSpeed * elapsedTime);
			bulletArray[i].bulletPos = CP_Vector_Add(bulletArray[i].bulletPos, bulletArray[i].acceleration);
			if (firstShoot == 1)
			{
				CP_Image_Draw(bullet.bulletSprite, bulletArray[i].bulletPos.x, bulletArray[i].bulletPos.y, bullet.width, bullet.height, 255);
				// printf("Drawing %d", bulletSpawnIndex);
			}
		}

		if (min < surviveMin) //! isCompleted)
		{

			if (spawnTimer <= 0)
			{
				spawnPosition = CP_Vector_Set(CP_Random_RangeFloat(wWidth / 8, wWidth), wHeight / 7);
				enemies[spawnIndex].pos.x = spawnPosition.x;
				enemies[spawnIndex].pos.y = spawnPosition.y;
				randomId = CP_Random_RangeInt(1, 2);
				enemies[spawnIndex].id = randomId;

				spawnIndex++;

				spawnTimer = startSpawnTimer;
			}
		}

		for (int i = 0; i < spawnIndex; i++)
		{
			// Enemy Render

			if (enemies[i].id == 1)
			{
				enemies[i].enemySprite = enemySprite1;
				enemies[i].width = CP_Image_GetWidth(enemies[i].enemySprite);
				enemies[i].height = CP_Image_GetHeight(enemies[i].enemySprite);
				enemies[i].health = 1;
			}
			else if (enemies[i].id == 2)
			{
				enemies[i].enemySprite = enemySprite2;
				enemies[i].width = CP_Image_GetWidth(enemies[i].enemySprite);
				enemies[i].height = CP_Image_GetHeight(enemies[i].enemySprite);
				enemies[i].health = 2;
			}
			// else if (enemies[i].id == 3)
			//{
			//	enemies[i].enemySprite = enmySprite3;
			//}

			// printf("%d\n", enemies[i].id);

			CP_Image_Draw(enemies[i].enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemies[i].width, enemies[i].height, 255);

			// CP_Image_Draw(enemy.enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemy.width, enemy.height, 255);
			enemies[i].pos = enemyMovement(character.Pos, enemies[i].pos, enemy.speed);
			for (int o = 0; o < obstructionCount; o++)
			{
				// check for obstructions
				enemies[i].pos = checkObsCollision(enemies[i].pos, enemies[i].width, enemies[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height);
			}

			//! sword swing attack enemy TO DO!!
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && swordSwingEnemey(swordSwingArea, enemies[i].pos, enemies[i].radius))
			{
				printf("sword hits enemy !!! yay \n");
			}
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

		// CLEAR BACKGROUND

		for (int i = 0; i < obstructionCount; i++)
		{
			// draw obstruction
			CP_Image_Draw(obs.rec_block[i].spriteImage, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height, 255);
			// check for obstructions
			character.Pos = checkObsCollision(character.Pos, character.width, character.height, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height);
		}
		//! draw sword swing area
		swordSwingArea = UpdateSwordSwing(swordSwingArea, character.Pos, character.width, character.height);
		CP_Settings_Fill(CP_Color_Create(222, 123, 11, 120));
		CP_Graphics_DrawRect(swordSwingArea.x, swordSwingArea.y, swordSwingArea.width, swordSwingArea.height);

		// check where character going out of bounds
		character.Pos = checkMapCollision(character.Pos, character.width / 2, wWidth - character.width / 2, character.height / 2, wHeight - character.height / 2);
		// check if projectile out of bounds, if so, delete it.
		for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
		{
			if (checkProjectileMapCollision(bulletArray[i].bulletPos, 0 + bullet.width / 2, wWidth - bullet.width / 2, 0 + bullet.height / 2, wHeight - bullet.height / 2) == 1)
			{
				for (int x = i; x - 1 < bulletSpawnIndex; ++x)
				{
					bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
				}
				bulletSpawnIndex--;
			}
		}

		// enemy obstruction
		for (int i = 0; i < (spawnIndex); ++i)
		{
			for (int j = 0; j < (spawnIndex); ++j)
			{
				if (i == j)
					continue;
				float xDistance = enemies[i].pos.x - enemies[j].pos.x;
				float yDistance = enemies[i].pos.y - enemies[j].pos.y;
				float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
				float toDisplace = 0.5 * distance - (enemy.radius * 2);

				if (distance < enemy.radius * 2)
				{
					float toDisplace = 0.5 * (distance - (enemy.radius * 2));
					enemies[i].pos.x -= toDisplace * (xDistance) / distance;
					enemies[i].pos.y -= toDisplace * (yDistance) / distance;

					enemies[j].pos.x += toDisplace * (xDistance) / distance;
					enemies[j].pos.y += toDisplace * (yDistance) / distance;
				}
			}
		}

		// enemies die to bullets
		/// for (int i = 1; i -1 < bulletSpawnIndex; ++i)
		for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
		{ // darren's way of implementing bullet spawn for loop
			for (int j = 0; j < (spawnIndex); ++j)
			{
				float xDistance = bulletArray[i].bulletPos.x - enemies[j].pos.x;

				float yDistance = bulletArray[i].bulletPos.y - enemies[j].pos.y;
				float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
				// printf("distance is %f\n", ddistance);

				for (int o = 0; o < obstructionCount; o++)
				{
					if (checkProjectileObsCollision(bulletArray[i].bulletPos, bulletArray[i].width, bulletArray[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height))
					{
						// check for obstructions
						for (int x = i; x - 1 < bulletSpawnIndex; ++x)
						{
							bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
																 // more info: https://codeforwin.org/2015/07/c-program-to-delete-element-from-array.html
						}
					}
				}
				if (distance < enemies[j].width * 2)
				{
					printf("enemy health before: %d", enemies[j].health);
					//--enemies[j].health;
					printf("enemy health after: %d", enemies[j].health);
					enemies[j].isDead = 1;
					unsigned int randomRate = CP_Random_RangeInt(1, 5);
					unsigned int dropId = CP_Random_RangeInt(1, 2);
					itemDrop[dropIndex].itemId = dropId;

					if (randomRate == 2 && enemies[j].isDead)
					{

						itemDrop[dropIndex].dropTrue = 1;

						if (itemDrop[dropIndex].itemId == 1)
						{
							itemDrop[dropIndex].dropSprite = dropHealthSprite;
							itemDrop[dropIndex].width = CP_Image_GetWidth(itemDrop[i].dropSprite);
							itemDrop[dropIndex].height = CP_Image_GetHeight(itemDrop[i].dropSprite);
						}
						else if (itemDrop[dropIndex].itemId == 2)
						{
							itemDrop[dropIndex].dropSprite = dropEnergySprite;
							itemDrop[dropIndex].width = CP_Image_GetWidth(itemDrop[i].dropSprite);
							itemDrop[dropIndex].height = CP_Image_GetHeight(itemDrop[i].dropSprite);
						}

						itemDrop[dropIndex].pos.x = enemies[j].pos.x;
						itemDrop[dropIndex].pos.y = enemies[j].pos.y;
						++dropIndex;
					}
					// if (enemies[j].isDead)
					for (int x = i; x - 1 < bulletSpawnIndex; ++x)
					{
						bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
															 // more info: https://codeforwin.org/2015/07/c-program-to-delete-element-from-array.html
					}
					for (int y = j; y < spawnIndex; ++y)
					{
						enemies[y] = enemies[y + 1]; // similar to above^
					}

					--bulletSpawnIndex, --spawnIndex;
					//}
				}
			}
		}

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			for (int i = 0; i < spawnIndex; i++)
			{
				if (checkDamage(character.Pos, character.width, character.height, enemies[i].pos, enemies[i].width, enemies[i].height) == 1)
				{
					if (healthChange == 0)
					{
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}

		// if character is invulnerable, don't take damage
		if (character.invulState == 1)
		{ // if invul, it will last for 2 seconds (2000 ms)
			invulElapsedTime += elapsedTime;

			if (invulElapsedTime >= 2)
			{ // if invul for more than 2 seconds, go back to being vul
				character.invulState = 0;
				invulElapsedTime = 0;
			}
		}

		// updates character's positon based off WASD inputs. Function defined in movement.c
		if (character.energy > 0)
		{
			character.Pos = charMovement(character.Pos, character.speed); // character movement
			if (playerNum == 1)
				gunPlayer = charImageRanged(gunPlayer, character.Pos);
			else if (playerNum == 2)
				swordPlayer = charImageMelee(swordPlayer, character.Pos, *characterFacing); // changes character sprite based on which direction he is facing
		}

		if (character.energy < 5)
		{
			energyRechargeTime += elapsedTime;

			if (energyRechargeTime >= 3)
			{ // if stunned for more than 2 seconds, go back to being unstunned
				++character.energy;
				energyRechargeTime = 0;
			}
		}

		for (int i = 0; i < dropIndex; ++i)
		{
			if (itemDrop[i].dropTrue == 1)
			{
				CP_Image_Draw(itemDrop[i].dropSprite, itemDrop[i].pos.x, itemDrop[i].pos.y, itemDrop[i].width, itemDrop[i].height, 255);
			}
		}

		if (character.health <= 0)
		{
			lose = 1;
		}
		else
		{
			lose = 0;
		}
	}
}

void level_2_Exit()
{
}
