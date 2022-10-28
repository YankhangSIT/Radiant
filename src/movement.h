#pragma once


CP_Vector charMovement(CP_Vector charPosition);
CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition);
CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY);
