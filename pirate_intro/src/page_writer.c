#include "genesis.h"
#include <gfx.h>
#include "page_writer.h"
#include "transition_helper.h"
#include "string_parser.h"

extern u16 vramIndex;
extern u8 framerate;
char **current_strings;

/* 
	Global pgwriter data 
*/
u16 pgwriter_state = 0;
u16 pgwriter_switch;
u16 pg_current_string_idx;
u16 pg_current_string_len;
u16 pg_current_char_idx;
u16 pg_x_offset;
u16 pg_current_char_x;
u16 pg_current_char_y = 2;
u16 pg_initial_char_y;
VDPPlan pg_current_plan;
u8 pgwriter_is_done;
u16 pgwriter_timer;
u16 pgwriter_display_duration = 50;
u16 pgwriter_options = (WRT_OPT_AUTO_NEXT_STRING | /*WRT_OPT_AUTO_RESTART |*/ WRT_OPT_WRITE_TO_PLAN_A);

u16 RSE_pgwriterSetup(void)
{
	u16 j;
	pg_current_plan = PLAN_A;

	SYS_disableInts();
	VDP_drawImageEx(PLAN_A, &sim1_font, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	for(j = 0; j  < 4; j++)
		RSE_clearTileRowA(j);
	SYS_enableInts();

	vramIndex += sim1_font.tileset->numTile;

	pgwriter_switch = FALSE;
	pgwriter_is_done = FALSE;
	pg_x_offset = 0;
	pgwriter_display_duration = RSE_FRAMES(50);

	return vramIndex;
}

void RSE_pgwriterSetDisplayDuration(u8 duration)
{
	pgwriter_display_duration = duration;
}

void RSE_pgwriterSetInitialY(u16 initial_y)
{	pg_initial_char_y = initial_y;	}

void RSE_pgwriterSetXOffset(u16 offset)
{ 
	pg_x_offset = offset;
}

void RSE_pgwriterRestart(void)
{
	pgwriter_switch = FALSE;
	pg_current_string_idx = 0;
	pg_current_char_idx = 0;
	pgwriter_state = WRT_CENTER_CUR_LINE;
	pgwriter_is_done = FALSE;
}

u16 inline RSE_pgwriterSetOption(u16 option)
{
	pgwriter_options |= option;
	return pgwriter_options;
}

u16 inline RSE_pgwriterUnsetOption(u16 option)
{
	pgwriter_options &= ~option;
	return pgwriter_options;
}

u16 RSE_pgwriterDrawString(char *str)
{
	char c;
	u16 i;

	c = str[pg_current_char_idx];

	if (c == 0)
		return FALSE;

	if (c != ' ')
	{
		i = charToTileIndex(c);
		if (i != 0xFF)
			VDP_setTileMapXY(pg_current_plan, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, TILE_USERINDEX + i), pg_current_char_x + pg_x_offset, pg_current_char_y);
			// VDP_setTileMapXY(pg_current_plan, TILE_USERINDEX + i + (FONT_LINE_OFFSET * fade), pg_current_char_x + fade + pg_x_offset, TILE_ATTR_FULL(pg_current_pal, FALSE, FALSE, FALSE, pg_current_char_y));
	}
	// else
	// 	VDP_setTileMapXY(pg_current_plan, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, TILE_SYSTEMINDEX), pg_current_char_x, pg_current_char_y);	

	pg_current_char_x++;
	pg_current_char_idx++;

	return TRUE;
}

