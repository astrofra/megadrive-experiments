#include <genesis.h>
#include <gfx.h>
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void displayFullScreenPicture(){
	u16 j;

	SYS_disableInts();
	VDP_setPlanSize(64, 32);
	SYS_enableInts();

	for(j = 0; j  < VDP_getPlanHeight(); j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(j);
		RSE_clearTileRowA(j);
	}	

	vramIndex = 8;

	VDP_waitDMACompletion();

	/* Pic 1 */

	// curTileInd = tmp_tile_index;
	SYS_disableInts();
	VDP_drawImageEx(APLAN, &endscreen_a, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, (224 - 192) >> 5, FALSE, TRUE);
	SYS_enableInts();

	VDP_waitDMACompletion();
	VDP_waitVSync();

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &endscreen_b, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex + endscreen_a.tileset->numTile), (320 - 288) >> 4, (224 - 192) >> 5, FALSE, TRUE);
	SYS_enableInts();

	VDP_fadePalTo(PAL1, endscreen_b.palette->data, RSE_FRAMES(16), FALSE);
	VDP_fadePalTo(PAL0, endscreen_a.palette->data, RSE_FRAMES(16), FALSE);

	while (TRUE)
		VDP_waitVSync();
}