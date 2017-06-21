#include <genesis.h>
#include <gfx.h>
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void ankouScreenFX(void){
	u16 vcount;

	RSE_turn_screen_to_black();

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	/* Draw the background */	

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setVerticalScroll(PLAN_B, 0);
	VDP_setVerticalScroll(PLAN_A, 0);
	VDP_setHorizontalScroll(PLAN_B, 0);
	VDP_setHorizontalScroll(PLAN_A, 0);	

	SYS_enableInts();

	vramIndex = TILE_USERINDEX;
	VDP_waitDMACompletion();

	/* Pic 0 */
	// tmp_tile_index = curTileInd;
	VDP_drawImageEx(PLAN_A, &exocet_ankou_back_0, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += exocet_ankou_back_0.tileset->numTile;
	VDP_waitVSync();

	VDP_drawImageEx(PLAN_A, &exocet_ankou_back_1, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 80 >> 3, 0, FALSE, TRUE);
	vramIndex += exocet_ankou_back_1.tileset->numTile;
	VDP_waitVSync();

	VDP_drawImageEx(PLAN_A, &exocet_ankou_back_2, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 160 >> 3, 0, FALSE, TRUE);
	vramIndex += exocet_ankou_back_2.tileset->numTile;
	VDP_waitVSync();

	VDP_drawImageEx(PLAN_A, &exocet_ankou_back_3, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 240 >> 3, 0, FALSE, TRUE);
	vramIndex += exocet_ankou_back_3.tileset->numTile;
	VDP_waitVSync();

	VDP_drawImageEx(PLAN_B, &exocet_ankou_front_0, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, 0,  FALSE, TRUE);
	vramIndex += exocet_ankou_front_0.tileset->numTile;
	VDP_waitVSync();

	VDP_drawImageEx(PLAN_B, &exocet_ankou_front_1, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 80 >> 3, 0, FALSE, TRUE);
	vramIndex += exocet_ankou_front_1.tileset->numTile;
	VDP_waitVSync();

	VDP_drawImageEx(PLAN_B, &exocet_ankou_front_2, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 160 >> 3, 0, FALSE, TRUE);
	vramIndex += exocet_ankou_front_2.tileset->numTile;
	VDP_waitVSync();

	VDP_drawImageEx(PLAN_B, &exocet_ankou_front_3, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 240 >> 3, 0, FALSE, TRUE);
	vramIndex += exocet_ankou_front_3.tileset->numTile;
	VDP_waitVSync();

	VDP_fadePalTo(PAL1, exocet_ankou_darken.palette->data, RSE_FRAMES(32), TRUE);
	RSE_pause(RSE_FRAMES(32));
	VDP_fadePalTo(PAL1, exocet_ankou_front_0.palette->data, RSE_FRAMES(24), TRUE);
	RSE_pause(RSE_FRAMES(24));
	VDP_fadePalTo(PAL0, exocet_ankou_back_0.palette->data, RSE_FRAMES(16), TRUE);
	RSE_pause(RSE_FRAMES(16));	

	vcount = 0;
	while(vcount < 60 * 5)
	{
		VDP_waitVSync();
		vcount++;
	}

	VDP_fadeOut(1, 63, 16, FALSE);

	RSE_resetScrolling();

	RSE_turn_screen_to_black();

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);

	SYS_enableInts();

	// vramIndex = TILE_USERINDEX;

}