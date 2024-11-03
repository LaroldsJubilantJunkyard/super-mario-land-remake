#pragma bank 255
#include <gb/gb.h>
#include <gb/emu_debug.h>
#include "levels.h"
#include "camera.h"
#include "objects.h"
#include "common.h"
#include "World1Area1.h"
#include "MarioSprites.h"
#include "World1Tileset.h"

BANKREF(Levels)
BANKREF_EXTERN(Player)
BANKREF_EXTERN(World1Tileset)


uint8_t currentLevelIndex=0;

const World worlds[2]={
    {.enemyCount=3,.tilesetBank=BANK(World1Tileset),.tilesetData=World1Tileset_tiles,.tilesetTileCount=World1Tileset_TILE_COUNT,.objectTypes={&objectTypes[0],&objectTypes[0],&objectTypes[0],&objectTypes[0]}},
    {.enemyCount=3}
};

const Level levels[4]={
    
    {.world=&worlds[0],.tileMap=World1Area1_map,.tileMapBank=BANK(World1Area1),.widthIntiles=World1Area1_WIDTH>>3},
    {.world=&worlds[0],.tileMap=World1Area1_map,.tileMapBank=BANK(World1Area1),.widthIntiles=World1Area1_WIDTH>>3},
    {.world=&worlds[1]},
    {.world=&worlds[1]}
};


void PopulateVRAMForWorldObjects(World* world)NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    uint8_t offset = 0;

    // player

    SWITCH_ROM(BANK(Player));

    set_sprite_data(0,MarioSprites_TILE_COUNT,MarioSprites_tiles);

    offset+=MarioSprites_TILE_COUNT;

    metaspriteTileOffsets[0]=0;

    for(uint8_t i=0;i<world->enemyCount;i++){

        SWITCH_ROM(world->objectTypes[i]->metaspriteBank);

        set_sprite_data(offset,world->objectTypes[i]->metaspriteTileCount,world->objectTypes[i]->metaspriteTiles);

        metaspriteTileOffsets[i+1]=offset;

        offset+=world->objectTypes[i]->metaspriteTileCount;
;
    }
    SWITCH_ROM(previous_bank);
}


void InitializeLevel(uint8_t index)NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    Level* currentLevel = &levels[currentLevelIndex=index];

    InitializeObjects();
    PopulateVRAMForWorldObjects(currentLevel->world);

    SWITCH_ROM(currentLevel->world->tilesetBank);

    set_bkg_data(0,currentLevel->world->tilesetTileCount,currentLevel->world->tilesetData);

    DrawFullCamera(0,0,currentLevel);

    SWITCH_ROM(previous_bank);
}

void UpdateAllObjects(World* world)NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    for(uint8_t i=0;i<MAX_OBJECTS;i++){
    
        Object* obj = &objects[i];

        if(!obj->active)continue;

        uint8_t index = obj->objectTypeIndex;

        ObjectType* objectType = world->objectTypes[index];

        SWITCH_ROM(objectType->updateFunctionBank);

        objectType->updateFunction(obj);

        uint8_t base_tile = metaspriteTileOffsets[obj->objectTypeIndex];
        
        move_metasprite_banked(objectType->metasprites,obj->frame,base_tile,8+(obj->scaledX>>4),16+(obj->scaledY>>4),objectType->metaspriteBank);
    }

    SWITCH_ROM(previous_bank);
}