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
#include "sound.h"

struct Character playerGun;
struct Character playerSword;

// Sprite Image
CP_Image gunPlayer;
CP_Image swordPlayer;

int isPaused;
float invulElapsedTime;
float invulTransparencyTime;
float energyRechargeTime;
float stunnedElapsedTime;
int healthChange;
float wWidth;
float wHeight;
// string array to use for text display
char timeString[MAX_LENGTH];
char characterHealthDisplay[MAX_LENGTH];
char characterEnergyDisplay[MAX_LENGTH];

void level_1_Init()
{
	clear();
	delayShootTime = 0.1f;
	delayShootStart = delayShootTime;
	delayShootTime = delayShootStart;
	CP_System_FullscreenAdvanced(1920, 1080);
	// CP_System_SetWindowSize(1920, 1080);
	bullet.bulletSpeed = 1000;
	spawnTimer = 1.f;
	startSpawnTimer = spawnTimer;
	bulletSpawnIndex = 0;
	elapsedTime = 1;
	surviveMin = 1;
	sec = 0;
	min = 0;
	spawnIndex = 0;
	spawnIndex = 0;
	firstShoot = 0;
	dropIndex = 0;
	lose = 0;
	canShoot = 0;
	level = 1;
	changeSpawnTimer = 0.1f;
	startSpawnChangeTimer = changeSpawnTimer;
	direction = 1;
	// Set window width and height to variables
	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();
	map_background = CP_Image_Load("Assets/map_background1.png");
	bullet.bulletSprite = CP_Image_Load("Assets/Ranged_Char_Bullet.png");
	enemySprite1 = CP_Image_Load("Assets/enemy1.png");
	dropShieldSprite = CP_Image_Load("Assets/Shield_Drop.png"); /// added
	dropEnergySprite = CP_Image_Load("Assets/batteryDrop.png");
	swordSwingSprite1 = CP_Image_Load("Assets/sword_swing.png");
	swordSwingSprite2 = CP_Image_Load("Assets/sword_swing2.png");
	stunned = CP_Image_Load("Assets/stunned_animation.png");
	hpPickup = CP_Image_Load("Assets/hp_pickup_animation.png");
	energyPickup = CP_Image_Load("Assets/energy_pickup_animation.png");
	char_energy = CP_Image_Load("Assets/Char_Energy.png");				 ///
	char_health = CP_Image_Load("Assets/Char_Health.png");				 /// removed drop health sprite
	shielded = CP_Image_Load("Assets/Unlimited_Health_Mode.png");		 ///
	unlimitedEnergy = CP_Image_Load("Assets/Unlimited_Energy_Mode.png"); ///
	obstruction1 = CP_Image_Load("Assets/obstruction1.png");
	obstruction2 = CP_Image_Load("Assets/obstruction2.png");
	obstruction3 = CP_Image_Load("Assets/obstruction3.png");
	obsWidth1 = (float)CP_Image_GetWidth(obstruction1);
	obsHeight1 = (float)CP_Image_GetHeight(obstruction1);
	obsWidth2 = (float)CP_Image_GetWidth(obstruction2);
	obsHeight2 = (float)CP_Image_GetHeight(obstruction2);
	obsWidth3 = (float)CP_Image_GetWidth(obstruction3);
	obsHeight3 = (float)CP_Image_GetHeight(obstruction3);
	stunnedWidth = (float)CP_Image_GetWidth(stunned);
	stunnedHeight = (float)CP_Image_GetHeight(stunned);
	bullet.width = (float)CP_Image_GetWidth(bullet.bulletSprite);
	bullet.height = (float)CP_Image_GetHeight(bullet.bulletSprite);
	// player sprite
	gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");

	// set spawn positions to 0 coordinate
	spawnPosition = CP_Vector_Set(0, 0);

	enemies[spawnIndex].pos.x = spawnPosition.x;
	enemies[spawnIndex].pos.y = spawnPosition.y;
	itemDrop[dropIndex].pos.x = spawnPosition.x;
	itemDrop[dropIndex].pos.y = spawnPosition.y;
	// set enemy width and height based on the sprite
	/*Darren Lua Code for setting width and height*/
	enemy.width = (float)CP_Image_GetWidth(enemySprite1) - 2.f;	  // 2.0 for polishing purposes
	enemy.height = (float)CP_Image_GetHeight(enemySprite1) - 2.f; // 2.0 for polishing purposes
	enemy.speed = 70;
	healthDrop.width = (float)CP_Image_GetWidth(healthDrop.dropSprite);
	healthDrop.height = (float)CP_Image_GetHeight(healthDrop.dropSprite);

	nextLevel.pos.x = wWidth / 2.0f;
	nextLevel.pos.y = wHeight / 2.0f - 200;
	resumeButton.pos.x = wWidth / 2.0f;
	resumeButton.pos.y = wHeight / 2.0f - 200;
	restartButton.pos.x = wWidth / 2.0f;
	restartButton.pos.y = wHeight / 2.0f - 50;
	menuButton.pos.x = wWidth / 2.0f;
	menuButton.pos.y = wHeight / 2.0f + 100;
	exitLevelButton.pos.x = wWidth / 2.0f;
	exitLevelButton.pos.y = wHeight / 2.0f + 250;

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
	character.transparency = 255;		// opaque initially, will be translucent in invul state
	character.shieldedState = 0;		///
	character.unlimitedEnergyState = 0; ///
	invulElapsedTime = 0;				// timer for invul
	invulTransparencyTime = 0;
	energyRechargeTime = 0; // timer for energyRecharge
	stunnedElapsedTime = 0;
	shieldedDuration = 0;		 ///
	unlimitedEnergyDuration = 0; ///

	// bullet start shoot spawn position
	bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2.f + 20, character.Pos.y + character.health / 2.f);

	bulletArray[bulletSpawnIndex].bulletPos = bullet.shootPosition;
	firstShoot = 0;

	isPaused = FALSE;

	// initiate obstruction
	for (int i = 0, x = 0; i < 6; i++, x += (int)obsWidth2)
	{
		obs.rec_block[i] = SetRect_(wWidth / 10.f + x, wHeight / 8.f, obsWidth2, obsHeight2 * 2.f, obstruction2);
	}
	for (int i = 6, x = 0; i < 12; i++, x -= (int)obsWidth2)
	{
		obs.rec_block[i] = SetRect_(wWidth * 9.f / 10.f + x, wHeight / 8.f, obsWidth2, obsHeight2 * 2.f, obstruction2);
	}
	for (int i = 12, x = 0; i < 18; i++, x += (int)obsWidth2)
	{
		obs.rec_block[i] = SetRect_(wWidth / 10.f + x, wHeight * 7.f / 8.f, obsWidth2, obsHeight2 * 2.f, obstruction2);
	}
	for (int i = 18, x = 0; i < 24; i++, x -= (int)obsWidth2)
	{
		obs.rec_block[i] = SetRect_(wWidth * 9.f / 10.f + x, wHeight * 7.f / 8.f, obsWidth2, obsHeight2 * 2.f, obstruction2);
	}
	for (int i = 24, y = 0; i < 27; i++, y += (int)obsHeight3)
	{
		obs.rec_block[i] = SetRect_(wWidth / 10.f - obsWidth2 / 2.f + obsWidth3 / 2.f, wHeight / 8.f + obsHeight3 / 2.f + y, obsWidth3 * 2.f, obsHeight3, obstruction3);
	}
	for (int i = 27, y = 0; i < 30; i++, y += (int)obsHeight3)
	{
		obs.rec_block[i] = SetRect_(wWidth * 9.f / 10.f + obsWidth2 / 2.f - obsWidth3 / 2.f, wHeight / 8.f + obsHeight3 / 2.f + y, obsWidth3 * 2.f, obsHeight3, obstruction3);
	}
	for (int i = 30, y = 0; i < 33; i++, y -= (int)obsHeight3)
	{
		obs.rec_block[i] = SetRect_(wWidth / 10.f - obsWidth2 / 2.f + obsWidth3 / 2.f, wHeight * 7.f / 8.f - obsHeight3 / 2.f + y, obsWidth3 * 2.f, obsHeight3, obstruction3);
	}
	for (int i = 33, y = 0; i < 36; i++, y -= (int)obsHeight3)
	{
		obs.rec_block[i] = SetRect_(wWidth * 9.f / 10.f + obsWidth2 / 2.f - obsWidth3 / 2.f, wHeight * 7.f / 8.f - obsHeight3 / 2.f + y, obsWidth3 * 2.f, obsHeight3, obstruction3);
	}
	// square obstruction
	for (int i = 36, x = 0, y = 0; i < 48; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth / 6.f + x, wHeight / 4.2f + obsHeight1 * 2 + y, obsWidth1, obsHeight1, obstruction1);
		x += (int)obs.rec_block[i].width;
		if (i == 41)
		{
			y += (int)(obs.rec_block[i].height + character.height * 2);
			x = 0;
		}
	}
	for (int i = 48, x = 0, y = 0; i < 66; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth * 5.f / 6.f + x, wHeight / 4.2f + y, obsWidth1, obsHeight1, obstruction1);
		x -= (int)obs.rec_block[i].width;
		if (i == 53 || i == 59)
		{
			y += (int)(obs.rec_block[i].height + character.height * 2);
			x = 0;
		}
	}

	// melee character swing sword area check
	swordSwingArea = SetSword(character.Pos.x - (character.width * 3.f) / 2.f, character.Pos.y, character.width * 3.f, character.height * 2.5f);
	swordSwingTime = 0;
	damageTakenTime = 0;
	swingSword = false;
	damageSound = false;
	characterFacing = 0;
	sword_swing = CP_Sound_Load("Assets/sword_swing.wav");
	projectile_shoot = CP_Sound_Load("Assets/projectile.wav");
	pickUp = CP_Sound_Load("Assets/pickup.wav");
	nextlvl_sound = CP_Sound_Load("Assets/nextLevel.wav");
	buttonClickSound = CP_Sound_Load("Assets/buttonClick.wav");
	damageTaken = CP_Sound_Load("Assets/takingDamage.wav");
	nextState = 0.f;
	startCount = FALSE;
	menuState = FALSE;
	exitState = FALSE;
	startCountG = 0.f;
	playVictorySound = FALSE;
	victorySoundCount = 0.f;
}

