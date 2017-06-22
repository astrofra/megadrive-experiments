#include "genesis.h"
#include <gfx.h>
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void fireFX(void)
{
	u16 i, vcount;

	SYS_disableInts();
	VDP_setScreenWidth256();
	VDP_setPlanSize(32, 64);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

	VDP_drawImageEx(PLAN_A, &conan_on_fire, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
	vramIndex += checkboard_0.tileset->numTile;
	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	SYS_enableInts();

	vcount = 0;

	while(vcount < 60 * 4)
	{
		VDP_waitVSync();
		if (vcount < 64)
			VDP_setVerticalScroll(PLAN_A, vcount);
		vcount++;
	}

	VDP_fadeOut(1, 63, RSE_FRAMES(16), FALSE);

	RSE_turn_screen_to_black();

	RSE_resetScrolling();

	for(i = 0; i  < VDP_getPlanHeight(); i++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(i);
		RSE_clearTileRowA(i);
	}	

	vramIndex = TILE_USERINDEX;

	SYS_disableInts();
	VDP_setScreenWidth320();
	SYS_enableInts();	
}