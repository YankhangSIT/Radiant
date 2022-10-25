#include <stdio.h>
#include "cprocessing.h"
#include <stdlib.h>
#include <math.h>
#include "carlevel.h"

#define GRID_COLS 192
#define GRID_ROWS 108
#define GRID_BUFFERS 2

#define ALIVE 1
#define DEAD 0

#define TRUE 1
#define FALSE 0

int gIsPaused;
int gGrids[GRID_BUFFERS][GRID_ROWS][GRID_COLS];
int sumOfLiveNeighbors;
float width;
float height;
int currentState;

int IsGridClicked(float area_corner_x, float area_corner_y, float area_width, float area_height, float click_x, float click_y)
{
    // TODO
    if (click_x < area_corner_x) {
        return 0;
    }
    else if (click_x > area_corner_x + area_width) {
        return 0;
    }
    else if (click_y < area_corner_y ) {
        return 0;
    }
    else if (click_y > area_corner_y + area_height) {
        return 0;
    }
    return 1;

}

void level_1_Init(void)
{
    /* Set every grids' cells as 'dead' */
    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            for (int i = 0; i < GRID_BUFFERS; ++i) {
                gGrids[i][row][col] = DEAD;
            }
        }
    }
    /*********************************************************
    *  Let's start with gGrids[0] as the 'reference grid'
    *  and gGrids[1] as the 'displaying grid'.
    *
    *  We initialize gGrids[0] with a simple 'glider'.
    *********************************************************/
   
    gGrids[0][1][2] = ALIVE;
    gGrids[0][2][2] = ALIVE;
    gGrids[0][3][2] = ALIVE;

    gGrids[0][1][3] = ALIVE;
    gGrids[0][2][3] = ALIVE;
    gGrids[0][3][3] = ALIVE;

    gGrids[0][1][4] = ALIVE;
    gGrids[0][2][4] = ALIVE;
    gGrids[0][3][4] = ALIVE;


    gGrids[0][50][80] = ALIVE;
    gGrids[0][51][80] = ALIVE;
    gGrids[0][52][80] = ALIVE;

    /* We start unpaused */
    gIsPaused = FALSE;

    /* Initialization of your other variables here */
    CP_System_SetWindowSize(1920, 1080);
    sumOfLiveNeighbors = 0;
    currentState = 0;
    width = CP_System_GetWindowWidth() / GRID_COLS;
    height = CP_System_GetWindowHeight() / GRID_ROWS;
}

void level_1_Update(void)
{
    //Game rendering
    CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_RectMode(CP_POSITION_CORNER);
    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            if (gGrids[0][row][col] == ALIVE)
                CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
            else CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
            CP_Settings_NoStroke();
            CP_Graphics_DrawRect(col * width, row * height, width, height);
        }
    }
    ////check key input
    //if (CP_Input_KeyTriggered(KEY_ANY)) {
    //    //pause game if any key triggered
    //    gIsPaused = !gIsPaused;
    //}
    ////Game paused logic
    //if (gIsPaused) {
    //    
    //   
    //}
    ////Game resume logic
    //else {
    //    for (int row = 0; row < GRID_ROWS; ++row) {
    //        for (int col = 0; col < GRID_COLS; ++col) {
    //            currentState = gGrids[0][row][col];
    //            
    //        }
    //    }
    //    for (int row = 0; row < GRID_ROWS; ++row) {
    //        for (int col = 0; col < GRID_COLS; ++col) {

    //            gGrids[0][row][col] = gGrids[1][row][col];

    //        }
    //    }
    //}
}

void level_1_Exit(void)
{

}
