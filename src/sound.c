//---------------------------------------------------------
// file:	sound.c
// author:	Wei Jingsong
// email:	jingsong.wei@digipen.edu
// brief:	Includes code for the sound variables
// 
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "sound.h"
CP_Sound sword_swing = NULL;
CP_Sound projectile_shoot = NULL;
CP_Sound pickUp = NULL;
CP_Sound nextlvl_sound = NULL;
CP_Sound buttonClickSound = NULL;
CP_Sound damageTaken = NULL;
CP_Sound gameOverSound = NULL;
CP_Sound backgroundMusic = NULL;
CP_Sound bossTime = NULL;
CP_Sound victorySound = NULL;
CP_Sound stunnedSound = NULL;
float backgroundVolume;
float sfxVolume;
int playStunnedSound = 1;
float StunnedSoundTime = 0;