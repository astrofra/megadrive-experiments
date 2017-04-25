#include <genesis.h>
#include <gfx.h>

#define TWISTER_TABLE_SIZE 1024
#define CST_CTRL_PORT 0xC00004
#define CST_DATA_PORT 0xC00000
#define CST_WRITE_VSRAM_ADDR(adr)   ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x10)

s16 twister_jump_table[TWISTER_TABLE_SIZE];
s16 twister_hjump_table[TWISTER_TABLE_SIZE];
// s16 scroll_jump_table_bg[TWISTER_TABLE_SIZE];
// s16 hscroll_jump_table[TWISTER_TABLE_SIZE];
// s16 hscroll_jump_table_bg[TWISTER_TABLE_SIZE];
// s16 hblank_table[TWISTER_TABLE_SIZE];
// s16 hblank_table_bg[TWISTER_TABLE_SIZE];
// s16 hscroll_table[256];
// s16 hscroll_table_bg[256];

extern u16 hscrl_adr;


void circleWavesFX(void)
{
	u16 vramIndex = TILE_USERINDEX;
	s16 i, j, k, rot_y = 0, ang_speed_y = 4, twist_y = 0, twist_inc = 0, prev_i;
	s16 r, g, b;
	u16 col;
	u16 vcount = 0;
	u16 pal_raster[4 * 32 * 14];

    vu16 *pw;
    vu32 *pl;

    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

	static void hBlank(){
		// VDP_setVerticalScroll(PLAN_A, scroll_jump_table[(GET_VCOUNTER + rot_y) & ((TWISTER_TABLE_SIZE >> 2) - 1)] + (64 + sinFix16(rot_y << 1)) << 1);

		/* Vertical scroll */
	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = twister_jump_table[(GET_VCOUNTER + vcount) & 1023];

	    i = ((GET_VCOUNTER + vcount) & 1023) >> 2;
	    i <<= 2;
	    i &= 0x7F;

	    if (i != prev_i)
	    	VDP_setPaletteColors(0, pal_raster + i + k, 4);
	    prev_i = i;

		/* Horizontal scroll */
	    *pl = GFX_WRITE_VRAM_ADDR(hscrl_adr);
	    *pw = twister_hjump_table[(GET_VCOUNTER + vcount) & 1023];	    
	}

    /* Prepare wave table */
    for(i = 0; i < TWISTER_TABLE_SIZE; i++)
    {
    	twister_jump_table[i] = -((i + sinFix16(i << 2) + 64 + ((cosFix16((i + 256) << 3) + 64) >> 1) ));
    	twister_hjump_table[i] = (sinFix16(i >> 1) - 64 + cosFix16((i + 256) << 3)) >> 4;
    }

	/* prepare raster palettes */
	for(k = 0; k < 14; k++)
	{
		VDP_waitVSync();
		for(i = 0; i < 32; i++)
			for(j = 0; j < 4; j++)
			{
				col = circles.palette->data[j];
				r = (col & (0xF << 8)) >> 8;
				g = (col & (0xF << 4)) >> 4;
				b = col & 0xF;

				if (i < 16)
				{
					r -= i;
					g -= (i >> 1);
					b -= (i >> 2);
				}
				else
				{
					r = r - (32 - i);				
					g = g - ((32 - i) >> 1);
					b = b - ((32 - i) >> 2);
				}

				r -= (k + 1);
				g -= (k + 1);
				b -= (k + 1);

				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;

				col = (r << 8) | (g << 4) | b;

				pal_raster[(i * 4) + j + (k * 4 * 32)] = col;
			}	
	}

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setHInterrupt(TRUE);
	VDP_setHIntCounter(1);

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

	SYS_enableInts();

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank);

	j = 0;
	k = 0;

    while (vcount < 60 * 10)
    {
        VDP_waitVSync();

        SYS_disableInts();
	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = twister_jump_table[vcount & 1023];

	    *pl = GFX_WRITE_VRAM_ADDR(hscrl_adr);
	    *pw = twister_hjump_table[vcount & 1023];	 	    
        SYS_enableInts();

        if (vcount > 60 * 8 && k < (4 * 13 * 32))
        	k += 32;

        vcount += 1;
    }

	// SPR_end();

	SYS_disableInts();

	RSE_resetScrolling();
	// VDP_clearPlan(PLAN_A, TRUE);
	// VDP_clearPlan(PLAN_B, TRUE);

	VDP_setHInterrupt(0);

	SYS_setHIntCallback(NULL);
	SYS_setVIntCallback(NULL);

	SYS_enableInts();

    RSE_turn_screen_to_black();	

	// vramIndex = TILE_USERINDEX;    
}