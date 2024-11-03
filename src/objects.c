#pragma bank 255

#include <gb/gb.h>
#include "gbdk/emu_debug.h"
#include "objects.h"

BANKREF(Objects)


Object objects[MAX_OBJECTS];

void InitializeObjects(void)BANKED{

    for(uint8_t i=0;i<MAX_OBJECTS;i++){
        objects[i].active=FALSE;
    }
}

void SpawnObject(uint8_t type, uint8_t column, uint8_t row) BANKED{

    EMU_printf("Spawning object %d at (%d,%d)",type,column,row);
}