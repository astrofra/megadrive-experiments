#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"
#include "string_parser.h"

extern u16 vramIndex;
extern u8 framerate;
extern char *demo_strings;

/* 
	Global writer data 
*/

u16 current_char_x;
u16 current_char_y;
u8 letter_width;
u16 current_char;
VDPPlan current_plan;
u8 current_pal;
u8 scroll_speed;
s16 scroll_x_offset;
u16 scroll_y_offset;
u8 scroll_local_offset;
u8 screen_w_tile;
s16 scroll_tile_y[1204];

// u16 inline computeStringLen(char *str)
// {
// 	u16 l = 0;
// 	while(str[l])
// 		l++;

// 	return l;
// }

// u16 inline charToTileIndex(char c)
// {
// 	if (c >= 'A' && c <= 'Z')
// 		return (u16)(c - 'A'); 

// 	if (c >= '0' && c <= '9')
// 		return (u16)((c  + 26) - '0');

// 	switch(c)
// 	{
// 		case '!':
// 			return FONT_PUNCT_OFFSET;
// 		case '.':
// 			return FONT_PUNCT_OFFSET + 1;
// 		case '\'':
// 			return FONT_PUNCT_OFFSET + 2;
// 		case '$':
// 			return FONT_PUNCT_OFFSET + 3;
// 		case ',':
// 			return FONT_PUNCT_OFFSET + 4;
// 		case '(':
// 			return FONT_PUNCT_OFFSET + 5;
// 		case ')':
// 			return FONT_PUNCT_OFFSET + 6;
// 		case '?':
// 			return FONT_PUNCT_OFFSET + 7;
// 		case '-':
// 			return FONT_PUNCT_OFFSET + 8;
// 		case '@':
// 			return FONT_PUNCT_OFFSET + 9;
// 		case ':':
// 			return FONT_PUNCT_OFFSET + 10;
// 		case '=':
// 			return FONT_PUNCT_OFFSET + 11;
// 		case '+':
// 			return FONT_PUNCT_OFFSET + 12;
// 		case 'c':
// 			return FONT_PUNCT_OFFSET + 13;
// 		case '[':
// 			return FONT_PUNCT_OFFSET + 14;
// 		case ']':
// 			return FONT_PUNCT_OFFSET + 15;		

// 	};

// 	/* if no character was found,
// 		we return a special code */
// 	return 0xFF;
// }

u16 RSE_writerSetup(void)
{
	u16 j;
	current_plan = PLAN_A;
	current_pal = PAL0;

	SYS_disableInts();
	VDP_drawImageEx(PLAN_A, &sim1_font, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	RSE_clearTileRowA(0);
	SYS_enableInts();

	vramIndex += sim1_font.tileset->numTile;
	current_char = 0;
	letter_width = 8;
	scroll_speed = 1;
	scroll_x_offset = 0;
	scroll_y_offset = 0;
	scroll_local_offset = 0;
	current_char_x = 0;
	current_char_y = 3;
	screen_w_tile = 64;

	for (j = 0; j < 1024; j++)
		scroll_tile_y[j] = (((sinFix16(j << 4) + sinFix16(j << 2) + 64) * 3) >> 3) - 48;

	return vramIndex;
}
// s16 scroll_tile_x[16];
void updateScrollText(void)
{
	scroll_x_offset -= scroll_speed;
	scroll_y_offset += scroll_speed;
	scroll_local_offset += scroll_speed;

	current_char_x = ((-scroll_x_offset) >> 3) - 1;

	if (scroll_local_offset >= letter_width)
	{
		char c;

		scroll_local_offset = 0;
		c = demo_strings[current_char];

		if (c == '\0')
			current_char = 1;
		else
		{
			if (c != ' ')
				VDP_setTileMapXY(current_plan, TILE_ATTR_FULL(current_pal, TRUE, FALSE, FALSE, TILE_USERINDEX + charToTileIndex(c)), current_char_x, current_char_y); //TILE_ATTR_FULL(current_pal, FALSE, FALSE, FALSE, current_char_y));
			else
				VDP_setTileMapXY(current_plan, 0, current_char_x, current_char_y); //TILE_ATTR_FULL(current_pal, FALSE, FALSE, FALSE, current_char_y));

		}

		if (scroll_x_offset <= (screen_w_tile * -8))
			scroll_x_offset -= screen_w_tile * -8;

		current_char++;
	}

	SYS_disableInts();

	/* V scroll */
	VDP_setVerticalScrollTile(current_plan, 0, &(scroll_tile_y[scroll_y_offset & 0x1ff]), (screen_w_tile >> 1) - 4, TRUE);
	DMA_waitCompletion();

	/* H scroll */
	VDP_setHorizontalScroll(current_plan, scroll_x_offset);

	SYS_enableInts();
}

void RSE_writerSetY(u16 initial_y)
{	current_char_y = initial_y;	}