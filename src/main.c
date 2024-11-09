#include <gb/gb.h>
#include <gbdk/far_ptr.h>
#include <stdint.h>
#include "camera.h"
#include "levels.h"
#include "objects.h"
#include "player.h"
#include "common.h"
#include "GameStateManager.h"


void main(void)
{
    InitializeGameStateManager();

	// Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;

    // Loop forever
    while(1) {

        metaspriteCount=0;

        joypadPrevious=joypadCurrent;
        joypadCurrent = joypad();

        UpdateGameStateManager();

        hide_sprites_range(metaspriteCount,40);

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
