#ifndef ENEMIES_HEADER 
#define ENEMIES_HEADER 

#include <gb/gb.h>
#include <gb/metasprites.h>

#define MAX_OBJECTS 10
#define MAX_OBJECT_TYPES 10




typedef struct ObjectStruct {

    int16_t scaledX, scaledY;
    int16_t velocityX, velocityY;
    uint8_t direction;
    uint8_t active;
    uint8_t frame;
    uint8_t objectTypeIndex;

} Object;


typedef struct ObjectTypeStruct{

    uint8_t metaspriteBank;
    uint8_t* metaspriteTiles;
    uint8_t metaspriteTileCount;
    metasprite_t** metasprites;

    uint8_t updateFunctionBank;
    void (*updateFunction)(Object* object)BANKED;

}ObjectType;

extern uint8_t metaspriteTileOffsets[MAX_OBJECTS];
extern Object objects[MAX_OBJECTS];
extern const ObjectType objectTypes[MAX_OBJECT_TYPES];

void SpawnObject(uint8_t type, uint8_t column, uint8_t row) BANKED;
void InitializeObjects(void)BANKED;

#endif