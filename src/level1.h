#pragma once

void level_1_Init(void);

void level_1_Update(void);

void level_1_Exit(void);


#define PI (3.141592653589793)
#define SIZE (100)
#define FALSE (0)
#define TRUE (1)
#define SPAWNSIZE (5)
#define SPAWNINDEX (4)
#define MAX_LENGTH (100)

int playerNum;

extern struct Button nextLevel;
extern struct Button restart;
extern struct Button menu;
extern struct Button exitLevel;


