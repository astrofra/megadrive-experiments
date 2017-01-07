#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void displayRSILogoFX(void)
{
	u16 fx_phase, i, j, k;
	s16 scroll_tile_x[(120 >> 3) + 8];

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);
	VDP_setHilightShadow(0); 

	vramIndex = TILE_USERINDEX;

	/* Draw the foreground */
	VDP_drawImageEx(PLAN_B, &rsi_logo_0, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, (224 - 120) >> 4, FALSE, TRUE);
	vramIndex += rsi_logo_0.tileset->numTile;

	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &rsi_logo_1, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, (64 >> 3) + ((224 - 120) >> 4), FALSE, TRUE);
	vramIndex += rsi_logo_1.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

	SYS_enableInts();

	DMA_waitCompletion();

	for (i = 0; i < (120 >> 3); i++)
		scroll_tile_x[i] = 0;

	VDP_fadePalTo(PAL1, rsi_logo_0.palette->data, RSE_FRAMES(16), TRUE);
	RSE_pause(80);

	VDP_fadePalTo(PAL1, palette_white, RSE_FRAMES(4), TRUE);

	for(j = 0; j  < VDP_getPlanWidth(); j++)
	{
		VDP_waitVSync();
		k = j / 8;

		for (i = 0; i < (120 >> 4); i++)
		{
			scroll_tile_x[i]+= k;
			if (i < (120 >> 4) - 1)
				scroll_tile_x[i]++;
		}

		for (; i < (120 >> 3); i++)
		{
			scroll_tile_x[i]-= k;
			if (i > (120 >> 4))
				scroll_tile_x[i]--;
		}

		if (j == RSE_FRAMES(4) + 1)
			VDP_fadePalTo(PAL1, rsi_logo_0.palette->data, RSE_FRAMES(8), TRUE);
		if (j == 16)
			VDP_fadeOut(1, 63, 32, TRUE);

		SYS_disableInts();
		VDP_setHorizontalScrollTile(PLAN_B, (224 - 120) >> 4, scroll_tile_x, 120 >> 3, TRUE);
		SYS_enableInts();
	}

	RSE_pause(32);

	SPR_end();
	RSE_resetScrolling();

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);

	SYS_enableInts();

	vramIndex = TILE_USERINDEX;
}