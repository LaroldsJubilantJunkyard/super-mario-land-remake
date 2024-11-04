#pragma bank 255

#include <gb/gb.h>
#include <gb/emu_debug.h>
#include <gb/metasprites.h>
#include "common.h"
#include "objects.h"
#include "camera.h"
#include "levels.h"
#include "MarioSprites.h"


BANKREF(Player)
BANKREF_EXTERN(MarioSprites)


Object* player;

void UpdatePlayer(Object* player)BANKED{

    if(joypadCurrent & J_RIGHT){
        player->velocityX=10;
    }else if(joypadCurrent & J_LEFT){
        player->velocityX=-10;
    }else{

        if((player->velocityX>>4)>0){
            player->velocityX-=1;
        }else if((player->velocityX>>4)<0){
            player->velocityX+=1;
        }else{
            player->velocityX=0;
        }
    }


    player->scaledX+=player->velocityX;


    UpdateCamera(player->scaledX>>4,player->scaledY>>4);
}   