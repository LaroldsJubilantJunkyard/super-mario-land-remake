#ifndef OBJECT_TYPE_HEADER 
#define OBJECT_TYPE_HEADER  set

#include <gb/gb.h>
#include <gb/metasprites.h>
#include "objects.h"

#define MAX_OBJECT_TYPES 10


typedef struct ObjectType{

    uint8_t metaspriteBank;
    uint8_t* metaspriteTiles;
    uint8_t metaspriteTileCount;
    metasprite_t** metasprites;
    uint8_t metaspriteTileStart;

    uint8_t updateFunctionBank;
    void (*updateFunction)(Object* object, struct ObjectType *type)BANKED;

}ObjectType;

typedef  void (*ObjectTypeUpdateFunction)(Object*,struct ObjectType*) ;


/**
 * @brief Our list of all object types. This is intentionally put in RAM, instead of ROM. So we can dynamically set it's `metaspriteTileStart` variable, and so
 * object type data can be accessible globally. 
 */
extern ObjectType objectTypes[MAX_OBJECT_TYPES];

void DrawObjectType(Object* obj, ObjectType* objectType)NONBANKED;


#endif