#include <genesis.h>
#include <gfx.h>
#include "cosine_table.h"
#define CHAR_SIZE 4

int main(){
	u16 hInterruptCounter = 0;
	u32 hscroll = 0;
	u32 hscrollInc = 0x30;
	u16 vblCount = 0;
	// char hInterruptCounterStr[CHAR_SIZE];
	u16 vramIndex = TILE_USERINDEX;

	void hBlank(){
		hInterruptCounter++;
		VDP_setHorizontalScroll(PLAN_A, hscroll);
		hscroll = (tsin[(hscrollInc + vblCount) & 0xFF]) >> 3;
		hscrollInc++;
	}
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setScreenWidth320();
	SYS_disableInts();
	VDP_setPalette(PAL0, car_image.palette->data);
	VDP_drawImageEx(APLAN, &car_image, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 1, 15, FALSE, FALSE);
	vramIndex += car_image.tileset->numTile;
	SYS_enableInts();
	VDP_drawText("H INTERRUPTION COUNTER :", 0, 5);
	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption
	while (1){
		VDP_waitVSync();
		vblCount++;
		hscrollInc = 0;
		// uintToStr(hscrollInc, hInterruptCounterStr, CHAR_SIZE);
		// VDP_drawText(hInterruptCounterStr, 0, 10);
	}
	return 0;
}