void inline RSE_pgwriterUpdateLine(void)
{
	if (WRT_HAS_OPTION(WRT_OPT_HALF_SPEED))
		if (pgwriter_state == WRT_WRITE_CUR_LINE)
		{
			pgwriter_switch = ~pgwriter_switch;
			if (pgwriter_switch)
				return;
		}

	if (WRT_HAS_OPTION(WRT_OPT_WRITE_TO_PLAN_A))
	{
		pg_current_plan = PLAN_A;
	}
	else
	{
		pg_current_plan = PLAN_B;
	}

	switch(pgwriter_state)
	{
		case WRT_CENTER_CUR_LINE:
			pg_current_string_len = computeStringLen((char *)current_strings[pg_current_string_idx]);
			pg_current_char_x = ((320 / 8) - pg_current_string_len) >> 1;
			pgwriter_state = WRT_WRITE_CUR_LINE;
			break;

		case WRT_WRITE_CUR_LINE:
			if (!RSE_pgwriterDrawString((char *)current_strings[pg_current_string_idx]))
			{
				pgwriter_timer = 0;
				pgwriter_state = WRT_WAIT;
			}
			break;

		case WRT_WAIT:
			if (pgwriter_timer++ > pgwriter_display_duration)
			{
				pgwriter_state = WRT_CLEAR_LINE;
				pg_current_char_x = 0;
			}
			break;

		case WRT_CLEAR_LINE:
			VDP_setTileMapXY(pg_current_plan, 0, pg_current_char_x + pg_x_offset, pg_current_char_y);
			pg_current_char_x++;
			if (pg_current_char_x > 320 / 8)
			{
				pg_current_char_x = 0;
				pg_current_char_idx = 0;
				pg_current_string_idx++;
				if (current_strings[pg_current_string_idx][0] == '\0')
				{
					pgwriter_is_done = TRUE;
					if (WRT_HAS_OPTION(WRT_OPT_AUTO_RESTART))
						pg_current_string_idx = 0;
					else
					{
						pgwriter_state = WRT_IDLE_MODE;
						return;
					}
				}
				else
				if (current_strings[pg_current_string_idx][0] == '\1')
					pg_current_char_y = pg_initial_char_y;


				pgwriter_state = WRT_CENTER_CUR_LINE;
			}
			break;

		case WRT_IDLE_MODE:
			return;
	}
}

u8 inline RSE_pgwriterIsDone(void)
{	return pgwriter_is_done; }

void inline RSE_pgwriterUpdateMultiLine(void)
{
	if (WRT_HAS_OPTION(WRT_OPT_HALF_SPEED))
		if (pgwriter_state == WRT_WRITE_CUR_LINE)
		{
			pgwriter_switch = ~pgwriter_switch;
			if (pgwriter_switch)
				return;
		}

	if (WRT_HAS_OPTION(WRT_OPT_WRITE_TO_PLAN_A))
	{
		pg_current_plan = PLAN_A;
	}
	else
	{
		pg_current_plan = PLAN_B;
	}

	switch(pgwriter_state)
	{
		case WRT_CENTER_CUR_LINE:
			pg_current_string_len = computeStringLen((char *)current_strings[pg_current_string_idx]);
			pg_current_char_x = ((320 / 8) - pg_current_string_len) >> 1;
			pgwriter_state = WRT_WRITE_CUR_LINE;
			break;

		case WRT_WRITE_CUR_LINE:
			if (!RSE_pgwriterDrawString((char *)current_strings[pg_current_string_idx]))
			{
				pgwriter_timer = 0;
				pgwriter_state = WRT_WAIT;
			}
			break;

		case WRT_WAIT:
			if (pgwriter_timer++ > pgwriter_display_duration)
			{
				pg_current_char_x = 0;
				pg_current_char_y++;
				pg_current_char_idx = 0;
				pg_current_string_idx++;
				if (current_strings[pg_current_string_idx][0] == '\0')
				{
					pgwriter_is_done = TRUE;
					if (WRT_HAS_OPTION(WRT_OPT_AUTO_RESTART))
						pg_current_string_idx = 0;
					else
					{
						pgwriter_state = WRT_IDLE_MODE;
						return;
					}
				}				
				pgwriter_state = WRT_CENTER_CUR_LINE;
			}
			break;

		case WRT_IDLE_MODE:
			return;
	}
}
