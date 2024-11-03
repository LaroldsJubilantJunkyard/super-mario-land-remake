#ifndef LEVELS_HEADER 
#define LEVELS_HEADER size_t

#include "hUGEDriver.h"

typedef struct WorldStruct{
    uint8_t* tilesetData;
    uint8_t tilesetTileCount;
    uint8_t tilesetBank;
    hUGESong_t music;
    uint8_t musicBank;
    uint8_t enemyCount;
} World;


typedef struct LevelStruct{

	const World* world;
	uint8_t* tileMap;
	uint8_t tileMapBank;
	uint16_t widthIntiles;
}Level;


extern uint8_t currentLevelIndex;

extern const Level levels[4];
extern const World worlds[2];


void InitializeLevel(uint8_t index)NONBANKED;

#endif