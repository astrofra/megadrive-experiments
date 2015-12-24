#include <genesis.h>
#include <gfx.h>
#include "resources.h"

void RSE_guruMeditation(void)
{
	u16 vramIndex = TILE_USERINDEX;
	u16 frame_flicking_timer = 0;
	u16 frame_is_on = TRUE;

	SYS_disableInts();
	VDP_setEnable(FALSE);

	VDP_setPlanSize(64, 32);

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	/* Load the fond tiles */
	VDP_setPalette(PAL0, guru_med.palette->data);
	VDP_setPalette(PAL1, guru_med.palette->data);
	VDP_drawImageEx(APLAN, &guru_med, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += guru_med.tileset->numTile;
	VDP_drawImageEx(BPLAN, &guru_med_frame, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);

	VDP_setEnable(TRUE);
	SYS_enableInts();

	while(TRUE)
	{
		VDP_waitVSync();
		frame_flicking_timer++;

		if (frame_flicking_timer > 50)
		{
			frame_is_on = !frame_is_on;
			frame_flicking_timer = 0;
			if (frame_is_on)
				VDP_setPalette(PAL1, guru_med.palette->data);
			else
				VDP_setPalette(PAL1, (u16*)palette_black);
		}		
	}
};
