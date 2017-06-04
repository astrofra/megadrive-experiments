#include <genesis.h>
#include <gfx.h>
#include "transition_helper.h"

#define TWISTER_TABLE_SIZE 1024
#define CST_CTRL_PORT 0xC00004
#define CST_DATA_PORT 0xC00000
#define CST_WRITE_VSRAM_ADDR(adr)   ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x10)

s16 twister_jump_table[TWISTER_TABLE_SIZE];
s16 twister_hjump_table[TWISTER_TABLE_SIZE];
s16 logo_yscroll_table[64];

// s16 scroll_jump_table_bg[TWISTER_TABLE_SIZE];
// s16 hscroll_jump_table[TWISTER_TABLE_SIZE];
// s16 hscroll_jump_table_bg[TWISTER_TABLE_SIZE];
// s16 hblank_table[TWISTER_TABLE_SIZE];
// s16 hblank_table_bg[TWISTER_TABLE_SIZE];
// s16 hscroll_table[256];
// s16 hscroll_table_bg[256];

// extern u16 hscrl_adr;
extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

static 	Sprite *sprites[16];
static u16 tmp_vcount;

void flamesWavesFX(void)
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

		tmp_vcount = (GET_VCOUNTER + vcount) & 1023;
		/* Vertical scroll */
	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = twister_jump_table[tmp_vcount];

	    // i = ((GET_VCOUNTER + vcount) & 1023); // >> 2;
	    // i = tmp_vcount >> 2;
	    // i <<= 2;
	    // i &= 0x7F;
	    i = tmp_vcount & 0x7C;

	    if (i != prev_i)
	    	VDP_setPaletteColors(0, pal_raster + i + k, 4);
	    prev_i = i;

		/* Horizontal scroll */
	    *pl = GFX_WRITE_VRAM_ADDR(0xB800);
	    *pw = twister_hjump_table[tmp_vcount];	    
	}

    /* Prepare tables */
    for(i = 0; i < TWISTER_TABLE_SIZE; i++)
    {
    	twister_jump_table[i] = -((i + sinFix16(i << 2) + 64 + ((cosFix16((i + 256) << 3) + 64) >> 1) ));
    	twister_hjump_table[i] = (sinFix16(i >> 1) - 64 + cosFix16((i + 256) << 3)) >> 4;
    }

	VDP_waitVSync();    

	for (i = 0; i < 64; i++)
		logo_yscroll_table[i] = (easing_table[i << 4] >> 4) - 64;    

	VDP_waitVSync();

	/* prepare raster palettes */
	for(k = 0; k < 14; k++)
	{
		VDP_waitVSync();
		for(i = 0; i < 32; i++)
			for(j = 0; j < 4; j++)
			{
				col = flames_0.palette->data[j];
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

				r -= (k + 1) << 1;
				g -= (k + 1) << 1;
				b -= (k + 1) << 1;

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

	SPR_init(0, 0, 0);

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setHInterrupt(TRUE);
	VDP_setHIntCounter(1);

	vramIndex = 8;

	/* Load the fond tiles */
	VDP_drawImageEx(PLAN_A, &flames_0, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &flames_0, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 256 >> 3, FALSE, FALSE);
	vramIndex += flames_0.tileset->numTile;

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &flames_1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 10, 0, FALSE, FALSE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &flames_1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 10, 256 >> 3, FALSE, FALSE);
	vramIndex += flames_1.tileset->numTile;

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &flames_2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 20, 0, FALSE, FALSE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &flames_2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 20, 256 >> 3, FALSE, FALSE);
	vramIndex += flames_2.tileset->numTile;

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &flames_3, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 30, 0, FALSE, FALSE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &flames_3, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 30, 256 >> 3, FALSE, FALSE);
	vramIndex += flames_3.tileset->numTile;

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_setVerticalScroll(PLAN_B, (easing_table[64 << 4] >> 4) - 64 - 64);
	VDP_drawImageEx(PLAN_B, &masiaka_title_pic, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 240) >> 4, (224 - 48) >> 4, FALSE, TRUE);
	vramIndex += masiaka_title_pic.tileset->numTile;	

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	// sprites[0] = SPR_addSprite(&sword, (320 - 48) >> 1, -128, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, vramIndex));
	sprites[0] = SPR_addSpriteEx(&sword, (320 - 48) >> 1, -128, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, vramIndex), 0, SPR_FLAG_AUTO_VISIBILITY | !SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	SPR_update(sprites, 1);	

	// VDP_setPalette(PAL0, flames_0.palette->data);
	// VDP_setPalette(PAL3, sword.palette->data);
	// VDP_setPalette(PAL1, masiaka_title_pic.palette->data);
	// VDP_setPaletteColor(0, 0x80A);

    VDP_setHilightShadow(0);

	SYS_enableInts();

	vcount = 0;
	VDP_fadePalTo(PAL3, sword.palette->data, RSE_FRAMES(8), TRUE);
    while (vcount < 32)	
	{
		VDP_waitVSync();
    	SPR_setPosition(sprites[0], (320 - 48) >> 1, (((224 - 128) >> 1) - 76 )+ (easing_table[vcount << 5] >> 4));
    	SPR_update(sprites, 1);
    	vcount++;
	}

	j = 0;
	k = 0;
	vcount = 0;

    while (vcount < 60 * 10)
    {
        VDP_waitVSync();

        switch(vcount)
        {
        	case 0:
	        	VDP_fadeTo(16, 31, palette_white, 6, TRUE);
	        	break;        	
        	case 2 + 8:
	        	VDP_fadePalTo(PAL1, masiaka_title_pic.palette->data, RSE_FRAMES(16), TRUE);
	        	break;
        	case 10 + 8:
				VDP_setHInterrupt(1);
				SYS_setHIntCallback(&hBlank);
	        	break;
        	case 60 * 10 - 20:
	        	VDP_fadePalTo(PAL1, palette_black, RSE_FRAMES(16), TRUE);
	        	break;
		}

        if (vcount < 64)
        {
        	// if (vcount < 32)
        	// {
	        // 	SPR_setPosition(sprites[0], (320 - 48) >> 1, (((224 - 128) >> 1) - 64 )+ (easing_table[vcount << 5] >> 4));
	        // 	SPR_update(sprites, 1);
        	// }
        	// VDP_setVerticalScroll(PLAN_B, logo_yscroll_table[vcount]); // (easing_table[vcount << 4] >> 4) - 64);
		    *pl = GFX_WRITE_VSRAM_ADDR(2);
		    *pw = logo_yscroll_table[vcount];        	
        }


        SYS_disableInts();
	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = twister_jump_table[vcount & 1023];

	    *pl = GFX_WRITE_VRAM_ADDR(0xB800);
	    *pw = twister_hjump_table[vcount & 1023];	 	    
        SYS_enableInts();

        if (vcount & 0x1 && vcount > 60 * 5 && k < (4 * 13 * 32))
        	k += 8;

        vcount += 1;
    }

	SPR_end();

	SYS_disableInts();

	RSE_resetScrolling();

	VDP_setHInterrupt(0);

	SYS_setHIntCallback(NULL);
	SYS_setVIntCallback(NULL);

	SYS_enableInts();

    RSE_turn_screen_to_black();	

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);
	// vramIndex = TILE_USERINDEX;    
}