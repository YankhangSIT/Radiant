#include "cprocessing.h"
#include "math.h"
#include "stdio.h"

CP_Vector charMovement(CP_Vector charPosition)
{
	/*float speed = 210.0;*/
	float speed = 500.0;
	float dtSpeed = speed * CP_System_GetDt(); //CHARACTER SPEED IS 210 UNITS PER SECOND

	if (CP_Input_KeyDown(KEY_A)) {
		charPosition.x -= dtSpeed;
	}
	else if (CP_Input_KeyDown(KEY_D)) {
		charPosition.x += dtSpeed;
	}
	if (CP_Input_KeyDown(KEY_W)) {
		charPosition.y -= dtSpeed;
	}
	else if (CP_Input_KeyDown(KEY_S)) {
		charPosition.y += dtSpeed;
	}

	return charPosition;
}

CP_Image charImage(CP_Image charImage) {
	if (CP_Input_KeyDown(KEY_A)) {
		charImage = CP_Image_Load("Assets/melee_char_facing_left.png");
	}
	else if (CP_Input_KeyDown(KEY_D)) {
		charImage = CP_Image_Load("Assets/melee_char_facing_right.png");
	}
	return charImage;
}

CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition)
{
	float enemySpeed = 10.0;
	float dtEnemySpeed = enemySpeed * CP_System_GetDt(); //ENEMY SPEED IS 100 UNITS PER SECOND

	if (charPosition.x > enemyPosition.x) {
		enemyPosition.x += dtEnemySpeed;
	}
	if (charPosition.x < enemyPosition.x) {
		enemyPosition.x -= dtEnemySpeed;
	}

	if (charPosition.y > enemyPosition.y) {
		enemyPosition.y += dtEnemySpeed;
	}
	if (charPosition.y < enemyPosition.y) {
		enemyPosition.y -= dtEnemySpeed;
	}

	return enemyPosition;
}


//toDisplace(enemy1[i].pos, enemy1[j].pos, enemy.radius);
float toDisplace(CP_Vector enemy1Pos, CP_Vector enemy2Pos, float radius) {
	float xDistance = enemy1Pos.x - enemy2Pos.x;
	float yDistance = enemy1Pos.y - enemy2Pos.y;
	float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
	float toDisplace = 0.5 * distance - (radius * 2);


}

/*
CP_Vector checkEnemyCollision(CP_Vector enemy1Position, CP_Vector enemy2Position, float radius) {
	// buffer is preferred distance between enemies
	float xDistance = enemy2Position.x - enemy1Position.x;
	float yDistance = enemy2Position.y - enemy1Position.y;
	float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
	float toDisplace = 0.5 * distance - (radius * 2);
	//printf("distance between enemy 1 and enemy 2 is: %f\n", distance);

	if (distance < radius) {
		CP_Vector vectorBetween = CP_Vector_Set(xDistance, yDistance);
		return vectorBetween;
		//2 has to go vectorbetween/2
		//1 has to go vectorbetween/-2
		//enemy2Position.x = enemy2Position.x * (vectorBetween.x * 0.5);
		//enemy2Position.y = enemy2Position.y * (vectorBetween.y * 0.5);
		//enemy1Position.x = enemy1Position.x * (vectorBetween.x * -0.5);
		//enemy1Position.y = enemy1Position.y * (vectorBetween.y * -0.5);
	}
	else {
		CP_Vector noChange = CP_Vector_Set(0, 0);
		return noChange;
	}
}
*/
