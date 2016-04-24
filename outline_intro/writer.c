#include "genesis.h"
#include <gfx.h>
#include "writer.h"

extern u16 vramIndex;
extern char **demo_strings;

/* 
	Global writer data 
*/
u16 writer_state = 0;
u16 writer_switch;
u16 current_string_idx;
u16 current_string_len;
u16 current_char_idx;
u16 current_char_x;
u16 current_char_y = 2;
u16 current_plan;
u16 writer_timer;
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
		return (u16)(c - '0') + 25;

	switch(c)
	{
		case '!':
			return FONT_PUNCT_OFFSET;
		case '"':
			return FONT_PUNCT_OFFSET + 1;
		case '#':
			return FONT_PUNCT_OFFSET + 2;
		case '$':
			return FONT_PUNCT_OFFSET + 3;
		case '%':
			return FONT_PUNCT_OFFSET + 4;
		case '&':
			return FONT_PUNCT_OFFSET + 5;
		case '\'':
			return FONT_PUNCT_OFFSET + 6;
		case '(':
			return FONT_PUNCT_OFFSET + 7;
		case ')':
			return FONT_PUNCT_OFFSET + 8;
		case '*':
			return FONT_PUNCT_OFFSET + 9;
		case '+':
			return FONT_PUNCT_OFFSET + 10;
		case ',':
			return FONT_PUNCT_OFFSET + 11;
		case '-':
			return FONT_PUNCT_OFFSET + 12;
		case '.':
			return FONT_PUNCT_OFFSET + 13;
		case '/':
			return FONT_PUNCT_OFFSET + 14;
		case ':':
			return FONT_PUNCT_OFFSET + 15;
		case ';':
			return FONT_PUNCT_OFFSET + 16;
		case '<':
			return FONT_PUNCT_OFFSET + 17;
		case '=':
			return FONT_PUNCT_OFFSET + 18;
		case '>':
			return FONT_PUNCT_OFFSET + 19;
		case '?':
			return FONT_PUNCT_OFFSET + 20;
		case '[':
			return FONT_PUNCT_OFFSET + 21;
		case '\\':
			return FONT_PUNCT_OFFSET + 22;
		case ']':
			return FONT_PUNCT_OFFSET + 23;
		case '^':
			return FONT_PUNCT_OFFSET + 24;									
		case '_':
			return FONT_PUNCT_OFFSET + 25;									
	};

	/* if no character was found,
		we return a special code */
	return 0xFF;
}

u16 RSE_writerSetup(void)
{
	current_plan = VDP_PLAN_A;

	SYS_disableInts();
	VDP_drawImageEx(APLAN, &oddball_fonts, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	VDP_clearPlan(APLAN, 0);
	SYS_enableInts();

	vramIndex += oddball_fonts.tileset->numTile;

	return vramIndex;
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
				VDP_setTileMapXY(current_plan, TILE_USERINDEX + i + (FONT_LINE_OFFSET * fade), current_char_x + fade, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, current_char_y));
		}
	}

	current_char_x++;
	current_char_idx++;

	return TRUE;
}

void inline RSE_writerUpdateLine(void)
{
	if (WRT_HAS_OPTION(WRT_OPT_WRITE_TO_PLAN_A))
		current_plan = VDP_PLAN_A;
	else
		current_plan = VDP_PLAN_B;

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
			if (writer_timer++ > 50)
			{
				writer_state = WRT_CLEAR_LINE;
				current_char_x = 0;
			}
			break;

		case WRT_CLEAR_LINE:
			VDP_setTileMapXY(current_plan, 0, current_char_x, current_char_y);
			current_char_x++;
			if (current_char_x > 320 / 8)
			{
				current_char_x = 0;
				current_char_idx = 0;
				current_string_idx++;
				if (demo_strings[current_string_idx][0] == '\0')
					current_string_idx = 0;

				writer_state = WRT_CENTER_CUR_LINE;
			}
			break;
	}
}
