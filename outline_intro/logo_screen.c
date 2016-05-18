#include "genesis.h"
#include <gfx.h>
#include "logo_screen.h"
#include "twister_fx.h"
#include "demo_strings.h"
#include "transition_helper.h"
#include "music.h"
#include "writer.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

s16 l_tile_scroll_h[1024];
u16 twister_y_offset;

u8 RSE_LogoScreen(void)
{
	u16 vblCount = 0, tmp_timer;
	s16 i, j, k;
	Sprite sprites[16];
	u16 smiley_phase = 0;
	s16 twister_jump_table[TWISTER_TABLE_SIZE];
	s16 y_logo_bounce;

	void inline drawVerticalStripes(void)
	{
	    u16 row, column;
	    u16 tile_stripes;

	    for(row = 0; row < NUM_ROWS; row++)
		    for(column = 0; column < NUM_SPOTLIGHTS; column++)
			    for(tile_stripes = 0; tile_stripes < SPOTLIGHT_WIDTH; tile_stripes++)
			    {
			       VDP_setTileMapXY( APLAN, TILE_ATTR_FULL(PAL0, column%2, 0, 0, TILE_SYSTEMINDEX),
			          (column * SPOTLIGHT_WIDTH) + tile_stripes, row);
			    }
	}

	void inline clearVerticalStripes(u16 row)
	{
	    u16 column;
	    u16 tile_stripes;

		for(column = 0; column < NUM_SPOTLIGHTS; column++)
			for(tile_stripes = 0; tile_stripes < SPOTLIGHT_WIDTH; tile_stripes++)
			{
				VDP_setTileMapXY( APLAN, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_SYSTEMINDEX),
				(column * SPOTLIGHT_WIDTH) + tile_stripes, row);
			}
	}

	s16 inline animateSmileyBounce(void)
	{
		s16 y;
		y = cosFix16(RSE_FRAMES(smiley_phase) << 3);
		if (y < 0)
			y = -y;
		y = 64 - y;

		SPR_setPosition(&sprites[0], ((SCR_W - 96) >> 1), 72 + y);
		SPR_setFrame(&sprites[0], 0);
	    SPR_update(sprites, 1);

	    if (smiley_phase == 0)
	    	VDP_fadePalTo(PAL2, smiley_gelmir.palette->data, RSE_FRAMES(16), TRUE);

	    smiley_phase++;
	    return y;
	}		

	/*
		Twister
	*/
	void initTwisterFx(void)
	{
		// s16 i, j;
		twister_y_offset = 0;

		for(i = 0, j = 0; i < TWISTER_TABLE_SIZE; i++)
		{
			j = sinFix16(i << 2) >> 2;
			twister_jump_table[i] = j;
		}

		VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	}

	void updateTwisterFx(u16 vcount_init, u16 duration, u16 offset)
	{
		u16 vcount, hbl_done = FALSE;

	    vu16 *pw;
	    vu32 *pl;

	    pw = (u16 *) GFX_DATA_PORT;
	    pl = (u32 *) GFX_CTRL_PORT;

		static void hBlank(){

		    *pl = CST_WRITE_VSRAM_ADDR(0);
		    *pw = twister_jump_table[(GET_VCOUNTER + vcount) & ((TWISTER_TABLE_SIZE >> 2) - 1)] - twister_y_offset;
		    if (!hbl_done)
		    {
		    	hbl_done = TRUE;
			    y_logo_bounce = animateSmileyBounce();	
		    }
		}

		VDP_setHInterrupt(1);
		SYS_setHIntCallback(&hBlank);

		vcount = vcount_init;
		while (vcount < duration)
		{
			VDP_waitVSync();
			hbl_done = FALSE;
			y_logo_bounce = 64 - y_logo_bounce;
			if (y_logo_bounce > 8)
				y_logo_bounce = 8;
			y_logo_bounce = 42 - y_logo_bounce;
			VDP_setVerticalScroll(PLAN_B, y_logo_bounce);
			twister_y_offset += offset;
			vcount++;
		}	
	}

	void disableTwisterFx(void)
	{
		VDP_setHInterrupt(0);
		VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
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

	vramIndex = fontIndex;
	demo_strings = (char **)strings_logo_0;

	/* 
		Group logo 
		Background (classic tile display)
	*/
	VDP_setHilightShadow(1); 
	VDP_drawImageEx(BPLAN, &logo_rse_bottom_9bits, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), ((SCR_W - LOGO_W) >> 4), (SCR_H - LOGO_H) >> 4, FALSE, FALSE);
    vramIndex += logo_rse_bottom_9bits.tileset->numTile;

	while(DMA_getQueueSize() > 0);

	drawVerticalStripes();

	while(DMA_getQueueSize() > 0);

	/* 
		Group logo 
		Large set of sprites
	*/		
	for(i = 0; i < 8; i++)
	{
	    SPR_initSprite(&sprites[i], &logo_rse_top_9bits, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, FALSE));
		SPR_setPosition(&sprites[i], ((SCR_W - LOGO_W) >> 1) + (i << 5), ((SCR_H - LOGO_H) >> 1) - 4 + 64);
		SPR_setFrame(&sprites[i], i);
	}

	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	SYS_enableInts();

	// RSE_pause(15);
	while(DMA_getQueueSize() > 0);


	/*
		Prepare a Sine table
		to distort the background using the per-line scrolling
	*/
	for(i = 0; i < 1024; i++)
		l_tile_scroll_h[i] = sinFix16(i << 2) / 2;

	play_music();

	RSE_pause(RSE_FRAMES(20));

	/* 
		Fade to the logo's palette
	*/
	VDP_fadePalTo(PAL2, logo_rse_top_9bits.palette->data, (32 * 60) / framerate, TRUE);

	for(i = 24; i > -16; i--)
	{
		VDP_waitVSync();
		for(k = 0; k < 8; k++)
		{
			j = i + (8 - k);
			if (j < 0)
				j = 0;
			j = (j * j) >> 5;
			SPR_setPosition(&sprites[k], ((SCR_W - LOGO_W) >> 1) + (k << 5), ((SCR_H - LOGO_H) >> 1) - 4 + j);
		}
		SPR_update(sprites, 8);
	}

	/*	
		Prepare text writer
	*/
	current_char_y = 18;
	writer_display_duration = 100;
	clearVerticalStripes(current_char_y);
	RSE_writerUnsetOption(WRT_OPT_WRITE_TO_PLAN_A);
	RSE_writerUnsetOption(WRT_OPT_AUTO_RESTART);
	RSE_writerSetOption(WRT_OPT_HALF_SPEED);
	RSE_writerSetDisplayDuration(RSE_FRAMES(40));

	RSE_pause(RSE_FRAMES(30));

	VDP_setPalette(PAL0, oddball_fonts.palette->data);
	VDP_fadePalTo(PAL1, logo_rse_bottom_9bits.palette->data, (64 * 60) / framerate, TRUE);

	/*	
		Animate the background
	*/
	vblCount = 0;
	tmp_timer = RSE_FRAMES(130);
	while (vblCount < tmp_timer)
	{
		VDP_waitVSync();
		VDP_setHorizontalScrollLine(PLAN_A, (SCR_H - LOGO_H) / 2, l_tile_scroll_h + (vblCount & 511), 60, TRUE);
		vblCount++;
	}

	/*	
		Write some text
		while animating the background
	*/
	tmp_timer += RSE_FRAMES(450);
	while (vblCount < tmp_timer)
	{
		VDP_waitVSync();
		VDP_setHorizontalScrollLine(PLAN_A, (SCR_H - LOGO_H) / 2, l_tile_scroll_h + (vblCount & 511), 60, TRUE);
		RSE_writerUpdateLine();
		vblCount++;
	}

	/*	
		Fade out the background
		while animating it
	*/
	VDP_fadePalTo(PAL1, palette_black, RSE_FRAMES(32), TRUE);

	tmp_timer += RSE_FRAMES(32);
	while (vblCount < tmp_timer)
	{
		VDP_waitVSync();
		VDP_setHorizontalScrollLine(PLAN_A, (SCR_H - LOGO_H) / 2, l_tile_scroll_h + (vblCount & 511), 60, TRUE);		
		vblCount++;
	}

	/*	
		Fade out the foreground
		while scrolling it from below
	*/
	VDP_fadeOut(1, 63, RSE_FRAMES(32), TRUE);

	for(i = 0; i < 32; i++)
	{
		VDP_waitVSync();
		for(k = 0; k < 8; k++)
		{
			j = i + k;
			j = (j * j) >> 5;
			SPR_setPosition(&sprites[k], ((SCR_W - LOGO_W) >> 1) + (k << 5), ((SCR_H - LOGO_H) >> 1) - 4 - j);
		}
		SPR_update(sprites, 8);
		VDP_setHorizontalScrollLine(PLAN_A, (SCR_H - LOGO_H) / 2, l_tile_scroll_h + (vblCount & 511), 60, TRUE);		
		vblCount++;
	}		

	RSE_clearTileRowB(current_char_y);

	/* 
		Demo logo 
	*/
	SYS_disableInts();
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setHilightShadow(0);
	SPR_end();
	vramIndex = fontIndex;

	/* 
		Demo logo 
		(classic tile display)
	*/
	VDP_drawImageEx(BPLAN, &logo_demo, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), ((SCR_W - LOGO_DEMO_W) >> 4), ((SCR_H - LOGO_DEMO_H) >> 4) - 2, FALSE, FALSE);
	vramIndex += logo_demo.tileset->numTile;

	SYS_enableInts();

	/*
		Smiley sprite
	*/
	SPR_init(257);
    SPR_initSprite(&sprites[0], &smiley_gelmir, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	SPR_setPosition(&sprites[0], ((SCR_W - 96) >> 1), 220);
	SPR_setFrame(&sprites[0], 0);
    SPR_update(sprites, 1);

	/*
		Prepare a new Sine table
	*/
	for(i = 0; i < 1024; i++)
	{
		k = 1024 - i;
		k = (k * k) >> 10;
		l_tile_scroll_h[i] = 32 + ((cosFix16(i << 2) * k) >> 10);
	}

	VDP_setVerticalScrollTile(PLAN_B, 0, l_tile_scroll_h, 32, TRUE);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_2TILE);

	/*
		Fade in the logo
		while scrolling it from below
		with an animated sine-based offset
	*/
	VDP_fadePalTo(PAL1, logo_demo.palette->data, RSE_FRAMES(32), TRUE);

	for(i = 0; i < 1024 - 32; i += 4)
	{
		VDP_waitVSync();
		VDP_setVerticalScrollTile(PLAN_B, 0, l_tile_scroll_h + i, 32, TRUE);

		if (i >= 1024 - (160 * 4))
			animateSmileyBounce();
	}

	VDP_fadePalTo(PAL0, outline_logo.palette->data, RSE_FRAMES(16), TRUE);

	/*
		Fake raster bar (tile based)
	*/
	VDP_drawImageEx(APLAN, &outline_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, ((SCR_H - LOGO_CHAR_H) >> 4) + 5, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &outline_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 112 >> 3, ((SCR_H - LOGO_CHAR_H) >> 4) + 5, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &outline_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 112 >> 2, ((SCR_H - LOGO_CHAR_H) >> 4) + 5, FALSE, FALSE);	
	
	// RSE_pause(60 * 5);
	initTwisterFx();
	updateTwisterFx(0, framerate * 3, 0);
	updateTwisterFx(framerate * 3, (framerate * 3) + (framerate >> 1), 1);
	updateTwisterFx((framerate * 3) + (framerate >> 1), framerate * 4, 2);
	updateTwisterFx((framerate * 3) + (framerate >> 1), (framerate * 4) + (framerate >> 3), 3);

	disableTwisterFx();
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	VDP_fadeOut(1, 63, RSE_FRAMES(10), TRUE);

	// for(i = 0; i  < 224 >> 3; i++)
	// 	clearVerticalStripes(i);

	for(i = 0; i  < 224 >> 3; i++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(i);
		RSE_clearTileRowA(i);
	}

	RSE_resetScrolling();

	SPR_end();

	return 0;
}
