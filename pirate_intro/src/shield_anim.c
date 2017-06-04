#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void shieldAnimFX(void)
{
	u16 fx_phase, i, j, k, vcount;
	s16 shield_hscroll[256];
	s16 scroll_tile_x[32], scroll_dir[32];

	SYS_disableInts();

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(128, 32);
	VDP_setHilightShadow(1); 

	vramIndex = 0;

	/* Draw the background */
	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 8, FALSE, TRUE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 16, FALSE, TRUE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 24, FALSE, TRUE);
	vramIndex += shield_anim.tileset->numTile;

	// /* Draw the foreground */
	for(i = 0; i < (224 - 120) >> 4; i++)
		RSE_clearTileRowBWithPrio(i);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);

	SYS_enableInts();

	DMA_waitCompletion();

	for (i = 0; i < (120 >> 3); i++)
		scroll_tile_x[i] = 0;

	VDP_waitVSync();

	for (i = 0; i < 4; i++)
	{ 
		VDP_waitVSync();
		for(j = 0; j < 8; j++)
		{
			shield_hscroll[i * 8 + j] = i * 4 * 64;
			if (i & 0x1)
				shield_hscroll[i * 8 + j] += 32;
			if (i && 0x1)
				scroll_dir[i * 8 + j] = 64;
			else
				scroll_dir[i * 8 + j] = -64;
		}
	}

	VDP_fadePalTo(PAL1, rsi_logo_0.palette->data, RSE_FRAMES(16), TRUE);
	vcount = 0;
	k = 0;
	while(vcount < RSE_FRAMES(60 * 4))
	{
		VDP_waitVSync();
		if (vcount == RSE_FRAMES(16) + 2)
				VDP_fadePalTo(PAL0, shield_anim.palette->data, RSE_FRAMES(16), TRUE);

		vcount++;
		k++;
		if (k > 2)
		{
			k = 0;
			VDP_setHorizontalScrollTile(PLAN_A, 0, shield_hscroll, 8 * 4, TRUE);
			for (i = 0; i < 4; i++)
				for(j = 0; j < 8; j++)
					shield_hscroll[i * 8 + j] += scroll_dir[i * 8 + j];
		}

	}

	RSE_turn_screen_to_black();

	SPR_end();
	RSE_resetScrolling();

	SYS_disableInts();

	VDP_setHilightShadow(0);

	VDP_waitVSync();

	SYS_enableInts();

	{
		u16 i;
		for(i = 0; i  < 224 >> 3; i++)
		{
			if (i & 0x1) VDP_waitVSync();
			RSE_clearTileRowB(i);
			RSE_clearTileRowA(i);
		}
	}		

	vramIndex = TILE_USERINDEX;
}