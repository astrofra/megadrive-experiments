#include <genesis.h>
#include <gfx.h>

static void beastScrollingFX();

int main(){
	JOY_init();
	beastScrollingFX();
	return 0;
}

#define	TABLE_LEN 160

u16 scroll_jump_table_v[TABLE_LEN];

static void beastScrollingFX(){
	u32 hscrollInc = 0;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	u16 i, j;

	/*	Hblank-based water fx */
	static void hBlank(){
		hscrollInc++;

		VDP_setHorizontalScroll(PLAN_A, scroll_jump_table_v[hscrollInc] * (-vblCount));
	}

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(256 >> 3, 256 >> 3);

	/* Draw the foreground */
	VDP_setPalette(PAL0, ground.palette->data);
	VDP_drawImageEx(APLAN, &ground, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += ground.tileset->numTile;

	SYS_enableInts();

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption

	j = 0;
	hscrollInc = 0;
	for(i = 0; i < TABLE_LEN; i++)
	{
		scroll_jump_table_v[i] = (hscrollInc >> 8) + 1;
		hscrollInc += j;

		if (i < TABLE_LEN >> 1)
			j++;
		else
			j--;
	}

	hscrollInc = 0;
	while (1){
		VDP_waitVSync();
		// BMP_showFPS(1);
		vblCount += 1;
		hscrollInc = 0;
	}
}