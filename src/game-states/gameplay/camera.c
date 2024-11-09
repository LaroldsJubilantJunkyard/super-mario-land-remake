#pragma bank 255

#include <gb/gb.h>
#include "levels.h"
#include "common.h"
#include "objects.h"
#include "camera.h"

BANKREF(Camera)
BANKREF_EXTERN(Levels)

int16_t camera_x;
int16_t old_camera_x;
uint8_t map_pos_x;
uint8_t old_map_pos_x;


void InitializeCamera(void)BANKED{

    // Position the camera at zero
    DrawFullCamera(0);
}

void DrawCameraRow(uint16_t column) NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(currentLevel->tileMapBank);

    uint16_t startObjectTiles = currentWorld->tilesetTileCount-(currentWorld->objectCount);
        
    uint8_t* currentLevelTilemap = currentLevel->tileMap;

    uint8_t* tileVRAMAddress = get_bkg_xy_addr(column,0);

    for(uint16_t i=0;i<18;i++){

        uint16_t tileIndex = column+i*currentLevel->widthIntiles;
        uint16_t tile = currentLevelTilemap[tileIndex];

        uint8_t isObject = tile >= startObjectTiles;

        if(isObject){

            SpawnObject(tile-startObjectTiles,column,i);

            tile=0;
        }
        
        set_vram_byte(tileVRAMAddress,tile);
        tileVRAMAddress+=32;

    }  


    SWITCH_ROM(previous_bank);
}

void  UpdateCameraPosition(int16_t cameraTargetX) BANKED{
    
    int16_t currentLevelWidthPixels = currentLevel->widthIntiles<<3;

    /**
     * @brief Try to put mario in the center of the camera, but don't go too far to the left or to the right.
     */
    camera_x=MAX(camera_x,MIN(cameraTargetX-80,currentLevelWidthPixels-160));

    SCX_REG = camera_x;

    // left or right
    map_pos_x = (uint8_t)(camera_x >> 3u);

}

void UpdateCamera(int16_t cameraTargetX) BANKED{

    UpdateCameraPosition(cameraTargetX);

    // if the tile fof our camera's position has changed
    if (map_pos_x != old_map_pos_x) {

        // We only move to the right
        if ((currentLevel->widthIntiles - 20u) > map_pos_x) DrawCameraRow(map_pos_x + 20u);    

        old_map_pos_x = map_pos_x;
    }

    // set old camera position to current camera position
    old_camera_x = camera_x;

}

void DrawFullCamera(int16_t cameraTargetX) BANKED{

    UpdateCameraPosition(cameraTargetX);

    // set old camera position to current camera position
    old_map_pos_x = map_pos_x;
    
    for(uint8_t i=0;i<21;i++){

        DrawCameraRow(map_pos_x+i);
    }
}