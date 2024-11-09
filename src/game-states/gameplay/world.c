#pragma bank 255

#include <gb/gb.h>

#include <gbdk/far_ptr.h>
#include "world.h"
#include "levels.h"
#include "camera.h"
#include "common.h"
#include "object-types.h"
#include "objects.h"
#include "MarioSprites.h"
#include "World1Tileset.h"
#include "MarioSprites.h"

BANKREF(Worlds)
BANKREF_EXTERN(Player)
BANKREF_EXTERN(Worlds)
BANKREF_EXTERN(World1Tileset)

World* currentWorld;

World worlds[2]={
    {.objectCount=4,.tilesetBank=BANK(World1Tileset),.tilesetData=World1Tileset_tiles,.tilesetTileCount=World1Tileset_TILE_COUNT,.objectTypes={&objectTypes[0],&objectTypes[1],&objectTypes[0],&objectTypes[0]}},
    {.objectCount=4}
};

void PopulateVRAMForWorldObjects(void)NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    uint8_t offset = 0;

    for(uint8_t i=0;i<currentWorld->objectCount;i++){

        SWITCH_ROM(currentWorld->objectTypes[i]->metaspriteBank);

        set_sprite_data(offset,currentWorld->objectTypes[i]->metaspriteTileCount,currentWorld->objectTypes[i]->metaspriteTiles);

        // Save where this object's tile data starts
        currentWorld->objectTypes[i]->metaspriteTileStart=offset;

        // Update the offset for the next object
        offset+=currentWorld->objectTypes[i]->metaspriteTileCount;
    }


    SWITCH_ROM(previous_bank);
}

void PopulateVRAMForWorldTileset(void)NONBANKED{
    
    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(currentWorld->tilesetBank);

    set_bkg_data(0,currentWorld->tilesetTileCount,currentWorld->tilesetData);

    SWITCH_ROM(previous_bank);
}

void InitializeWorld(void)BANKED{


    currentWorld = (currentLevel->world);

    PopulateVRAMForWorldObjects();
    PopulateVRAMForWorldTileset();
}


void UpdateAllObjectsInWorld(void)NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    for(uint8_t i=0;i<MAX_OBJECTS;i++){
    
        Object* obj = &objects[i];

        // Make sure the object is 
        if(!obj->active)continue;

        uint8_t index = obj->objectTypeIndex;

        ObjectType* objectType = currentWorld->objectTypes[index];

        FAR_PTR farPtr = TO_FAR_PTR(objectType->updateFunction,objectType->updateFunctionBank);

        FAR_CALL(farPtr, void (*)(Object*,struct ObjectType*),obj,objectType);

        SWITCH_ROM(objectType->metaspriteBank);

        uint8_t base_tile = objectType->metaspriteTileStart;

        uint8_t x = 8+(obj->scaledX>>4)-camera_x;
        uint8_t y = 16+(obj->scaledY>>4);

        if(obj->direction==Direction_Right)metaspriteCount+= move_metasprite_ex(objectType->metasprites[obj->frame],base_tile,0,metaspriteCount,x,y);
        else metaspriteCount+= move_metasprite_flipx(objectType->metasprites[obj->frame],base_tile,0,metaspriteCount,x,y);

    }

    SWITCH_ROM(previous_bank);
}
