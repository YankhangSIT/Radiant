CP_Vector charMovement(CP_Vector charPosition, float charSpeed);
CP_Image charImageMelee(CP_Image charImage);
CP_Image charImageRanged(CP_Image charImage);
CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition, float enemySpeed);
float toDisplace(CP_Vector enemy1Pos, CP_Vector enemy2Pos, float radius);

//CP_Vector checkEnemyCollision(CP_Vector enemy1Position, CP_Vector enemy2Position, float buffer);