void level_1_Update()
{
	CP_Sound_ResumeGroup(CP_SOUND_GROUP_1);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (playVictorySound)
	{
		victorySoundCount += 1.f;
	}
	if (victorySoundCount == 2.f)
		CP_Sound_PlayAdvanced(nextlvl_sound, 0.5f, 0.5f, FALSE, CP_SOUND_GROUP_0);

	if (CP_Input_KeyTriggered(KEY_ESCAPE) && win == FALSE)
	{
		isPaused = !isPaused;
	}

	if (isPaused && win == FALSE)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 500, 2000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Paused", wWidth / 2.0f, wHeight / 2.0f - 300);

		Button("Resume", resumeButton.pos.x, resumeButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		Button("Restart", restartButton.pos.x, restartButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		Button("Menu", menuButton.pos.x, menuButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		Button("Exit", exitLevelButton.pos.x, exitLevelButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, 0, 255, 0, 0, 0, 0, 255);
	}

	if (min == surviveMin || lose == 1)
	{

		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 500, 2000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		if (lose == 0)
		{
			CP_Sound_PauseGroup(CP_SOUND_GROUP_1);
			playVictorySound = TRUE;
			CP_Font_DrawText("You survived Level 1!", wWidth / 2.0f, wHeight / 2.0f - 300);
			Button("Next level", nextLevel.pos.x, nextLevel.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);
			Button("Restart", restartButton.pos.x, restartButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);
			Button("Menu", menuButton.pos.x, menuButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);
			Button("Exit", exitLevelButton.pos.x, exitLevelButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		}
		else
		{
			CP_Sound_PauseGroup(CP_SOUND_GROUP_1);
			CP_Engine_SetNextGameState(game_Over_page_Init, game_Over_page_Update, game_Over_page_Exit);
		}

		if (lose == 0)
		{
			win = TRUE;
		}
		isPaused = TRUE;
	}

	if (isPaused)
	{
		// delay call next game state by 0.1 sec to register the button sound
		elapsedTime = CP_System_GetDt();
		if (startCount)
			nextState += elapsedTime;
		if (nextState > 0.2)
		{
			if (exitState)
				CP_Engine_Terminate();
			else if (menuState)
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			else
				CP_Engine_SetNextGameState(level_2_Init, level_2_Update, level_2_Exit);
		}

		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (lose == 0)
		{
			if (win == TRUE)
			{
				if (IsAreaClicked(nextLevel.pos.x, nextLevel.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
				{
					delayShootTime = delayShootStart;

					CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					if (!nextState)
						startCount = TRUE;

				}
				else if (IsAreaClicked(nextLevel.pos.x, nextLevel.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
				{
					Button("Next level", nextLevel.pos.x, nextLevel.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, 220, 100, 0, 255, 0, 0, 0, 0, 255);
				}
			}

			if (IsAreaClicked(resumeButton.pos.x, resumeButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
			{
				if (win == FALSE)
				{
					CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					delayShootTime = delayShootStart;
					isPaused = !isPaused;
				}
			}
			else if (win == FALSE && IsAreaClicked(resumeButton.pos.x, resumeButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
			{
				Button("Resume", resumeButton.pos.x, resumeButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, 220, 100, 0, 255, 0, 0, 0, 0, 255);
			}
		}

		if (IsAreaClicked(restartButton.pos.x, restartButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			if (isPaused == TRUE)
			{
				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				win = FALSE;
				level_1_Init();
			}
		}
		else if (IsAreaClicked(restartButton.pos.x, restartButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y))
		{
			Button("Restart", restartButton.pos.x, restartButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 50, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		}

		if (IsAreaClicked(menuButton.pos.x, menuButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
			{
				startCount = TRUE;
				menuState = TRUE;
			}
		}
		else if (IsAreaClicked(menuButton.pos.x, menuButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Menu", menuButton.pos.x, menuButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 100, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		}

		if (IsAreaClicked(exitLevelButton.pos.x, exitLevelButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
			{
				startCount = TRUE;
				exitState = TRUE;
			}
		}
		else if (IsAreaClicked(exitLevelButton.pos.x, exitLevelButton.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Exit", exitLevelButton.pos.x, exitLevelButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 250, 220, 100, 0, 255, 0, 0, 0, 0, 255);
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
		if (damageSound)
		{
			damageTakenTime += elapsedTime;
			if (damageTakenTime > 2)
			{
				damageTakenTime = 0;
				damageSound = false;
			}
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
		// keeps spawning for 1 min
		if (min < surviveMin)
		{
			changeSpawnTimer -= elapsedTime;			
			if (changeSpawnTimer <= 0)
			{
				//change directions every time change spawn timer reaches 0 or less
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
				/*reset the spawn timer*/
				changeSpawnTimer = startSpawnChangeTimer;
			}

			// check spawn timer and acts as rate of spawn
			if (spawnTimer <= 0)
			{

				// set random spawn position based on width and height of the screen
				/*The 4 directions represent different locations of the spawn */
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
					spawnPosition = CP_Vector_Set(wWidth - 200, CP_Random_RangeFloat(wHeight / 7, wHeight));
				}
				else if (direction == 4)
				{
					spawnPosition = CP_Vector_Set(CP_Random_RangeFloat(wWidth / 8, wWidth), wHeight - 200);
				}
				// set spawn positions of the enemies
				enemies[spawnIndex].pos.x = spawnPosition.x;
				enemies[spawnIndex].pos.y = spawnPosition.y;
				//  add one to enemy count and set spawn index to 1 for the enemy
				spawnIndex++;
				// restart spawn time
				spawnTimer = startSpawnTimer;
			}
		}

		// spawn as much items as there are spawn index which represent the number of enemies as well as the enemy spawn index
		for (int i = 0; i < spawnIndex; i++)
		{
			// set enemy sprite to enemy sprite1
			enemies[i].enemySprite = enemySprite1;
			//set the width and height to the respective sprite
			enemies[i].width = (float)CP_Image_GetWidth(enemies[i].enemySprite);
			enemies[i].height = (float)CP_Image_GetHeight(enemies[i].enemySprite);
			enemies[i].health = 1;

			// enemy movement
			enemies[i].pos = enemyMovement(character.Pos, enemies[i].pos, enemy.speed);

			for (int o = 0; o < obstructionCount1; o++)
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
					CP_Sound_PlayAdvanced(projectile_shoot, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);

					/*Shoot Mechanic done by Darren Lua*/
					CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
					/*Only increment after the index 0 bullet is spawned*/
					if (firstShoot == 1)
					{
						++bulletSpawnIndex;
					}
					/*Set the bullet vector directions from the shooting position to mouse click position*/
					bulletArray[bulletSpawnIndex].directionBullet = CP_Vector_Subtract(mouseClickPos, bullet.shootPosition);
					/*Set bullet's position to the shooting position*/
					bulletArray[bulletSpawnIndex].bulletPos = bullet.shootPosition;
					/*Normalize the direction to prevent the bullet speed from changing based on distance vector*/
					bulletArray[bulletSpawnIndex].normalizedDirection = CP_Vector_Normalize(bulletArray[bulletSpawnIndex].directionBullet);
					firstShoot = 1;

					// energy deplete function
					if (character.unlimitedEnergyState != 1)
					{

						--character.energy;
					}
				}
			}
			/*bullet movement*/
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{	/*scale the acceleration of the bullet based on the normalized direction and the speed*/
				bulletArray[i].acceleration = CP_Vector_Scale(bulletArray[i].normalizedDirection, bullet.bulletSpeed * elapsedTime);
				/*Add the bullet's acceleration vector to the bullet's position*/
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

			// enemies dying to bullets
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

						/*Darren Lua Item Drop code*/										
						if (enemies[j].health <= 0)
						{						
							 //randomize spawn rate from 1 to 2 meaning 1 in 4 chance of spawn
							unsigned int randomRate = CP_Random_RangeInt(1, 4);
							// randomly set drop id between 1 or 2
							unsigned int dropId = CP_Random_RangeInt(1, 2);
							//set drop Id and drop boolean to true
							itemDrop[dropIndex].itemId = dropId;
							itemDrop[dropIndex].dropTrue = 1;
							if (randomRate == 2)
							{
								// check item drop's id by the spawn index of the drop
								if (itemDrop[dropIndex].itemId == 1)
								{
									// if item's id is 1 set the item's dropSprite to the dropHealthSprite
									itemDrop[dropIndex].dropSprite = dropShieldSprite;
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
								itemDrop[dropIndex].pos.x = enemies[j].pos.x;
								itemDrop[dropIndex].pos.y = enemies[j].pos.y;
								/*Increment drop index*/
								++dropIndex;
							}
						}

						// deletion of projectile after hitting enemy
						for (int x = i; x - 1 < bulletSpawnIndex; ++x)
						{
							bulletArray[x] = bulletArray[x + 1];
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
				for (int o = 0; o < obstructionCount1; o++)
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
					CP_Sound_PlayAdvanced(sword_swing, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				}
				for (int i = 0; i < spawnIndex; i++)
				{ // SWORD SWING
					if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && swordSwingEnemey(swordSwingArea, enemies[i].pos, enemies[i].width))
					{
						--enemies[i].health;
						/*Darren Lua Item Drop code*/
						if (enemies[i].health <= 0)
						{							
							//randomize spawn rate from 1 to 4 meaning 1 in 4 chance of spawn
							unsigned int randomRate = CP_Random_RangeInt(1, 4);
							// randomly set drop id between 1 or 2
							unsigned int dropId = CP_Random_RangeInt(1, 2);
							//set drop Id and drop boolean to true
							itemDrop[dropIndex].itemId = dropId;
							itemDrop[dropIndex].dropTrue = 1;
							if (randomRate == 2)
							{
								// check item drop's id by the spawn index of the drop
								if (itemDrop[dropIndex].itemId == 1)
								{
									// if item's id is 1 set the item's dropSprite to the dropHealthSprite
									itemDrop[dropIndex].dropSprite = dropShieldSprite;
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
								/*Increment drop index*/
								++dropIndex;
							}
						}

						if (enemies[i].health <= 0)
						{
							for (int y = i; y < spawnIndex; ++y)
							{
								enemies[y] = enemies[y + 1];
							}
							--spawnIndex;
						}
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

		// check player collision with obstruction
		for (int i = 0; i < obstructionCount1; i++)
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
		if (character.invulState != 1 && character.shieldedState != 1)
		{ // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i < spawnIndex; i++)
			{
				if (checkDamage(character.Pos, character.width, character.height, enemies[i].pos, (enemies[i].width / 2)) == 1 && enemies[i].health > 0)
				{
					if (healthChange == 0)
					{
						if (!damageTakenTime)
						{
							damageSound = true;
							CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0); // sound for damage taken
						}

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
			if (checkDamage(character.Pos, character.width, character.height, itemDrop[i].pos, itemDrop[i].width / 2.f) == 1)
			{
				CP_Sound_PlayAdvanced(pickUp, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				if (itemDrop[i].itemId == 1) // shield drop
				{
					character.shieldedState = 1;
					shieldedDuration = 0;
					CP_Image_Draw(hpPickup, character.Pos.x, character.Pos.y - 55, (float)CP_Image_GetWidth(hpPickup), (float)CP_Image_GetHeight(hpPickup), 255);
				}
				else if (itemDrop[i].itemId == 2) // health drop
				{
					character.unlimitedEnergyState = 1;
					unlimitedEnergyDuration = 0;
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

		// character power ups
		if (character.shieldedState == 1)
		{
			CP_Image_Draw(shielded, character.Pos.x, character.Pos.y, (float)CP_Image_GetWidth(shielded), (float)CP_Image_GetHeight(shielded), 255);
			shieldedDuration += elapsedTime;

			if (shieldedDuration >= 3)
			{
				character.shieldedState = 0;
				shieldedDuration = 0;
			}
		}
		if (character.unlimitedEnergyState == 1)
		{
			CP_Image_Draw(unlimitedEnergy, character.Pos.x + 5, character.Pos.y, (float)CP_Image_GetWidth(unlimitedEnergy), (float)CP_Image_GetHeight(unlimitedEnergy), 255);
			unlimitedEnergyDuration += elapsedTime;

			if (unlimitedEnergyDuration >= 3)
			{
				character.unlimitedEnergyState = 0;
				unlimitedEnergyDuration = 0;
			}
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

		// if char dies
		if (character.health <= 0)
		{
			lose = 1;
		}
		else
		{
			lose = 0;
		}

		//Darren draw enemies, player and bullet code 
		// draw enemy 
		for (int i = 0; i < spawnIndex; i++)
		{
			CP_Image_Draw(enemies[i].enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemies[i].width, enemies[i].height, 255);
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
			if (itemDrop[i].dropTrue == 1)
			{
				CP_Image_Draw(itemDrop[i].dropSprite, itemDrop[i].pos.x, itemDrop[i].pos.y, itemDrop[i].width, itemDrop[i].height, 255);
			}
		}
		// display timer done by Darren Lua
		CP_Settings_TextSize(100.0f);
		sprintf_s(timeString, MAX_LENGTH, "%d:%.2f", min, sec);
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Font_DrawText(timeString, wWidth / 2.0f, wHeight / 2.0f - 450);
		CP_Settings_TextSize(35.0f);


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
	}
}

void level_1_Exit()
{
	CP_Sound_Free(&sword_swing);
	CP_Sound_Free(&projectile_shoot);
	CP_Sound_Free(&pickUp);
	CP_Sound_Free(&nextlvl_sound);
	CP_Sound_Free(&buttonClickSound);
	CP_Sound_Free(&damageTaken);
	CP_Image_Free(&obstruction1);
	CP_Image_Free(&obstruction2);
	CP_Image_Free(&obstruction3);
	CP_Image_Free(&map_background);
}
