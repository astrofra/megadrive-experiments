#include <genesis.h>
#include <gfx.h>
#define CHAR_SIZE 4



int main(){
	u16 hInterruptCounter = 0;
	u32 hscroll = 0;
	u32 hscrollInc = 0x30;
	u16 vblCount = 0;

	void hBlank(){
		hInterruptCounter++;
		VDP_setHorizontalScroll(PLAN_A, hscroll >> 8);
		if (hInterruptCounter % 2 == 0){
			hscroll += hscrollInc;
		}
		else{
			hscroll -= hscrollInc;
		}
	}

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setScreenWidth320();

	char hInterruptCounterStr[CHAR_SIZE];
	u16 vramIndex = TILE_USERINDEX;

	SYS_disableInts();
	VDP_setPalette(PAL0, car_image.palette->data);
	VDP_drawImageEx(APLAN, &car_image, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 1, 15, FALSE, FALSE);
	vramIndex += car_image.tileset->numTile;
	SYS_enableInts();

	VDP_drawText("H INTERRUPTION COUNTER :", 0, 5);

	SYS_enableInts();
	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption

	while (1){
		VDP_waitVSync();
		vblCount++;
		hscrollInc += 0x8;
		uintToStr(hInterruptCounter, hInterruptCounterStr, CHAR_SIZE);
		VDP_drawText(hInterruptCounterStr, 0, 10);
	}
	return 0;
}