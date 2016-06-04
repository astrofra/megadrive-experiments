#include <genesis.h>
#include <gfx.h>
#include "transition_helper.h"

#define	TABLE_LEN (224 >> 3)

static void fastStarFieldFX();

s16 scroll_PLAN_B[TABLE_LEN];
u8 scroll_speed[TABLE_LEN];

int main(){
	fastStarFieldFX();
	return 0;
}

static void fastStarFieldFX()
{
	u16 vramIndex = TILE_USERINDEX;
	s16 i, ns, s;

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(32, 32);

	/* Draw the foreground */
	// RSE_turn_screen_to_black();
	VDP_drawImageEx(BPLAN, &starfield, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, TRUE, FALSE);
	vramIndex += starfield.tileset->numTile; 	

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

	SYS_enableInts();

	s = 1;
	for(i = 0; i < TABLE_LEN; i++)
	{
		scroll_PLAN_B[i] = 0;
		do
		{
			ns = -((random() % 3) + 1);
		}
		while (ns == s);
		scroll_speed[i] = ns;
		s = ns;
	}

	while (TRUE)
	{
		VDP_waitVSync();
		BMP_showFPS(1);
		VDP_setHorizontalScrollTile(PLAN_B, 2, scroll_PLAN_B, TABLE_LEN, TRUE);
		for(i = 0; i < TABLE_LEN; i++)
			scroll_PLAN_B[i] = (scroll_PLAN_B[i] + scroll_speed[i]) & 0xFF;

	}
}
