#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u8 framerate;
extern char **demo_strings;

/* 
	Global writer data 
*/
u16 writer_state = 0;
u16 writer_switch;
u16 current_string_idx;
u16 current_string_len;
u16 current_char_idx;
u16 x_offset;
u16 current_char_x;
u16 current_char_y = 2;
u16 initial_char_y;
u16 current_plan;
u8 current_pal;
u8 writer_is_done;
u16 writer_timer;
u16 writer_display_duration = 50;
u16 writer_options = (WRT_OPT_AUTO_NEXT_STRING | WRT_OPT_AUTO_RESTART | WRT_OPT_WRITE_TO_PLAN_A);

u16 inline computeStringLen(char *str)
{
	u16 l = 0;
	while(str[l])
		l++;

	return l;
}

u16 inline charToTileIndex(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (u16)(c - 'A'); 

	if (c >= '0' && c <= '9')
		return (u16)((c  + 26) - '0');

	switch(c)
	{
		case '!':
			return FONT_PUNCT_OFFSET;
		case '\'':
			return FONT_PUNCT_OFFSET + 1;
		case '"':
			return FONT_PUNCT_OFFSET + 2;
		case '$':
			return FONT_PUNCT_OFFSET + 3;
		case ',':
			return FONT_PUNCT_OFFSET + 4;
		case '(':
			return FONT_PUNCT_OFFSET + 5;
		case ')':
			return FONT_PUNCT_OFFSET + 6;
		case '?':
			return FONT_PUNCT_OFFSET + 7;
		case '-':
			return FONT_PUNCT_OFFSET + 8;
		case '@':
			return FONT_PUNCT_OFFSET + 9;
		case ':':
			return FONT_PUNCT_OFFSET + 10;
		case '=':
			return FONT_PUNCT_OFFSET + 11;
		case '+':
			return FONT_PUNCT_OFFSET + 12;
		case 'c':
			return FONT_PUNCT_OFFSET + 13;
		case '[':
			return FONT_PUNCT_OFFSET + 14;
		case ']':
			return FONT_PUNCT_OFFSET + 15;		

	};

	/* if no character was found,
		we return a special code */
	return 0xFF;
}

