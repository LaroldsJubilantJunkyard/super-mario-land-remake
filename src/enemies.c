#pragma bank 255


#include <gb/gb.h>
#include "objects.h"
#include "camera.h"


BANKREF(Enemies)

void UpdateEnemy1(Object* enemy1) BANKED{


    enemy1->scaledX-=4;

    if((enemy1->scaledX<<4)<camera_min_x-10){
        enemy1->active=FALSE;
    }
}