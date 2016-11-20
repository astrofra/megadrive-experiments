#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void displayBarbPictureFX(void)
{
	u16 fx_phase, j;

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	// SPR_init(1, 1, 1);

	/* Draw the foreground */
	VDP_drawImageEx(PLAN_A, &barbarian_pic_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
	vramIndex += barbarian_pic_A.tileset->numTile;
	VDP_drawImageEx(PLAN_B, &barbarian_pic_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
	vramIndex += barbarian_pic_B.tileset->numTile;

	SYS_enableInts();

	// VDP_fadePalTo(PAL1, barbarian_pic_B_dark.palette->data, 32, TRUE);
	// RSE_pause(64);
	// VDP_fadePalTo(PAL1, barbarian_pic_B.palette->data, 32, TRUE);
	// RSE_pause(64);
	// VDP_fadePalTo(PAL0, barbarian_pic_A.palette->data, 32, TRUE);
	// RSE_pause(64);

	fx_phase = 0;
	while(fx_phase < 60 * 2) // (vball_phase < VBALL_PHASE_QUIT)
	{
		VDP_waitVSync();
		fx_phase++;
		// BMP_showFPS(0);
	}

	for(j = 0; j  < VDP_getPlanHeight(); j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(j);
		RSE_clearTileRowA(j);
	}	

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);

	SYS_enableInts();	
}