#include <genesis.h>
#include <gfx.h>

#define TWISTER_TABLE_SIZE 1024
#define CST_CTRL_PORT 0xC00004
#define CST_DATA_PORT 0xC00000
#define CST_WRITE_VSRAM_ADDR(adr)   ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x10)

s16 twister_jump_table[TWISTER_TABLE_SIZE];
// s16 scroll_jump_table_bg[TWISTER_TABLE_SIZE];
// s16 hscroll_jump_table[TWISTER_TABLE_SIZE];
// s16 hscroll_jump_table_bg[TWISTER_TABLE_SIZE];
// s16 hblank_table[TWISTER_TABLE_SIZE];
// s16 hblank_table_bg[TWISTER_TABLE_SIZE];
// s16 hscroll_table[256];
// s16 hscroll_table_bg[256];


void circleWavesFX(void)
{
	u16 vramIndex = TILE_USERINDEX;
	s16 i, j, rot_y = 0, ang_speed_y = 4, twist_y = 0, twist_inc = 0, prev_i;
	u16 vcount = 0;
	u16 pal_raster[4 * 32];

    vu16 *pw;
    vu32 *pl;

    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

	static void hBlank(){
		// VDP_setVerticalScroll(PLAN_A, scroll_jump_table[(GET_VCOUNTER + rot_y) & ((TWISTER_TABLE_SIZE >> 2) - 1)] + (64 + sinFix16(rot_y << 1)) << 1);

	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = twister_jump_table[(GET_VCOUNTER + vcount) & 1023];

	    i = ((GET_VCOUNTER + vcount) & 1023) >> 2;
	    i <<= 2;
	    i &= 0x7F;

	    if (i != prev_i)
	    	VDP_setPaletteColors(0, pal_raster + i, 4);
	    prev_i = i;
	}

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	vramIndex = TILE_USERINDEX;

	/* Load the fond tiles */
	VDP_drawImageEx(PLAN_A, &circles, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	VDP_drawImageEx(PLAN_A, &circles, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 256 >> 3, FALSE, FALSE);
	vramIndex += circles.tileset->numTile;
	VDP_drawImageEx(PLAN_B, &masiaka_title_pic, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 240) >> 4, (224 - 48) >> 4, FALSE, TRUE);
	vramIndex += masiaka_title_pic.tileset->numTile;	

	VDP_setPalette(PAL0, circles.palette->data);
	VDP_setPalette(PAL1, masiaka_title_pic.palette->data);
	// VDP_setPaletteColor(0, 0x80A);

    VDP_setHilightShadow(0);

    for(i = 0; i < TWISTER_TABLE_SIZE; i++)
    	twister_jump_table[i] = -((i + sinFix16(i << 2) + 64 + ((cosFix16((i + 256) << 3) + 64) >> 1) ));

	SYS_enableInts();

	/* prepare raster palettes */
	for(i = 0; i < 32; i++)
		for(j = 0; j < 4; j++)
		{
			u16 col;
			s16 r, g, b;
			col = circles.palette->data[j];
			r = (col & (0xF << 8)) >> 8;
			g = (col & (0xF << 4)) >> 4;
			b = col & 0xF;

			if (i < 16)
			{
				r -= (i >> 2);
				g -= (i >> 1);
				b -= i;
			}
			else
			{
				r = r - ((32 - i) >> 2);
				g = g - ((32 - i) >> 1);
				b = b - (32 - i);				
			}

			if (r < 0) r = 0;
			if (g < 0) g = 0;
			if (b < 0) b = 0;

			col = (r << 8) | (g << 4) | b;

			pal_raster[(i * 4) + j] = col;
		}

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank);

    while (TRUE)
    {
        VDP_waitVSync();

        SYS_disableInts();
	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = twister_jump_table[vcount & 1023];
        SYS_enableInts();

        vcount += 1;
    }	
}