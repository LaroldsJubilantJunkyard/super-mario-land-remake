#ifndef ENEMIES_HEADER 
#define ENEMIES_HEADER 

#include <gb/gb.h>

#define MAX_OBJECTS 10

typedef struct ObjectStruct {

    int16_t scaledX, scaledY;
    int16_t velocityX, velocityY;
    uint8_t direction;
    uint8_t active;
} Object;

extern Object objects[MAX_OBJECTS];

void SpawnObject(uint8_t type, uint8_t column, uint8_t row) BANKED;
void InitializeObjects(void)BANKED;

#endif