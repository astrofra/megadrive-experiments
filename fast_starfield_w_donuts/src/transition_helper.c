#include "genesis.h"

const u16 palette_white[16] =
{
    0x0000,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,

    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF,
    0x0FFF
};


const s16 tile_sc_table[] =  { 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void RSE_turn_screen_to_white(void)
{
	/* Turn whole palette to white */
	u16 i;
	for(i = 0; i < 63; i++)
	{
		VDP_setPaletteColor(i, 0xFFF);
	}

}

void RSE_turn_screen_to_black(void)
{
	/* Turn whole palette to black */
	u16 i;
	for(i = 0; i < 63; i++)
	{
		VDP_setPaletteColor(i, 0x000);
	}

}

void RSE_turn_screen_to_color(u16 col)
{
	/* Turn whole palette to the specified color */
	u16 i;
	
	for(i = 0; i < 63; i++)
		VDP_setPaletteColor(i, col);

}

void RSE_pause(u16 frames)
{
	while(--frames > 0)
		VDP_waitVSync();
}

void RSE_clearTileRowB(u16 row)
{
	u16 col, max_col;
	max_col = VDP_getPlanWidth(); 
	for(col = 0; col < max_col; col++)
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_SYSTEMINDEX), col, row);
}

void RSE_clearTileRowA(u16 row)
{
	u16 col, max_col;
	max_col = VDP_getPlanWidth(); 
	for(col = 0; col < max_col; col++)
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_SYSTEMINDEX), col, row);
}

void RSE_clearTileRowAPrioTrue(u16 row)
{
	u16 col, max_col;
	max_col = VDP_getPlanWidth(); 
	for(col = 0; col < max_col; col++)
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, TRUE, 0, 0, TILE_SYSTEMINDEX), col, row);
}

void RSE_resetScrolling(void)
{
	SYS_disableInts();
	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);
	VDP_setHorizontalScrollTile(PLAN_A, 0, tile_sc_table, 32, TRUE);
	VDP_setVerticalScrollTile(PLAN_A, 0, tile_sc_table, 32, TRUE);	
	VDP_setHorizontalScrollTile(PLAN_B, 0, tile_sc_table, 32, TRUE);
	VDP_setVerticalScrollTile(PLAN_B, 0, tile_sc_table, 32, TRUE);
	SYS_enableInts();

	VDP_waitVSync();

	SYS_disableInts();
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setVerticalScroll(PLAN_B, 0);
	VDP_setVerticalScroll(PLAN_A, 0);
	VDP_setHorizontalScroll(PLAN_B, 0);
	VDP_setHorizontalScroll(PLAN_A, 0);	
	SYS_enableInts();	
}

void RSE_clearAll(void)
{
	RSE_resetScrolling();

	SPR_end();
	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);	

	SYS_disableInts();
	SYS_enableInts();
}