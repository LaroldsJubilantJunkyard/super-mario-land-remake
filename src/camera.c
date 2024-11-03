#pragma bank 255

#include <gb/gb.h>
#include "levels.h"
#include "common.h"
#include "objects.h"

int16_t camera_x, camera_y;
int16_t old_camera_x, old_camera_y;
uint8_t map_pos_x;
uint8_t old_map_pos_x;

void DrawCameraRow(uint16_t column, Level* currentLevel) NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(currentLevel->tileMapBank);

    uint16_t startObjectTiles =currentLevel->world->tilesetTileCount-(currentLevel->world->enemyCount+1);

    for(uint16_t i=0;i<18;i++){

        uint16_t tileIndex = column+i*currentLevel->widthIntiles;
        uint16_t tile = currentLevel->tileMap[tileIndex];

        uint8_t isObject = tile >= startObjectTiles;

        if(isObject){

            SpawnObject(tile-startObjectTiles,column,i);

            tile=0;
        }

        
        set_bkg_tile_xy(column,i,tile);

    }  


    SWITCH_ROM(previous_bank);
}

void UpdateCamera(int16_t cameraTargetX, int16_t cameraTargetY, Level* currentLevel) BANKED{

    int16_t currentLevelWidthPixels = currentLevel->widthIntiles>>3;
    camera_x=MAX(cameraTargetX-80,MIN(0,currentLevelWidthPixels-160));

    // left or right
    map_pos_x = (uint8_t)(camera_x >> 3u);
    if (map_pos_x != old_map_pos_x) {
        if (camera_x < old_camera_x) {
            DrawCameraRow(map_pos_x,currentLevel);     
        } else {
            if ((currentLevel->widthIntiles - 20u) > map_pos_x) DrawCameraRow(map_pos_x + 20u,currentLevel);     
        }
        old_map_pos_x = map_pos_x;
    }
}

void DrawFullCamera(int16_t cameraTargetX, int16_t cameraTargetY, Level* currentLevel) BANKED{

   int16_t currentLevelWidthPixels = currentLevel->widthIntiles<<3;
   camera_x=MAX(cameraTargetX-80,MIN(0,currentLevelWidthPixels-160));

    // left or right
    map_pos_x = (uint8_t)(camera_x >> 3u);
    
    for(uint8_t i=0;i<21;i++){
        DrawCameraRow(map_pos_x+i,currentLevel);
    }
}