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
#include <stdbool.h>
#include <stdlib.h>
#include "button.h"
#include "gameOverpage.h"
#include "global.h"

struct Character playerGun;
struct Character playerSword;

// Sprite Image
CP_Image gunPlayer;
CP_Image swordPlayer;

int isPaused;
float elapsedTime;
float invulElapsedTime;
float invulTransparencyTime;
float energyRechargeTime;
float stunnedElapsedTime;
int healthChange;
float wWidth;
float wHeight;

// obstruction obj in map.h
Obstruction obs;
float obsWidth4;
float obsHeight4;
float obsWidth5;
float obsHeight5;
float obsWidth6;
float obsHeight6;
float stunnedWidth;
float stunnedHeight;
// triangle area for sword swing
Sword swordSwingArea;
float swordSwingTime;
bool swingSword;
int characterFacing;
// string array to use for text display
char timeString[MAX_LENGTH];
char characterHealthDisplay[MAX_LENGTH];
char characterEnergyDisplay[MAX_LENGTH];

CP_Image map_background;
CP_Image swordSwingSprite1;
CP_Image swordSwingSprite2;
CP_Image stunned;
CP_Image hpPickup;
CP_Image energyPickup;
CP_Image obstruction1;
CP_Image obstruction2;
CP_Image obstruction3;

