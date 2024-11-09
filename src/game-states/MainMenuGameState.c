#pragma bank 255

#include <gb/gb.h>
#include "Font.h"
#include "text.h"
#include "common.h"
#include "StartScreenBackground.h"
#include "GameStateManager.h"

BANKREF(MainMenuGameState)
BANKREF_EXTERN(StartScreenBackground)
BANKREF_EXTERN(Font)

uint8_t mainMenuSelection=0;

void UpdateMainMenuSelection(void){

    if(mainMenuSelection==0){
        set_bkg_tile_xy(4,13,41);
        set_bkg_tile_xy(4,14,0);
    }else {
        set_bkg_tile_xy(4,13,0);
        set_bkg_tile_xy(4,14,41);
    }
}

void SetupMainMenuGameState(void)BANKED{

    set_bkg_data_banked(0,Font_TILE_COUNT,Font_tiles,BANK(Font));
    set_bkg_data_banked(Font_TILE_COUNT,StartScreenBackground_TILE_COUNT,StartScreenBackground_tiles,BANK(StartScreenBackground));

    set_bkg_based_tiles_banked(0,0,20,18,StartScreenBackground_map,Font_TILE_COUNT,BANK(StartScreenBackground));

    DrawText(9,11,"000000");
    DrawText(6,13,"START");
    DrawText(6,14,"CONTINUE X");

    UpdateMainMenuSelection();
}
void UpdateMainMenuGameState(void)BANKED{

    if(A_BUTTON_PRESSED){
        nextGameState=GameState_Gameplay;
    }

    if(DOWN_BUTTON_PRESSED){
        mainMenuSelection= (mainMenuSelection+1)%2;

        UpdateMainMenuSelection();
    }
    
    if(UP_BUTTON_PRESSED){
        mainMenuSelection= mainMenuSelection==0? 1 : 0;

        UpdateMainMenuSelection();
    }
}