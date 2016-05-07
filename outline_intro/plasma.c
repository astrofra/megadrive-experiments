#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "demo_strings.h"
#include "transition_helper.h"

#define MAX_SIMULATION 6;

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

s16 p_tile_scroll_h[2048],
	p_tile_scroll_v[2048];

/*
	Plasma screen
	mode : 
		0 : credits mode
		1 : greetings mode
*/
void RSE_plasma(u8 mode)
{
	u32 vblCount = 0, i, j;
	u16 tmp_timer;
	Image plasma_img;

	u16 palette_cycle[16 * 16];

	RSE_turn_screen_to_black();

	switch(mode)
	{
		case 0:
			plasma_img = plasma;
			current_char_y = 4;
			writer_display_duration = 10;
			demo_strings = (char **)strings_credits;
			break;

		case 1:
			plasma_img = plasma_greets;
			current_char_y = 2;
			writer_display_duration = 20;
			demo_strings = (char **)strings_greets;
			break;
	}

	/*
		Init scroll
	*/
	for(i = 0; i < 2048; i++)
	{
		p_tile_scroll_h[i] = (sinFix16(i << 2) >> 1) - 32; //  + ((sinFix16((i + 256) << 4) >> 1) * sinFix16(i) / 350);
		p_tile_scroll_v[i] = (cosFix16(i << 2)) + 64 + ((cosFix16((i + 128) << 4) >> 1) * sinFix16(i + 256) / 350);
	}

	/*
		Init palette
	*/
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j <  16; j++)
			palette_cycle[j + (i * 16)] = (plasma_img.palette->data[(j + i) & 0xF]); // | (((sinFix16(i * 64) + 64) >> 1) & 0x00F);

		palette_cycle[i * 16] = 0x0;
	}

	/*
		Init writer
	*/
	RSE_writerSetOption(WRT_OPT_WRITE_TO_PLAN_A);
	RSE_writerUnsetOption(WRT_OPT_AUTO_RESTART);	
	RSE_writerRestart();		

	RSE_resetScrolling();

	VDP_waitVSync();
	SYS_disableInts();
	VDP_setPlanSize(64, 32);
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setHilightShadow(0);	

	vramIndex = fontIndex;

	vramIndex += plasma_img.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);	

	VDP_setPalette(PAL0, oddball_fonts.palette->data);
	VDP_setPalette(PAL1, plasma_img.palette->data);

	SYS_enableInts();

	tmp_timer = (512 * 60) / framerate;
	while (vblCount < tmp_timer || !RSE_writerIsDone())
	{
		VDP_waitVSync();

		RSE_writerUpdateMultiLine();

		if (vblCount < 9)
		{
			switch(vblCount)
			{
				case 0:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
					break;
					
				case 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 0, FALSE, TRUE);			
					break;
					
				case 2:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 0, FALSE, TRUE);
					break;
					
				case 3:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 128 >> 3, FALSE, TRUE);
					break;
					
				case 4:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 128 >> 3, FALSE, TRUE);
					break;
					
				case 5:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 128 >> 3, FALSE, TRUE);
					break;
					
				case 6:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 256 >> 3, FALSE, TRUE);
					break;
					
				case 7:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 256 >> 3, FALSE, TRUE);
					break;
					
				case 8:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 256 >> 3, FALSE, TRUE);
					break;	
			}
		}

		VDP_setHorizontalScrollTile(PLAN_B, 0, p_tile_scroll_h + ((vblCount << 1) & 1023), 32, TRUE);
		VDP_setVerticalScrollTile(PLAN_B, 0, p_tile_scroll_v + (vblCount & 1023), 32, TRUE);
		VDP_setPalette(PAL1, palette_cycle + (((vblCount >> 2) << 4) & 255));
		vblCount++;
	}

	/*
		Fade out
	*/
	VDP_fadeOut(1, 63, 32, TRUE);	
	i = 0;

	while (i < 32)
	{
		VDP_waitVSync();

		VDP_setHorizontalScrollTile(PLAN_B, 0, p_tile_scroll_h + ((vblCount << 1) & 1023), 32, TRUE);
		VDP_setVerticalScrollTile(PLAN_B, 0, p_tile_scroll_v + (vblCount & 1023), 32, TRUE);
		vblCount++;
		i++;
	}

	VDP_waitVSync();

	SPR_end();	

	RSE_resetScrolling();
}
