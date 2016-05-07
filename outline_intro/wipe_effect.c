#include "genesis.h"
#include <gfx.h>
#include "wipe_effect.h"

// transition_pattern_0

#define WIPE_TILE_WIDTH	13

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

extern u16 current_plan;
extern u8 current_pal;

void transition_fx(u8 frames, u16 vramindex_start)
{
	s16 i, j, k, l;
	u16 sw, sh;

	current_plan = VDP_PLAN_A;
	current_pal = PAL0;

	SYS_disableInts();

	vramIndex = vramindex_start;
	// u16  VDP_getPlanWidth();
	// u16  VDP_getPlanHeight();

	VDP_drawImageEx(APLAN, &transition_pattern_0, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
    // vramIndex += transition_pattern_0.tileset->numTile;

    SYS_enableInts();

    sw = VDP_getPlanWidth();
    sh = VDP_getPlanHeight();

    for(i = 0; i < sw + WIPE_TILE_WIDTH; i++)
    {
		VDP_waitVSync();

    	for(j = 0; j < sh; j++)
    		for(k = 0; k < WIPE_TILE_WIDTH; k++)
	    	{
	    		l = i - k;
	    		if (l < 0)
	    			l = 0;
	    		else
	    		if (l > sw)
	    			l = sw - 1;

	    		l -= j;
	    		if (l < 0)
	    			break;
	    		else
	    		if (l > sw)
	    			break;

	    		VDP_setTileMapXY(current_plan, vramIndex + k, l, j); //TILE_ATTR_FULL(current_pal, FALSE, FALSE, FALSE, j));
	    	}
	}
}