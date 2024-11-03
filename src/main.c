#include <gb/gb.h>
#include <stdint.h>
#include "camera.h"
#include "levels.h"
#include "objects.h"
#include "common.h"


void main(void)
{
	// Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;

    
    InitializeLevel(0);

    // Loop forever
    while(1) {

        metaspriteCount=0;

        const World* world = levels[currentLevelIndex].world;

		// Game main loop processing goes here
        UpdateAllObjects(world);

        hide_sprites_range(metaspriteCount,40);

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
