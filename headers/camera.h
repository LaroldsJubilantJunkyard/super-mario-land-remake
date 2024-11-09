
#ifndef CAMERA_HEADER 
#define CAMERA_HEADER set

#include <gb/gb.h>
#include "levels.h"


extern int16_t camera_x;

void InitializeCamera(void)BANKED;
void UpdateCamera(int16_t cameraTargetX) BANKED;
void DrawFullCamera(int16_t cameraTargetX) BANKED;


#endif