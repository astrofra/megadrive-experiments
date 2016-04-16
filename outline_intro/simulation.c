#include "genesis.h"
#include <gfx.h>
#include "simulation_0.h"
#include "transition_helper.h"

void RSE_physics_simulation(void)
{
	u32 vblCount = 0, i, j;
	u16 vramIndex = TILE_USERINDEX;
	Sprite sprites[80];

	RSE_turn_screen_to_black();

	SYS_disableInts();
	MEM_init();
	VDP_setPlanSize(64, 32);
	VDP_setScreenWidth320();
	VDP_clearPlan(APLAN, 1);
	VDP_clearPlan(BPLAN, 1);	
	SPR_init(257);
	for(i = 0; i < SIMULATION_0_NODE_LEN;i++)
	{
	    SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
		SPR_setPosition(&sprites[i], 0, 0);
	}

    SPR_update(sprites, SIMULATION_0_NODE_LEN);
	VDP_setHilightShadow(0);

	vramIndex = TILE_USERINDEX;

	VDP_drawImageEx(APLAN, &level_0, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += level_0.tileset->numTile;

	VDP_setPalette(PAL0, level_0.palette->data);
	VDP_setPalette(PAL2, ball_metal.palette->data);

	SYS_enableInts();

	// VDP_fadePalTo(PAL2, ball_metal.palette->data, 64, TRUE);

	while (TRUE)
	{
		VDP_waitVSync();
		// BMP_showFPS(1);
	
		j = vblCount * SIMULATION_0_NODE_LEN * 3;
		for(i = 0; i < SIMULATION_0_NODE_LEN;i++)
		{
			sprites[i].x = physics_sim_0[j++];
			sprites[i].y = physics_sim_0[j++];
			SPR_setFrame(&sprites[i], physics_sim_0[j++]);
		}

		SPR_update(sprites, SIMULATION_0_NODE_LEN);

		vblCount++;
		if (vblCount >= SIMULATION_0_FRAME_LEN)
			vblCount = 0;
	}
}