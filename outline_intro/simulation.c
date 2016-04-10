#include "genesis.h"
#include <gfx.h>
#include "simulation.h"
#include "transition_helper.h"

void RSE_physics_simulation(void)
{
	u32 vblCount = 0, i, j;
	u16 vramIndex = TILE_USERINDEX;
	Sprite sprites[SIMULATION_NODE_LEN];

	RSE_turn_screen_to_black();

	SYS_disableInts();
	MEM_init();
	VDP_setPlanSize(32, 32);
	VDP_setScreenWidth320();
	VDP_clearPlan(APLAN, 1);
	VDP_clearPlan(BPLAN, 1);	
	SPR_init(257);
	for(i = 0; i < SIMULATION_NODE_LEN;i++)
	{
	    SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
		SPR_setPosition(&sprites[i], 0, 0);
	}
    SPR_update(sprites, SIMULATION_NODE_LEN);
	VDP_setHilightShadow(0); 
	SYS_enableInts();

	VDP_fadePalTo(PAL2, ball_metal.palette->data, 64, TRUE);

	while (TRUE)
	{
		VDP_waitVSync();
		// BMP_showFPS(1);
	
		j = vblCount * SIMULATION_NODE_LEN * 3;
		for(i = 0; i < SIMULATION_NODE_LEN;i++)
		{
			sprites[i].x = physics_sim[j++];
			sprites[i].y = physics_sim[j++];
			SPR_setFrame(&sprites[i], physics_sim[j++]);
		}

		SPR_update(sprites, SIMULATION_NODE_LEN);

		vblCount++;
		if (vblCount >= SIMULATION_FRAME_LEN)
			vblCount = 0;
	}
}