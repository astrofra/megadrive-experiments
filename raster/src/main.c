#include <genesis.h>
#include <gfx.h>
#include "cosine_table.h"
static void rasterPalette();
static void rasterScroll();

int main(){
	VDP_drawText("A - SCROLL RASTER", 10, 10);
	VDP_drawText("B - PALETTE RASTER", 10, 12);
	JOY_init();
	while(1){
		VDP_waitVSync();
		if (JOY_readJoypad(JOY_1) & BUTTON_A){
			rasterScroll();
		}
		if (JOY_readJoypad(JOY_1) & BUTTON_B){
			rasterPalette();
		}
	}
	return 0;
}

static void rasterPalette(){
	u16 vramIndex = TILE_USERINDEX;
	u16 currentPalette = 0;
	u16 vblCount = 0;
	const u16 palette_y[16]= {
		0x0002,
		0x00EE,
		0x0444,
		0x04EE,
		0x02EE,
		0x00CC,
		0x0888,
		0x0C0A,
		0x0088,
		0x0EEE,
		0x0EEE,
		0x0E2E,
		0x0A08,
		0x06EE,
		0x0AEE,
		0x02EA
	};
	const u16 palette_g[16]={
		0x0022,
		0x00E2,
		0x0444,
		0x04E6,
		0x02E4,
		0x00C0,
		0x0888,
		0x020C,
		0x0080,
		0x0EEE,
		0x0EEE,
		0x042E,
		0x020A,
		0x06E8,
		0x0AEA,
		0x06E2
	};
	const u16 palette_b[16]={
		0x0020,
		0x0E60,
		0x0444,
		0x0E84,
		0x0E82,
		0x0C40,
		0x0888,
		0x00C6,
		0x0820,
		0x0EEE,
		0x0EEE,
		0x02E8,
		0x00A4,
		0x0EA6,
		0x0ECA,
		0x0E22
	};
	const u16 palette_v[16]={
		0x0200,
		0x0E0E,
		0x0444,
		0x0E4E,
		0x0E2E,
		0x0C0C,
		0x0888,
		0x0AC0,
		0x0808,
		0x0EEE,
		0x0EEE,
		0x0EE2,
		0x08A0,
		0x0E6E,
		0x0EAE,
		0x0A2E
	};
	static void hBlank(){
		if (currentPalette >= 5) {currentPalette = 0;}
		switch (currentPalette) {
			case 0:
				VDP_setPalette(0, car_image.palette->data);
				currentPalette++;
				break;
			case 1:
				VDP_setPalette(0, palette_g);
				currentPalette++;
				break;
			case 2:
				VDP_setPalette(0, palette_y);
				currentPalette++;
				break;
			case 3:
				VDP_setPalette(0, palette_v);
				currentPalette++;
				break;
			case 4:
				VDP_setPalette(0, palette_b);
				currentPalette++;
				break;
				
			default:
				currentPalette++;
				break;
		}
	}
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setScreenWidth320();
	SYS_disableInts();
	//VDP_setPalette(PAL0, car_image.palette->data);
	VDP_setPalette(PAL0, palette_black);
	VDP_drawImageEx(BPLAN, &car_image, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 1, 15, FALSE, FALSE);
	vramIndex += car_image.tileset->numTile;
	SYS_enableInts();
	VDP_drawTextBG(APLAN,"PALETTE RASTER TEST",0, 0, 0);
	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption
	while (1){
		VDP_waitVSync();
		vblCount++;
	}
}

static void rasterScroll(){
	u16 hInterruptCounter = 0;
	u32 hscroll = 0;
	u32 hscrollInc = 0x30;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	static void hBlank(){
		hInterruptCounter++;
		VDP_setHorizontalScroll(PLAN_B, hscroll);
		hscroll = (tsin[(hscrollInc + vblCount) & 0xFF]) >> 3;
		hscrollInc++;
	}	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setScreenWidth320();
	SYS_disableInts();
	VDP_setPalette(PAL0, car_image.palette->data);
	VDP_drawImageEx(BPLAN, &car_image, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 1, 15, FALSE, FALSE);
	vramIndex += car_image.tileset->numTile;
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
