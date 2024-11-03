#pragma bank 255
#include <gb/gb.h>
#include "levels.h"
#include "camera.h"
#include "World1Area1.h"
#include "World1Tileset.h"

BANKREF(Levels)
BANKREF_EXTERN(World1Tileset)


uint8_t currentLevelIndex=0;

const World worlds[2]={
    {.enemyCount=3,.tilesetBank=BANK(World1Tileset),.tilesetData=World1Tileset_tiles,.tilesetTileCount=World1Tileset_TILE_COUNT},
    {.enemyCount=3}
};
const Level levels[4]={
    
    {.world=&worlds[0],.tileMap=World1Area1_map,.tileMapBank=BANK(World1Area1),.widthIntiles=World1Area1_WIDTH>>3},
    {.world=&worlds[0],.tileMap=World1Area1_map,.tileMapBank=BANK(World1Area1),.widthIntiles=World1Area1_WIDTH>>3},
    {.world=&worlds[1]},
    {.world=&worlds[1]}
};

void InitializeLevel(uint8_t index)NONBANKED{

    InitializeObjects();

    uint8_t previous_bank = CURRENT_BANK;

    Level* currentLevel = &levels[currentLevelIndex=index];

    SWITCH_ROM(currentLevel->world->tilesetBank);

    set_bkg_data(0,currentLevel->world->tilesetTileCount,currentLevel->world->tilesetData);

    DrawFullCamera(0,0,currentLevel);

    SWITCH_ROM(previous_bank);
}