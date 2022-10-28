#pragma once


CP_Vector charMovement(CP_Vector charPosition);
CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition);
CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY);
CP_Vector checkEnemyCollision(CP_Vector enemy1Position, CP_Vector enemy2Position, float buffer);