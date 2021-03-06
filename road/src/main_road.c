#include <genesis.h>
#include "gfx.h"
#include "main_road.h"
const u32 strip[8][16] = {

	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,

	0x33344333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,

	0x33344333,
	0x33344333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,

	0x33344333,
	0x33344333,
	0x33344333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,

	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,

	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33333333,
	0x33333333,
	0x33333333,

	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33333333,
	0x33333333,

	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33333333,

	0x33333333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,

	0x33333333,
	0x33333333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,

	0x33333333,
	0x33333333,
	0x33333333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,

	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33344333,
	0x33344333,
	0x33344333,
	0x33344333,

	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33344333,
	0x33344333,
	0x33344333,

	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33344333,
	0x33344333,

	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33344333,

	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333,
	0x33333333
};

void test(){
}

void main_road(){
	#define SCROLL_LINE_MAX		1024

	u16 vram_index = TILE_USERINDEX;
	s16 scroll_values[SCROLL_LINE_MAX];
	u16 vblCount = 0;
    u16 strip_vram_index = 0;
    u16 strip_current = 0;
	char strip_current_str[3];
            
	static void scroll_init(){
		u16 i = 0; for (i = 0; i < SCROLL_LINE_MAX; i++){
			scroll_values[i] = sinFix16(i << 2) / 2;
		}
	}
	
	static void load_strip_tile(){
        strip_vram_index = vram_index;
        VDP_loadTileData(strip, vram_index, 16, 1);
        vram_index += 16;
	}

    static void strip_tile_update(){

		VDP_setTileMapXY(BPLAN, strip_vram_index , 19, 17);
		VDP_setTileMapXY(BPLAN, strip_vram_index + 15, 19, 18);
		VDP_setTileMapXY(BPLAN, strip_vram_index , 19, 19);
		VDP_setTileMapXY(BPLAN, strip_vram_index + 15, 19, 20);
		VDP_setTileMapXY(BPLAN, strip_vram_index,  19, 21);
		VDP_setTileMapXY(BPLAN, strip_vram_index + 15, 19, 22);
		VDP_setTileMapXY(BPLAN, strip_vram_index , 19, 23);
		VDP_setTileMapXY(BPLAN, strip_vram_index + 15, 19, 24);
		VDP_setTileMapXY(BPLAN, strip_vram_index,  19, 25);
		VDP_setTileMapXY(BPLAN, strip_vram_index + 15, 19, 26);
		VDP_setTileMapXY(BPLAN, strip_vram_index,  19, 27);

		intToStr(strip_current, strip_current_str, 2);
		VDP_drawText(strip_current_str, 10, 10);

		if (vblCount % 15 == 0){
			strip_current++;
			strip_current = strip_current & 15;
		}
    }

    VDP_setPalette(PAL0, road_image.palette->data);
    VDP_drawImageEx(BPLAN, &road_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vram_index), 0, 0, FALSE, TRUE);
	vram_index += road_image.tileset->numTile;
    VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	
	scroll_init();
	load_strip_tile();

    while (1) {
		VDP_waitVSync();
		vblCount++;
		
        strip_tile_update();
		VDP_setHorizontalScrollLine(PLAN_B, 120, scroll_values + (vblCount & 511), 124, 1);
	}
}