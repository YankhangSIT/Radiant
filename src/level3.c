//---------------------------------------------------------
// file:	level3.c
// author:	Koh Yan Khang, Lua Wei Xiang Darren, Wei Jingsong
// email:	yankhang.k@digipen.edu, weixiangdarren.lua@digipen.edu, jingsong.wei@digipen.edu
// brief:	Includes code for the third level of the game, with 2 types of monster of different healths, with a special "ghost" type
//
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

// header files
#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "movement.h"
#include "combat.h"
#include "mainmenu.h"
#include "math.h"
#include "level3.h"
#include "spawn.h"
#include "map.h"
#include <stdbool.h>
#include <stdlib.h>
#include "button.h"
#include "gameOverpage.h"
#include "global.h"
#include "win.h"
#include "sound.h"

// two structs for two classes
struct Character playerGun;
struct Character playerSword;

// Sprite Image for char
CP_Image gunPlayer;
CP_Image swordPlayer;

// variables
int isPaused;
float elapsedTime;
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
char pointsacc[MAX_POINTS];
void level_3_Init()
{
	// level init
	clear();
	CP_System_FullscreenAdvanced(1920, 1080);
	level = 3;
	wWidth = (float)CP_System_GetWindowWidth();
	wHeight = (float)CP_System_GetWindowHeight();

	// ranged char init
	delayShootTime = 0.1f;
	delayShootStart = delayShootTime;
	delayShootTime = delayShootStart;
	bullet.bulletSpeed = 1000;
	bulletSpawnIndex = 0;
	firstShoot = 0;
	bullet.bulletSprite = CP_Image_Load("Assets/Ranged_Char_Bullet.png");
	bullet.width = (float)CP_Image_GetWidth(bullet.bulletSprite);
	bullet.height = (float)CP_Image_GetHeight(bullet.bulletSprite);
	if (playerNum == 1)
	{
		character.playerSprite = gunPlayer;
		character.width = (float)CP_Image_GetWidth(gunPlayer);
		character.height = (float)CP_Image_GetHeight(gunPlayer);
	}
	bullet.shootPosition = CP_Vector_Set(character.Pos.x + character.width / 2.f + 20, character.Pos.y + character.health / 2.f);
	bulletArray[bulletSpawnIndex].bulletPos = bullet.shootPosition;
	firstShoot = 0;

	// melee char init
	swordSwingSprite1 = CP_Image_Load("Assets/sword_swing.png");
	swordSwingSprite2 = CP_Image_Load("Assets/sword_swing2.png");
	if (playerNum == 2)
	{
		character.playerSprite = swordPlayer;
		character.width = (float)CP_Image_GetWidth(swordPlayer);
		character.height = (float)CP_Image_GetHeight(swordPlayer);
		canShoot = 0;
	}
	swordSwingArea = SetSword(character.Pos.x - (character.width * 3.f) / 2.f, character.Pos.y, character.width * 3.f, character.height * 2.5f);
	swordSwingTime = 0;
	swingSword = false;
	characterFacing = 0;

	// enemy init
	spawnTimer = 1.7f;
	startSpawnTimer = spawnTimer;
	spawnIndex = 0;
	changeSpawnTimer = 0.1f;
	startSpawnChangeTimer = changeSpawnTimer;
	enemySprite1 = CP_Image_Load("Assets/Monster_4.png");
	enemySprite2 = CP_Image_Load("Assets/Monster_2.png");
	damagedSprite1 = CP_Image_Load("Assets/Monster_4_Damaged.png");
	damagedSprite2 = CP_Image_Load("Assets/Monster_2_Damaged.png");
	spawnPosition = CP_Vector_Set(0, 0);
	enemies[spawnIndex].pos.x = spawnPosition.x;
	enemies[spawnIndex].pos.y = spawnPosition.y;
	enemy.width = (float)CP_Image_GetWidth(enemySprite1) - 2.f;	  // 2.0 for polishing purposes
	enemy.height = (float)CP_Image_GetHeight(enemySprite1) - 2.f; // 2.0 for polishing purposes
	enemy.speed = 100;

	// drops init
	dropIndex = 0;
	dropShieldSprite = CP_Image_Load("Assets/Shield_Drop.png"); /// added
	dropEnergySprite = CP_Image_Load("Assets/batteryDrop.png");
	itemDrop[dropIndex].pos.x = spawnPosition.x;
	itemDrop[dropIndex].pos.y = spawnPosition.y;
	healthDrop.width = (float)CP_Image_GetWidth(healthDrop.dropSprite);
	healthDrop.height = (float)CP_Image_GetHeight(healthDrop.dropSprite);

	// misc init
	elapsedTime = 0;
	surviveMin = 1;
	sec = 0;
	min = 0;
	lose = 0;
	win = 0;
	direction = 3;
	// map init
	map_background = CP_Image_Load("Assets/map_background3.png");
	CP_Image obstruction1 = CP_Image_Load("Assets/obstruction4.png");
	CP_Image obstruction2 = CP_Image_Load("Assets/obstruction5.png");
	CP_Image obstruction3 = CP_Image_Load("Assets/obstruction6.png");
	CP_Image obstruction7 = CP_Image_Load("Assets/obstruction7.png");
	CP_Image obstruction8 = CP_Image_Load("Assets/obstruction8.png");
	CP_Image obstruction9 = CP_Image_Load("Assets/obstruction9.png");
	obsWidth7 = (float)CP_Image_GetWidth(obstruction7);
	obsHeight7 = (float)CP_Image_GetHeight(obstruction7);
	obsWidth8 = (float)CP_Image_GetWidth(obstruction8);
	obsHeight8 = (float)CP_Image_GetHeight(obstruction8);
	obsWidth9 = (float)CP_Image_GetWidth(obstruction9);
	obsHeight9 = (float)CP_Image_GetHeight(obstruction9);

	// gameplay init
	canShoot = 0;
	stunned = CP_Image_Load("Assets/stunned_animation.png");
	char_energy = CP_Image_Load("Assets/Char_Energy.png");
	char_health = CP_Image_Load("Assets/Char_Health.png");
	shielded = CP_Image_Load("Assets/Unlimited_Health_Mode.png");
	unlimitedEnergy = CP_Image_Load("Assets/Unlimited_Energy_Mode.png");
	stunnedWidth = (float)CP_Image_GetWidth(stunned);
	stunnedHeight = (float)CP_Image_GetHeight(stunned);
	gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");

	/*Button position/size for pause menu and next level panel, the offset variable is the value to make the button bigger when hovered over*/
	buttonWidthOffset = 20;
	buttonHeightOffset = 20;

	nextLevel.pos.x = wWidth / 2.0f;
	nextLevel.pos.y = wHeight / 2.0f - 200;
	nextLevel.width = 300;
	nextLevel.height = 80;

	resumeButton.pos.x = wWidth / 2.0f;
	resumeButton.pos.y = wHeight / 2.0f - 200;
	resumeButton.width = 300;
	resumeButton.height = 80;

	restartButton.pos.x = wWidth / 2.0f;
	restartButton.pos.y = wHeight / 2.0f - 50;
	restartButton.width = 300;
	restartButton.height = 80;

	menuButton.pos.x = wWidth / 2.0f;
	menuButton.pos.y = wHeight / 2.0f + 100;
	menuButton.width = 300;
	menuButton.height = 80;

	exitLevelButton.pos.x = wWidth / 2.0f;
	exitLevelButton.pos.y = wHeight / 2.0f + 250;
	exitLevelButton.width = 300;
	exitLevelButton.height = 80;

	character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	character.health = 5;	  // start with 5 hp
	character.energy = 5;	  // start with 5 energy
	character.invulState = 0; // start not invul
	character.speed = 210;
	character.transparency = 255; // opaque initially, will be translucent in invul state
	character.shieldedState = 0;
	character.unlimitedEnergyState = 0;
	character.points = previousLevelPoints;
	invulElapsedTime = 0; // timer for invul
	invulTransparencyTime = 0;
	energyRechargeTime = 0; // timer for energyRecharge
	stunnedElapsedTime = 0;
	shieldedDuration = 0;
	unlimitedEnergyDuration = 0;
	isPaused = FALSE;
	nextState = 0.f;
	startCount = FALSE;
	menuState = FALSE;
	exitState = FALSE;
	startCountG = 0.f;
	playVictorySound = FALSE;
	victorySoundCount = 0.f;

	// sound init
	sword_swing = CP_Sound_Load("Assets/sword_swing.wav");
	projectile_shoot = CP_Sound_Load("Assets/projectile.wav");
	pickUp = CP_Sound_Load("Assets/pickup.wav");
	nextlvl_sound = CP_Sound_Load("Assets/nextLevel.wav");
	buttonClickSound = CP_Sound_Load("Assets/buttonClick.wav");
	damageTaken = CP_Sound_Load("Assets/takingDamage.wav");
	stunnedSound = CP_Sound_Load("Assets/stunned.wav");
	// initiate obstruction
	// trees
	for (int i = obstructionCount2, x = 0, y = 0; i < 113; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth * 1 / 10 + x, (float)(wHeight * 1.f / 2.f - obsHeight9 * 0.25 + y), obsWidth9, (float)(obsHeight9 * 0.5), obstruction9);
		x += (int)obs.rec_block[i].width;
		if (i == 106)
		{
			x = 0;
			y += (int)(obs.rec_block[i].height * 2.5);
		}
	}
	// skulls
	for (int i = 113, x = 0, y = 0; i < 129; i++)
	{

		obs.rec_block[i] = SetRect_((float)(wWidth * 1.1 / 2 + x), wHeight * 1 / 2 + y, obsWidth8, obsHeight8, obstruction8);
		x += (int)obs.rec_block[i].width;
		if (i == 120)
		{
			x = 0;
			y -= (int)(obs.rec_block[i].height * 3);
		}
	}
	// top left rocks
	for (int i = 129, x = 0; i < 132; i++)
	{

		obs.rec_block[i] = SetRect_((float)(obsWidth7 * 1.5 + x), (float)(wHeight * 0.8 / 3), obsWidth7, obsHeight7, obstruction7);
		x += (int)(obs.rec_block[i].width * 2);
	}
	// bottom right rocks
	for (int i = 132, x = 0; i < 135; i++)
	{

		obs.rec_block[i] = SetRect_(wWidth * 5 / 6 + x, (float)(wHeight * 1.3 / 2 + obsHeight7), obsWidth7, obsHeight7, obstruction7);
		x -= (int)(obs.rec_block[i].width * 2);
	}
	CP_Sound_ResumeGroup(CP_SOUND_GROUP_1);
	playStunnedSound = 1;
	StunnedSoundTime = 0;
}

