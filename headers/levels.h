#ifndef LEVELS_HEADER 
#define LEVELS_HEADER size_t

#include "hUGEDriver.h"
#include "object-types.h"
#include "world.h"

typedef struct LevelStruct{

	const World* world;
	uint8_t* tileMap;
	uint8_t tileMapBank;
	uint16_t widthIntiles;
}Level;


extern uint8_t currentLevelIndex;

extern Level levels[4];
extern Level* currentLevel;

void InitializeLevel(uint8_t index)BANKED;

#endif