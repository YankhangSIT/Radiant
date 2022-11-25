//---------------------------------------------------------
// file:	level4.c
// author:	Koh Yan Khang, Lua Wei Xiang Darren, Wei Jingsong
// email:	yankhang.k@digipen.edu, weixiangdarren.lua@digipen.edu, jingsong.wei@digipen.edu
// brief:	Includes code for the final level of the game, with a final boss consisting of two attack patterns.
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
#include "level4.h"
#include "spawn.h"
#include "map.h"
#include <stdbool.h>
#include <stdlib.h>
#include "button.h"
#include "gameOverpage.h"
#include "global.h"
#include "sound.h"
#include "win.h"

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
float bossMovement;

// string array to use for text display
char timeString[MAX_LENGTH];
char characterHealthDisplay[MAX_LENGTH];
char characterEnergyDisplay[MAX_LENGTH];

void level_4_Init()
{
	// level init
	clear();
	CP_System_FullscreenAdvanced(1920, 1080);
	level = 4;
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

	// boss init
	bossBullet.bulletSpeed = 250;
	bossBullet.startBulletSpeed = bossBullet.bulletSpeed;
	bossBullet.bulletSprite = CP_Image_Load("Assets/Triple_Boss_Bullet.png");
	bossBulletSprite2 = CP_Image_Load("Assets/Spiral_Boss_Bullet.png");
	bossSprite = CP_Image_Load("Assets/Final_boss.png");
	damagedSprite1 = CP_Image_Load("Assets/Final_boss_Damaged.png");
	bossBulletIndex = 0;
	bossBulletIndex2 = 0;
	bossBulletIndex3 = 0;
	bossBullet.width = (float)CP_Image_GetWidth(bossBullet.bulletSprite);
	bossBullet.height = (float)CP_Image_GetHeight(bossBullet.bulletSprite);
	boss.enemySprite = bossSprite;
	boss.pos = CP_Vector_Set(wWidth / 2, wHeight / 6);
	boss.width = (float)CP_Image_GetWidth(bossSprite);
	boss.height = (float)CP_Image_GetHeight(bossSprite);
	boss.height = (float)CP_Image_GetHeight(bossSprite);
	// boss.health = 20;
	boss.health = 1;
	boss.maxHealth = boss.health;
	bossMovement = 5;
	bossShootTimer = 0.5f;
	startBossShootTimer = bossShootTimer;
	bossShootTimer2 = 0.4f;
	startBossShootTimer2 = bossShootTimer2;
	bossShootTimer3 = 0.05f;
	startBossShootTimer3 = bossShootTimer3;
	bossBullet.shootPosition = CP_Vector_Set(boss.pos.x, boss.pos.y);
	bossBullet.shootPosition2 = CP_Vector_Set(boss.pos.x, boss.pos.y);
	bossBullet.shootPosition3 = CP_Vector_Set(boss.pos.x, boss.pos.y);
	changeAttackTimer = 2.f; /*Boss Change Attack Timer*/
	startChangeTimer = changeAttackTimer;
	attackMode = 1;
	bossChangeAttack = 0;
	directionAngle = 0;
	rotationSpeed = 30.142f; /*Boss Bullet shoot rotation speed*/
	bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
	bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
	bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
	for (int i = 0; i < SIZE; i++)
	{
		bossBulletArray[i].isSpawn = 0;
	}

	for (int i = 0; i < SIZE; i++)
	{
		bossBulletArray2[i].isSpawn = 0;
	}

	for (int i = 0; i < SIZE; i++)
	{
		bossBulletArray3[i].isSpawn = 0;
	}

	// drops init (necessary?)
	dropIndex = 0;
	dropShieldSprite = CP_Image_Load("Assets/Shield_Drop.png");
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
	direction = 1;

	// map init
	map_background = CP_Image_Load("Assets/map_background4.png");
	obstruction10 = CP_Image_Load("Assets/obstruction10.png");
	obsWidth10 = (float)CP_Image_GetWidth(obstruction10);
	obsHeight10 = (float)CP_Image_GetHeight(obstruction10);
	obs.rec_block[obstructionCount3] = SetRect_(obsWidth10 / 2, wHeight / 2, obsWidth10, obsHeight10, obstruction10);
	obs.rec_block[obstructionCount3 + 1] = SetRect_(wWidth - obsWidth10 / 2, wHeight / 2, obsWidth10, obsHeight10, obstruction10);
	// gameplay init
	canShoot = 0;
	gunPlayer = CP_Image_Load("Assets/ranged_char_facing_front.png");
	swordPlayer = CP_Image_Load("Assets/melee_char_facing_front.png");
	energyPickup = CP_Image_Load("Assets/energy_pickup_animation.png");
	char_energy = CP_Image_Load("Assets/Char_Energy.png");
	char_health = CP_Image_Load("Assets/Char_Health.png");
	nextLevel.pos.x = wWidth / 2.0f;
	nextLevel.pos.y = wHeight / 2.0f - 200;
	hpBarCurrLengthX = wWidth / boss.maxHealth * boss.health;
	hpbarOriginalX = hpBarCurrLengthX;
	character.Pos = CP_Vector_Set(wWidth / 2, wHeight / 2);
	character.health = 5;	  // start with 5 hp
	character.energy = 5;	  // start with 5 energy
	character.invulState = 0; // start not invul
	character.shieldedState = 0;
	character.unlimitedEnergyState = 0;
	character.speed = 210;
	character.transparency = 255; // opaque initially, will be translucent in invul state
	invulElapsedTime = 0;		  // timer for invul
	invulTransparencyTime = 0;
	energyRechargeTime = 0; // timer for energyRecharge
	stunnedElapsedTime = 0;
	shieldedDuration = 0;
	unlimitedEnergyDuration = 0;
	isPaused = 0;
	nextState = 0.f;
	startCount = FALSE;
	menuState = FALSE;
	exitState = FALSE;
	gameOverState = FALSE;
	startCountG = 0.f;

	// sound init
	sword_swing = CP_Sound_Load("Assets/sword_swing.wav");
	projectile_shoot = CP_Sound_Load("Assets/projectile.wav");
	pickUp = CP_Sound_Load("Assets/pickup.wav");
	buttonClickSound = CP_Sound_Load("Assets/buttonClick.wav");
	damageTaken = CP_Sound_Load("Assets/takingDamage.wav");
	bossTime = CP_Sound_Load("Assets/bossTime.mp3");
	stunnedSound = CP_Sound_Load("Assets/stunned.wav");
	CP_Sound_PlayAdvanced(bossTime, 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_2);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_2, *&backgroundVolume);
	CP_Sound_PauseGroup(CP_SOUND_GROUP_1);
	CP_Sound_ResumeGroup(CP_SOUND_GROUP_2);
	playStunnedSound = 1;
	StunnedSoundTime = 0;
}