u16 RSE_writerSetup(void)
{
	u16 j;
	current_plan = VDP_PLAN_A;
	current_pal = PAL0;

	SYS_disableInts();
	VDP_drawImageEx(APLAN, &oddball_fonts, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	for(j = 0; j  < VDP_getPlanHeight(); j++)
		RSE_clearTileRowA(j);
	SYS_enableInts();

	vramIndex += oddball_fonts.tileset->numTile;

	writer_switch = FALSE;
	writer_is_done = FALSE;
	x_offset = 0;
	writer_display_duration = RSE_FRAMES(50);

	return vramIndex;
}

void RSE_writerSetDisplayDuration(u8 duration)
{
	writer_display_duration = duration;
}

void RSE_writerSetInitialY(u16 initial_y)
{	initial_char_y = initial_y;	}

void RSE_writerSetXOffset(u16 offset)
{ 
	x_offset = offset;
}

void RSE_writerRestart(void)
{
	writer_switch = FALSE;
	current_string_idx = 0;
	current_char_idx = 0;
	writer_state = WRT_CENTER_CUR_LINE;
	writer_is_done = FALSE;
}

u16 inline RSE_writerSetOption(u16 option)
{
	writer_options |= option;
	return writer_options;
}

u16 inline RSE_writerUnsetOption(u16 option)
{
	writer_options &= ~option;
	return writer_options;
}

u16 RSE_writerDrawString(char *str)
{
	char c;
	u16 i, fade, faded_idx;
	for (fade = 0; fade < 4; fade++)
	{
		faded_idx = current_char_idx + fade;
		c = str[faded_idx];

		if (fade == 0 && c == 0)
			return FALSE;

		if (c != ' ')
		{
			i = charToTileIndex(c);
			if (faded_idx < current_string_len && i != 0xFF)
				VDP_setTileMapXY(current_plan, TILE_USERINDEX + i + (FONT_LINE_OFFSET * fade), current_char_x + fade + x_offset, TILE_ATTR_FULL(current_pal, FALSE, FALSE, FALSE, current_char_y));
		}
	}

	current_char_x++;
	current_char_idx++;

	return TRUE;
}

void inline RSE_writerUpdateLine(void)
{
	if (WRT_HAS_OPTION(WRT_OPT_HALF_SPEED))
		if (writer_state == WRT_WRITE_CUR_LINE)
		{
			writer_switch = ~writer_switch;
			if (writer_switch)
				return;
		}

	if (WRT_HAS_OPTION(WRT_OPT_WRITE_TO_PLAN_A))
	{
		current_plan = VDP_PLAN_A;
		current_pal = PAL0;
	}
	else
	{
		current_plan = VDP_PLAN_B;
		current_pal = PAL1;
	}

	switch(writer_state)
	{
		case WRT_CENTER_CUR_LINE:
			current_string_len = computeStringLen((char *)demo_strings[current_string_idx]);
			current_char_x = ((320 / 8) - current_string_len) >> 1;
			writer_state = WRT_WRITE_CUR_LINE;
			break;

		case WRT_WRITE_CUR_LINE:
			if (!RSE_writerDrawString((char *)demo_strings[current_string_idx]))
			{
				writer_timer = 0;
				writer_state = WRT_WAIT;
			}
			break;

		case WRT_WAIT:
			if (writer_timer++ > writer_display_duration)
			{
				writer_state = WRT_CLEAR_LINE;
				current_char_x = 0;
			}
			break;

		case WRT_CLEAR_LINE:
			VDP_setTileMapXY(current_plan, 0, current_char_x + x_offset, current_char_y);
			current_char_x++;
			if (current_char_x > 320 / 8)
			{
				current_char_x = 0;
				current_char_idx = 0;
				current_string_idx++;
				if (demo_strings[current_string_idx][0] == '\0')
				{
					writer_is_done = TRUE;
					if (WRT_HAS_OPTION(WRT_OPT_AUTO_RESTART))
						current_string_idx = 0;
					else
					{
						writer_state = WRT_IDLE_MODE;
						return;
					}
				}
				else
				if (demo_strings[current_string_idx][0] == '\1')
					current_char_y = initial_char_y;


				writer_state = WRT_CENTER_CUR_LINE;
			}
			break;

		case WRT_IDLE_MODE:
			return;
	}
}

u8 inline RSE_writerIsDone(void)
{	return writer_is_done; }

void inline RSE_writerUpdateMultiLine(void)
{
	if (WRT_HAS_OPTION(WRT_OPT_HALF_SPEED))
		if (writer_state == WRT_WRITE_CUR_LINE)
		{
			writer_switch = ~writer_switch;
			if (writer_switch)
				return;
		}

	if (WRT_HAS_OPTION(WRT_OPT_WRITE_TO_PLAN_A))
	{
		current_plan = VDP_PLAN_A;
		current_pal = PAL0;
	}
	else
	{
		current_plan = VDP_PLAN_B;
		current_pal = PAL1;
	}

	switch(writer_state)
	{
		case WRT_CENTER_CUR_LINE:
			current_string_len = computeStringLen((char *)demo_strings[current_string_idx]);
			current_char_x = ((320 / 8) - current_string_len) >> 1;
			writer_state = WRT_WRITE_CUR_LINE;
			break;

		case WRT_WRITE_CUR_LINE:
			if (!RSE_writerDrawString((char *)demo_strings[current_string_idx]))
			{
				writer_timer = 0;
				writer_state = WRT_WAIT;
			}
			break;

		case WRT_WAIT:
			if (writer_timer++ > writer_display_duration)
			{
				current_char_x = 0;
				current_char_y++;
				current_char_idx = 0;
				current_string_idx++;
				if (demo_strings[current_string_idx][0] == '\0')
				{
					writer_is_done = TRUE;
					if (WRT_HAS_OPTION(WRT_OPT_AUTO_RESTART))
						current_string_idx = 0;
					else
					{
						writer_state = WRT_IDLE_MODE;
						return;
					}
				}				
				writer_state = WRT_CENTER_CUR_LINE;
			}
			break;

		case WRT_IDLE_MODE:
			return;
	}
}
