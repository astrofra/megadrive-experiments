#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

static 	Sprite *sprites[16];

void displayRSELogoFX(void)
{
	u16 fx_phase, i, j, k, vcount;
	s16 shield_hscroll[256];
	s16 scroll_tile_x[32], scroll_dir[32];

	SYS_disableInts();

	// VDP_clearPlan(PLAN_A, 0);
	// VDP_clearPlan(PLAN_B, 0);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	SPR_init(64, 180, 180);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(128, 32);
	VDP_setHilightShadow(1); 

	vramIndex = 0;

	/* Draw the background */
	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 8, FALSE, TRUE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 16, FALSE, TRUE);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	VDP_drawImageEx(PLAN_A, &shield_anim, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 24, FALSE, TRUE);
	vramIndex += shield_anim.tileset->numTile;

	/* Draw the foreground */
	for(i = 0; i < (224 - 120) >> 4; i++)
		RSE_clearTileRowBWithPrio(i);

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();

	for(i = 21; i < 28; i++)
		RSE_clearTileRowBWithPrio(i);	

	VDP_drawImageEx(PLAN_B, &rsi_logo_0, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 120) >> 4, FALSE, TRUE);
	vramIndex += rsi_logo_0.tileset->numTile;

	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &rsi_logo_1, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, (64 >> 3) + ((224 - 120) >> 4), FALSE, TRUE);
	vramIndex += rsi_logo_1.tileset->numTile;

	/* Shadow sprite */
	sprites[0] = SPR_addSprite(&rse_logo_shadow, 40, ((224 - 120) >> 1) + 70, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, 0));
	SPR_update(sprites, 1);

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);

	SYS_enableInts();

	DMA_waitCompletion();

	for (i = 0; i < (120 >> 3); i++)
		scroll_tile_x[i] = 0;

	VDP_waitVSync();

	for (i = 0; i < 4; i++)
	{ 
		VDP_waitVSync();
		for(j = 0; j < 8; j++)
		{
			shield_hscroll[i * 8 + j] = i * 4 * 64;
			if (i & 0x1)
				shield_hscroll[i * 8 + j] += 32;
			if (i && 0x1)
				scroll_dir[i * 8 + j] = 64;
			else
				scroll_dir[i * 8 + j] = -64;
		}
	}

	// VDP_fadePalTo(PAL1, palette_white, RSE_FRAMES(4), TRUE);

	VDP_fadePalTo(PAL1, rsi_logo_0.palette->data, RSE_FRAMES(16), TRUE);
	vcount = 0;
	k = 0;
	while(vcount < RSE_FRAMES(60 * 4))
	{
		VDP_waitVSync();
		if (vcount == RSE_FRAMES(16) + 2)
				VDP_fadePalTo(PAL0, shield_anim.palette->data, RSE_FRAMES(16), TRUE);

		vcount++;
		k++;
		if (k > 2)
		{
			k = 0;
			VDP_setHorizontalScrollTile(PLAN_A, 0, shield_hscroll, 8 * 4, TRUE);
			for (i = 0; i < 4; i++)
				for(j = 0; j < 8; j++)
				{
					shield_hscroll[i * 8 + j] += scroll_dir[i * 8 + j];
					// if (scroll_dir[i * 8 + j] < 0 && shield_hscroll[i * 8 + j] < 128)
					// 	scroll_dir[i * 8 + j] *= -1;
					// else
					// if (scroll_dir[i * 8 + j] > 0 && shield_hscroll[i * 8 + j] > 1024 - 128)
					// 	scroll_dir[i * 8 + j] *= -1;

				}
		}

	}

	for(j = 0; j  < VDP_getPlanWidth(); j++)
	{
		VDP_waitVSync();
		k = j >> 3;

		for (i = 0; i < (120 >> 4); i++)
		{
			scroll_tile_x[i]+= k;
			if (i < (120 >> 4) - 1)
				scroll_tile_x[i]++;
		}

		for (; i < (120 >> 3); i++)
		{
			scroll_tile_x[i]-= k;
			if (i > (120 >> 4))
				scroll_tile_x[i]--;
		}

		if (j == RSE_FRAMES(4) + 1)
			VDP_fadePalTo(PAL1, rsi_logo_0.palette->data, RSE_FRAMES(8), TRUE);
		if (j == 16)
			VDP_fadeOut(0, 63, 32, TRUE);

		SYS_disableInts();
		VDP_setHorizontalScrollTile(PLAN_B, (224 - 120) >> 4, scroll_tile_x, 120 >> 3, TRUE);
		SYS_enableInts();
	}

	RSE_pause(32);
	RSE_turn_screen_to_black();

	SPR_end();
	RSE_resetScrolling();

	SYS_disableInts();

	// // VDP_clearPlan(PLAN_A, TRUE);
	// // VDP_clearPlan(PLAN_B, TRUE);

	VDP_setHilightShadow(0);

	VDP_waitVSync();

	SYS_enableInts();

	vramIndex = TILE_USERINDEX;
}