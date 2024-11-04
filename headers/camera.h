
#ifndef CAMERA_HEADER 
#define CAMERA_HEADER set

#include <gb/gb.h>
#include "levels.h"


extern int16_t camera_x,camera_min_x;


void InitializeCamera(void)BANKED;
void UpdateCamera(int16_t cameraTargetX, int16_t cameraTargetY) NONBANKED;
void DrawFullCamera(int16_t cameraTargetX, int16_t cameraTargetY, Level* currentLevel) BANKED;


#endif