void level_3_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	// Force victory sound to not loop with game update function
	if (playVictorySound)
	{
		victorySoundCount += 1.f;
	}
	if (victorySoundCount == 2.f)
		CP_Sound_PlayAdvanced(nextlvl_sound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);

	if (CP_Input_KeyTriggered(KEY_ESCAPE) && win == FALSE)
	{
		isPaused = !isPaused;
	}
	/*pause panel*/
	if (isPaused && win == FALSE)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 1000, 2000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Paused", wWidth / 2.0f, wHeight / 2.0f - 400);
		CP_Settings_TextSize(35.0f);
		Button("Resume Game", resumeButton.pos.x, resumeButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, resumeButton.width, resumeButton.height, 0, 255, 0, 0, 0, 0, 255);
		Button("Restart Game", restartButton.pos.x, restartButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 50, restartButton.width, restartButton.height, 0, 255, 0, 0, 0, 0, 255);
		Button("Exit to Main Menu", menuButton.pos.x, menuButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 100, menuButton.width, menuButton.height, 0, 255, 0, 0, 0, 0, 255);
		Button("Quit Game", exitLevelButton.pos.x, exitLevelButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 250, exitLevelButton.width, exitLevelButton.height, 0, 255, 0, 0, 0, 0, 255);
	}
	/* win/next level panel*/
	if (min == surviveMin || lose == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 1000, 2000);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		if (lose == 0)
		{
			CP_Sound_PauseGroup(CP_SOUND_GROUP_1);
			playVictorySound = TRUE;
			CP_Settings_TextSize(100.0f);
			CP_Font_DrawText("You survived Level 3!", wWidth / 2.0f, wHeight / 2.0f - 400.f);
			CP_Settings_TextSize(35.0f);
			Button("Next level", nextLevel.pos.x, nextLevel.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, nextLevel.width, nextLevel.height, 0, 255, 0, 0, 0, 0, 255);
			Button("Restart Game", restartButton.pos.x, restartButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 50, restartButton.width, restartButton.height, 0, 255, 0, 0, 0, 0, 255);
			Button("Exit to Main Menu", menuButton.pos.x, menuButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 100, menuButton.width, menuButton.height, 0, 255, 0, 0, 0, 0, 255);
			Button("Quit Game", exitLevelButton.pos.x, exitLevelButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 250, exitLevelButton.width, exitLevelButton.height, 0, 255, 0, 0, 0, 0, 255);
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
		CP_Sound_PauseGroup(CP_SOUND_GROUP_1);
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
			{
				level_4_Init();
				CP_Engine_SetNextGameState(level_4_Init, level_4_Update, level_4_Exit);
			}
		}
		/* UI button code*/
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (lose == 0)
		{
			if (win == TRUE)
			{	// next level button
				if (IsAreaClicked(nextLevel.pos.x, nextLevel.pos.y, nextLevel.width, nextLevel.height, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
				{
					delayShootTime = delayShootStart;

					CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					if (!nextState)
						startCount = TRUE;
				}
				else if (IsAreaClicked(nextLevel.pos.x, nextLevel.pos.y, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
				{
					Button("Next level", nextLevel.pos.x, nextLevel.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, nextLevel.width + buttonWidthOffset, nextLevel.height + buttonHeightOffset, 0, 255, 0, 0, 0, 0, 255);
				}
			}

			if (IsAreaClicked(resumeButton.pos.x, resumeButton.pos.y, resumeButton.width, resumeButton.height, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
			{
				if (win == FALSE)
				{
					CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					delayShootTime = delayShootStart;
					isPaused = !isPaused;
				}
			} // resume button
			else if (win == FALSE && IsAreaClicked(resumeButton.pos.x, resumeButton.pos.y, resumeButton.width, resumeButton.height, mouseClickPos.x, mouseClickPos.y) == 1)
			{
				Button("Resume Game", resumeButton.pos.x, resumeButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 200, resumeButton.width + buttonWidthOffset, resumeButton.height + buttonHeightOffset, 0, 255, 0, 0, 0, 0, 255);
			}
		}

		if (IsAreaClicked(restartButton.pos.x, restartButton.pos.y, restartButton.width, restartButton.height, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			if (isPaused == TRUE)
			{
				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				win = FALSE;
				level_3_Init();
			}
		}
		else if (IsAreaClicked(restartButton.pos.x, restartButton.pos.y, restartButton.width, restartButton.height, mouseClickPos.x, mouseClickPos.y))
		{ // restart button
			Button("Restart Game", restartButton.pos.x, restartButton.pos.y, wWidth / 2.0f, wHeight / 2.0f - 50, restartButton.width + buttonWidthOffset, restartButton.height + buttonHeightOffset, 0, 255, 0, 0, 0, 0, 255);
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
		else if (IsAreaClicked(menuButton.pos.x, menuButton.pos.y, menuButton.width, menuButton.height, mouseClickPos.x, mouseClickPos.y) == 1)
		{ // menu button
			Button("Exit to Main Menu", menuButton.pos.x, menuButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 100, menuButton.width + buttonWidthOffset, menuButton.height + buttonHeightOffset, 0, 255, 0, 0, 0, 0, 255);
		}

		if (IsAreaClicked(exitLevelButton.pos.x, exitLevelButton.pos.y, exitLevelButton.width, exitLevelButton.height, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
			{
				startCount = TRUE;
				exitState = TRUE;
			}
		}
		else if (IsAreaClicked(exitLevelButton.pos.x, exitLevelButton.pos.y, exitLevelButton.width, exitLevelButton.height, mouseClickPos.x, mouseClickPos.y) == 1)
		{ // exit button
			Button("Quit Game", exitLevelButton.pos.x, exitLevelButton.pos.y, wWidth / 2.0f, wHeight / 2.0f + 250, exitLevelButton.width + buttonWidthOffset, exitLevelButton.height + buttonHeightOffset, 0, 255, 0, 0, 0, 0, 255);
		}
	}

	if (!isPaused)
	{
		CP_Sound_ResumeGroup(CP_SOUND_GROUP_1);
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

		spawnTimer -= elapsedTime;
		// keeps spawning for 1 minute
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
		}

		// check if spawn timer
		if (spawnTimer <= 0)
		{
			// set random spawn position based on width and height of the screen
			/*The 4 directions represent different locations of the spawn */
			if (direction == 1)	/*top of the map*/
			{
				spawnPosition = CP_Vector_Set(CP_Random_RangeFloat(40, wWidth - 40), 40);
			}
			else if (direction == 2) /*left of the map*/
			{
				spawnPosition = CP_Vector_Set(40, CP_Random_RangeFloat(40, wHeight - 40));
			}
			else if (direction == 3) /*right of the map*/
			{
				spawnPosition = CP_Vector_Set(wWidth - 40, CP_Random_RangeFloat(40, wHeight - 40));
			}
			else if (direction == 4)  /*bottom of the map*/
			{
				spawnPosition = CP_Vector_Set(CP_Random_RangeFloat(40, wWidth - 40), wHeight - 40);
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

			//setting enemy id, health and their sprites with their respective width and height
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
				enemies[spawnIndex].health = 3;
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

		for (int i = 0; i < spawnIndex; i++)
		{
			// enemy movement
			enemies[i].pos = enemyMovement(character.Pos, enemies[i].pos, enemy.speed);

			for (int o = obstructionCount2; o < obstructionCount3; o++)
			{
				// check for obstructions
				if (enemies[i].id == 2)
				{ // ghost monster 4 can move through obstructions
					enemies[i].pos = checkObsCollision(enemies[i].pos, enemies[i].width, enemies[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height);
				}
			}
		}

		if (playerNum == 1)
		{ // IF RANGED CHAR
			bullet.shootPosition = CP_Vector_Set(character.Pos.x, character.Pos.y);

			// SHOOT PROJECTILE MECHANIC

			/*Darren Lua Shoot Projectile Code*/
			if (character.energy > 0)
			{
				if (CP_Input_MouseClicked() && canShoot == 1)
				{
					CP_Sound_PlayAdvanced(projectile_shoot, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
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
			/*bullet movement/velocity*/
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				/*scale the acceleration of the bullet based on the normalized direction and the speed*/
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

						// deletion of projectile after hitting enemy
						for (int x = i; x - 1 < bulletSpawnIndex; ++x)
						{
							bulletArray[x] = bulletArray[x + 1]; // to "delete" element from array
						}
						--bulletSpawnIndex;

						if (enemies[j].health <= 0)
						{
							if (enemies[j].id == 1) {
								character.points += 30;
							}
							else if (enemies[j].id == 2) {
								character.points += 20;
							}

							/*Spawn Item Function*/
							// randomize spawn rate from 1 to 2 meaning 1 in 2 chance of spawn
							/*takes in enemies array struct, itemDrop array struct, 2 CP_Image sprites, pointer to drop index
							j is int and represents enemy index, 1 , 2 represent random range of 1 to 2*/
							spawnItem(enemies, itemDrop, dropShieldSprite, dropEnergySprite, &dropIndex, j, 1, 2);

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
				for (int o = obstructionCount2; o < obstructionCount3; o++)
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

						/*set take damage effect */
						enemies[i].takeDamage = 1.0f;
						/*Darren Lua Item Drop Mechanic*/

						if (enemies[i].health <= 0)
						{
							if (enemies[i].id == 1) {
								character.points += 30;
							}
							else if (enemies[i].id == 2) {
								character.points += 20;
							}

							/*Spawn Item Function*/
							// randomize spawn rate from 1 to 2 meaning 1 in 2 chance of spawn
							/*takes in enemies array struct, itemDrop array struct, 2 CP_Image sprites, pointer to drop index
							i is int and represents enemy index, 1 , 2 represent random range of 1 to 2*/
							spawnItem(enemies, itemDrop, dropShieldSprite, dropEnergySprite, &dropIndex, i, 1, 2);

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

		for (int i = obstructionCount2; i < obstructionCount3; i++)
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
						CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0); // sound for damage taken
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
				}
				else if (itemDrop[i].itemId == 2) // health drop
				{
					character.unlimitedEnergyState = 1;
					unlimitedEnergyDuration = 0;
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
				playStunnedSound = TRUE;
				energyRechargeTime = 0;
			}

			if (character.energy < 1)
			{ // draw stunned animation
				if (playStunnedSound)
				{
					CP_Sound_PlayAdvanced(stunnedSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					StunnedSoundTime += elapsedTime;
					if (StunnedSoundTime)
						playStunnedSound = FALSE;
				}
				else
				{
					StunnedSoundTime = 0;
				}
				CP_Image_Draw(stunned, character.Pos.x, character.Pos.y - 55, (float)CP_Image_GetWidth(stunned), (float)CP_Image_GetHeight(stunned), 255);
			}
		}

		// enemy damaged sprite + draw enemies
		for (int i = 0; i < spawnIndex; i++)
		{
			// damage effect code by Darren Lua
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
				enemies[i].takeDamage -= 1;
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
				if (enemies[i].id == 1)
				{ // draw ghost monster_4 with translucent silhouette
					CP_Image_Draw(enemies[i].enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemies[i].width, enemies[i].height, 150);
				}
				else
				{
					CP_Image_Draw(enemies[i].enemySprite, enemies[i].pos.x, enemies[i].pos.y, enemies[i].width, enemies[i].height, 255);
				}
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

		CP_Settings_TextSize(100.0f);
		sprintf_s(timeString, MAX_LENGTH, "%d:%.2f", min, sec);
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Font_DrawText(timeString, wWidth / 2.0f, wHeight / 2.0f - 450);
		CP_Settings_TextSize(35.0f);

		// display points 
		CP_Settings_TextSize(50.0f);
		sprintf_s(pointsacc, MAX_POINTS, " %d", character.points);
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Font_DrawText("Points: ", wWidth / 2.0f + 750, wHeight / 2.0f - 500);
		CP_Font_DrawText(pointsacc, wWidth / 2.0f + 900, wHeight / 2.0f - 500);
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

void level_3_Exit()
{
	CP_Sound_Free(&sword_swing);
	CP_Sound_Free(&projectile_shoot);
	CP_Sound_Free(&pickUp);
	CP_Sound_Free(&nextlvl_sound);
	CP_Sound_Free(&buttonClickSound);
	CP_Sound_Free(&damageTaken);
	CP_Image_Free(&obstruction4);
	CP_Image_Free(&obstruction5);
	CP_Image_Free(&obstruction6);
	CP_Image_Free(&map_background);
	CP_Sound_Free(&stunnedSound);
}
