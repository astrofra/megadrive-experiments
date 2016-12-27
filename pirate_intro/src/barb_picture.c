#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void displayBarbPictureFX(void)
{
	u16 fx_phase, j, scroll_A_y, scroll_B_y;
	static 	Sprite *sprites[16];
	static	u16 palsrc[64], paldst[64];

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);
	VDP_setHilightShadow(0); 

	vramIndex = 8;

	RSE_turn_screen_to_color(barb_pic_2_front.palette->data[0]);

	/* Draw the foreground */
	VDP_drawImageEx(PLAN_B, &barb_pic_2_back, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += barb_pic_2_back.tileset->numTile;
	VDP_drawImageEx(PLAN_A, &barb_pic_2_front, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += barb_pic_2_front.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	VDP_setVerticalScroll(PLAN_A, 336 - 224);
	VDP_setVerticalScroll(PLAN_B, 336 - 224);

	SYS_enableInts();

	DMA_waitCompletion();

	for (j = 0; j < 64; j++)
	{
		palsrc[j] = barb_pic_2_front.palette->data[0];
		paldst[j] = 0x000;
	}

	for (j = 0; j < 16; j++)
	{
		paldst[j] = barb_pic_2_front.palette->data[j];
		paldst[j + 16] = barb_pic_2_back.palette->data[j];
	}

	// VDP_fadePalTo(PAL0, barb_pic_2_front.palette->data, RSE_FRAMES(8), FALSE);
	// VDP_fadePalTo(PAL1, barb_pic_2_back.palette->data, RSE_FRAMES(8), TRUE);
	VDP_fade(0, 31, palsrc, paldst, 32, TRUE);

	fx_phase = 0;
	while(fx_phase < 256)
	{
		VDP_waitVSync();
		j = easing_table[fx_phase << 2];

		scroll_A_y = (336 - 224) - ((j * (336 - 224)) >> 10);
		scroll_B_y = (336 - 224) - ((j * (336 - 224)) >> 10);

		VDP_setVerticalScroll(PLAN_A, scroll_A_y);
		VDP_setVerticalScroll(PLAN_B, scroll_B_y);

		fx_phase++;
	}

	fx_phase = 0;
	while(fx_phase < 256)
	{
		VDP_waitVSync();
		j = easing_table[fx_phase << 2];

		scroll_A_y = (j * 80) >> 10;
		scroll_B_y = (j * 80) >> 10;

		VDP_setVerticalScroll(PLAN_A, scroll_A_y);
		VDP_setVerticalScroll(PLAN_B, scroll_B_y);

		fx_phase++;
	}

	fx_phase = 0;
	while(fx_phase < 256)
	{
		VDP_waitVSync();
		j = easing_table[fx_phase << 2];

		scroll_A_y = 80 - ((j * 40) >> 10);
		scroll_B_y = 80 - ((j * 40) >> 10);

		VDP_setVerticalScroll(PLAN_A, scroll_A_y);
		VDP_setVerticalScroll(PLAN_B, scroll_B_y);

		fx_phase++;
	}	

	RSE_pause(4 * 60);

	VDP_fadeOut(0, 63, 32, FALSE);

	RSE_turn_screen_to_black();

	RSE_resetScrolling();

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);

	SYS_enableInts();

	vramIndex = TILE_USERINDEX;
}