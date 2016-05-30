#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "demo_strings.h"
#include "transition_helper.h"

#define MAX_SIMULATION 6;

#define PLASMA_SCROLL_A(A) 		VDP_setVerticalScrollTile(PLAN_A, 0, p_tile_scroll_h + ((vblCount << 1) & 1023), 32, FALSE); \
								VDP_setHorizontalScrollTile(PLAN_A, 0, p_tile_scroll_v + (vblCount & 1023), 32, FALSE);

#define PLASMA_SCROLL_B(A) 		VDP_setHorizontalScrollTile(PLAN_B, 0, p_tile_scroll_h + ((vblCount << 1) & 1023), 32, FALSE); \
								VDP_setVerticalScrollTile(PLAN_B, 0, p_tile_scroll_v + (vblCount & 1023), 32, FALSE);

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

s16 p_tile_scroll_h[2048],
	p_tile_scroll_v[2048];

u16 p_palette_cycle[16 * 16];

/*
	Plasma screen
	mode : 
		0 : credits mode
		1 : greetings mode
*/

void RSE_plasma_init(void)
{
	u16 i;
	/*
		Init scroll
	*/
	for(i = 0; i < 2048; i++)
	{
		p_tile_scroll_h[i] = (sinFix16(i << 2) >> 1) - 32;
		p_tile_scroll_v[i] = (cosFix16(i << 2)) + 64 + ((cosFix16((i + 128) << 4) >> 1) * sinFix16(i + 256) / 350);
	}
}

void RSE_plasma(u8 mode)
{
	u32 vblCount = 0;
	u16 i, j;
	u16 tmp_timer;
	u16 col;
	Image plasma_img;

	RSE_turn_screen_to_black();

	switch(mode)
	{
		case 0:
			plasma_img = plasma;
			current_char_y = 4;
			writer_display_duration = 10;
			demo_strings = (char **)strings_credits;

			/*
				Init palette
			*/
			for(i = 0; i < 16; i++)
			{
				VDP_waitVSync();
				for(j = 0; j <  16; j++)
					p_palette_cycle[j + (i * 16)] = (plasma_img.palette->data[(j + i) & 0xF]);

				p_palette_cycle[i * 16] = 0x0;
			}
			break;

		case 1:
			plasma_img = plasma_greets;
			current_char_y = 2;
			writer_display_duration = 20;
			demo_strings = (char **)strings_greets;

			/*
				Init palette
			*/
			col = plasma_img.palette->data[15];
			for(i = 0; i < 16; i++)
			{
				VDP_waitVSync();
				for(j = 0; j <  16; j++)
					p_palette_cycle[j + ((15 - i) * 16)] = (plasma_img.palette->data[(j + i) & 0xF]);

			}	

			for(i = 0; i < 16; i++)
			{
				p_palette_cycle[i * 16] = 0x0;
				p_palette_cycle[(i * 16) + 15] = col;
			}	

			break;
	}	

	/*
		Init writer
	*/
	RSE_writerSetOption(WRT_OPT_WRITE_TO_PLAN_A);
	RSE_writerUnsetOption(WRT_OPT_AUTO_RESTART);
	RSE_writerSetInitialY(2);
	RSE_writerRestart();		

	RSE_resetScrolling();

	VDP_waitVSync();

	SYS_disableInts();
	VDP_setPlanSize(64, 32);
	// VDP_clearPlan(APLAN, 0);
	// VDP_clearPlan(BPLAN, 0);
	VDP_setHilightShadow(0);	

	vramIndex = fontIndex;

	// vramIndex += plasma_img.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);	

	VDP_setPalette(PAL0, oddball_fonts.palette->data);
	VDP_setPalette(PAL1, plasma_img.palette->data);

	SYS_enableInts();

	/*
		Draw the plasma
		(frame interleaved)
	*/
	tmp_timer = (512 * 60) / framerate;
	while (vblCount < tmp_timer || !RSE_writerIsDone())
	{
		VDP_waitVSync();

		/*
			Draw a top/bottom line
			to frame the image.
		*/
		if (vblCount < 328 >> 3)
		{
			i = vblCount;
			/* Top line */
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + FONT_LINE_OFFSET - 2, i, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 0));
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + (FONT_LINE_OFFSET << 1) - 2, i + 1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 0));
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + (FONT_LINE_OFFSET << 2) - 2, i + 2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 0));

			/* Bottom line */
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + FONT_LINE_OFFSET - 1, (320 >> 3) - i, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, (224 >> 3) - 1));
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + (FONT_LINE_OFFSET << 1) - 1, (320 >> 3) - i - 1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, (224 >> 3) - 1));
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + (FONT_LINE_OFFSET << 2) - 1, (320 >> 3) - i - 2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, (224 >> 3) - 1));
		}
		else
			RSE_writerUpdateMultiLine();

		if (vblCount < 9 << 1)
		{
			switch(vblCount)
			{
				case 0:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
					vramIndex += plasma_img.tileset->numTile;
					break;
					
				case 1 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 0, FALSE, FALSE);			
					break;
					
				case 2 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 0, FALSE, FALSE);
					break;
					
				case 3 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 128 >> 3, FALSE, FALSE);
					break;
					
				case 4 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 128 >> 3, FALSE, FALSE);
					break;
					
				case 5 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 128 >> 3, FALSE, FALSE);
					break;
					
				case 6 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 256 >> 3, FALSE, FALSE);
					break;
					
				case 7 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 128 >> 3, 256 >> 3, FALSE, FALSE);
					break;
					
				case 8 << 1:
					VDP_drawImageEx(BPLAN, &plasma_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 256 >> 3, FALSE, FALSE);
					break;	
			}
		}

		// PLASMA_SCROLL_A();
		PLASMA_SCROLL_B();
		VDP_setPalette(PAL1, p_palette_cycle + (((vblCount >> 2) << 4) & 255));
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

		// VDP_setHorizontalScrollTile(PLAN_B, 0, p_tile_scroll_h + ((vblCount << 1) & 1023), 32, TRUE);
		// VDP_setVerticalScrollTile(PLAN_B, 0, p_tile_scroll_v + (vblCount & 1023), 32, TRUE);
		// PLASMA_SCROLL_A();
		PLASMA_SCROLL_B();
		vblCount++;
		i++;
	}

	VDP_waitVSync();

	SPR_end();	

	RSE_resetScrolling();
}