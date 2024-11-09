#ifndef ENEMIES_HEADER 
#define ENEMIES_HEADER 


#include <gb/gb.h>
#include <gbdk/far_ptr.h>


#include <gb/metasprites.h>

#define MAX_OBJECTS 10


typedef enum DirectionEnum{Direction_Right,Direction_Left}Direction;

typedef struct ObjectStruct {

    int16_t scaledX, scaledY;
    int16_t velocityX, velocityY;
    Direction direction;
    uint8_t active;
    uint8_t frame;
    uint8_t objectTypeIndex;
} Object;



extern uint8_t metaspriteTileOffsets[MAX_OBJECTS];
extern Object objects[MAX_OBJECTS];

void SpawnObject(uint8_t type, uint8_t column, uint8_t row) BANKED;
void InitializeObjects(void)BANKED;


#endif