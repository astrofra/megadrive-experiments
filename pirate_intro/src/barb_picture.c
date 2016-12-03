#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void displayBarbPictureFX(void)
{
	u16 fx_phase, j, scroll_A_y, scroll_B_y;

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);

	// SPR_init(1, 1, 1);

	/* Draw the foreground */
	VDP_drawImageEx(PLAN_A, &barb_pic_front, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += barb_pic_front.tileset->numTile;
	VDP_drawImageEx(PLAN_B, &barb_pic_back, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += barb_pic_back.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	VDP_setVerticalScroll(PLAN_A, 280);
	VDP_setVerticalScroll(PLAN_B, 128);

	SYS_enableInts();

	// VDP_fadePalTo(PAL1, barb_pic_back.palette->data, 16, TRUE);
	// RSE_pause(16);
	VDP_fadePalTo(PAL1, palette_white, RSE_FRAMES(8), TRUE);
	RSE_pause(8);
	VDP_fadePalTo(PAL1, barb_pic_back.palette->data, RSE_FRAMES(16), TRUE);
	RSE_pause(16);

	VDP_fadePalTo(PAL0, barb_pic_front.palette->data, RSE_FRAMES(64), TRUE);
	// RSE_pause(16);

	fx_phase = 0;
	while(fx_phase < 256) // (vball_phase < VBALL_PHASE_QUIT)
	{
		VDP_waitVSync();
		j = easing_table[fx_phase << 2];

		scroll_A_y = 280 - ((j * 280) / 1024);
		scroll_B_y = 128 - ((j * 128) / 1024);

		VDP_setVerticalScroll(PLAN_A, scroll_A_y);
		VDP_setVerticalScroll(PLAN_B, scroll_B_y);

		if (fx_phase == 256 - 64)
			VDP_fadePalTo(PAL0, palette_white, RSE_FRAMES(8), TRUE);
		if (fx_phase == 256 - 56)
			VDP_fadePalTo(PAL0, barb_pic_front.palette->data, RSE_FRAMES(8), TRUE);		

		fx_phase++;
		// BMP_showFPS(0);
	}

	RSE_pause(4 * 60);

	VDP_fadeOut(1, 63, 64, TRUE);

	for(j = 0; j  < VDP_getPlanHeight(); j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(j);
		VDP_waitVSync();
		RSE_clearTileRowA(j);
	}	

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);

	SYS_enableInts();	
}