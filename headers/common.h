#ifndef COMMON_HEADER 
#define COMMON_HEADER __EDG_SIZE_TYPE__


#define MIN(A,B) ((A)<(B)?(A):(B))
#define MAX(A,B) ((A)>(B)?(A):(B))


extern uint8_t metaspriteCount;
extern uint8_t joypadCurrent;
extern uint8_t joypadPrevious;

uint8_t move_metasprite_banked(const metasprite_t **metasprites, uint8_t index, uint8_t base_tile,uint8_t x, uint8_t y, uint8_t bank) NONBANKED;

#endif