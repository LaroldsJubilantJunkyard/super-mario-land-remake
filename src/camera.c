#pragma bank 255

#include <gb/gb.h>
#include "levels.h"
#include "common.h"
#include "objects.h"

BANKREF(Camera)
BANKREF_EXTERN(Levels)

int16_t camera_x, camera_y;
int16_t old_camera_x, old_camera_y;
uint8_t map_pos_x;
uint8_t old_map_pos_x;
int16_t camera_min_x;


void InitializeCamera(void)BANKED{
    camera_x=camera_min_x;
    map_pos_x=old_map_pos_x=0;
}

void DrawCameraRow(uint16_t column, Level* currentLevel,uint8_t widthIntiles) NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;


    SWITCH_ROM(BANK(Levels));

    uint16_t startObjectTiles =currentLevel->world->tilesetTileCount-(currentLevel->world->enemyCount+1);

    for(uint16_t i=0;i<18;i++){

        
        uint8_t* currentLevelTilemap = currentLevel->tileMap;

        SWITCH_ROM(currentLevel->tileMapBank);


        uint16_t tileIndex = column+i*widthIntiles;
        uint16_t tile = currentLevelTilemap[tileIndex];

        uint8_t isObject = tile >= startObjectTiles;

        if(isObject){

            SpawnObject(tile-startObjectTiles,column,i);

            tile=0;
        }

        
        set_bkg_tile_xy(column,i,tile);

    }  


    SWITCH_ROM(previous_bank);
}

uint8_t UpdateCameraPosition(int16_t cameraTargetX) NONBANKED{
    
    uint8_t widthIntiles= 0;

    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(BANK(Levels));
    
    Level* currentLevel = &levels[currentLevelIndex];

    widthIntiles = currentLevel->widthIntiles;

    SWITCH_ROM(previous_bank);

    int16_t currentLevelWidthPixels = widthIntiles<<3;

    SCX_REG=camera_x=MAX(camera_min_x,MIN(cameraTargetX-80,currentLevelWidthPixels-160));

    camera_min_x = camera_x;

    // left or right
    map_pos_x = (uint8_t)(camera_x >> 3u);

    return widthIntiles;
}

void UpdateCamera(int16_t cameraTargetX, int16_t cameraTargetY) NONBANKED{

    Level* currentLevel = &levels[currentLevelIndex];

    uint8_t widthIntiles = UpdateCameraPosition(cameraTargetX);

    if (map_pos_x != old_map_pos_x) {
        if (camera_x < old_camera_x) {
            DrawCameraRow(map_pos_x,currentLevel,widthIntiles);     
        } else {
            if ((widthIntiles - 20u) > map_pos_x) DrawCameraRow(map_pos_x + 20u,currentLevel,widthIntiles);     
        }
        old_map_pos_x = map_pos_x;
    }

    // set old camera position to current camera position
    old_camera_x = camera_x;

}

void DrawFullCamera(int16_t cameraTargetX, int16_t cameraTargetY, Level* currentLevel) BANKED{


    uint8_t widthIntiles = UpdateCameraPosition(cameraTargetX);

    old_map_pos_x = map_pos_x;
    
    for(uint8_t i=0;i<21;i++){
        DrawCameraRow(map_pos_x+i,currentLevel,widthIntiles);
    }
}