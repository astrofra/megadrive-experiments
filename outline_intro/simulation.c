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

#define MAX_SIMULATION 6

#define SIM_MODE_RUN			0
#define SIM_MODE_SCROLL			1
#define SIM_MODE_SET_NEW_SIM	2

extern u16 vramIndex;
extern u16 fontIndex;

void RSE_physics_simulation(u8 first_sim, u8 last_sim)
{
	u32 vblCount = 0, i, j;
	Sprite sprites[80];
	u8 current_scenario;
	s16 *physics_sim;
	s16 sim_frame_len, sim_node_len;
	u8 sim_mode;
	s8 scroll_speed;
	s16 scroll_x;

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
	VDP_setPlanSize(128, 32);
	VDP_clearPlan(APLAN, 1);
	VDP_clearPlan(BPLAN, 1);	
	SPR_init(257);
	for(i = 0; i < SIMULATION_0_NODE_LEN;i++)
	{
	    SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));
		SPR_setPosition(&sprites[i], 0, 0);
	}

    SPR_update(sprites, sim_node_len);
	VDP_setHilightShadow(0);

	vramIndex = fontIndex;

	VDP_drawImageEx(BPLAN, &level_bg, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);

	SYS_enableInts();

	for(i = 2; i < 640 >> 3; i ++)
	{
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), i, 0);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 1), i, 1);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 2), i, 2);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 3), i, 3);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 4), i, 4);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 5), i, 5);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 6), i, 6);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 7), i, 7);
		for(j = 8; j < 25; j += 2)
			VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 8), i, j);
		for(j = 9; j < 24; j += 2)
			VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 9), i, j);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 10), i, ((224 - 8) >> 3) - 2);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 11), i, ((224 - 8) >> 3) - 1);
		VDP_setTileMapXY(VDP_PLAN_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex + 12), i, ((224 - 8) >> 3));
	}

	vramIndex += level_bg.tileset->numTile;

	SYS_disableInts();

	VDP_drawImageEx(APLAN, &level_0, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 48) >> 3, FALSE, TRUE);

	VDP_setPalette(PAL0, level_0.palette->data);
	VDP_setPalette(PAL1, level_bg.palette->data);
	VDP_setPalette(PAL2, ball_metal.palette->data);

	SYS_enableInts();

	/*	
		Prepare text writer
	*/
	current_char_y = 2;
	RSE_writerSetOption(WRT_OPT_WRITE_TO_PLAN_A);
	// VDP_setPalette(PAL0, oddball_fonts.palette->data);

	sim_mode = SIM_MODE_RUN;
	scroll_speed = -1;
	scroll_x = 0;	

	while (current_scenario <= last_sim)
	{
		VDP_waitVSync();

		switch(sim_mode)
		{
			case SIM_MODE_RUN:
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
					sim_mode = SIM_MODE_SCROLL;
				}
				break;

			case SIM_MODE_SCROLL:
				scroll_x += (scroll_speed << 2);
				if (scroll_speed > 0)
				{
					if (scroll_x > 0)
					{
						scroll_x = 0;
						scroll_speed = -1;
						sim_mode = SIM_MODE_SET_NEW_SIM;
					}
				}
				else
				{
					if (scroll_x < -320)
					{
						scroll_x = -320;
						scroll_speed = 1;
						sim_mode = SIM_MODE_SET_NEW_SIM;
					}					
				}
				VDP_setHorizontalScroll(PLAN_A, scroll_x);
				VDP_setHorizontalScroll(PLAN_B, scroll_x >> 2);
				break;

			case SIM_MODE_SET_NEW_SIM:
					current_scenario++;
					current_scenario %= MAX_SIMULATION;
					set_simulation();
					sim_mode = SIM_MODE_RUN;
					break;
		}

	}

	SPR_end();
}
