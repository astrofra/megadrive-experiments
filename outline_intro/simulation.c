#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "demo_strings.h"
#include "simulation_0.h"
#include "simulation_1.h"
#include "simulation_2.h"
#include "simulation_3.h"
#include "wipe_effect.h"
#include "transition_helper.h"

#define MAX_SIMULATION 6

#define SIM_MODE_RUN			0
#define SIM_CLEAR_SPR			1
#define SIM_MODE_SCROLL			2
#define SIM_MODE_SET_NEW_SIM	3
#define SIM_CLEAR_SCREEN		4
#define SIM_MODE_EXIT			5

#define SIM_0_END_OFFSET		0
#define SIM_1_END_OFFSET		0
#define SIM_2_END_OFFSET		0
#define SIM_3_END_OFFSET		0

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void RSE_physics_simulation(u8 first_sim, u8 last_sim)
{
	u32 vblCount = 0, i, j;
	Sprite sprites[80];
	u8 current_scenario;
	s16 *physics_sim;
	s16 sim_frame_len, sim_node_len;
	u8 sim_mode;
	s8 scroll_speed;
	s16 scroll_x, tscr;

	void inline set_simulation(void)
	{
		switch(current_scenario)
		{
			case 0:
				physics_sim = (s16 *)physics_sim_0;
				sim_frame_len = SIMULATION_0_FRAME_LEN;
				sim_node_len = SIMULATION_0_NODE_LEN + (SIM_0_END_OFFSET * framerate);
				demo_strings = (char **)strings_sim_0;
				RSE_writerRestart();
				break;

			case 1:
				physics_sim = (s16 *)physics_sim_1;
				sim_frame_len = SIMULATION_1_FRAME_LEN;
				sim_node_len = SIMULATION_1_NODE_LEN + (SIM_1_END_OFFSET * framerate);
				demo_strings = (char **)strings_sim_1;
				RSE_writerRestart();
				break;

			case 2:
				physics_sim = (s16 *)physics_sim_2;
				sim_frame_len = SIMULATION_2_FRAME_LEN;
				sim_node_len = SIMULATION_2_NODE_LEN + (SIM_2_END_OFFSET * framerate);
				demo_strings = (char **)strings_sim_2;
				RSE_writerRestart();
				break;

			case 3:
				physics_sim = (s16 *)physics_sim_3;
				sim_frame_len = SIMULATION_3_FRAME_LEN;
				sim_node_len = SIMULATION_3_NODE_LEN + (SIM_3_END_OFFSET * framerate);
				demo_strings = (char **)strings_sim_3;
				RSE_writerRestart();
				break;	
		}
	};

	RSE_turn_screen_to_black();

	current_scenario = first_sim;
	set_simulation();

	SYS_disableInts();
	VDP_setPlanSize(128, 32);
	// VDP_clearPlan(APLAN, 0);
	// VDP_clearPlan(BPLAN, 0);	
	VDP_setHilightShadow(0);
	SYS_enableInts();

	SPR_init(257);
	for(i = 0; i < SIMULATION_0_NODE_LEN;i++)
	{
	    SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));
		SPR_setPosition(&sprites[i], 0, 0);
		SPR_setAlwaysVisible(&sprites[i], TRUE);
	}

    SPR_update(sprites, sim_node_len);

	for(j = 0; j  < VDP_getPlanHeight(); j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(j);
	}

	vramIndex = fontIndex;

	VDP_drawImageEx(BPLAN, &level_bg, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);

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

	for(j = 0; j  < VDP_getPlanHeight(); j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowA(j);
	}

	vramIndex += level_bg.tileset->numTile;

	switch(current_scenario)
	{
		case 0:
		case 1:
			VDP_drawImageEx(APLAN, &level_0, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 48) >> 3, FALSE, TRUE);
			vramIndex += level_0.tileset->numTile;
			VDP_drawImageEx(APLAN, &level_1, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 320 >> 3, (224 - 208) >> 3, FALSE, TRUE);
			break;

		case 2:
		case 3:
			VDP_drawImageEx(APLAN, &level_2, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 88) >> 3, FALSE, TRUE);
			vramIndex += level_2.tileset->numTile;
			VDP_drawImageEx(APLAN, &level_3, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 320 >> 3, (224 - 186) >> 3, FALSE, TRUE);
			break;			
	}

	SYS_disableInts();

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
	scroll_speed = 1;
	scroll_x = 0;

	while (current_scenario <= last_sim && sim_mode != SIM_MODE_EXIT)
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
					if (current_scenario < last_sim)
						sim_mode = SIM_CLEAR_SPR;
					else
						sim_mode = SIM_CLEAR_SCREEN;
				}
				break;

			case SIM_CLEAR_SPR:
				for(i = 0; i < sim_node_len;i++)
				{
					sprites[i].x = 348 + 0x80;
					sprites[i].y = 250 + 0x80;
				}
				SPR_update(sprites, sim_node_len);
				sim_mode = SIM_MODE_SCROLL;
				break;

			case SIM_MODE_SCROLL:
				scroll_x += scroll_speed;

				if (scroll_speed > 0)
				{
					if (scroll_x > 256)
					{
						scroll_x = 256;
						scroll_speed = -1;
						sim_mode = SIM_MODE_SET_NEW_SIM;
					}
				}
				else
				{
					if (scroll_x < 0)
					{
						scroll_x = 0;
						scroll_speed = 1;
						sim_mode = SIM_MODE_SET_NEW_SIM;
					}					
				}
				
				tscr = scroll_x * 4;
				if (tscr >= EASING_TABLE_LEN)
					tscr = EASING_TABLE_LEN - 1;
				else
					if (tscr < 0)
						tscr = 0;
				tscr = (easing_table[tscr] * -320) >> 10;
				VDP_setHorizontalScroll(PLAN_A, tscr);
				VDP_setHorizontalScroll(PLAN_B, tscr >> 2);
				RSE_writerSetXOffset((-tscr) >> 3);
				break;

			case SIM_MODE_SET_NEW_SIM:
				vblCount = 0;
				current_scenario++;
				current_scenario %= MAX_SIMULATION;
				set_simulation();
				sim_mode = SIM_MODE_RUN;
				break;

			case SIM_CLEAR_SCREEN:
				VDP_fadeOut(1, 63, 32, TRUE);
				RSE_pause(RSE_FRAMES(32));
				// transition_fx(0, vramIndex);
				sim_mode = SIM_MODE_EXIT;
				break;

			case SIM_MODE_EXIT:
				break;
		}

	}

	SPR_end();
	RSE_resetScrolling();
	RSE_writerSetXOffset(0);

	RSE_turn_screen_to_black();

	for(i = 0; i  < 224 >> 3; i++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(i);
		RSE_clearTileRowA(i);
	}
}
