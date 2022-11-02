#include <stdio.h>
#include "cprocessing.h"
#include <stdlib.h>
#include<stdbool.h>
#include <math.h>
#include "level1.h"



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
CP_Vector checkObsCollision(CP_Vector charPosition, float x, float y, float width, float height) {
    if (charPosition.x > x - width && charPosition.x < x && charPosition.y > y - height && charPosition.y < y) {

       if (fabsf(charPosition.x - (x - width)) < fabsf(charPosition.x-x))
            charPosition.x = x - width;
        else if (fabsf(charPosition.x - (x - width)) > fabsf(charPosition.x - x))
            charPosition.x = x;

        // if (fabsf(charPosition.y - (y - height)) < fabsf(charPosition.y - y))
        //    charPosition.y = y - height;
        //else if (fabsf(charPosition.x - (y - height)) > fabsf(charPosition.y - y))
        //    charPosition.y = y;
    }
       
       
    
    return charPosition;
}
