//---------------------------------------------------------
// file:	main.c
// author:	Koh Yan Khang
// email:	yankhang.k@digipen.edu
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright � 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "mainmenu.h"
#include "level1.h"
#include "splashScreen.h"
#include "characterSelect.h"
#include "loadingScreen.h"
#include "gameOverpage.h"
#include "win.h"
#include "leaderboard.h"
#include "credits.h"
#include "credits_2.h"
#include "Howtoplay.h"
#include "credits_4.h"
int main(void)
{


	CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	//CP_Engine_SetNextGameState(leaderboard_init, leaderboard_update, leaderboard_exit);
	CP_Engine_Run();
	return 0;
}
