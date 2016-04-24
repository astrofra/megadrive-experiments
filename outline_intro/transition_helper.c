#include "genesis.h"

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
	/* Turn whole palette to white */
	u16 i;
	for(i = 0; i < 63; i++)
	{
		VDP_setPaletteColor(i, 0x000);
	}

}

void RSE_pause(u16 frames)
{
	while(--frames > 0)
		VDP_waitVSync();
}

void RSE_clearTileRow(u16 row)
{
	u16 col, max_col;
	max_col = VDP_getPlanWidth(); 
	for(col = 0; col < max_col; col++)
		VDP_setTileMapXY(BPLAN, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_SYSTEMINDEX), col, row);
}