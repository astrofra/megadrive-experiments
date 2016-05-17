#include <genesis.h>
#include <gfx.h>
#include "img_seq.h"
#include "transition_helper.h"

#define RSE_DOT_UNPACK_2 TILE_BITS
#define RSE_DOT_UNPACK_3 (TILE_BITS * 2)
#define RSE_DOT_UNPACK_4 (TILE_BITS * 3)

#define RSE_DOT_MASK_1 ((1 << TILE_BITS) - 1)
#define RSE_DOT_MASK_2 ((1 << (TILE_BITS * 2)) - 1)
#define RSE_DOT_MASK_3 ((1 << (TILE_BITS * 3)) - 1)
#define RSE_DOT_MASK_4 ((1 << (TILE_BITS * 4)) - 1)

#define RSE_GFX_WRITE_VRAM_ADDR(adr)    ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x00)
#define RSE_CTRL_PORT 0xC00004
#define RSE_DATA_PORT 0xC00000

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void RSE_gridTileAnimation()
{
	u16 vblCount = 0, i;
	// Sprite sprites[16];
	u16 tmp_timer;

	static void inline drawDotMatrix(void)
	{
		u16 i = 0, j = 0, k;
		u16 tile_index, luma, unpacked_luma;
		u16 plan_width_by_y = 0;

	    vu32 *plctrl;
	    vu16 *pwdata;
	    u32 addr;

		k = tore_tunnel_IMG_LEN;
		tile_index = (vblCount & (tore_tunnel_IMG_COUNT - 1)) * tore_tunnel_IMG_LEN;

		plctrl = (u32 *) RSE_CTRL_PORT;
	    pwdata = (u16 *) RSE_DATA_PORT;

		while(k--)
		{
			luma = star_tunnel_seq[tile_index];

			unpacked_luma = (luma & RSE_DOT_MASK_4) >> RSE_DOT_UNPACK_4;
			addr = VDP_PLAN_A + ((i + plan_width_by_y) << 1);
		    *plctrl = RSE_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = vramIndex + unpacked_luma;
		    i++;

			unpacked_luma = (luma & RSE_DOT_MASK_3) >> RSE_DOT_UNPACK_3;
			addr = VDP_PLAN_A + ((i + plan_width_by_y) << 1);
		    *plctrl = RSE_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = vramIndex + unpacked_luma;
		    i++;

			unpacked_luma = (luma & RSE_DOT_MASK_2) >> RSE_DOT_UNPACK_2;
			addr = VDP_PLAN_A + ((i + plan_width_by_y) << 1);
		    *plctrl = RSE_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = vramIndex + unpacked_luma;
		    i++;

			unpacked_luma = luma & RSE_DOT_MASK_1;
			addr = VDP_PLAN_A + ((i + plan_width_by_y) << 1);
		    *plctrl = RSE_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = vramIndex + unpacked_luma;
		    i++;			

			if (i >= 40)
			{
				i = 0;
				j++;
				plan_width_by_y = VDP_getPlanWidth() * j;
			}

			tile_index++;
		}
	}

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	// VDP_clearPlan(APLAN, 0);
	// VDP_clearPlan(BPLAN, 0);

	vramIndex = fontIndex;

	/* Load the fond tiles */
	VDP_drawImageEx(APLAN, &pat_round, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	// vramIndex += pat_round.tileset->numTile;

	// VDP_drawImageEx(BPLAN, &rse_logo, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 200) / 16, (240 - 50) / 16, FALSE, FALSE);
	// vramIndex += rse_logo.tileset->numTile;	

	VDP_setPalette(PAL0, pat_round.palette->data);
	// VDP_setPalette(PAL1, rse_logo.palette->data);

	// SPR_init(257);
 //    SPR_initSprite(&sprites[0], &rse_logo_shadow, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));
 //    // SPR_initSprite(&sprites[1], &rse_logo_shadow_alt, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));
	// SPR_setPosition(&sprites[0], (320 - 160) >> 1, ((240 - 50) >> 1) + 8);
 //    SPR_update(sprites, 1);	

 //    VDP_setHilightShadow(0);

	SYS_enableInts();

	tmp_timer = RSE_FRAMES(20);

	while (vblCount < tmp_timer) // || !RSE_writerIsDone())
	{
		VDP_waitVSync();
		drawDotMatrix();
		vblCount++;
	}

	VDP_fadeOut(0, 63, RSE_FRAMES(16), TRUE);

	i = 0;
	while (i < RSE_FRAMES(16)) // || !RSE_writerIsDone())
	{
		VDP_waitVSync();
		drawDotMatrix();
		vblCount++;
		i++;
	}

	RSE_turn_screen_to_black();

	for(i = 0; i  < 224 >> 3; i++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(i);
		RSE_clearTileRowA(i);
	}	

	RSE_resetScrolling();
}