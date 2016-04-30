#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "demo_strings.h"
#include "transition_helper.h"

#define MAX_SIMULATION 6;

extern u16 vramIndex;
extern u16 fontIndex;

void RSE_plasma(void)
{
	u32 vblCount = 0, i, j;

	// u16 vramIndex = TILE_USERINDEX;
	s16 tile_scroll_h[2048],
		tile_scroll_v[2048];

	u16 palette_cycle[16 * 16];

	RSE_turn_screen_to_black();

	/*
		Init scroll
	*/
	for(i = 0; i < 2048; i++)
	{
		tile_scroll_h[i] = (sinFix16(i << 2) >> 1) - 32; //  + ((sinFix16((i + 256) << 4) >> 1) * sinFix16(i) / 350);
		tile_scroll_v[i] = (cosFix16(i << 2)) + 64 + ((cosFix16((i + 128) << 4) >> 1) * sinFix16(i + 256) / 350);
	}

	/*
		Init palette
	*/
	for(i = 0; i < 16; i++)
		for(j = 0; j <  16; j++)
			palette_cycle[j + (i * 16)] = (plasma.palette->data[(j + i) & 0xF]); // | (((sinFix16(i * 64) + 64) >> 1) & 0x00F);

	VDP_waitVSync();
	SYS_disableInts();
	// VDP_setPlanSize(64, 32);
	VDP_clearPlan(APLAN, 1);
	VDP_clearPlan(BPLAN, 1);
	VDP_setHilightShadow(0);	

	vramIndex = fontIndex;

	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 0, FALSE, TRUE);
	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 0, FALSE, TRUE);

	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 128 >> 3, FALSE, TRUE);
	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 128 >> 3, FALSE, TRUE);
	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 128 >> 3, FALSE, TRUE);

	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 256 >> 3, FALSE, TRUE);
	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 256 >> 3, FALSE, TRUE);
	VDP_drawImageEx(APLAN, &plasma, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 256 >> 3, FALSE, TRUE);

	vramIndex += plasma.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);	

	SYS_enableInts();

	VDP_setPalette(PAL0, plasma.palette->data);

	while (vblCount < 512)
	{
		VDP_waitVSync();

		VDP_setHorizontalScrollTile(PLAN_A, 0, tile_scroll_h + ((vblCount << 1) & 1023), 32, TRUE);
		VDP_setVerticalScrollTile(PLAN_A, 0, tile_scroll_v + (vblCount & 1023), 32, TRUE);
		VDP_setPalette(PAL0, palette_cycle + ((vblCount >> 2) & 255));
		// VDP_setPalette(PAL0, palette_cycle + sinFix16(vblCount) + 64);
		vblCount++;
	}

	/*
		Fade out
	*/
	VDP_fadeOut(1, 63, 32, TRUE);	
	i = 0;

	while (i < 32)
	{
		VDP_waitVSync();

		VDP_setHorizontalScrollTile(PLAN_A, 0, tile_scroll_h + ((vblCount << 1) & 1023), 32, TRUE);
		VDP_setVerticalScrollTile(PLAN_A, 0, tile_scroll_v + (vblCount & 1023), 32, TRUE);
		vblCount++;
		i++;
	}

	VDP_waitVSync();

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setVerticalScroll(PLAN_B, 0);
	VDP_setVerticalScroll(PLAN_A, 0);
	VDP_setHorizontalScroll(PLAN_B, 0);
	VDP_setHorizontalScroll(PLAN_A, 0);	

	SPR_end();	
}
