#pragma bank 255


#include <gb/gb.h>
#include "objects.h"
#include "object-types.h"
#include "camera.h"


BANKREF(Enemies)

void UpdateEnemy1(Object* enemy1, struct ObjectType* Type) BANKED{


    enemy1->scaledX-=4;

    if((enemy1->scaledX<<4)<camera_x-10){
        enemy1->active=FALSE;
    }
}