#include  <gb/gb.h>
#include <gb/metasprites.h>

uint8_t metaspriteCount= 0;
uint8_t joypadCurrent=0;
uint8_t joypadPrevious=0;

uint8_t move_metasprite_banked(const metasprite_t **metasprites, uint8_t index, uint8_t base_tile,uint8_t x, uint8_t y, uint8_t bank) NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(bank);

    uint8_t count = move_metasprite(metasprites[index],base_tile,metaspriteCount,x,y);

    SWITCH_ROM(previous_bank);

    metaspriteCount+=count;

    return count;
}