void level_4_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	/* Pause Code*/
	if (CP_Input_KeyTriggered(KEY_ESCAPE) && win == 0)
	{
		isPaused = !isPaused;
	}
	/* Pause Menu Panel*/
	if (isPaused && win == 0)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f, 500, wHeight);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Paused", wWidth / 2.0f, wHeight / 2.0f - 300);
		Button("Resume", wWidth / 2.0f, wHeight / 2.0f - 200, wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		Button("Restart", wWidth / 2.0f, wHeight / 2.0f - 50, wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		Button("Menu", wWidth / 2.0f, wHeight / 2.0f + 100, wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, 0, 255, 0, 0, 0, 0, 255);
		Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 250, wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, 0, 255, 0, 0, 0, 0, 255);
	}

	if (boss.health <= 0 || lose == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

		CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 500, wHeight);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		if (lose == 0)
		{
			character.points += 100;

			CP_Sound_PauseGroup(CP_SOUND_GROUP_2);
			CP_Engine_SetNextGameState(win_init, win_update, win_exit);
		}
		else
		{
			CP_Sound_PauseGroup(CP_SOUND_GROUP_2);
			CP_Engine_SetNextGameState(game_Over_page_Init, game_Over_page_Update, game_Over_page_Exit);
		}

		// if (lose == 0)
		//{
		//	win = 1;
		// }

		isPaused = 1;
	}

	if (isPaused)
	{
		CP_Sound_PauseGroup(CP_SOUND_GROUP_2);
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
		}

		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (lose == 0)
		{
			if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
			{
				if (win == 0)
				{
					CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					delayShootTime = delayShootStart;
					isPaused = !isPaused;
				}
			}
			else if (win == FALSE && IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 200, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
			{
				Button("Resume", wWidth / 2.0f, wHeight / 2.0f - 200, wWidth / 2.0f, wHeight / 2.0f - 200, 220, 100, 0, 255, 0, 0, 0, 0, 255);
			}
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			if (isPaused == TRUE)
			{
				CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
				win = FALSE;
				level_4_Init();
			}
		}
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 50, 180, 80, mouseClickPos.x, mouseClickPos.y))
		{
			Button("Restart", wWidth / 2.0f, wHeight / 2.0f - 50, wWidth / 2.0f, wHeight / 2.0f - 50, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
			{
				startCount = TRUE;
				menuState = TRUE;
			}
		}
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Menu", wWidth / 2.0f, wHeight / 2.0f + 100, wWidth / 2.0f, wHeight / 2.0f + 100, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		}

		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1 && CP_Input_MouseClicked())
		{
			CP_Sound_PlayAdvanced(buttonClickSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
			if (!nextState)
			{
				startCount = TRUE;
				exitState = TRUE;
			}
		}
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 250, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1)
		{
			Button("Exit", wWidth / 2.0f, wHeight / 2.0f + 250, wWidth / 2.0f, wHeight / 2.0f + 250, 220, 100, 0, 255, 0, 0, 0, 0, 255);
		}
	}

	if (!isPaused)
	{
		CP_Sound_ResumeGroup(CP_SOUND_GROUP_2);
		CP_Settings_ImageMode(CP_POSITION_CENTER);
		CP_Image_Draw(map_background, wWidth / 2.0f, wHeight / 2.0f, wWidth, wHeight, 255);
		elapsedTime = CP_System_GetDt();
		sec += elapsedTime;
		/*timer code*/
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

		if (playerNum == 1)
		{ // IF RANGED CHAR
			bullet.shootPosition = CP_Vector_Set(character.Pos.x, character.Pos.y);

			// SHOOT PROJECTILE MECHANIC
			/*Shoot Projectile Code*/
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
			/*player bullet movement*/
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

			// boss takes damage from bullets
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				float xDistance = bulletArray[i].bulletPos.x - boss.pos.x;
				float yDistance = bulletArray[i].bulletPos.y - boss.pos.y;
				float distance = (float)sqrt(pow(xDistance, 2) + pow(yDistance, 2));

				// enemies die to bullets
				if (distance < (boss.width - 150.f) && firstShoot == 1) //-150 is fine tuning
				{														// less than bullet radius x2
					--boss.health;
					boss.takeDamage = 1.0f;
					// deletion of projectile after hitting enemy
					for (int x = i; x - 1 < bulletSpawnIndex; ++x)
					{
						bulletArray[x] = bulletArray[x + 1];
					}
					--bulletSpawnIndex;
				}
			}

			// BULLETS DISAPPEAR WHEN COLLIDING WITH OBSTRUCTIONS
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				for (int o = obstructionCount3; o < obstructionCount4; o++)
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

			// BULLETS DISAPPEAR WHEN COLLIDING WITH OBSTRUCTIONS
			for (int i = 0; i - 1 < bulletSpawnIndex; ++i)
			{
				for (int o = obstructionCount3; o < obstructionCount4; o++)
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
				{																															 // SWORD SWING
					if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && swordSwingEnemey(swordSwingArea, boss.pos, (boss.width / 2.f - 60.f))) // 60 is for fine-tuning, boss too fat
					{
						--boss.health;
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

		// draw obs and check player collision with obstruction
		for (int i = obstructionCount3; i < obstructionCount4; i++)
		{
			// draw obstruction
			CP_Image_Draw(obs.rec_block[i].spriteImage, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height, 255);
			// check for obstructions
			character.Pos = checkObsCollision(character.Pos, character.width, character.height, obs.rec_block[i].x, obs.rec_block[i].y, obs.rec_block[i].width, obs.rec_block[i].height);
		}

		// check where character going out of bounds
		character.Pos = checkMapCollision(character.Pos, character.width / 2, wWidth - character.width / 2, character.height / 2, wHeight - character.height / 2);

		/// no enemy obstruction

		// FINAL BOSS MOVEMENT
		if (boss.pos.x < 200.f)
		{
			if (bossMovement < 0)
			{
				bossMovement *= -1;
			}
		}
		else if (boss.pos.x > wWidth - 200.f)
		{
			if (bossMovement > 0)
			{
				bossMovement *= -1;
			}
		}
		boss.pos.x += bossMovement;

		/*Health Bar*/
		/*Corner Mode for the health bar to decrease health from the right*/
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawRect(0, wHeight - 100, hpbarOriginalX, 50);
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(0, wHeight - 100, hpBarCurrLengthX, 50);
		/*For the Boss health bar scaling with the window width*/
		hpBarCurrLengthX = wWidth / boss.maxHealth * boss.health;
		/*Display Boss Health Values*/
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_TextSize(70.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		sprintf_s(timeString, MAX_LENGTH, "Boss Health:%d/%d", boss.health, boss.maxHealth);
		CP_Font_DrawText(timeString, wWidth / 2, wHeight - 75);
		CP_Settings_TextSize(35.0f);

		//  FINAL BOSS MECHANICS

		/*Boss Bullet Projectile*/
		/*Set shooting position to relative position of the boss*/
		bossBullet.shootPosition = CP_Vector_Set(boss.pos.x, boss.pos.y);
		bossBullet.shootPosition2 = CP_Vector_Set(boss.pos.x + boss.width / 2, boss.pos.y);
		bossBullet.shootPosition3 = CP_Vector_Set(boss.pos.x - boss.width / 2, boss.pos.y);

		if (bossChangeAttack == 1)
		{
			changeAttackTimer -= elapsedTime;
		}

		if (changeAttackTimer <= 0)
		{
			/*change attack modes*/
			if (attackMode == 2)
			{
				attackMode = 3;
			}
			else if (attackMode == 1)
			{
				attackMode = 2;
			}
			else if (attackMode == 3)
			{
				attackMode = 1;
			}
			bossChangeAttack = 0;
			/*reset timer*/
			changeAttackTimer = startChangeTimer;
			bossShootTimer = startBossShootTimer;
			bossShootTimer2 = startBossShootTimer2;
			bossShootTimer3 = startBossShootTimer3;
		}
		/*For Boss bullets moving in three parallel direction*/
		if (attackMode == 1)
		{
			bossShootTimer -= elapsedTime;

			if (bossShootTimer <= 0)
			{
				/*Back to Original Boss Bullet Sprite*/
				bossBulletArray[bossBulletIndex].bulletSprite = bossBullet.bulletSprite;
				bossBulletArray[bossBulletIndex].width = (float)CP_Image_GetWidth(bossBulletArray[(int)bossBulletIndex].bulletSprite);
				bossBulletArray[bossBulletIndex].height = (float)CP_Image_GetHeight(bossBulletArray[(int)bossBulletIndex].bulletSprite);

				/*Direction Vector to the player*/
				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				/*Normalised Direction based on the center bullet shoot position*/
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);
				/*Set Bullet Spawn to true*/
				bossBulletArray[bossBulletIndex].isSpawn = 1;

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				/*Normalised Direction based on the center bullet shoot position*/
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex2].directionBullet);
				/*Set Bullet Spawn to true*/
				bossBulletArray2[bossBulletIndex2].isSpawn = 1;

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				/*Normalised Direction based on the center bullet shoot position*/
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex3].directionBullet);
				/*Set Bullet Spawn to true*/
				bossBulletArray3[bossBulletIndex3].isSpawn = 1;

				bossChangeAttack = 1;
				++bossBulletIndex;
				++bossBulletIndex2;
				++bossBulletIndex3;
				bossShootTimer = startBossShootTimer;
			}
		} /*For Boss bullets moving in converging path*/
		else if (attackMode == 2)
		{
			bossShootTimer2 -= elapsedTime;
			if (bossShootTimer2 <= 0)
			{
				/*Back to Original Boss Bullet Sprite*/
				bossBulletArray[bossBulletIndex].bulletSprite = bossBullet.bulletSprite;
				bossBulletArray[bossBulletIndex].width = (float)CP_Image_GetWidth(bossBulletArray[(int)bossBulletIndex].bulletSprite);
				bossBulletArray[bossBulletIndex].height = (float)CP_Image_GetHeight(bossBulletArray[(int)bossBulletIndex].bulletSprite);

				/*Direction Vector to the player which is from character.pos to the boss shooting position*/
				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition);
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);
				bossBulletArray[bossBulletIndex].isSpawn = 1;

				bossBulletArray2[bossBulletIndex2].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition2);
				bossBulletArray2[bossBulletIndex2].bulletPos = bossBullet.shootPosition2;
				bossBulletArray2[bossBulletIndex2].normalizedDirection = CP_Vector_Normalize(bossBulletArray2[bossBulletIndex2].directionBullet);
				bossBulletArray2[bossBulletIndex2].isSpawn = 1;

				bossBulletArray3[bossBulletIndex3].directionBullet = CP_Vector_Subtract(character.Pos, bossBullet.shootPosition3);
				bossBulletArray3[bossBulletIndex3].bulletPos = bossBullet.shootPosition3;
				bossBulletArray3[bossBulletIndex3].normalizedDirection = CP_Vector_Normalize(bossBulletArray3[bossBulletIndex3].directionBullet);
				bossBulletArray3[bossBulletIndex3].isSpawn = 1;
				/*bool to change boss attack*/
				bossChangeAttack = 1;
				/*Increment the 3 bullet indices uses for the 3 arrays*/
				++bossBulletIndex;
				++bossBulletIndex2;
				++bossBulletIndex3;
				bossShootTimer2 = startBossShootTimer2;
			}
		} /*For Boss bullets moving in spiral path*/
		else if (attackMode == 3)
		{
			bossShootTimer3 -= elapsedTime;
			/*Change Boss Bullet Sprite*/
			bossBulletArray[bossBulletIndex].bulletSprite = bossBulletSprite2;
			bossBulletArray[bossBulletIndex].width = (float)CP_Image_GetWidth(bossBulletArray[(int)bossBulletIndex].bulletSprite);
			bossBulletArray[bossBulletIndex].height = (float)CP_Image_GetHeight(bossBulletArray[(int)bossBulletIndex].bulletSprite);

			if (bossShootTimer3 <= 0)
			{

				/*Direction Vector based on the Angle of Rotation */
				bossBulletArray[bossBulletIndex].directionBullet = CP_Vector_Set((float)(cos(directionAngle)), (float)(sin(directionAngle)));
				/*Changing of Direction Angle based on elasped time*/
				directionAngle += rotationSpeed * elapsedTime;
				bossBulletArray[bossBulletIndex].bulletPos = bossBullet.shootPosition;
				bossBulletArray[bossBulletIndex].normalizedDirection = CP_Vector_Normalize(bossBulletArray[bossBulletIndex].directionBullet);
				/*Set Bullet Spawn to true*/
				bossBulletArray[bossBulletIndex].isSpawn = 1;
				/*bool to change boss attack*/
				bossChangeAttack = 1;
				++bossBulletIndex;
				/*reset timer*/
				bossShootTimer3 = startBossShootTimer3;
			}
		}

		/* Bullet Boss Bullet Velocity code*/

		for (int i = 0; i < bossBulletIndex; ++i)
		{
			/* move only bullets that are spawned*/
			if (bossBulletArray[i].isSpawn == 1)
			{
				bossBulletArray[i].acceleration = CP_Vector_Scale(bossBulletArray[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray[i].bulletPos = CP_Vector_Add(bossBulletArray[i].bulletPos, bossBulletArray[i].acceleration);
			}
		}

		for (int i = 0; i < bossBulletIndex2; ++i)
		{
			/* move only bullets that are spawned*/
			if (bossBulletArray2[i].isSpawn == 1)
			{
				bossBulletArray2[i].acceleration = CP_Vector_Scale(bossBulletArray2[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray2[i].bulletPos = CP_Vector_Add(bossBulletArray2[i].bulletPos, bossBulletArray2[i].acceleration);
			}
		}

		for (int i = 0; i < bossBulletIndex3; ++i)
		{
			/* move only bullets that are spawned*/
			if (bossBulletArray3[i].isSpawn == 1)
			{
				bossBulletArray3[i].acceleration = CP_Vector_Scale(bossBulletArray3[i].normalizedDirection, bossBullet.bulletSpeed * elapsedTime);
				bossBulletArray3[i].bulletPos = CP_Vector_Add(bossBulletArray3[i].bulletPos, bossBulletArray3[i].acceleration);
			}
		}

		// damage taking and 2 second invulnerability after code.
		healthChange = 0;											   // to prevent -3 health per frame when colliding with 3 mobs
		if (character.invulState != 1 && character.shieldedState != 1) // TAKE DAMAGE FROM BOSS BULLET ARRAY 1
		{															   // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i < bossBulletIndex; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray[i].bulletPos, (bossBulletArray[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{
						CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}
		if (character.invulState != 1 && character.shieldedState != 1) // TAKE DAMAGE FROM BOSS BULLET ARRAY 2
		{															   // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i < bossBulletIndex2; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray2[i].bulletPos, (bossBulletArray2[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{
						CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}
		if (character.invulState != 1 && character.shieldedState != 1) // TAKE DAMAGE FROM BOSS BULLET ARRAY 3
		{															   // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			for (int i = 0; i < bossBulletIndex3; ++i)
			{
				if (checkDamage(character.Pos, character.width, character.height, bossBulletArray3[i].bulletPos, (bossBulletArray3[i].width / 2)) == 1)
				{
					if (healthChange == 0)
					{
						CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
						character.health = takeDamage(character.health);
						healthChange = 1; // telling program health has changed, dont change again in this frame
					}
					character.invulState = 1;
				}
			}
		}
		if (character.invulState != 1 && character.shieldedState != 1) // TAKE DAMAGE WHEN COLLIDE WITH BOSS
		{															   // if not invul, check for damage (collision with mobs) every frame
			character.transparency = 255;
			if (checkDamage(character.Pos, character.width, character.height, boss.pos, (boss.width / 2)) == 1)
			{
				if (healthChange == 0)
				{
					CP_Sound_PlayAdvanced(damageTaken, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_0);
					character.health = takeDamage(character.health);
					healthChange = 1; // telling program health has changed, dont change again in this frame
				}
				character.invulState = 1;
			}
		}

		// check if projectile out of bounds, if so, delete it.
		for (int i = 0; i < bossBulletIndex; ++i)
		{
			if (checkProjectileMapCollision(bossBulletArray[i].bulletPos, 0 + bossBullet.width / 2, wWidth - bossBullet.width / 2, 0 + bossBullet.height / 2, wHeight - bossBullet.height / 2) == 1)
			{
				for (int x = i; x < bossBulletIndex; ++x)
				{
					bossBulletArray[x] = bossBulletArray[x + 1]; // to "delete" element from array
				}
				--bossBulletIndex;
			}
		}

		for (int i = 0; i < bossBulletIndex2; ++i)
		{
			if (checkProjectileMapCollision(bossBulletArray2[i].bulletPos, 0 + bossBullet.width / 2, wWidth - bossBullet.width / 2, 0 + bossBullet.height / 2, wHeight - bossBullet.height / 2) == 1)
			{
				for (int x = i; x < bossBulletIndex2; ++x)
				{
					bossBulletArray2[x] = bossBulletArray2[x + 1]; // to "delete" element from array
				}
				--bossBulletIndex2;
			}
		}

		for (int i = 0; i < bossBulletIndex3; ++i)
		{
			if (checkProjectileMapCollision(bossBulletArray3[i].bulletPos, 0 + bossBullet.width / 2, wWidth - bossBullet.width / 2, 0 + bossBullet.height / 2, wHeight - bossBullet.height / 2) == 1)
			{
				for (int x = i; x < bossBulletIndex3; ++x)
				{
					bossBulletArray3[x] = bossBulletArray3[x + 1]; // to "delete" element from array
				}
				--bossBulletIndex3;
			}
		}

		// BULLETS DISAPPEAR WHEN COLLIDING WITH OBSTRUCTIONS
		for (int i = 0; i < bossBulletIndex; ++i)
		{
			for (int o = obstructionCount3; o < obstructionCount4; o++)
			{ // check if projectile hits obstructions, if so, delete it.
				if (checkProjectileObsCollision(bossBulletArray[i].bulletPos, bossBulletArray[i].width, bossBulletArray[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height))
				{
					// check for obstructions
					for (int x = i; x < bossBulletIndex; ++x)
					{
						bossBulletArray[x] = bossBulletArray[x + 1]; // to "delete" element from array
					}
					--bossBulletIndex;
				}
			}
		}

		for (int i = 0; i < bossBulletIndex2; ++i)
		{
			for (int o = obstructionCount3; o < obstructionCount4; o++)
			{ // check if projectile hits obstructions, if so, delete it.
				if (checkProjectileObsCollision(bossBulletArray2[i].bulletPos, bossBulletArray2[i].width, bossBulletArray2[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height))
				{
					// check for obstructions
					for (int x = i; x < bossBulletIndex2; ++x)
					{
						bossBulletArray2[x] = bossBulletArray2[x + 1]; // to "delete" element from array
					}
					--bossBulletIndex2;
				}
			}
		}

		for (int i = 0; i < bossBulletIndex3; ++i)
		{
			for (int o = obstructionCount3; o < obstructionCount4; o++)
			{ // check if projectile hits obstructions, if so, delete it.
				if (checkProjectileObsCollision(bossBulletArray3[i].bulletPos, bossBulletArray3[i].width, bossBulletArray3[i].height, obs.rec_block[o].x, obs.rec_block[o].y, obs.rec_block[o].width, obs.rec_block[o].height))
				{
					// check for obstructions
					for (int x = i; x < bossBulletIndex3; ++x)
					{
						bossBulletArray3[x] = bossBulletArray3[x + 1]; // to "delete" element from array
					}
					--bossBulletIndex3;
				}
			}
		}

		// check boss projectile collision with obstruction

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

		if (boss.takeDamage == 1.0f)
		{
			boss.enemySprite = damagedSprite1;
			CP_Image_Draw(boss.enemySprite, boss.pos.x, boss.pos.y, boss.width, boss.height, 255);
			boss.takeDamage -= 1;
		}
		else
		{
			boss.enemySprite = bossSprite;
		}

		CP_Image_Draw(boss.enemySprite, boss.pos.x, boss.pos.y, boss.width, boss.height, 255);

		for (int i = 0; i < bossBulletIndex; ++i)
		{
			/* draw only bullets that are spawned*/
			if (bossBulletArray[i].isSpawn == 1)
			{
				CP_Image_Draw(bossBulletArray[i].bulletSprite, bossBulletArray[i].bulletPos.x, bossBulletArray[i].bulletPos.y, bullet.width, bullet.height, 255);
			}
		}

		for (int i = 0; i < bossBulletIndex2; ++i)
		{
			/* draw only bullets that are spawned*/
			if (bossBulletArray2[i].isSpawn == 1)
			{
				CP_Image_Draw(bossBullet.bulletSprite, bossBulletArray2[i].bulletPos.x, bossBulletArray2[i].bulletPos.y, bullet.width, bullet.height, 255);
			}
		}

		for (int i = 0; i < bossBulletIndex3; ++i)
		{
			/* draw only bullets that are spawned*/
			if (bossBulletArray3[i].isSpawn == 1)
			{
				CP_Image_Draw(bossBullet.bulletSprite, bossBulletArray3[i].bulletPos.x, bossBulletArray3[i].bulletPos.y, bullet.width, bullet.height, 255);
			}
		}
	}
}

void level_4_Exit()
{
	CP_Sound_Free(&sword_swing);
	CP_Sound_Free(&projectile_shoot);
	CP_Sound_Free(&pickUp);
	CP_Sound_Free(&nextlvl_sound);
	CP_Sound_Free(&buttonClickSound);
	CP_Sound_Free(&gameOverSound);
	CP_Sound_Free(&damageTaken);
	CP_Image_Free(&obstruction1);
	CP_Image_Free(&obstruction2);
	CP_Image_Free(&obstruction3);
	CP_Image_Free(&map_background);
	CP_Sound_Free(&stunnedSound);
}