void level_2_Init()
{
	// CP_System_Fullscreen();
	delayShootTime = 0.1f;
	delayShootStart = delayShootTime;
	delayShootTime = delayShootStart;
	CP_System_FullscreenAdvanced(1920, 1080);
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
	level = 2;
	changeSpawnTimer = 0.1f;
	startSpawnChangeTimer = changeSpawnTimer;
	direction = 2;
	// Set window width and height to variables
	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();
	map_background = CP_Image_Load("Assets/map_background2.png");
	bullet.bulletSprite = CP_Image_Load("Assets/playerBullet.png");
	enemySprite1 = CP_Image_Load("Assets/enemy1.png");
	enemySprite2 = CP_Image_Load("Assets/Monster_2.png");
	damagedSprite1 = CP_Image_Load("Assets/enemy1Damaged.png");
	damagedSprite2 = CP_Image_Load("Assets/Monster_2_Damaged.png");

	dropHealthSprite = CP_Image_Load("Assets/healthDrop.png");
	dropEnergySprite = CP_Image_Load("Assets/batteryDrop.png");
	swordSwingSprite1 = CP_Image_Load("Assets/sword_swing.png");
	swordSwingSprite2 = CP_Image_Load("Assets/sword_swing2.png");
	CP_Image obstruction4 = CP_Image_Load("Assets/obstruction4.png");
	CP_Image obstruction5 = CP_Image_Load("Assets/obstruction5.png");
	CP_Image obstruction6 = CP_Image_Load("Assets/obstruction6.png");
	enemy.radius = 39;
	bullet.width = (float)CP_Image_GetWidth(bullet.bulletSprite);
	bullet.height = (float)CP_Image_GetWidth(bullet.bulletSprite);
	// player sprite
	gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");
	hpPickup = CP_Image_Load("Assets/hp_pickup_animation.png");
	energyPickup = CP_Image_Load("Assets/energy_pickup_animation.png");
	obsWidth4 = (float)CP_Image_GetWidth(obstruction4);
	obsHeight4 = (float)CP_Image_GetHeight(obstruction4);
	obsWidth5 = (float)CP_Image_GetWidth(obstruction5);
	obsHeight5 = (float)CP_Image_GetHeight(obstruction5);
	obsWidth6 = (float)CP_Image_GetWidth(obstruction6);
	obsHeight6 = (float)CP_Image_GetHeight(obstruction6);
	// set spawn positions to 0 coordinate
	spawnPosition = CP_Vector_Set(0, 0);
	enemies[spawnIndex].pos.x = spawnPosition.x;
	enemies[spawnIndex].pos.y = spawnPosition.y;
	itemDrop[dropIndex].pos.x = spawnPosition.x;
	itemDrop[dropIndex].pos.y = spawnPosition.y;
	enemy.speed = 70;

	// player type gun
	if (playerNum == 1)
	{
		character.playerSprite = gunPlayer;
		character.width = (float)CP_Image_GetWidth(gunPlayer);
		character.height = (float)CP_Image_GetHeight(gunPlayer);
	}

	// player type sword
	if (playerNum == 2)
	{
		character.playerSprite = swordPlayer;
		character.width = (float)CP_Image_GetWidth(swordPlayer);
		character.height = (float)CP_Image_GetHeight(swordPlayer);
		canShoot = 0;
	}

	character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	character.health = 5;	  // start with 5 hp
	character.energy = 5;	  // start with 5 energy
	character.invulState = 0; // start not invul
	character.speed = 210;
	character.transparency = 255; // opaque initially, will be translucent in invul state
	invulElapsedTime = 0;		  // timer for invul
	energyRechargeTime = 0;		  // timer for energyRecharge
	stunnedElapsedTime = 0;

	// bullet start shoot spawn position
	bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2 + 20, character.Pos.y + character.health / 2);

	bulletArray[bulletSpawnIndex].bulletPos = bullet.shootPosition;

	isPaused = FALSE;

	// initiate obstruction
	obs.rec_block[obstructionCount1 + 1] = SetRect_(wWidth * 2.3 / 4, wHeight * 1.3 / 4, obsWidth4 * 1.8, obsHeight4 * 1.8, obstruction4);
	for (int i = obstructionCount1 + 2, x = 0; i < 107; i++)
	{
		obs.rec_block[i] = SetRect_(wWidth * 1 / 8 + x, wHeight * 2 / 4, obsWidth6 * 0.8, obsHeight6 * 0.8, obstruction6);
		x += obsWidth6;
	}
	for (int i = 107, x = 0; i < 110; i++)
	{
		obs.rec_block[i] = SetRect_(wWidth * 4.5 / 5 + x, wHeight * 7 / 8, obsWidth6 * 0.8, obsHeight6 * 0.8, obstruction6);
		x -= obsWidth6;
	}
	for (int i = 110, x = 0, y = 0; i < 116; i++)
	{
		obs.rec_block[i] = SetRect_(wWidth * 2.3 / 3 + x, wHeight * 1 / 2 + y, obsWidth6 * 0.8, obsHeight6 * 0.8, obstruction6);
		x += obsWidth6;
		if (i == 112)
		{
			x = 0;
			y += obsHeight6;
		}
	}
	for (int i = 116, x = 0, y = 0; i < 128; i++)
	{
		obs.rec_block[i] = SetRect_(wWidth * 1 / 16 + x, wHeight * 1.3 / 2 + y, obsWidth5, obsHeight5 * 0.7, obstruction5);
		x += obsWidth5;
		if (i == 117 || i == 121)
		{
			x = 0;
			y += obsHeight5 * 0.7;
		}
	}
	for (int i = 128, x = 0, y = 0; i < 132; i++)
	{
		obs.rec_block[i] = SetRect_(wWidth * 1 / 3 + x, wHeight * 0.8 / 2 + y, obsWidth5, obsHeight5 * 0.7, obstruction5);
		x += obsWidth5;
		y += obsHeight5 * 0.7 + 80.f;
	}
	for (int i = 132, x = 0, y = 0; i < 135; i++)
	{
		obs.rec_block[i] = SetRect_(wWidth * 0.5 / 4 + x, wHeight * 0.5 / 3, obsWidth5, obsHeight5 * 0.7, obstruction5);
		x += obsWidth5 * 2;
	}
	for (int i = 135, x = 0, y = 0; i < 147; i++)
	{
		obs.rec_block[i] = SetRect_(wWidth * 2.4 / 3 + x, wHeight * 1 / 8 + y, obsWidth5, obsHeight5 * 0.7, obstruction5);
		if (i < 139)
			x += obsWidth5;
		if (i == 140 || i == 141)
		{
			y += obs.rec_block[i].height;
		}
		if (i > 141)
			x -= obsWidth5;
	}

	swordSwingArea = SetSword(character.Pos.x - (character.width * 3) / 2, character.Pos.y, character.width * 3.f, character.height * 2.5f);
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
		//	printf("paused screen state  lv2 %d", isPaused);
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
			if (win == TRUE)
			{
				if (IsAreaClicked(nextLevel.pos.x, nextLevel.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
				{
					delayShootTime = delayShootStart;

					clear();
					printf("next Level");
					// level_2_Init();
					CP_Engine_SetNextGameState(level_3_Init, level_3_Update, level_3_Exit);

					// printf("pause  state win lv1 %d", isPaused);
				}
			}

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
				//	printf("paused state win lv2 %d", isPaused);
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
			// prevent the player from shooting immediately when resuming, restarting or when entering the game
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
		// keeps spawning until the player survives
		if (min < surviveMin)
		{
			changeSpawnTimer -= elapsedTime;
			// printf("change spawntimer %f\n" , changeSpawnTimer);
			if (changeSpawnTimer <= 0)
			{
				changeSpawnTimer = startSpawnChangeTimer;
			}
		}

		// check if spawn timer
		if (spawnTimer <= 0)
		{

			// set random spawn position based on width and height of the screen
			if (direction == 1)
			{
				spawnPosition = CP_Vector_Set(CP_Random_RangeFloat(wWidth / 8, wWidth), wHeight / 7);
			}
			else if (direction == 2)
			{
				spawnPosition = CP_Vector_Set(wWidth / 8, CP_Random_RangeFloat(wHeight / 7, wHeight));
			}
			else if (direction == 3)
			{
				spawnPosition = CP_Vector_Set(wWidth - 200, CP_Random_RangeFloat(wHeight / 7, wWidth));
			}
			else if (direction == 4)
			{
				spawnPosition = CP_Vector_Set(CP_Random_RangeFloat(wWidth / 8, wWidth), wHeight - 200);
			}
			// set spawn position of enemy
			enemies[spawnIndex].pos.x = spawnPosition.x;
			enemies[spawnIndex].pos.y = spawnPosition.y;
			// enemies[spawnIndex].isDead = 0;
			//  add one to enemy count and set spawn index to 1 for the enemy
			spawnIndex++;
			// restart spawn time
			spawnTimer = startSpawnTimer;
		}

		// spawn as much items as there are spawn index which represent the number of enemies as well as the enemy spawn index
		for (int i = 0; i < spawnIndex; i++)
		{
			randomId = CP_Random_RangeInt(1, 2);
			enemies[spawnIndex].id = randomId;
			if (enemies[spawnIndex].id == 1)
			{
				// set enemy with this id to the respective sprite
				enemies[spawnIndex].enemySprite = enemySprite1;
				// set the width and height to the respective sprite
				enemies[spawnIndex].width = (float)CP_Image_GetWidth(enemies[(int)spawnIndex].enemySprite);
				enemies[spawnIndex].height = (float)CP_Image_GetHeight(enemies[(int)spawnIndex].enemySprite);
				// set health for the enemy id number
				enemies[spawnIndex].health = 1;
			}
			else if (enemies[spawnIndex].id == 2)
			{
				// set enemy with this id to the respective sprite
				enemies[spawnIndex].enemySprite = enemySprite2;
				// set the width and height to the respective sprite
				enemies[spawnIndex].width = (float)CP_Image_GetWidth(enemies[(int)spawnIndex].enemySprite);
				enemies[spawnIndex].height = (float)CP_Image_GetHeight(enemies[(int)spawnIndex].enemySprite);
				// set health for the enemy id number
				enemies[spawnIndex].health = 2;
			}

			// enemy movement
			enemies[i].pos = enemyMovement(character.Pos, enemies[i].pos, enemy.speed);

			for (int o = obstructionCount1 + 1; o < obstructionCount2; o++)
			{
				// check for obstructions
				enemies[i].pos = checkObsCollision(enemies[i].pos, enemies[i].width, enemies[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height);
			}
		}

		if (playerNum == 1)
		{ // IF RANGED CHAR
			bullet.shootPosition = CP_Vector_Set(character.Pos.x, character.Pos.y);

			// SHOOT PROJECTILE MECHANIC
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
			}

			// check if projectile out of bounds, if so, delete it.
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				if (checkProjectileMapCollision(bulletArray[i].bulletPos, 0 + bullet.width / 2, wWidth - bullet.width / 2, 0 + bullet.height / 2, wHeight - bullet.height / 2) == 1)
				{
					for (int x = i; x - 1 < bulletSpawnIndex; ++x)
					{
						bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
					}
					--bulletSpawnIndex;
				}
			}

			// enemies die to bullets
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				for (int j = 0; j < (spawnIndex); ++j)
				{
					float xDistance = bulletArray[i].bulletPos.x - enemies[j].pos.x;
					float yDistance = bulletArray[i].bulletPos.y - enemies[j].pos.y;
					float distance = (float)sqrt(pow(xDistance, 2) + pow(yDistance, 2));

					// enemies die to bullets
					if (distance < enemies[j].width && enemies[j].health > 0 && firstShoot == 1)
					{ // less than bullet radius x2
						// decrease health after collision
						--enemies[j].health;
						// activate take damge effect
						enemies[j].takeDamage = 1.0f;

						// randomize spawn rate from 1 to 3
						unsigned int randomRate = CP_Random_RangeInt(1, 3);
						// randomly set drop id between 1 or 2
						unsigned int dropId = CP_Random_RangeInt(1, 2);

						itemDrop[dropIndex].itemId = dropId;

						if (randomRate == 2 && enemies[j].health <= 0)
						{

							itemDrop[dropIndex].dropTrue = 1;
							// check item drop's id by the spawn index of the drop
							if (itemDrop[dropIndex].itemId == 1)
							{
								// if item's id is 1 set the item's dropSprite to the dropHealthSprite
								itemDrop[dropIndex].dropSprite = dropHealthSprite;
								// set the width and height to the respective sprite
								itemDrop[dropIndex].width = (float)CP_Image_GetWidth(itemDrop[(int)dropIndex].dropSprite);
								itemDrop[dropIndex].height = (float)CP_Image_GetHeight(itemDrop[(int)dropIndex].dropSprite);
							}
							else if (itemDrop[dropIndex].itemId == 2)
							{
								// if items's id is 2 set the item's dropSprite to the dropEnergySprite
								itemDrop[dropIndex].dropSprite = dropEnergySprite;
								// set the width and height to the respective sprite
								itemDrop[dropIndex].width = (float)CP_Image_GetWidth(itemDrop[(int)dropIndex].dropSprite);
								itemDrop[dropIndex].height = (float)CP_Image_GetHeight(itemDrop[(int)dropIndex].dropSprite);
							}
							// set item with the drop index to the enemy coordinate
							itemDrop[dropIndex].pos.x = enemies[j].pos.x;
							itemDrop[dropIndex].pos.y = enemies[j].pos.y;
							++dropIndex;
						}

						// deletion of projectile after hitting enemy
						for (int x = i; x - 1 < bulletSpawnIndex; ++x)
						{
							bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
																 // more info: https://codeforwin.org/2015/07/c-program-to-delete-element-from-array.html
						}
						--bulletSpawnIndex;

						if (enemies[j].health <= 0)
						{
							for (int y = j; y < spawnIndex; ++y)
							{
								enemies[y] = enemies[y + 1];
							}
							--spawnIndex;
						}
					}
				}
			}

			// BULLETS DISAPPEAR WHEN COLLIDING WITH OBSTRUCTIONS
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				for (int o = obstructionCount1 + 1; o < obstructionCount2; o++)
				{ // check if projectile hits obstructions, if so, delete it.
					if (checkProjectileObsCollision(bulletArray[i].bulletPos, bulletArray[i].width, bulletArray[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height))
					{
						// check for obstructions
						for (int x = i; x - 1 < bulletSpawnIndex; ++x)
						{
							bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
																 // more info: https://codeforwin.org/2015/07/c-program-to-delete-element-from-array.html
						}
						--bulletSpawnIndex;
					}
				}
			}
		}

		if (playerNum == 2)
		{ // MELEE CHAR
			if (character.energy > 0)
			{
				if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
				{
					swingSword = true;
				}
				for (int i = 0; i < spawnIndex; i++)
				{ // SWORD SWING
					if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && swordSwingEnemey(swordSwingArea, enemies[i].pos, enemies[i].radius))
					{
						--enemies[i].health;
						enemies[i].takeDamage = 1.0f;
						unsigned int randomRate = CP_Random_RangeInt(1, 4);
						// randomly set drop id between 1 or 2
						unsigned int dropId = CP_Random_RangeInt(1, 2);
						itemDrop[dropIndex].itemId = dropId;
						if (randomRate == 2 && enemies[i].health <= 0)
						{

							itemDrop[dropIndex].dropTrue = 1;
							// check item drop's id by the spawn index of the drop
							if (itemDrop[dropIndex].itemId == 1)
							{
								// if item's id is 1 set the item's dropSprite to the dropHealthSprite
								itemDrop[dropIndex].dropSprite = dropHealthSprite;
								// set the width and height to the respective sprite
								itemDrop[dropIndex].width = (float)CP_Image_GetWidth(itemDrop[(int)dropIndex].dropSprite);
								itemDrop[dropIndex].height = (float)CP_Image_GetHeight(itemDrop[(int)dropIndex].dropSprite);
							}
							else if (itemDrop[dropIndex].itemId == 2)
							{
								// if item's id is 2 set the item's dropSprite to the dropEnergySprite
								itemDrop[dropIndex].dropSprite = dropEnergySprite;
								// set the width and height to the respective sprite
								itemDrop[dropIndex].width = (float)CP_Image_GetWidth(itemDrop[(int)dropIndex].dropSprite);
								itemDrop[dropIndex].height = (float)CP_Image_GetHeight(itemDrop[(int)dropIndex].dropSprite);
							}
							// set item with the drop index to the enemy coordinate
							itemDrop[dropIndex].pos.x = enemies[i].pos.x;
							itemDrop[dropIndex].pos.y = enemies[i].pos.y;
							++dropIndex;
						}

						if (enemies[i].health <= 0)
						{
							for (int y = i; y < spawnIndex; ++y)
							{
								enemies[y] = enemies[y + 1]; // similar to above^
							}

							--spawnIndex;
						}
					}
				}
				if (CP_Input_MouseClicked())
				{
					character.energy = energyDeplete(character.energy);
				}
			}
			if (swingSword)
			{
				swordSwingTime += elapsedTime;
				if (swordSwingTime > 0)
				{
					if (characterFacing)
						CP_Image_Draw(swordSwingSprite1, swordSwingArea.x, swordSwingArea.y, (float)CP_Image_GetWidth(swordSwingSprite1), (float)CP_Image_GetHeight(swordSwingSprite1), 255);
					else
						CP_Image_Draw(swordSwingSprite2, swordSwingArea.x, swordSwingArea.y, (float)CP_Image_GetWidth(swordSwingSprite2), (float)CP_Image_GetHeight(swordSwingSprite2), 255);
					if (swordSwingTime > 0.2)
					{
						swordSwingTime = 0;
						swingSword = false;
					}
				}
			}

			// update sword swing area to follow character position
			swordSwingArea = UpdateSwordSwing(swordSwingArea, character.Pos, character.width, character.height);
		}

		// check player collision with obstruction
		for (int i = obstructionCount1 + 1; i < obstructionCount2; i++)
		{
			// draw obstruction
			CP_Image_Draw(obs.rec_block[i].spriteImage, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height, 255);
			// check for obstructions
			character.Pos = checkObsCollision(character.Pos, character.width, character.height, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height);
		}

		// check where character going out of bounds
		character.Pos = checkMapCollision(character.Pos, character.width / 2, wWidth - character.width / 2, character.height / 2, wHeight - character.height / 2);

		// enemy obstruction
		for (int i = 0; i < (spawnIndex); ++i)
		{
			for (int j = 0; j < (spawnIndex); ++j)
			{
				if (i == j)
					continue;
				float xDistance = enemies[i].pos.x - enemies[j].pos.x;
				float yDistance = enemies[i].pos.y - enemies[j].pos.y;
				float distance = (float)sqrt(pow(xDistance, 2) + pow(yDistance, 2));
				float toDisplace = 0.5f * distance - (enemies[j].width);

				if (distance < enemies[j].width)
				{
					float toDisplace = 0.5f * (distance - (enemies[j].width));
					enemies[i].pos.x -= toDisplace * (xDistance) / distance;
					enemies[i].pos.y -= toDisplace * (yDistance) / distance;

					enemies[j].pos.x += toDisplace * (xDistance) / distance;
					enemies[j].pos.y += toDisplace * (yDistance) / distance;
				}
			}
		}

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i < spawnIndex; i++)
			{
				if (checkDamage(character.Pos, character.width, character.height, enemies[i].pos, (enemies[i].width / 2)) == 1 && enemies[i].health > 0)
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

		// pickup items
		for (int i = 0; i < dropIndex; ++i)
		{ // itemDrop[dropIndex]
			if (checkDamage(character.Pos, character.width, character.height, itemDrop[i].pos, itemDrop[i].width, itemDrop[i].height) == 1)
			{
				if (itemDrop[i].itemId == 1) // health drop
				{
					++character.health;
					CP_Image_Draw(hpPickup, character.Pos.x, character.Pos.y - 55, (float)CP_Image_GetWidth(hpPickup), (float)CP_Image_GetHeight(hpPickup), 255);
				}
				else if (itemDrop[i].itemId == 2) // health drop
				{
					++character.energy;
					CP_Image_Draw(energyPickup, character.Pos.x, character.Pos.y - 55, (float)CP_Image_GetWidth(energyPickup), (float)CP_Image_GetHeight(energyPickup), 255);
				}

				for (int y = i; y < dropIndex; ++y)
				{
					itemDrop[y] = itemDrop[y + 1]; // similar to above^
				}
				--dropIndex;
			}
		}

		// if character is invulnerable, don't take damage
		if (character.invulState == 1)
		{
			invulElapsedTime += elapsedTime;

			if (invulElapsedTime >= 2)
			{ // if invul for more than 2 seconds, go back to being vul
				character.invulState = 0;
				invulElapsedTime = 0;
			}
			// will character will flicker to represent invulnerability
			invulTransparencyTime += elapsedTime;
			if (invulTransparencyTime >= 0.2f)
			{
				if (character.transparency == 255)
				{
					character.transparency = 100;
					invulTransparencyTime = 0;
				}
				else if (character.transparency == 100)
				{
					character.transparency = 255;
					invulTransparencyTime = 0;
				}
			}
		}

		// updates character's positon based off WASD inputs. Function defined in movement.c
		if (character.energy > 0)
		{
			character.Pos = charMovement(character.Pos, character.speed); // character movement
			if (playerNum == 1)
				gunPlayer = charImageRanged(gunPlayer, character.Pos);
			else if (playerNum == 2)
				swordPlayer = charImageMelee(swordPlayer, character.Pos, &characterFacing); // changes character sprite based on which direction he is facing
		}

		// recharge energy if < 5
		if (character.energy < 5)
		{
			energyRechargeTime += elapsedTime;

			if (energyRechargeTime >= 3)
			{ // if stunned for more than 2 seconds, go back to being unstunned
				++character.energy;
				energyRechargeTime = 0;
			}

			if (character.energy < 1)
			{ // draw stunned animation
				CP_Image_Draw(stunned, character.Pos.x, character.Pos.y - 55, (float)CP_Image_GetWidth(stunned), (float)CP_Image_GetHeight(stunned), 255);
			}
		}

		// enemy damaged sprite + draw enemies
		for (int i = 0; i < spawnIndex; i++)
		{
			// check any enemies that take damage
			if (enemies[i].takeDamage == 1.0f)
			{
				if (enemies[i].id == 1)
				{
					// change enemy sprite with id 1 to the  damagedSprite1
					enemies[i].enemySprite = damagedSprite1;
					CP_Image_Draw(enemies[i].enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemies[i].width, enemies[i].height, 255);
				}
				else if (enemies[i].id == 2)
				{
					// change enemy sprite with id 2 to the  damagedSprite1
					enemies[i].enemySprite = damagedSprite2;
					CP_Image_Draw(enemies[i].enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemies[i].width, enemies[i].height, 255);
				}
				enemies[i].takeDamage -= elapsedTime;
			}
			else
			{
				if (enemies[i].id == 1)
				{
					enemies[i].enemySprite = enemySprite1;
				}
				else if (enemies[i].id == 2)
				{
					enemies[i].enemySprite = enemySprite2;
				}
			}
			// only draw enemies that are alive
			if (enemies[i].health > 0)
			{
				CP_Image_Draw(enemies[i].enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemies[i].width, enemies[i].height, 255);
			}
		}

		// if char dies
		if (character.health <= 0)
		{
			lose = 1;
		}
		else
		{
			lose = 0;
		}

		// draw player
		if (playerNum == 1)
		{
			CP_Image_Draw(gunPlayer, character.Pos.x, character.Pos.y, character.width, character.height, character.transparency);

			// draw projectile
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				if (firstShoot == 1)
				{
					CP_Image_Draw(bullet.bulletSprite, bulletArray[i].bulletPos.x, bulletArray[i].bulletPos.y, bullet.width, bullet.height, 255);
				}
			}
		}
		if (playerNum == 2)
		{
			CP_Image_Draw(swordPlayer, character.Pos.x, character.Pos.y, character.width, character.height, character.transparency);
		}

		for (int i = 0; i < dropIndex; ++i)
		{
			// check if any item drop is set to true
			if (itemDrop[i].dropTrue == 1)
			{
				CP_Image_Draw(itemDrop[i].dropSprite, itemDrop[i].pos.x, itemDrop[i].pos.y, itemDrop[i].width, itemDrop[i].height, 255);
			}
		}

		// display timer
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
	}
}

void level_2_Exit()
{
}
