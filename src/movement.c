#include "cprocessing.h"
#include "math.h"
#include "stdio.h"

CP_Vector charMovement(CP_Vector charPosition)
{
	float speed = 210.0;
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

CP_Vector enemyMovement(CP_Vector charPosition, CP_Vector enemyPosition)
{
	float enemySpeed = 50.0;
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

CP_Vector checkMapCollision(CP_Vector charPosition, float minX, float maxX, float minY, float maxY) {
	if (charPosition.x <= minX) {
		charPosition.x = minX;
	}
	else if (charPosition.x >= maxX) {
		charPosition.x = maxX;
	}
	if (charPosition.y <= minY) {
		charPosition.y = minY;
	}
	else if (charPosition.y >= maxY) {
		charPosition.y = maxY;
	}
	return charPosition;
	
}