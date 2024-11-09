#pragma bank 255

#include <gb/gb.h>
#include <gbdk/far_ptr.h>
#include <stdint.h>
#include "camera.h"
#include "levels.h"
#include "objects.h"
#include "player.h"
#include "common.h"
#include "GameStateManager.h"

BANKREF(GameStateManager)

BANKREF_EXTERN(GameplayGameState)
BANKREF_EXTERN(SplashScreenGameState)
BANKREF_EXTERN(MainMenuGameState)

typedef void (*GameStateFunction)(void) BANKED; // define type for some_bank2_proc1() function

void SetupSplashScreenGameState(void) BANKED;
void SetupMainMenuGameState(void) BANKED;
void SetupGameplayGameState(void) BANKED;

void UpdateSplashScreenGameState(void) BANKED;
void UpdateMainMenuGameState(void) BANKED;
void UpdateGameplayGameState(void) BANKED;

GameStates  currentGameState, nextGameState;
FAR_PTR currentGameStateUpdate, currentGameStateSetup;


void InitializeGameStateManager(void) BANKED{

    currentGameState=GameState_FirstLoad;
    nextGameState=GameState_StartScreen;
}

void SwitchGameStateFunctions(void){

    currentGameState=nextGameState;

    switch(currentGameState){
        case GameState_SplashScreen: 
            currentGameStateSetup = to_far_ptr(SetupSplashScreenGameState,BANK(SplashScreenGameState));
            currentGameStateUpdate = to_far_ptr(UpdateSplashScreenGameState,BANK(SplashScreenGameState));
            break;
        case GameState_StartScreen: 
            currentGameStateSetup = to_far_ptr(SetupMainMenuGameState,BANK(MainMenuGameState));
            currentGameStateUpdate = to_far_ptr(UpdateMainMenuGameState,BANK(MainMenuGameState));
            break;
        case GameState_Gameplay: 
            currentGameStateSetup = to_far_ptr(SetupGameplayGameState,BANK(GameplayGameState));
            currentGameStateUpdate = to_far_ptr(UpdateGameplayGameState,BANK(GameplayGameState));
            break;
    }

}

void UpdateGameStateManager(void)BANKED{

    if(nextGameState!=currentGameState){

        SwitchGameStateFunctions();

        FAR_CALL(currentGameStateSetup, GameStateFunction);
    }


    FAR_CALL(currentGameStateUpdate, GameStateFunction);
}
