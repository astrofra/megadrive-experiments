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
		VDP_setHorizontalScroll(PLAN_A, tsin[(hscrollInc + vblCount) & 0xFF] >> 3);
		VDP_setHorizontalScroll(PLAN_B, tcos[(hscrollInc + vblCount) & 0xFF] >> 3);
		hscrollInc++;
	}	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setScreenWidth320();
	SYS_disableInts();

	VDP_setPalette(PAL0, water_tex_front.palette->data);
	VDP_drawImageEx(APLAN, &water_tex_front, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += water_tex_front.tileset->numTile;

	VDP_setPalette(PAL1, water_tex_back.palette->data);
	VDP_drawImageEx(BPLAN, &water_tex_back, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += water_tex_back.tileset->numTile;

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