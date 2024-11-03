
#ifndef CAMERA_HEADER 
#define CAMERA_HEADER set

#include <gb/gb.h>
#include "levels.h"

void UpdateCamera(int16_t cameraTargetX, int16_t cameraTargetY, Level* currentLevel) BANKED;
void DrawFullCamera(int16_t cameraTargetX, int16_t cameraTargetY, Level* currentLevel) BANKED;


#endif