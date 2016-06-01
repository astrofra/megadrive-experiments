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
	u16 vblCount = 0, i, w;
	// u8 frame_switch = 0;
	u16 tmp_timer;
	Sprite sprites[16];

	static void inline drawDotMatrix(void)
	{
		u16 i = 0, j = 0, k;
		u16 tile_index, luma, unpacked_luma;
		u16 plan_width_by_y = 0;

		// frame_switch = !frame_switch;
		// if (frame_switch)
		// 	return;

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

			unpacked_luma = (luma & RSE_DOT_MASK_3) >> RSE_DOT_UNPACK_3;
			addr += 2;
		    *plctrl = RSE_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = vramIndex + unpacked_luma;

			unpacked_luma = (luma & RSE_DOT_MASK_2) >> RSE_DOT_UNPACK_2;
			addr += 2;
		    *plctrl = RSE_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = vramIndex + unpacked_luma;

			unpacked_luma = luma & RSE_DOT_MASK_1;
			addr += 2;
		    *plctrl = RSE_GFX_WRITE_VRAM_ADDR(addr);
		    *pwdata = vramIndex + unpacked_luma;
		    i += 4;			

			if (i >= 40)
			{
				i = 0;
				plan_width_by_y += w;
			}

			tile_index++;
		}
	}

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);
	w = VDP_getPlanWidth();
	SPR_init(257);

	vramIndex = fontIndex;

	/* Load the fond tiles */
	VDP_drawImageEx(APLAN, &pat_round, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	// VDP_setPalette(PAL0, pat_round.palette->data);

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_drawImageEx(BPLAN, &alexkidd, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex + pat_round.tileset->numTile), ((320 - 207) >> 4) + 3, (128 >> 3) + 4, FALSE, FALSE);
	VDP_setVerticalScroll(PLAN_B, -64);
	// VDP_setPalette(PAL1, alexkidd.palette->data);

	SYS_enableInts();

	SPR_initSprite(&sprites[0], &alexkidd_overlay, 48, 4, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, FALSE));
	SPR_update(sprites, 1);

	VDP_fadePalTo(PAL1, alexkidd.palette->data, 32, TRUE);
	for(i = 0; i < 32; i++)
	{
		VDP_waitVSync();
		VDP_setVerticalScroll(PLAN_B, ((easing_table[i << 5] * (108 + 64)) / 1024) - 64);
	}

	VDP_fadePalTo(PAL2, alexkidd_overlay.palette->data, 16, TRUE);
	for(i = 0; i < 32; i+=2)
	{
		VDP_waitVSync();
		SPR_setPosition(&sprites[0], (easing_table[i << 5] * 48) / 1024, 4);
		SPR_update(sprites, 1);
	}	

	tmp_timer = RSE_FRAMES(32);
	VDP_fadePalTo(PAL0, pat_round.palette->data, tmp_timer, TRUE);

	while (vblCount < tmp_timer)
	{
		VDP_waitVSync();
		drawDotMatrix();
		vblCount++;
	}

	tmp_timer += RSE_FRAMES(60 * 3);
	
	while (vblCount < tmp_timer)
	{
		VDP_waitVSync();
		drawDotMatrix();
		vblCount++;
	}	

	tmp_timer += RSE_FRAMES(16);
	VDP_fadeOut(0, 63, RSE_FRAMES(16), TRUE);

	while (vblCount < tmp_timer)
	{
		VDP_waitVSync();
		drawDotMatrix();
		vblCount++;
	}

	RSE_turn_screen_to_black();

	SPR_end();

	for(i = 0; i  < 224 >> 3; i++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(i);
		RSE_clearTileRowA(i);
	}	

	RSE_resetScrolling();
}