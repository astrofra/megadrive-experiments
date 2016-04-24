#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "demo_strings.h"
#include "simulation_0.h"
#include "simulation_1.h"
#include "transition_helper.h"

#define MAX_SIMULATION 2;

extern u16 vramIndex;
extern u16 fontIndex;

void RSE_physics_simulation(void)
{
	u32 vblCount = 0, i, j;
	// u16 vramIndex = TILE_USERINDEX;
	Sprite sprites[80];
	u8 current_scenario = 0;
	s16 *physics_sim;
	s16 sim_frame_len, sim_node_len;

	void inline set_simulation(void)
	{
		switch(current_scenario)
		{
			case 0:
				physics_sim = (s16 *)physics_sim_0;
				sim_frame_len = SIMULATION_0_FRAME_LEN;
				sim_node_len = SIMULATION_0_NODE_LEN;
				demo_strings = (char **)strings_sim_0;
				RSE_writerRestart();
				break;

			case 1:
				physics_sim = (s16 *)physics_sim_1;
				sim_frame_len = SIMULATION_1_FRAME_LEN;
				sim_node_len = SIMULATION_1_NODE_LEN;
				demo_strings = (char **)strings_sim_1;
				RSE_writerRestart();
				break;
		}
	};

	RSE_turn_screen_to_black();

	set_simulation();

	VDP_waitVSync();
	SYS_disableInts();
	// VDP_setPlanSize(64, 32);
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

	vramIndex = fontIndex;

	VDP_drawImageEx(BPLAN, &level_0, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	vramIndex += level_0.tileset->numTile;

	SYS_enableInts();

	VDP_setPalette(PAL1, level_0.palette->data);
	VDP_setPalette(PAL2, ball_metal.palette->data);

	/*	
		Prepare text writer
	*/
	current_char_y = 2;
	RSE_writerSetOption(WRT_OPT_WRITE_TO_PLAN_A);
	VDP_setPalette(PAL0, oddball_fonts.palette->data);

	while (TRUE)
	{
		VDP_waitVSync();

		RSE_writerUpdateLine();
	
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
