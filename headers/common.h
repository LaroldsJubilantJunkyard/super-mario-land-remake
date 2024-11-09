#ifndef COMMON_HEADER 
#define COMMON_HEADER __EDG_SIZE_TYPE__


#define MIN(A,B) ((A)<(B)?(A):(B))
#define MAX(A,B) ((A)>(B)?(A):(B))

#define A_BUTTON_PRESSED ((joypadCurrent & J_A) && !(joypadPrevious & J_A))
#define B_BUTTON_PRESSED ((joypadCurrent & J_B) && !(joypadPrevious & J_B))
#define UP_BUTTON_PRESSED ((joypadCurrent & J_UP) && !(joypadPrevious & J_UP))
#define DOWN_BUTTON_PRESSED ((joypadCurrent & J_DOWN) && !(joypadPrevious & J_DOWN))
#define LEFT_BUTTON_PRESSED ((joypadCurrent & J_LEFT) && !(joypadPrevious & J_LEFT))
#define RIGHT_BUTTON_PRESSED ((joypadCurrent & J_RIGHT) && !(joypadPrevious & J_RIGHT))
#define START_BUTTON_PRESSED ((joypadCurrent & J_START) && !(joypadPrevious & J_START))
#define SELECT_BUTTON_PRESSED ((joypadCurrent & J_SELECT) && !(joypadPrevious & J_SELECT))


extern uint8_t metaspriteCount;
extern uint8_t joypadCurrent;
extern uint8_t joypadPrevious;

void set_bkg_data_banked(uint8_t start, uint8_t tileCount, uint8_t* tiles, uint8_t bank) NONBANKED;
void set_bkg_tiles_banked(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t* map, uint8_t bank) NONBANKED;
void set_bkg_based_tiles_banked(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t* map,uint8_t base, uint8_t bank) NONBANKED;
uint8_t move_metasprite_banked(const metasprite_t **metasprites, uint8_t index, uint8_t base_tile,uint8_t x, uint8_t y, uint8_t bank) NONBANKED;

#endif