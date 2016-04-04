#include "genesis.h"
#include <gfx.h>

void RSE_LogoScreen(void);

int main()
{
	RSE_LogoScreen();
}

void RSE_turn_screen_to_white(void)
{
	/* Turn whole palette to white */
	u16 i;
	for(i = 0; i < 63; i++)
	{
		VDP_setPaletteColor(i, 0xFFF);
	}

}

void RSE_pause(u16 frames)
{
	while(--frames > 0)
		VDP_waitVSync();
}

void RSE_LogoScreen(void)
{
	SYS_disableInts();
	RSE_turn_screen_to_white();
	VDP_setScreenWidth320();
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);	
	VDP_drawImageEx(APLAN, &logo_rse_3d, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 50), 0, ((240 - 80) >> 4) - 1, FALSE, TRUE);
	SYS_enableInts();

	RSE_pause(15);

	/* Fade to the logo's palette */
	VDP_fadePalTo(PAL1, logo_rse_3d.palette->data, 32, TRUE);

	/* Complimentary fade for the #0 color */
	{
		u16 i,j;
		for(i = 0; i < 15; i++)
		{
			VDP_waitVSync();
			j = 15 - i;
			VDP_setPaletteColor(0, j | (j << 4) | (j << 8));
		}
	}

	while (TRUE)
		VDP_waitVSync();	
}
