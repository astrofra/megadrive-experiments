#include <genesis.h>
#include <gfx.h>
#include "main_axelay_fx.h"



void main_axelay_fx(u16 vbl_to_exit){
	u16 scroll_jump_table_v[512];
	u32 hscrollInc = 0;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	u16 i, j;

	/*	Hblank-based water fx */
	static void hBlank(){
		hscrollInc++;

		VDP_setVerticalScroll(PLAN_A, scroll_jump_table_v[hscrollInc] - (vblCount & (64 * 8 - 1)));
		VDP_setVerticalScroll(PLAN_B, scroll_jump_table_v[hscrollInc] - ((vblCount >> 1) & (64 * 8 - 1)));
	}

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(256 >> 3, 256 >> 3);

	/* Draw the foreground */
	VDP_setPalette(PAL0, clouds.palette->data);
	VDP_drawImageEx(APLAN, &clouds, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += clouds.tileset->numTile;

	/* Draw the background */
	VDP_setPalette(PAL1, sea.palette->data);
	VDP_drawImageEx(BPLAN, &sea, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += sea.tileset->numTile;

	SYS_enableInts();

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption

	j = 30;
	hscrollInc = 0;
	for(i = 0; i < TABLE_LEN; i++)
	{
		scroll_jump_table_v[i] = hscrollInc;
		hscrollInc += (j >> 2);

		if (i < 8)
			j-=2;
		else
			j--;

		if (j <= 4)
			j = 4;
	}

	hscrollInc = 0;
	while (vblCount < vbl_to_exit){
		VDP_waitVSync();
		// BMP_showFPS(1);
		vblCount += 1;
		hscrollInc = 0;
	}
}