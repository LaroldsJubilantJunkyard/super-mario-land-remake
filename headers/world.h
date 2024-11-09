#ifndef WORLD_HEADER 
#define WORLD_HEADER size_t

#include "hUGEDriver.h"
#include "object-types.h"

typedef struct WorldStruct{
    uint8_t* tilesetData;
    uint8_t tilesetTileCount;
    uint8_t tilesetBank;
    hUGESong_t music;
    uint8_t musicBank;
    uint8_t objectCount;
    ObjectType* objectTypes[MAX_OBJECT_TYPES];

} World;




extern World worlds[2];
extern World* currentWorld;

void InitializeWorld(void)BANKED;
void UpdateAllObjectsInWorld(void)NONBANKED;

#endif