#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "movement.h"
#include "combat.h"
#include "mainmenu.h"
#include "math.h"
#include "level4.h"
#include "spawn.h"
#include "map.h"
#include <stdbool.h>
#include <stdlib.h>
#include "button.h"
#include "gameOverpage.h"
#include "global.h"
#include "sound.h"

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
float obsWidth7;
float obsHeight7;
float obsWidth8;
float obsHeight8;
float obsWidth9;
float obsHeight9;
float stunnedWidth;
float stunnedHeight;

// area for sword swing
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
CP_Image obstruction7;
CP_Image obstruction8;
CP_Image obstruction9;

void level_4_Init()
{
	clear();
	// CP_System_Fullscreen();
	delayShootTime = 0.1f;
	delayShootStart = delayShootTime;
	delayShootTime = delayShootStart;
	CP_System_FullscreenAdvanced(1920, 1080);
	bullet.bulletSpeed = 1000;
	bossBullet.bulletSpeed = 50;
	spawnTimer = 1.7f;

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
	win = 0;
	canShoot = 0;
	level = 4;
	changeSpawnTimer = 0.1f;
	startSpawnChangeTimer = changeSpawnTimer;
	direction = 1;
	// Set window width and height to variables
	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();
	map_background = CP_Image_Load("Assets/map_background3.png");
	bullet.bulletSprite = CP_Image_Load("Assets/playerBullet.png");
	bossBullet.bulletSprite = CP_Image_Load("Assets/playerBullet.png");

	enemySprite1 = CP_Image_Load("Assets/enemy1.png");

	dropShieldSprite = CP_Image_Load("Assets/Shield_Drop.png");
	dropEnergySprite = CP_Image_Load("Assets/batteryDrop.png");
	swordSwingSprite1 = CP_Image_Load("Assets/sword_swing.png");
	swordSwingSprite2 = CP_Image_Load("Assets/sword_swing2.png");
	CP_Image obstruction7 = CP_Image_Load("Assets/obstruction7.png");
	CP_Image obstruction8 = CP_Image_Load("Assets/obstruction8.png");
	CP_Image obstruction9 = CP_Image_Load("Assets/obstruction9.png");
	bullet.width = (float)CP_Image_GetWidth(bullet.bulletSprite);
	bullet.height = (float)CP_Image_GetHeight(bullet.bulletSprite);
	// player sprite
	gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");
	stunned = CP_Image_Load("Assets/stunned_animation.png");
	hpPickup = CP_Image_Load("Assets/hp_pickup_animation.png");
	energyPickup = CP_Image_Load("Assets/energy_pickup_animation.png");
	char_energy = CP_Image_Load("Assets/Char_Energy.png"); ///
	char_health = CP_Image_Load("Assets/Char_Health.png"); /// removed drop health sprite

	bossSprite = CP_Image_Load("Assets/Final_boss.png");
	// set spawn positions to 0 coordinate
	spawnPosition = CP_Vector_Set(0, 0);

	enemies[spawnIndex].pos.x = spawnPosition.x;
	enemies[spawnIndex].pos.y = spawnPosition.y;
	itemDrop[dropIndex].pos.x = spawnPosition.x;
	itemDrop[dropIndex].pos.y = spawnPosition.y;

	
	// enemy width and height
	enemy.width = (float)CP_Image_GetWidth(enemySprite1) - 2.f;	  // 2.0 for polishing purposes
	enemy.height = (float)CP_Image_GetHeight(enemySprite1) - 2.f; // 2.0 for polishing purposes
	enemy.speed = 70;
	healthDrop.width = (float)CP_Image_GetWidth(healthDrop.dropSprite);
	healthDrop.height = (float)CP_Image_GetHeight(healthDrop.dropSprite);

	nextLevel.pos.x = wWidth / 2.0f;
	nextLevel.pos.y = wHeight / 2.0f - 200;
	// player type gun
	if (playerNum == 1)
	{
		character.playerSprite = gunPlayer;
		character.width = (float)CP_Image_GetWidth(gunPlayer);
		character.height = (float)CP_Image_GetHeight(gunPlayer);
		// canShoot = 1;
	}

	// player type sword
	if (playerNum == 2)
	{
		character.playerSprite = swordPlayer;
		character.width = (float)CP_Image_GetWidth(swordPlayer);
		character.height = (float)CP_Image_GetHeight(swordPlayer);
		canShoot = 0;
	}

	bossBulletIndex = 0;
	
	bossBullet.width = (float)CP_Image_GetWidth(bossBullet.bulletSprite);
	bossBullet.height = (float)CP_Image_GetHeight(bossBullet.bulletSprite);
	boss.enemySprite = bossSprite;
	boss.pos = CP_Vector_Set(wWidth / 2, wHeight/6);
	boss.width = (float) CP_Image_GetWidth(bossSprite);
	boss.height = (float) CP_Image_GetHeight(bossSprite);
	bossShootTimer = 0.5f;
	startBossShootTimer = bossShootTimer;
	bossBullet.shootPosition = CP_Vector_Set(boss.pos.x, boss.pos.y);
	bossBullet.shootPosition2 = CP_Vector_Set(boss.pos.x, boss.pos.y);
	bossBullet.shootPosition3 = CP_Vector_Set(boss.pos.x, boss.pos.y);
	bossShoot = 0;
	changeAttackTimer = 5.f;
	startChangeTimer = changeAttackTimer;
	attackMode = 1;


	firstShoot = 0;
	directionAngle = 0;
	rotationSpeed = 2000.f;

	character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	character.health = 5;				// start with 5 hp
	character.energy = 5;				// start with 5 energy
	character.invulState = 0;			// start not invul
	character.shieldedState = 0;		///
	character.unlimitedEnergyState = 0; ///
	character.speed = 210;
	character.transparency = 255; // opaque initially, will be translucent in invul state
	invulElapsedTime = 0;		  // timer for invul
	invulTransparencyTime = 0;
	energyRechargeTime = 0;		  // timer for energyRecharge
	stunnedElapsedTime = 0;
	shieldedDuration = 0;		 ///
	unlimitedEnergyDuration = 0; ///

	// bullet start shoot spawn position
	bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2.f + 20, character.Pos.y + character.health / 2.f);

	bulletArray[bulletSpawnIndex].bulletPos = bullet.shootPosition;

	bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
	bossBulletArray2[bossBulletIndex].bulletPos = bossBullet.shootPosition2;
	bossBulletArray3[bossBulletIndex].bulletPos = bossBullet.shootPosition3;
	firstShoot = 0;

	isPaused = FALSE;



	// initiate obstruction
	// initiate obstruction
	for (int i = obstructionCount2 + 1, x = 0, y = 0; i < 160; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth * 1 / 10 + x, wHeight * 1 / 2 + y, obsWidth9, obsHeight9 * 0.5, obstruction9);
		x += obs.rec_block[i].width;
		if (i == 153)
		{
			x = 0;
			y += obs.rec_block[i].height * 2;
		}
	}
	for (int i = 160, x = 0, y = 0; i < 176; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth * 1.1 / 2 + x, wHeight * 1 / 2 + y, obsWidth8, obsHeight8, obstruction8);
		x += obs.rec_block[i].width;
		if (i == 167)
		{
			x = 0;
			y -= obs.rec_block[i].height * 3;
		}
	}
	for (int i = 176, x = 0, y = 0; i < 183; i++)
	{

		obs.rec_block[i] = SetRect_(obsWidth7 * 1.5 + x, wHeight * 0.8 / 3 + y, obsWidth7, obsHeight7, obstruction7);
		if (i < 180)
			x += obs.rec_block[i].width;
		if (i >= 180)
		{
			y -= obs.rec_block[i].height;
		}
	}
	for (int i = 183, y = 0; i < 186; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth * 5 / 6, wHeight * 1.3 / 2 + y, obsWidth7, obsHeight7, obstruction7);
		y += obs.rec_block[i].height;
	}

	// melee character swing sword area check
	swordSwingArea = SetSword(character.Pos.x - (character.width * 3.f) / 2.f, character.Pos.y, character.width * 3.f, character.height * 2.5f);
	swordSwingTime = 0;
	swingSword = false;
	characterFacing = 0;
}

