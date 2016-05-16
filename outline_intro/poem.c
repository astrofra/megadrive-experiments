#include "genesis.h"
#include <gfx.h>
#include "transition_helper.h"

extern u16 vramIndex;
extern u8 framerate;

/*
	Poem by Metoikos
*/

void RSE_poem(void)
{
	s16 i,j,k;
	RSE_turn_screen_to_black();
	RSE_resetScrolling();
	VDP_waitVSync();

	SYS_disableInts();
	VDP_setPlanSize(64, 32);
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	VDP_setHilightShadow(0);	

	vramIndex = TILE_USERINDEX;
	VDP_drawImageEx(APLAN, &poem, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 144) >> 4, FALSE, FALSE);
	vramIndex += poem.tileset->numTile;

	// VDP_setPalette(PAL0, poem.palette->data);
	SYS_enableInts();

	VDP_fadePalTo(PAL0, poem.palette->data, 32, TRUE);

	/*
		Scroll up
	*/
	k = RSE_FRAMES(40);
	for(i = 0; i < k; i++)
	{
		VDP_waitVSync();
		j = easing_table[i * 1024 / k];
		j = (j * k) >> 11;
		VDP_setVerticalScroll(PLAN_A, j - 10);
	}

	RSE_pause(RSE_FRAMES(12 * 60));
	VDP_fadeOut(1, 63, 32, FALSE);

	SPR_end();	
	RSE_resetScrolling();

	RSE_turn_screen_to_black();
	vramIndex = TILE_USERINDEX;
}
