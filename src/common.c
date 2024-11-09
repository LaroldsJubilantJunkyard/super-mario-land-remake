#include  <gb/gb.h>
#include <gb/metasprites.h>

uint8_t metaspriteCount= 0;
uint8_t joypadCurrent=0;
uint8_t joypadPrevious=0;

void set_bkg_data_banked(uint8_t start, uint8_t tileCount, uint8_t* tiles, uint8_t bank) NONBANKED{
 
    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(bank);

    set_bkg_data(start,tileCount,tiles);

    SWITCH_ROM(previous_bank);
}

void set_bkg_tiles_banked(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t* map, uint8_t bank) NONBANKED{
 
    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(bank);

    set_bkg_tiles(x,y,w,h,map);

    SWITCH_ROM(previous_bank);
}
void set_bkg_based_tiles_banked(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t* map,uint8_t base, uint8_t bank) NONBANKED{
    
    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(bank);

    set_bkg_based_tiles(x,y,w,h,map,base);

    SWITCH_ROM(previous_bank);
}

uint8_t move_metasprite_banked(const metasprite_t **metasprites, uint8_t index, uint8_t base_tile,uint8_t x, uint8_t y, uint8_t bank) NONBANKED{

    uint8_t previous_bank = CURRENT_BANK;

    SWITCH_ROM(bank);

    uint8_t count = move_metasprite(metasprites[index],base_tile,metaspriteCount,x,y);

    SWITCH_ROM(previous_bank);

    metaspriteCount+=count;

    return count;
}