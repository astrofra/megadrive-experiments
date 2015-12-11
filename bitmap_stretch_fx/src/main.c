#include <genesis.h>
#include <gfx.h>
#include "cosine_table.h"

static void xRotatingCube();

int main(){
	JOY_init();
	xRotatingCube();
	return 0;
}

#define	Y_OFFSET	(32 << 3)
#define STEP_AMOUNT 6

u16 scroll_jump_table[256 * (1 << STEP_AMOUNT)];

static void xRotatingCube(){
	u32 hscrollInc = 0x30;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	u16 i, j;
	u16 logo_y_reverse = 0;

	/*	Hblank-based water fx */
	static void hBlank(){
		hscrollInc++;

		if (hscrollInc < 0x8 || hscrollInc > 0xFF)
			VDP_setVerticalScroll(PLAN_A, 0);
		else
		{
			/* Foreground */
			i = tcos[vblCount];
			i += 512;
			i >>= (STEP_AMOUNT + 1);
			i &= ((1 << STEP_AMOUNT) - 1);
			j = scroll_jump_table[hscrollInc + (i << 8) - 0x8];

			if (j > 200)
				VDP_setVerticalScroll(PLAN_A, 0);
			else
			{
				if (logo_y_reverse)
					VDP_setVerticalScroll(PLAN_A, Y_OFFSET + 160 - j);
				else
					VDP_setVerticalScroll(PLAN_A, Y_OFFSET + j);
			}
		}
	}	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);
	SYS_disableInts();

	/* Draw the foreground */
	VDP_setPalette(PAL0, wood_plank.palette->data);
	VDP_drawImageEx(APLAN, &wood_plank, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, (Y_OFFSET >> 3) + 1, FALSE, FALSE);
	vramIndex += wood_plank.tileset->numTile;

	SYS_enableInts();

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption

	for(j = 0; j < (1 << STEP_AMOUNT); j++)
		for(i = 0; i < 256; i++)
		{
			scroll_jump_table[i + (j << 8)] = i << j;
		}


	while (1){
		VDP_waitVSync();
		BMP_showFPS(1);
		/*	Count the VBL, 
			used in the Hblank routine as the main scrolling increment */
		vblCount += 4;
		if (vblCount > COSINE_TABLE_LEN - 1)
		{
			vblCount = 0;
			logo_y_reverse = !logo_y_reverse;
		}
		/* Reset the line counter for the Hblank routine */
		hscrollInc = 0;
	}
}