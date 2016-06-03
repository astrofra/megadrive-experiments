#include <genesis.h>
#include <gfx.h>
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

#define BMP_Y_OFFSET	1

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

	/* Pic A */
	SYS_disableInts();
	VDP_drawImageEx(APLAN, &endscreen_a, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_a.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(APLAN, &endscreen_a2, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, (48 >> 3) + BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_a2.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(APLAN, &endscreen_a3, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, (48 >> 2) + BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_a3.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(APLAN, &endscreen_a4, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, ((48 * 3) >> 3) + BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_a4.tileset->numTile;			


	/* Pic B */
	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &endscreen_b, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_b.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &endscreen_b2, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, (48 >> 3) + BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_b2.tileset->numTile;	

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &endscreen_b3, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, (48 >> 2) + BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_b3.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &endscreen_b4, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 288) >> 4, ((48 * 3) >> 3) + BMP_Y_OFFSET, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += endscreen_b4.tileset->numTile;	

	VDP_fadePalTo(PAL1, endscreen_b.palette->data, RSE_FRAMES(16), FALSE);
	VDP_fadePalTo(PAL0, endscreen_a.palette->data, RSE_FRAMES(16), FALSE);

	while (TRUE)
		VDP_waitVSync();
}