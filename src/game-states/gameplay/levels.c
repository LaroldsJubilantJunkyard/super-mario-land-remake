#pragma bank 255
#include <gb/gb.h>
#include <gb/emu_debug.h>
#include "levels.h"
#include "camera.h"
#include "world.h"
#include "objects.h"
#include "common.h"
#include "World1Area1.h"
#include "MarioSprites.h"
#include "World1Tileset.h"

BANKREF(Levels)
BANKREF_EXTERN(Player)
BANKREF_EXTERN(Worlds)
BANKREF_EXTERN(World1Tileset)


uint8_t currentLevelIndex=0;
Level levels[4]={
    
    {.world=&worlds[0],.tileMap=World1Area1_map,.tileMapBank=BANK(World1Area1),.widthIntiles=World1Area1_WIDTH>>3},
    {.world=&worlds[0],.tileMap=World1Area1_map,.tileMapBank=BANK(World1Area1),.widthIntiles=World1Area1_WIDTH>>3},
    {.world=&worlds[1]},
    {.world=&worlds[1]}
};

Level* currentLevel;

void InitializeLevel(uint8_t index)BANKED{

    /**
     * @brief Copy the current level from ROM, into RAM. So later values can be used
     * without having to switch banks.
     */
    currentLevel = &levels[currentLevelIndex = index];

    InitializeWorld();
    InitializeObjects();
    InitializeCamera();
}

