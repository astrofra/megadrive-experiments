#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"
#include "demo_strings.h"
#include "page_writer.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

u16 palette_bg[16];

void shieldAnimFX(void)
{
	u16 fx_phase, i, j, k, vcount, vcount2;
	s16 si, sj;
	s16 shield_hscroll[256];
	s16 scroll_tile_x[32], scroll_dir[32], wipe_tile_x[32];
	u16 bx, by;
	bx = 2; by = 2;

	SYS_disableInts();

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(128, 32);
	VDP_setHilightShadow(1); 

	vramIndex = fontIndex;

	/* Draw the background */
	for(i = 0; i < 4; i++)
	{
		VDP_drawImageEx(PLAN_B, &shield_anim_0, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, i << 3 , FALSE, TRUE);

		SYS_enableInts();
		VDP_waitVSync();
		SYS_disableInts();
	}

	vramIndex += shield_anim_0.tileset->numTile;

	for(i = 0; i < 4; i++)
	{
		VDP_drawImageEx(PLAN_B, &shield_anim_1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 512 >> 3, i << 3 , FALSE, TRUE);

		SYS_enableInts();
		VDP_waitVSync();
		SYS_disableInts();
	}

	vramIndex += shield_anim_1.tileset->numTile;

	VDP_setPaletteColor(17, 0x000);

	for(i = 0; i < 15; i++)
	{
		VDP_drawImageEx(PLAN_A, &transition_pattern, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, i << 1, FALSE, TRUE);
		SYS_enableInts();
		VDP_waitVSync();
		SYS_disableInts();
	}

	vramIndex += transition_pattern.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

	SYS_enableInts();

	DMA_waitCompletion();

	for (i = 0; i < 32; i++)
		scroll_tile_x[i] = 0;

	for (i = 0; i < 32; i++)
		wipe_tile_x[i] = 0;

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

	for(i = 0; i < 16; i++)
		palette_bg[i] = shield_anim_0.palette->data[i];

	palette_bg[0] = flames_0.palette->data[2];

	/* init writer */
	pg_current_char_y = 4;
	pgwriter_display_duration = 20;
	demo_strings = (char **)strings_greets;

	vcount = 0;
	vcount2 = 0;
	k = 0;

	while(vcount2 < RSE_FRAMES(60 * 2))
	{
		VDP_waitVSync();

		if (vcount2 > 0 || RSE_pgwriterIsDone())
			vcount2++;

		if (vcount == RSE_FRAMES(16) + 2)
				VDP_fadePalTo(PAL0, shield_anim_0.palette->data, RSE_FRAMES(16), TRUE);
		else
		/* wipe fx */
		if (vcount > RSE_FRAMES(40) && vcount < RSE_FRAMES(80))
		{
			si = vcount - RSE_FRAMES(40);
			sj = (si * 700) / RSE_FRAMES(80 - 40);
			for (i = 0; i < 32; i++)
			{
				si = sj + i - 32;
				if (si < -700) si = -700;
				wipe_tile_x[i] = si;
			}
			VDP_setHorizontalScrollTile(PLAN_A, 0, wipe_tile_x, 8 << 2, TRUE);
		}
		else
		/* clear the wipe fx layer */
		if (vcount >= RSE_FRAMES(80) && vcount < RSE_FRAMES(80) + 32)
			RSE_clearTileRowAWithPrio(vcount - RSE_FRAMES(80));
		else
		/* reset the scroll offset */
		if (vcount == RSE_FRAMES(80) + 40)
		{
			for (i = 0; i < 32; i++)
				wipe_tile_x[i] = 0;
			VDP_setHorizontalScrollTile(PLAN_A, 0, wipe_tile_x, 8 << 2, TRUE);
		}

		if (vcount == RSE_FRAMES(70))
				VDP_fadePalTo(PAL0, palette_bg, RSE_FRAMES(16), TRUE);

		if (vcount == RSE_FRAMES(200))
			VDP_fadePalTo(PAL2, sim1_font.palette->data, RSE_FRAMES(16), TRUE);
		else
		if (vcount > RSE_FRAMES(200))
			RSE_pgwriterUpdateMultiLine();

		if (by < (224 >> 3) - 2 && vcount > RSE_FRAMES(100))
		{
			VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL2, FALSE, 0, 0, TILE_SYSTEMINDEX), bx, by);
			VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL2, FALSE, 0, 0, TILE_SYSTEMINDEX), bx+1, by);

			bx += 2;
			if (bx >= (320 >> 3) - 2)
			{
				bx = 2;
				by++;
			}

		}

		/* Animate the shields in the background */
		vcount++;
		k++;
		if (k > 2)
		{
			k = 0;
			VDP_setHorizontalScrollTile(PLAN_B, 0, scroll_tile_x, 8 << 2, TRUE);
			for (i = 0; i < 4; i++)
				for(j = 0; j < 8; j++)
					shield_hscroll[(i << 3) + j] += scroll_dir[(i << 3) + j];

			for(i = 0; i < 32; i++)
			{
				j = i >> 3;
				scroll_tile_x[i] = shield_hscroll[i] + sinFix16((vcount + (j << 4)) << 3);
			}
		}

		/* exit transition */
		if (vcount2 > RSE_FRAMES(30))
		{
			if (vcount2 == RSE_FRAMES(30) + 5)
 				VDP_fadeOut(0, 63, 16, TRUE);

			for (i = 0; i < 32; i++)
				if (i & 0x1)
					wipe_tile_x[i] += (i >> 1) + 1;
				else
					wipe_tile_x[i] -= ((i >> 1) + 1);

			VDP_setHorizontalScrollTile(PLAN_A, 0, wipe_tile_x, 8 << 2, TRUE);			
		}

	}

	RSE_turn_screen_to_black();

	SPR_end();
	RSE_resetScrolling();

	SYS_disableInts();

	VDP_setHilightShadow(0);

	VDP_waitVSync();

	SYS_enableInts();

	{
		u16 i;
		for(i = 0; i  < 224 >> 3; i++)
		{
			if (i & 0x1) VDP_waitVSync();
			RSE_clearTileRowB(i);
			RSE_clearTileRowA(i);
		}
	}		

	vramIndex = TILE_USERINDEX;
}