#include "genesis.h"
#include <gfx.h>
#include "logo_screen.h"
#include "transition_helper.h"
#include "music.h"

void RSE_LogoScreen(void)
{
	u16 vblCount = 0;
	s16 i, j, k;
	u16 vramIndex = TILE_USERINDEX;
	s16 tile_scroll_h[1024];
	Sprite sprites[16];

	void inline DrawSpotlights(void)
	{
	    u16 row, column;
	    u16 tile_spotlight;

	    for(row = 0; row < NUM_ROWS; row++)
		    for(column = 0; column < NUM_SPOTLIGHTS; column++)
			    for(tile_spotlight = 0; tile_spotlight < SPOTLIGHT_WIDTH; tile_spotlight++)
			    {
			       VDP_setTileMapXY( APLAN, TILE_ATTR_FULL(PAL0, column%2, 0, 0, VRAM_POS_TILE_VOID),
			          (column * SPOTLIGHT_WIDTH) + tile_spotlight, row);
			    }
	}

	/* 
		Screen init 
	*/
	SYS_disableInts();
	VDP_setPlanSize(64, 64);
	RSE_turn_screen_to_black();
	VDP_setScreenWidth320();
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);	
	SPR_init(257);

	/* 
		Group logo 
	*/
	VDP_setHilightShadow(1); 
	VDP_drawImageEx(BPLAN, &logo_rse_bottom_9bits, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), ((SCR_W - LOGO_W) >> 4), (SCR_H - LOGO_H) >> 4, FALSE, TRUE);
	DrawSpotlights();

    vramIndex += logo_rse_bottom_9bits.tileset->numTile;

	for(i = 0; i < 16; i++)
	{
	    SPR_initSprite(&sprites[i], &logo_rse_top_9bits, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
		SPR_setPosition(&sprites[i], ((SCR_W - LOGO_W) >> 1) + (i << 4), ((SCR_H - LOGO_H) >> 1) - 4 + 64);
		SPR_setFrame(&sprites[i], i);
	}
    SPR_update(sprites, 1);

	// VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	SYS_enableInts();

	RSE_pause(15);

	for(i = 0; i < 1024; i++)
		tile_scroll_h[i] = sinFix16(i << 2) / 2;

	play_music();

	/* Fade to the logo's palette */
	VDP_fadePalTo(PAL2, logo_rse_top_9bits.palette->data, 32, TRUE);
	
	for(i = 24; i > -16; i--)
	{
		VDP_waitVSync();
		for(k = 0; k < 16; k++)
		{
			j = i + (16 - k);
			if (j < 0)
				j = 0;
			j = (j * j) >> 5;
			SPR_setPosition(&sprites[k], ((SCR_W - LOGO_W) >> 1) + (k << 4), ((SCR_H - LOGO_H) >> 1) - 4 + j);
		}
		SPR_update(sprites, 16);
	}

	VDP_fadePalTo(PAL1, logo_rse_bottom_9bits.palette->data, 64, TRUE);

	vblCount = 0;
	while (vblCount < 60 * 5)
	{
		VDP_waitVSync();
		VDP_setHorizontalScrollLine(PLAN_A, (SCR_H - LOGO_H) / 2, tile_scroll_h + (vblCount & 511), 80, TRUE);		
		vblCount++;
	}

	VDP_fadePalTo(PAL1, palette_black, 32, TRUE);
	while (vblCount < (60 * 5) + 32)
	{
		VDP_waitVSync();
		VDP_setHorizontalScrollLine(PLAN_A, (SCR_H - LOGO_H) / 2, tile_scroll_h + (vblCount & 511), 80, TRUE);		
		vblCount++;
	}

	VDP_fadeOut(1, 63, 32, TRUE);

	for(i = 0; i < 32; i++)
	{
		VDP_waitVSync();
		for(k = 0; k < 16; k++)
		{
			j = i + k;
			j = (j * j) >> 5;
			SPR_setPosition(&sprites[k], ((SCR_W - LOGO_W) >> 1) + (k << 4), ((SCR_H - LOGO_H) >> 1) - 4 - j);
		}
		SPR_update(sprites, 16);
		VDP_setHorizontalScrollLine(PLAN_A, (SCR_H - LOGO_H) / 2, tile_scroll_h + (vblCount & 511), 80, TRUE);		
		vblCount++;
	}

	/* 
		Demo logo 
	*/
	SYS_disableInts();
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setHilightShadow(0);
	SPR_end();
	vramIndex = TILE_USERINDEX;

	VDP_drawImageEx(BPLAN, &logo_demo, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), ((SCR_W - LOGO_DEMO_W) >> 4), ((SCR_H - LOGO_DEMO_H) >> 4) - 2, FALSE, TRUE);
	vramIndex += logo_demo.tileset->numTile;

	VDP_drawImageEx(APLAN, &outline_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), ((SCR_W - LOGO_CHAR_W) >> 4), ((SCR_H - LOGO_CHAR_H) >> 4) + 5, FALSE, TRUE);
	VDP_setVerticalScroll(PLAN_A, 64 - 8);
	// VDP_setPalette(PAL0, the_red_bot.palette->data);
	SYS_enableInts();

	VDP_fadePalTo(PAL1, logo_demo.palette->data, 32, TRUE);

	for(i = 0; i < 32; i++)
	{
		VDP_waitVSync();
		j = (i * i) >> 5;
		VDP_setVerticalScroll(PLAN_B, j);
		VDP_setVerticalScroll(PLAN_A, ((32 - j) << 1) - 8);
	}

	VDP_fadePalTo(PAL0, outline_logo.palette->data, 16, TRUE);

	RSE_pause(60 * 5);

	VDP_fadeOut(1, 63, 32, TRUE);
	RSE_pause(60);

}