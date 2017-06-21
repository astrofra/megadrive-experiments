#include <genesis.h>
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

static	u16 palsrc[64], paldst[64];

void displayBarbTitleFX(void)
{
	u16 fx_phase, j, scroll_A_y, scroll_B_y, tmp_vramIndex;
	static 	Sprite *sprites[16];

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);
	VDP_setHilightShadow(0);

	vramIndex = TILE_USERINDEX;

	/* Draw the foreground */
	VDP_drawImageEx(PLAN_A, &barb_pic_front, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += barb_pic_front.tileset->numTile;

	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	/* Draw the background */
	VDP_drawImageEx(PLAN_B, &barb_pic_back_0, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += barb_pic_back_0.tileset->numTile;

	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();	

	VDP_drawImageEx(PLAN_B, &barb_pic_back_1, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 64 >> 3, FALSE, TRUE);
	vramIndex += barb_pic_back_1.tileset->numTile;

	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &barb_pic_back_2, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 128 >> 3, FALSE, TRUE);
	vramIndex += barb_pic_back_2.tileset->numTile;

	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &barb_pic_back_3, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, (128 + 80) >> 3, FALSE, TRUE);
	vramIndex += barb_pic_back_3.tileset->numTile;

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	VDP_setVerticalScroll(PLAN_A, 280);
	VDP_setVerticalScroll(PLAN_B, 128);

	SYS_enableInts();

	DMA_waitCompletion();

	/* Title sprite */
	Object title_object;
	u16 tileIndexes;
	SPR_init(1, 0, 0);

    TileSet* tileset = masiaka_title.animations[0]->frames[0]->tileset;
    VDP_loadTileSet(tileset, vramIndex, TRUE);
    tileIndexes = vramIndex;	

	sprites[0] = SPR_addSprite(&masiaka_title, (320 - 240) >> 1, 256, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	SPR_setAutoTileUpload(sprites[0], FALSE);
	sprites[0]->data = (u32) &title_object;
	SPR_setVRAMTileIndex(sprites[0], tileIndexes);
	SPR_update(sprites, 1);

	VDP_fadePalTo(PAL1, palette_white_bg, RSE_FRAMES(8), TRUE);
	RSE_pause(8);
	VDP_fadePalTo(PAL1, barb_pic_back_0.palette->data, RSE_FRAMES(16), TRUE);
	RSE_pause(16);

	VDP_fadePalTo(PAL0, barb_pic_front.palette->data, RSE_FRAMES(64), TRUE);
	// RSE_pause(16);

	fx_phase = 0;
	while(fx_phase < 256)
	{
		VDP_waitVSync();
		j = easing_table[fx_phase << 2];

		scroll_A_y = 280 - ((j * 280) / 1024);
		scroll_B_y = 128 - ((j * 128) / 1024);

		VDP_setVerticalScroll(PLAN_A, scroll_A_y);
		VDP_setVerticalScroll(PLAN_B, scroll_B_y);

		if (fx_phase == 256 - 64 - 16)
			VDP_fadePalTo(PAL0, palette_white_bg, RSE_FRAMES(8), TRUE);
		if (fx_phase == 256 - 56 - 16)
			VDP_fadePalTo(PAL0, barb_pic_front.palette->data, RSE_FRAMES(8), TRUE);

		if (fx_phase == 256 - 64)
		{

		}
		else
		if (fx_phase >= 256 - 64)
		{
			if (fx_phase == 256 - 64)
				VDP_fadePalTo(PAL2, palette_white_bg, RSE_FRAMES(8), TRUE);

			if (fx_phase == 256 - (64 - 12))
				VDP_fadePalTo(PAL2, masiaka_title.palette->data, RSE_FRAMES(32), TRUE);

			j = fx_phase - (256 - 64);

			SPR_setPosition(sprites[0], (320 - 240) >> 1, ((224 - 48) >> 1) - ((easing_table[j << 4] >> 5) - 16));
			SPR_update(sprites, 1);
		}		

		fx_phase++;
		// BMP_showFPS(0);
	}

	RSE_pause(60);

	for(j = 0; j < 64; j++)
	{
		palsrc[j] = 0x000;
		paldst[j] = 0x000;
	}

	for(j = 0; j < 16; j++)
	{
		palsrc[j] = barb_pic_front.palette->data[j]; 
		palsrc[j + (16 * PAL1)] = barb_pic_back_0.palette->data[j]; 
		palsrc[j + (16 * PAL2)] = masiaka_title.palette->data[j]; 

		paldst[j + (16 * PAL2)] = masiaka_title.palette->data[j]; 
	}

	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);

	VDP_fade(0, 63, palsrc, paldst, 32, TRUE);

	for(fx_phase = 0; fx_phase < 64; fx_phase++)
	{
		if (fx_phase == 42)
			VDP_fadePalTo(PAL2, palette_white_bg, RSE_FRAMES(4), TRUE);
		if (fx_phase == 48)
			VDP_fadePalTo(PAL2, masiaka_title.palette->data, RSE_FRAMES(16), TRUE);
	}

	RSE_pause(16);

	VDP_fadeOut(1, 63, 32, TRUE);
	RSE_pause(32);

	RSE_turn_screen_to_black();

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	SPR_end();
	RSE_resetScrolling();

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);

	SYS_enableInts();

	vramIndex = TILE_USERINDEX;
}