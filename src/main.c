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
//yk was here
//darren was here
//don was here
//js here

int main(void)
{

	CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_Run();
	return 0;
}
