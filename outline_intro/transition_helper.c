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