void level_4_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (CP_Input_KeyTriggered(KEY_ESCAPE) && win == FALSE)
	{
		isPaused = !isPaused;
	}

	if (isPaused && win == FALSE)
	{
		// printf("paused screen state lv1 %d", isPaused);
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

	if (min == surviveMin || lose == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 500, 1000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		if (lose == 0)
		{
			CP_Font_DrawText("You survived Level 4!", wWidth / 2.0f, wHeight / 2.0f - 300);
			Button("Next level", nextLevel.pos.x, nextLevel.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);
			Button("Restart", wWidth / 2.0f, wHeight / 2.0f - 50, wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);
			Button("Menu", wWidth / 2.0f, wHeight / 2.0f + 100, wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);
			Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 250, wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		}
		else
		{
			CP_Engine_SetNextGameState(game_Over_page_init, game_Over_page_update, game_Over_page_exit);
		}

		if (lose == 0)
		{
			win = TRUE;
		}
		isPaused = TRUE;
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

					printf("next Level");
					// level_2_Init();
					// CP_Engine_SetNextGameState(level_2_Init, level_2_Update, level_2_Exit);

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
				win = FALSE;
				clear();
				level_4_Init();
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
			++min;
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

		// timers
		spawnTimer -= elapsedTime;
		bossShootTimer -= elapsedTime;

		// keeps spawning until the player survives
		if (min < surviveMin)
		{
			changeSpawnTimer -= elapsedTime;
			if (changeSpawnTimer <= 0)
			{
				if (direction == 4)
				{
					direction = 1;
				}
				else if (direction == 3)
				{
					direction = 4;
				}
				else if (direction == 2)
				{
					direction = 3;
				}
				else if (direction == 1)
				{
					direction = 2;
				}

				changeSpawnTimer = startSpawnChangeTimer;
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
		}
		// spawn as much items as there are spawn index which represent the number of enemies as well as the enemy spawn index
		//for (int i = 0; i < spawnIndex; i++)
		//{

		//	randomId = CP_Random_RangeInt(1, 2);
		//	enemies[spawnIndex].id = randomId;
		//	if (enemies[spawnIndex].id == 1)
		//	{
		//		// set enemy with this id to the respective sprite
		//		enemies[spawnIndex].enemySprite = enemySprite1;
		//		// set the width and height to the respective sprite
		//		enemies[spawnIndex].width = (float)CP_Image_GetWidth(enemies[(int)spawnIndex].enemySprite);
		//		enemies[spawnIndex].height = (float)CP_Image_GetHeight(enemies[(int)spawnIndex].enemySprite);
		//		// set health for the enemy id number
		//		enemies[spawnIndex].health = 1;
		//	}
		//	else if (enemies[spawnIndex].id == 2)
		//	{
		//		// set enemy with this id to the respective sprite
		//		enemies[spawnIndex].enemySprite = enemySprite2;
		//		// set the width and height to the respective sprite
		//		enemies[spawnIndex].width = (float)CP_Image_GetWidth(enemies[(int)spawnIndex].enemySprite);
		//		enemies[spawnIndex].height = (float)CP_Image_GetHeight(enemies[(int)spawnIndex].enemySprite);
		//		// set health for the enemy id number
		//		enemies[spawnIndex].health = 2;
		//	}

		//	enemies[i].pos = enemyMovement(character.Pos, enemies[i].pos, enemy.speed);
		//	for (int o = obstructionCount2 + 1; o < obstructionCount3; o++)
		//	{
		//		// check for obstructions
		//		enemies[i].pos = checkObsCollision(enemies[i].pos, enemies[i].width, enemies[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height);
		//	}
		//}

		if (playerNum == 1)
		{ // IF RANGED CHAR
			bullet.shootPosition = CP_Vector_Set(character.Pos.x, character.Pos.y);

			// SHOOT PROJECTILE MECHANIC
			if (character.energy > 0)
			{
				if (CP_Input_MouseClicked() && canShoot == 1)
				{
					//CP_Sound_PlayAdvanced(projectile_shoot, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
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
					if (character.unlimitedEnergyState != 1)
					{
						--character.energy;
					}
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

			//// NO enemies this level to die to bullets
			

			// BULLETS DISAPPEAR WHEN COLLIDING WITH OBSTRUCTIONS // NEED JS TO UPDATE WHEN PILLARS ARE IMPLEMENTED
			//for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			//{
			//	for (int o = obstructionCount1 + 1; o < obstructionCount2; o++)
			//	{ // check if projectile hits obstructions, if so, delete it.
			//		if (checkProjectileObsCollision(bulletArray[i].bulletPos, bulletArray[i].width, bulletArray[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height))
			//		{
			//			// check for obstructions
			//			for (int x = i; x - 1 < bulletSpawnIndex; ++x)
			//			{
			//				bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
			//				// more info: https://codeforwin.org/2015/07/c-program-to-delete-element-from-array.html
			//			}
			//			--bulletSpawnIndex;
			//		}
			//	}
			//}
		

			// BULLETS DISAPPEAR WHEN COLLIDING WITH OBSTRUCTIONS
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				for (int o = obstructionCount2 + 1; o < obstructionCount3; o++)
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
					//CP_Sound_PlayAdvanced(sword_swing, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				}
				for (int i = 0; i < spawnIndex; i++)
				{ // SWORD SWING
					if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && swordSwingEnemey(swordSwingArea, enemies[i].pos, enemies[i].radius))
					{
						//--enemies[i].health;
						//NO DROPS FROM ENEMIES

						/*if (enemies[i].health <= 0)
						{
							for (int y = i; y < spawnIndex; ++y)
							{
								enemies[y] = enemies[y + 1];
							}
							--spawnIndex;
						}*/
					}
				}
				if (CP_Input_MouseClicked() && character.unlimitedEnergyState != 1)
				{
					--character.energy;
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

		// check player collision with obstruction // NEED JS TO UPDATE WHEN PILLARS ARE IMPLEMENTED
		//for (int i = 0; i < obstructionCount1; i++)
		//{
		//	// draw obstruction
		//	CP_Image_Draw(obs.rec_block[i].spriteImage, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height, 255);
		//	// check for obstructions
		//	character.Pos = checkObsCollision(character.Pos, character.width, character.height, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height);
		//}

		// check where character going out of bounds
		character.Pos = checkMapCollision(character.Pos, character.width / 2, wWidth - character.width / 2, character.height / 2, wHeight - character.height / 2);

		/// no enemy obstruction

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
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

		changeAttackTimer -= elapsedTime;
		bossBullet.shootPosition = CP_Vector_Set(boss.pos.x, boss.pos.y);	
		bossBullet.shootPosition2 = CP_Vector_Set(boss.pos.x + boss.width/2 , boss.pos.y);
		bossBullet.shootPosition3 = CP_Vector_Set(boss.pos.x - boss.width/2, boss.pos.y);
		if (bossShootTimer <= 0)
		{
			
			if (bossShoot == 1)
			{
				++bossBulletIndex;
				++bossBulletIndex2;
				++bossBulletIndex3;
			}

			printf("timer: %f \n", changeAttackTimer);
			if (changeAttackTimer <= 0)

			{
				if (attackMode == 2)
				{
					attackMode = 1;
					printf("switching to attack 1 \n");
				}
				else if (attackMode == 1)
				{
					attackMode = 2;
					printf("switching to attack 2 \n");
				}
				/*	else if (attackMode == 3)
					{

						attackMode = 1;
						printf("switching to attack 1 \n");
					}*/

				changeAttackTimer = startChangeTimer;
			}
			if (attackMode == 1)
			{
				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex3].directionBullet);
			}
			else if (attackMode == 2)
			{

				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray2[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray3[bossBulletIndex3].directionBullet);

			}
			/*		else if (attackMode == 3)
					{
						CP_Vector acceleration = CP_Vector_Scale(AngleToVector(directionAngle), bossBullet.bulletSpeed * elapsedTime);
						directionAngle += rotationSpeed * elapsedTime;
						bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
						bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Add(bossBulletArray[bossBulletIndex].bulletPos, acceleration);

						printf("angle: %f \n", directionAngle);
						bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);


			}*/
			bossShoot = 1;
			bossShootTimer = startBossShootTimer;
		}

		for (int i = 0; i - 1 < bossBulletIndex; ++i)
		{
			
			if (bossShoot == 1)
			{
				bossBulletArray[i].acceleration = CP_Vector_Scale(bossBulletArray[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray[i].bulletPos = CP_Vector_Add(bossBulletArray[i].bulletPos, bossBulletArray[i].acceleration);
			}
		}
		for (int i = 0; i - 1 < bossBulletIndex2; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray2[i].acceleration = CP_Vector_Scale(bossBulletArray2[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray2[i].bulletPos = CP_Vector_Add(bossBulletArray2[i].bulletPos, bossBulletArray2[i].acceleration);
			}
		}

		for (int i = 0; i - 1 < bossBulletIndex3; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray3[i].acceleration = CP_Vector_Scale(bossBulletArray3[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray3[i].bulletPos = CP_Vector_Add(bossBulletArray3[i].bulletPos, bossBulletArray3[i].acceleration);
			}
		}

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1 && character.shieldedState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i - 1 < bossBulletIndex; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray[i].bulletPos, (bossBulletArray[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{	// sound to be implemented
						//if (!damageTakenTime)
						//{
						//	damageSound = true;
						//	CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0); // sound for damage taken
						//}

						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}

		changeAttackTimer -= elapsedTime;
		bossBullet.shootPosition = CP_Vector_Set(boss.pos.x, boss.pos.y);	
		bossBullet.shootPosition2 = CP_Vector_Set(boss.pos.x + boss.width/2 , boss.pos.y);
		bossBullet.shootPosition3 = CP_Vector_Set(boss.pos.x - boss.width/2, boss.pos.y);
		if (bossShootTimer <= 0)
		{
			
			if (bossShoot == 1)
			{
				++bossBulletIndex;
				++bossBulletIndex2;
				++bossBulletIndex3;
			}

			printf("timer: %f \n", changeAttackTimer);
			if (changeAttackTimer <= 0)

			{
				if (attackMode == 2)
				{
					attackMode = 1;
					printf("switching to attack 1 \n");
				}
				else if (attackMode == 1)
				{
					attackMode = 2;
					printf("switching to attack 2 \n");
				}
				/*	else if (attackMode == 3)
					{

						attackMode = 1;
						printf("switching to attack 1 \n");
					}*/

				changeAttackTimer = startChangeTimer;
			}
			if (attackMode == 1)
			{
				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex3].directionBullet);
			}
			else if (attackMode == 2)
			{

				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray2[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray3[bossBulletIndex3].directionBullet);

			}
			/*		else if (attackMode == 3)
					{
						CP_Vector acceleration = CP_Vector_Scale(AngleToVector(directionAngle), bossBullet.bulletSpeed * elapsedTime);
						directionAngle += rotationSpeed * elapsedTime;
						bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
						bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Add(bossBulletArray[bossBulletIndex].bulletPos, acceleration);

						printf("angle: %f \n", directionAngle);
						bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);


			}*/
			bossShoot = 1;
			bossShootTimer = startBossShootTimer;
		}

		for (int i = 0; i - 1 < bossBulletIndex; ++i)
		{
			
			if (bossShoot == 1)
			{
				bossBulletArray[i].acceleration = CP_Vector_Scale(bossBulletArray[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray[i].bulletPos = CP_Vector_Add(bossBulletArray[i].bulletPos, bossBulletArray[i].acceleration);
			}
		}
		for (int i = 0; i - 1 < bossBulletIndex2; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray2[i].acceleration = CP_Vector_Scale(bossBulletArray2[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray2[i].bulletPos = CP_Vector_Add(bossBulletArray2[i].bulletPos, bossBulletArray2[i].acceleration);
			}
		}

		for (int i = 0; i - 1 < bossBulletIndex3; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray3[i].acceleration = CP_Vector_Scale(bossBulletArray3[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray3[i].bulletPos = CP_Vector_Add(bossBulletArray3[i].bulletPos, bossBulletArray3[i].acceleration);
			}
		}

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1 && character.shieldedState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i - 1 < bossBulletIndex; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray[i].bulletPos, (bossBulletArray[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{	// sound to be implemented
						//if (!damageTakenTime)
						//{
						//	damageSound = true;
						//	CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0); // sound for damage taken
						//}

						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}

		changeAttackTimer -= elapsedTime;
		bossBullet.shootPosition = CP_Vector_Set(boss.pos.x, boss.pos.y);	
		bossBullet.shootPosition2 = CP_Vector_Set(boss.pos.x + boss.width/2 , boss.pos.y);
		bossBullet.shootPosition3 = CP_Vector_Set(boss.pos.x - boss.width/2, boss.pos.y);
		if (bossShootTimer <= 0)
		{
			
			if (bossShoot == 1)
			{
				++bossBulletIndex;
				++bossBulletIndex2;
				++bossBulletIndex3;
			}

			printf("timer: %f \n", changeAttackTimer);
			if (changeAttackTimer <= 0)

			{
				if (attackMode == 2)
				{
					attackMode = 1;
					printf("switching to attack 1 \n");
				}
				else if (attackMode == 1)
				{
					attackMode = 2;
					printf("switching to attack 2 \n");
				}
				/*	else if (attackMode == 3)
					{

						attackMode = 1;
						printf("switching to attack 1 \n");
					}*/

				changeAttackTimer = startChangeTimer;
			}
			if (attackMode == 1)
			{
				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex3].directionBullet);
			}
			else if (attackMode == 2)
			{

				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray2[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray3[bossBulletIndex3].directionBullet);

			}
			/*		else if (attackMode == 3)
					{
						CP_Vector acceleration = CP_Vector_Scale(AngleToVector(directionAngle), bossBullet.bulletSpeed * elapsedTime);
						directionAngle += rotationSpeed * elapsedTime;
						bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
						bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Add(bossBulletArray[bossBulletIndex].bulletPos, acceleration);

						printf("angle: %f \n", directionAngle);
						bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);


			}*/
			bossShoot = 1;
			bossShootTimer = startBossShootTimer;
		}

		for (int i = 0; i - 1 < bossBulletIndex; ++i)
		{
			
			if (bossShoot == 1)
			{
				bossBulletArray[i].acceleration = CP_Vector_Scale(bossBulletArray[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray[i].bulletPos = CP_Vector_Add(bossBulletArray[i].bulletPos, bossBulletArray[i].acceleration);
			}
		}
		for (int i = 0; i - 1 < bossBulletIndex2; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray2[i].acceleration = CP_Vector_Scale(bossBulletArray2[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray2[i].bulletPos = CP_Vector_Add(bossBulletArray2[i].bulletPos, bossBulletArray2[i].acceleration);
			}
		}

		for (int i = 0; i - 1 < bossBulletIndex3; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray3[i].acceleration = CP_Vector_Scale(bossBulletArray3[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray3[i].bulletPos = CP_Vector_Add(bossBulletArray3[i].bulletPos, bossBulletArray3[i].acceleration);
			}
		}

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1 && character.shieldedState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i - 1 < bossBulletIndex; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray[i].bulletPos, (bossBulletArray[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{	// sound to be implemented
						//if (!damageTakenTime)
						//{
						//	damageSound = true;
						//	CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0); // sound for damage taken
						//}

						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}

		// FINAL BOSS MECHANICS
		changeAttackTimer -= elapsedTime;
		bossBullet.shootPosition = CP_Vector_Set(boss.pos.x, boss.pos.y);
		bossBullet.shootPosition2 = CP_Vector_Set(boss.pos.x + boss.width / 2, boss.pos.y);
		bossBullet.shootPosition3 = CP_Vector_Set(boss.pos.x - boss.width / 2, boss.pos.y);
		if (bossShootTimer <= 0)
		{

			if (bossShoot == 1)
			{
				++bossBulletIndex;
				++bossBulletIndex2;
				++bossBulletIndex3;
			}

			printf("timer: %f \n", changeAttackTimer);
			if (changeAttackTimer <= 0)

			{
				if (attackMode == 2)
				{
					attackMode = 1;
					printf("switching to attack 1 \n");
				}
				else if (attackMode == 1)
				{
					attackMode = 2;
					printf("switching to attack 2 \n");
				}
				/*	else if (attackMode == 3)
					{

						attackMode = 1;
						printf("switching to attack 1 \n");
					}*/

				changeAttackTimer = startChangeTimer;
			}
			if (attackMode == 1)
			{
				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex3].directionBullet);
			}
			else if (attackMode == 2)
			{

				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray2[bossBulletIndex2].directionBullet);

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray3[bossBulletIndex3].directionBullet);

			}
			/*		else if (attackMode == 3)
					{
						CP_Vector acceleration = CP_Vector_Scale(AngleToVector(directionAngle), bossBullet.bulletSpeed * elapsedTime);
						directionAngle += rotationSpeed * elapsedTime;
						bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
						bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Add(bossBulletArray[bossBulletIndex].bulletPos, acceleration);

						printf("angle: %f \n", directionAngle);
						bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);


			}*/
			bossShoot = 1;
			bossShootTimer = startBossShootTimer;
		}

		for (int i = 0; i - 1 < bossBulletIndex; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray[i].acceleration = CP_Vector_Scale(bossBulletArray[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray[i].bulletPos = CP_Vector_Add(bossBulletArray[i].bulletPos, bossBulletArray[i].acceleration);
			}
		}
		for (int i = 0; i - 1 < bossBulletIndex2; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray2[i].acceleration = CP_Vector_Scale(bossBulletArray2[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray2[i].bulletPos = CP_Vector_Add(bossBulletArray2[i].bulletPos, bossBulletArray2[i].acceleration);
			}
		}

		for (int i = 0; i - 1 < bossBulletIndex3; ++i)
		{

			if (bossShoot == 1)
			{
				bossBulletArray3[i].acceleration = CP_Vector_Scale(bossBulletArray3[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray3[i].bulletPos = CP_Vector_Add(bossBulletArray3[i].bulletPos, bossBulletArray3[i].acceleration);
			}
		}

		// damage taking and 2 second invulnerability after code.
		healthChange = 0; // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1 && character.shieldedState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i - 1 < bossBulletIndex; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray[i].bulletPos, (bossBulletArray[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{
						//CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}
		if (character.invulState != 1 && character.shieldedState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i - 1 < bossBulletIndex2; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray2[i].bulletPos, (bossBulletArray2[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{
						//CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}
		if (character.invulState != 1 && character.shieldedState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i - 1 < bossBulletIndex3; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray3[i].bulletPos, (bossBulletArray3[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{
						//CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}

		// no items to pickup

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

		// no power ups

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

		// if char dies
		if (character.health <= 0)
		{
			lose = 1;
		}
		else
		{
			lose = 0;
		}

		// no enemies to draw
		

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

		// display char health and energy ///
		CP_Font_DrawText("Health:", 50, 50);
		for (int i = 0; i < character.health; ++i)
		{
			CP_Image_Draw(char_health, (float)i * 52 + 150, 50, (float)CP_Image_GetWidth(char_health), (float)CP_Image_GetHeight(char_health), 255);
		}

		CP_Font_DrawText("Energy:", 50, 102);
		for (int i = 0; i < character.energy; ++i)
		{
			CP_Image_Draw(char_energy, (float)i * 52 + 150, 102, (float)CP_Image_GetWidth(char_energy), (float)CP_Image_GetHeight(char_energy), 255);
		}


		CP_Image_Draw(boss.enemySprite, boss.pos.x, boss.pos.y, boss.width, boss.height, 255);

		for (int i = 0; i - 1 < bossBulletIndex; ++i)
		{
			if (bossShoot == 1)
			{
				CP_Image_Draw(bossBullet.bulletSprite, bossBulletArray[i].bulletPos.x, bossBulletArray[i].bulletPos.y, bullet.width, bullet.height, 255);
				// printf("Drawing %d", bulletSpawnIndex);
			}
		}

		for (int i = 0; i - 1 < bossBulletIndex2; ++i)
		{
			if (bossShoot == 1)
			{
				CP_Image_Draw(bossBullet.bulletSprite, bossBulletArray2[i].bulletPos.x, bossBulletArray2[i].bulletPos.y, bullet.width, bullet.height, 255);
				// printf("Drawing %d", bulletSpawnIndex);
			}
		}

		for (int i = 0; i - 1 < bossBulletIndex3; ++i)
		{
			if (bossShoot == 1)
			{
				CP_Image_Draw(bossBullet.bulletSprite, bossBulletArray3[i].bulletPos.x, bossBulletArray3[i].bulletPos.y, bullet.width, bullet.height, 255);
				// printf("Drawing %d", bulletSpawnIndex);
			}
		}
	}
}

void level_4_Exit()
{
}
