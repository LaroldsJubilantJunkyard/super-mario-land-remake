#pragma bank 255

#include <gb/gb.h>
#include "gbdk/emu_debug.h"
#include "objects.h"
#include "levels.h"
#include "MarioSprites.h"

BANKREF(Objects)
BANKREF_EXTERN(Player)


void UpdatePlayer(Object* player)BANKED;

const ObjectType objectTypes[MAX_OBJECT_TYPES] = {

    // The first object should always be the player
    {.updateFunctionBank=BANK(Player),.updateFunction=UpdatePlayer,.metasprites=MarioSprites_metasprites,.metaspriteTiles=MarioSprites_tiles,.metaspriteBank=BANK(MarioSprites),.metaspriteTileCount=MarioSprites_TILE_COUNT},
};

Object objects[MAX_OBJECTS];
uint8_t metaspriteTileOffsets[MAX_OBJECTS];

void InitializeObjects(void)BANKED{


    for(uint8_t i=0;i<MAX_OBJECTS;i++){
        objects[i].active=FALSE;
        objects[i].frame=0;
        metaspriteTileOffsets[i]=0;
    }

}


void SpawnObject(uint8_t typeIndex, uint8_t column, uint8_t row) BANKED{

    EMU_printf("Spawning object %d at (%d,%d)",typeIndex,column,row);

    for(uint8_t i=0;i<MAX_OBJECTS;i++){
    
        Object* obj = &objects[i];

        if(obj->active)continue;

        obj->scaledX = (column<<3)<<4;
        obj->scaledY = (row<<3)<<4;
        obj->direction=TRUE;
        obj->velocityX=0;
        obj->velocityY=0;
        obj->objectTypeIndex=typeIndex;
        obj->active=TRUE;

        break;
    }

}