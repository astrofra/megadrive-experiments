#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "demo_strings.h"
#include "simulation_0.h"
#include "simulation_1.h"
#include "simulation_2.h"
#include "simulation_3.h"
#include "simulation_4.h"
#include "simulation_5.h"
#include "transition_helper.h"

#define MAX_SIMULATION 6;

extern u16 vramIndex;
extern u16 fontIndex;

void RSE_physics_simulation(u8 first_sim, u8 last_sim)
{
	u32 vblCount = 0, i, j;
	// u16 vramIndex = TILE_USERINDEX;
	Sprite sprites[80];
	u8 current_scenario;
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

			case 2:
				physics_sim = (s16 *)physics_sim_2;
				sim_frame_len = SIMULATION_2_FRAME_LEN;
				sim_node_len = SIMULATION_2_NODE_LEN;
				demo_strings = (char **)strings_sim_2;
				RSE_writerRestart();
				break;

			case 3:
				physics_sim = (s16 *)physics_sim_3;
				sim_frame_len = SIMULATION_3_FRAME_LEN;
				sim_node_len = SIMULATION_3_NODE_LEN;
				demo_strings = (char **)strings_sim_3;
				RSE_writerRestart();
				break;	

			case 4:
				physics_sim = (s16 *)physics_sim_4;
				sim_frame_len = SIMULATION_4_FRAME_LEN;
				sim_node_len = SIMULATION_4_NODE_LEN;
				demo_strings = (char **)strings_sim_4;
				RSE_writerRestart();
				break;	

			case 5:
				physics_sim = (s16 *)physics_sim_4;
				sim_frame_len = SIMULATION_4_FRAME_LEN;
				sim_node_len = SIMULATION_4_NODE_LEN;
				demo_strings = (char **)strings_sim_5;
				RSE_writerRestart();
				break;		
		}
	};

	RSE_turn_screen_to_black();

	current_scenario = first_sim;
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

	while (current_scenario <= last_sim)
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

	SPR_end();
}
