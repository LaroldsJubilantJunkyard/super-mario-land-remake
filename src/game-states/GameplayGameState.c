#pragma bank 255

#include <gb/gb.h>
#include "levels.h"
#include "world.h"

BANKREF(GameplayGameState)

void SetupGameplayGameState(void)BANKED{
    
    InitializeLevel(0);
}

void UpdateGameplayGameState(void)BANKED{

    // Game main loop processing goes here
    UpdateAllObjectsInWorld();

}