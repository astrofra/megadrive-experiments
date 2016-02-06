#include <genesis.h>
#include <gfx.h>
#include "resources.h"

#define CST_GFX_WRITE_VRAM_ADDR(adr)    ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x00)
#define CST_CTRL_PORT 0xC00004
#define CST_DATA_PORT 0xC00000

static void starsGrid();

int main()
{
	starsGrid();
	return 0;
}

static void starsGrid()
{
	u16 vblCount = 0, i;
	u16 vramIndex = TILE_USERINDEX;
	s16 tile_scroll_h[1024],
		tile_scroll_v[1024];

	static void inline drawStarsStaticGrid(void)
	{
		u16 i = 0, j = 0, k = 0, m = 0, luma;
		u16 plan_width_by_y = 0;

	    vu32 *plctrl;
	    vu16 *pwdata;
	    u32 addr;

		plctrl = (u32 *) CST_CTRL_PORT;
	    pwdata = (u16 *) CST_DATA_PORT;

		while(j < 32)
		{
			luma = ((i + (m >> 1)) & 30) << 2;
			m++;
		
			addr = VDP_PLAN_A + ((i + k + plan_width_by_y) << 1);
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma;

			addr += 2;
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma + 1;

			addr = VDP_PLAN_A + ((i + k + VDP_getPlanWidth() * (j + 1)) << 1);
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma + 2;

			addr += 2;
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma + 3;		    

		    i += 2;	
	
			if (i >= 40)
			{
				i = 0;
				j += 3;
				plan_width_by_y = VDP_getPlanWidth() * j;
				// return;
			}
		}
	}		

	static void inline drawStarsGrid(void)
	{
		u16 i = 0, j = 0, k = 0, luma;
		u16 plan_width_by_y = 0;

	    vu32 *plctrl;
	    vu16 *pwdata;
	    u32 addr;

		plctrl = (u32 *) CST_CTRL_PORT;
	    pwdata = (u16 *) CST_DATA_PORT;

		while(j < 32)
		{
			luma = ((i + (vblCount >> 1)) & 30) << 2;
		
			addr = VDP_PLAN_A + ((i + plan_width_by_y) << 1);
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma;

			addr += 2;
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma + 1;

			addr = VDP_PLAN_A + ((i + VDP_getPlanWidth() * (j + 1)) << 1);
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma + 2;

			addr += 2;
		    *plctrl = CST_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = TILE_USERINDEX + luma + 3;		    

		    i += 6;	
	
			if (i >= 40)
			{
				i = 0;
				j += 3;
				plan_width_by_y = VDP_getPlanWidth() * j;
				// return;
			}
		}
	}

	for(i = 0; i < 1024; i++)
	{
		tile_scroll_h[i] = sinFix16(i << 2) / 2;
		tile_scroll_v[i] = cosFix16(i << 2) / 4;
	}

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);

	/* Load the fond tiles */
	VDP_drawImageEx(APLAN, &stars_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += stars_anim.tileset->numTile;

	VDP_drawImageEx(BPLAN, &rse_logo, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 200) / 16, (240 - 50) / 16, FALSE, FALSE);
	vramIndex += rse_logo.tileset->numTile;		

	VDP_clearPlan(APLAN, 0);

	VDP_setPalette(PAL0, stars_anim.palette->data);
	VDP_setPalette(PAL1, rse_logo.palette->data);

	drawStarsStaticGrid();

    VDP_setHilightShadow(0);

    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);

	SYS_enableInts();

	SND_startPlay_XGM(zsenilia_theme);
	SND_setMusicTempo_XGM(50);	

	while (TRUE)
	{
		VDP_waitVSync();
		// if ((vblCount & 0x1) == 0)	
			drawStarsGrid();
		vblCount++;
		VDP_setHorizontalScrollTile(PLAN_A, 0, tile_scroll_h + (vblCount & 511), 32, TRUE);
		VDP_setVerticalScrollTile(PLAN_A, 0, tile_scroll_v + ((vblCount << 1) & 511), 32, TRUE);
		VDP_setHorizontalScrollTile(PLAN_B, 0, tile_scroll_v + ((vblCount << 1) & 511), 32, TRUE);
		VDP_setVerticalScrollTile(PLAN_B, 0, tile_scroll_h + (vblCount & 511), 32, TRUE);		
	}
}