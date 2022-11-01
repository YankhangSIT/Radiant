#pragma once

int checkDamage(CP_Vector charPosition, float charWidth, float charHeight, CP_Vector enemyPosition, float enemyWidth, float enemyHeight);
//CP_Vector checkEnemyCollision(CP_Vector enemy1Position, CP_Vector enemy2Position, float buffer);
int takeDamage(int charHealth);