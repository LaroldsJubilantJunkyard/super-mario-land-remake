#pragma bank 255

#include <gb/gb.h>
#include "gbdk/emu_debug.h"
#include "objects.h"
#include "object-types.h"
#include "camera.h"
#include "common.h"
#include "levels.h"
#include "MarioSprites.h"
#include "player.h"

BANKREF(ObjectTypes)
BANKREF_EXTERN(Player)
BANKREF_EXTERN(Enemies)

void UpdatePlayer(Object* player,ObjectType* objectType)BANKED;
void UpdateEnemy1(Object* enemy1,ObjectType* objectType) BANKED;

/**
 * @brief Our list of all object types. This is intentionally put in RAM, instead of ROM. So we can dynamically set it's `metaspriteTileStart` variable, and so
 * object type data can be accessible globally. 
 */
ObjectType objectTypes[MAX_OBJECT_TYPES] = {

    // The first object should always be the player
    {.updateFunctionBank=BANK(Player),.updateFunction=UpdatePlayer,.metasprites=MarioSprites_metasprites,.metaspriteTiles=MarioSprites_tiles,.metaspriteBank=BANK(MarioSprites),.metaspriteTileCount=MarioSprites_TILE_COUNT},
    {.updateFunctionBank=BANK(Enemies),.updateFunction=UpdateEnemy1,.metasprites=MarioSprites_metasprites,.metaspriteTiles=MarioSprites_tiles,.metaspriteBank=BANK(MarioSprites),.metaspriteTileCount=MarioSprites_TILE_COUNT},
    
};

void DrawObjectType(Object* obj, ObjectType* objectType)NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(objectType->metaspriteBank);

    uint8_t base_tile = objectType->metaspriteTileStart;

    uint8_t x = 8+(obj->scaledX>>4)-camera_x;
    uint8_t y = 16+(obj->scaledY>>4);

    if(obj->direction==Direction_Right)metaspriteCount+= move_metasprite_ex(objectType->metasprites[obj->frame],base_tile,0,metaspriteCount,x,y);
    else metaspriteCount+= move_metasprite_flipx(objectType->metasprites[obj->frame],base_tile,0,metaspriteCount,x,y);

    SWITCH_ROM(previous_bank);
}