#include "genesis.h"
#include <gfx.h>
#include "simulation_0.h"
#include "simulation_1.h"
#include "transition_helper.h"

#define MAX_SIMULATION 2;

void RSE_physics_simulation(void)
{
	u32 vblCount = 0, i, j;
	u16 vramIndex = TILE_USERINDEX;
	Sprite sprites[80];
	u8 current_scenario = 0;
	s16 *physics_sim = NULL;
	s16 sim_frame_len, sim_node_len;

	void set_simulation(void)
	{
		switch(current_scenario)
		{
			case 0:
				physics_sim = physics_sim_0;
				sim_frame_len = SIMULATION_0_FRAME_LEN;
				sim_node_len = SIMULATION_0_NODE_LEN;
				break;

			case 1:
				physics_sim = physics_sim_1;
				sim_frame_len = SIMULATION_1_FRAME_LEN;
				sim_node_len = SIMULATION_1_NODE_LEN;
				break;
		}
	}

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
		// SPR_setFrame(&sprites[i], i%12);
	}

    SPR_update(sprites, sim_node_len);
	VDP_setHilightShadow(0);

	vramIndex = TILE_USERINDEX;

	VDP_drawImageEx(APLAN, &level_0, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += level_0.tileset->numTile;

	VDP_setPalette(PAL0, level_0.palette->data);
	VDP_setPalette(PAL2, ball_metal.palette->data);

	SYS_enableInts();

	set_simulation();

	while (TRUE)
	{
		VDP_waitVSync();
	
		j = vblCount * sim_node_len * 3;
		for(i = 0; i < sim_node_len;i++)
		{
			sprites[i].x = physics_sim[j++];
			sprites[i].y = physics_sim[j++];
			SPR_setFrame(&sprites[i], physics_sim[j++]);
		}

		SPR_update(sprites, sim_node_len);

		vblCount++;
		if (vblCount >= sim_frame_len)
		{
			vblCount = 0;
			current_scenario++;
			current_scenario %= MAX_SIMULATION;
			set_simulation();
		}
	}
}