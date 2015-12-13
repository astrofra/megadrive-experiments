#include <genesis.h>
#include <gfx.h>

static void beastScrollingFX();

int main(){
	JOY_init();
	beastScrollingFX();
	return 0;
}

#define	TABLE_LEN 80


static void beastScrollingFX(){
	u32 hscrollInc = 0;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	short i, j;
	u16 scroll_jump_table_v[TABLE_LEN];

	/*	Hblank-based water fx */
	static void hBlank(){
		hscrollInc++;
		if (hscrollInc < TABLE_LEN)
			VDP_setHorizontalScroll(PLAN_B, 320 - ((scroll_jump_table_v[hscrollInc] * vblCount) >> 4));
		else
			VDP_setHorizontalScroll(PLAN_B, 0);
	}

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	/* Draw the foreground */
	VDP_setPalette(PAL1, ground.palette->data);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 24, 0, FALSE, FALSE);
	vramIndex += ground.tileset->numTile;

	VDP_setPalette(PAL0, rse_logo.palette->data);
	VDP_drawImageEx(APLAN, &rse_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += rse_logo.tileset->numTile;	

	SYS_enableInts();

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption

	j = 0;
	for(i = 0; i < TABLE_LEN; i++)
	{
		scroll_jump_table_v[i] = (u16)j;

		if (i < 40)
			j++;
		else
			j--;
	}

	hscrollInc = 0;
	while (1){
		hscrollInc = 0;
		VDP_waitVSync();
		vblCount += 1;
	}
}