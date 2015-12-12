#include <genesis.h>
#include <gfx.h>

static void axelayFX();

int main(){
	JOY_init();
	axelayFX();
	return 0;
}

#define	TABLE_LEN 512

u16 scroll_jump_table_v[512];
u16 scroll_jump_table_h[512];

static void axelayFX(){
	u32 hscrollInc = 0;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	u16 i, j;

	/*	Hblank-based water fx */
	static void hBlank(){
		hscrollInc++;

		VDP_setVerticalScroll(PLAN_A, scroll_jump_table_v[hscrollInc] - (vblCount & (64 * 8 - 1)));
		VDP_setHorizontalScroll(PLAN_A, scroll_jump_table_h[hscrollInc] - (vblCount & (64 * 8 - 1)));

		VDP_setVerticalScroll(PLAN_B, scroll_jump_table_v[hscrollInc] - ((vblCount >> 1) & (64 * 8 - 1)));
		VDP_setHorizontalScroll(PLAN_B, scroll_jump_table_h[hscrollInc] - ((vblCount >> 1) & (64 * 8 - 1)));
	}

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);
	SYS_disableInts();

	/* Draw the background */
	VDP_setPalette(PAL1, sea.palette->data);
	VDP_drawImageEx(BPLAN, &sea, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	VDP_drawImageEx(BPLAN, &sea, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, 256 >> 3, FALSE, FALSE);
	VDP_drawImageEx(BPLAN, &sea, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 256 >> 3, 0, FALSE, FALSE);
	VDP_drawImageEx(BPLAN, &sea, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 256 >> 3, 256 >> 3, FALSE, FALSE);
	vramIndex += sea.tileset->numTile;	

	/* Draw the foreground */
	VDP_setPalette(PAL0, clouds.palette->data);
	VDP_drawImageEx(APLAN, &clouds, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &clouds, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 256 >> 3, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &clouds, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 256 >> 3, 0, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &clouds, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 256 >> 3, 256 >> 3, FALSE, FALSE);
	vramIndex += clouds.tileset->numTile;

	SYS_enableInts();

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption

	j = 30;
	hscrollInc = 0;
	for(i = 0; i < TABLE_LEN; i++)
	{
		scroll_jump_table_v[i] = hscrollInc;
		scroll_jump_table_h[i] = hscrollInc >> 1;
		hscrollInc += (j >> 2);

		if (i < 8)
			j-=2;
		else
			j--;

		if (j <= 4)
			j = 4;
	}

	hscrollInc = 0;
	while (1){
		VDP_waitVSync();
		// BMP_showFPS(1);
		vblCount += 1;
		hscrollInc = 0;
	}
}