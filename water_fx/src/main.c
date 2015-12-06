#include <genesis.h>
#include <gfx.h>
#include "cosine_table.h"

static void rasterScroll();

int main(){
	JOY_init();
	rasterScroll();
	return 0;
}

static void rasterScroll(){
	u16 hInterruptCounter = 0;
	u32 hscroll = 0;
	u32 hscrollInc = 0x30;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	static void hBlank(){
		hInterruptCounter++;
		/* Background */
		VDP_setHorizontalScroll(PLAN_B, tcos[((hscrollInc + vblCount) << 2) & (COSINE_TABLE_LEN - 1)] >> 5);
		VDP_setVerticalScroll(PLAN_B, (tsin[((hscrollInc + vblCount) << 2) & (COSINE_TABLE_LEN - 1)] >> 8) + 0xFF - ((vblCount >> 2) & 0xFF));
		/* Foreground */
		VDP_setHorizontalScroll(PLAN_A, tsin[(hscrollInc + vblCount) & (COSINE_TABLE_LEN - 1)] >> 4);
		VDP_setVerticalScroll(PLAN_A, (tcos[((hscrollInc + vblCount) << 2) & (COSINE_TABLE_LEN - 1)] >> 7) + 0xFF - ((vblCount >> 1) & 0xFF));
		hscrollInc++;
	}	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	// VDP_setScreenWidth256();
	// VDP_setScreenHeight224();
	VDP_setPlanSize(64, 64);
	SYS_disableInts();

	/* Background */
	VDP_setPalette(PAL1, water_tex_back.palette->data);
	VDP_drawImageEx(BPLAN, &water_tex_back, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += water_tex_back.tileset->numTile;

	/* Foreground */
	VDP_setPalette(PAL0, water_tex_front.palette->data);
	VDP_drawImageEx(APLAN, &water_tex_front, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &water_tex_front, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 256, FALSE, FALSE);
	vramIndex += water_tex_front.tileset->numTile;

	SYS_enableInts();
	VDP_drawTextBG(APLAN,"SCROLLING RASTER TEST",0, 0, 0);

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption

	while (1){
		VDP_waitVSync();
		vblCount++;
		hscrollInc = 0;
	}
}