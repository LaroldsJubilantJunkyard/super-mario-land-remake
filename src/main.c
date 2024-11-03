#include <gb/gb.h>
#include <stdint.h>
#include "camera.h"
#include "levels.h"
#include "objects.h"


void main(void)
{
	// Turn the background map on to make it visible
    SHOW_BKG;
    
    InitializeLevel(0);

    // Loop forever
    while(1) {


		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
