#include <genesis.h>
#include <gfx.h>
#include "resources.h"
#include "sprites_traj.h"
#include "demo_strings.h"

#define SPRITE_COUNT 48
#define HBLANK_STEP 50
#define FONT_PUNCT_OFFSET 36

#define WRT_CENTER_CUR_LINE 0
#define WRT_WRITE_CUR_LINE 1
#define WRT_WAIT 2
#define WRT_CLEAR_LINE 3

static void RSE_xmasIntro();

int main(){
	JOY_init();
	RSE_xmasIntro();
	return 0;
}

static u16 inline computeStringLen(char *str)
{
	u16 l = 0;
	while(str[l])
		l++;

	return l;
}

static u16 inline charToTileIndex(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (u16)(c - 'A'); 

	if (c >= '0' && c <= '9')
		return (u16)(c - '0') + 27;

	switch(c)
	{
		case '.':
			return FONT_PUNCT_OFFSET;
		case '/':
			return FONT_PUNCT_OFFSET + 1;
		case ':':
			return FONT_PUNCT_OFFSET + 2;
		case '!':
			return FONT_PUNCT_OFFSET + 3;
		case ',':
			return FONT_PUNCT_OFFSET + 4;
		case ';':
			return FONT_PUNCT_OFFSET + 5;
		case '(':
			return FONT_PUNCT_OFFSET + 6;
		case ')':
			return FONT_PUNCT_OFFSET + 7;
		case '=':
			return FONT_PUNCT_OFFSET + 8;
		case '+':
			return FONT_PUNCT_OFFSET + 9;
		case '*':
			return FONT_PUNCT_OFFSET + 10;
		case '#':
			return FONT_PUNCT_OFFSET + 11;
	};

	/* if no character was found,
		we return a special code */
	return 0xFF;
}

static void RSE_xmasIntro()
{
	u32 hscrollInc = 0;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	short i;
	Sprite sprites[SPRITE_COUNT];
	u16 *tmp_spr_traj;

	u16 writer_state;
	u16 current_string_idx;
	u16 current_char_idx;
	u16 current_char_x;
	u16 writer_timer;

	static u16 drawString(char *str)
	{
		char c;
		u16 i;
		c = str[current_char_idx];

		if (c == 0)
			return FALSE;

		if (c != ' ')
		{
			i = charToTileIndex(c);
			if (i != 0xFF)
				VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + i, current_char_x, 22); // drawCharTiles(i, current_char_x);
		}

		current_char_x++;
		current_char_idx++;

		return TRUE;
	}

	static void inline RSE_updateLineWriter(void)
	{
		switch(writer_state)
		{
			case WRT_CENTER_CUR_LINE:
				current_char_x = ((320 / 8) - computeStringLen(demo_strings[current_string_idx])) >> 1;
				writer_state = WRT_WRITE_CUR_LINE;
				break;

			case WRT_WRITE_CUR_LINE:
				if (!drawString(demo_strings[current_string_idx]))
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
				VDP_setTileMapXY(VDP_PLAN_A, 0, current_char_x, 22);
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

		}		
	}

	/*	Hblank-based water fx */
	static void hBlank(){
		hscrollInc++;
		if (hscrollInc < (200 / HBLANK_STEP))
		{
			VDP_setPaletteColors(0, rse_logo.palette->data, 8);
			VDP_setHorizontalScroll(PLAN_A, sinFix16(vblCount << 2));
		}	
		else
		{
			VDP_setHorizontalScroll(PLAN_A, 0);
			VDP_setPaletteColors(0, squarish_font.palette->data, 8);
		}
	}

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	/* Load the fond tiles */
	VDP_drawImageEx(BPLAN, &squarish_font, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += squarish_font.tileset->numTile;	

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	/* Draw the foreground */
	VDP_setPalette(PAL1, ground.palette->data);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 2, FALSE, FALSE);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 24, 2, FALSE, FALSE);
	vramIndex += ground.tileset->numTile;

	/* Draw the logo */
	VDP_setPalette(PAL0, rse_logo.palette->data);
	VDP_drawImageEx(APLAN, &rse_logo, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 7, FALSE, FALSE);
	vramIndex += rse_logo.tileset->numTile;	    

	for(i = 0; i < SPRITE_COUNT; i++)
		SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));

	VDP_setPalette(PAL2, ball_metal.palette->data);
	SPR_init(SPRITE_COUNT);

	SYS_enableInts();

	VDP_setHIntCounter(HBLANK_STEP);
	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption	

	SND_startPlay_XGM(midnight);

	current_string_idx = 0;
	current_char_idx = 0;
	current_char_x = 0;
	writer_timer = 0;

	writer_state = WRT_CENTER_CUR_LINE;

	while (1)
	{
		hscrollInc = 0;
		VDP_waitVSync();
		VDP_setHorizontalScroll(PLAN_B, -vblCount);

		tmp_spr_traj = spr_traj + ((vblCount << 1) & (SPRT_TABLE_LEN - 1));
		for(i = 0; i < SPRITE_COUNT; i++)
		{
			sprites[i].x = *(tmp_spr_traj++);
			sprites[i].y = *(tmp_spr_traj++);
			if (sprites[i].x > 160 + 0x80)
				sprites[i].attribut = sprites[i].attribut | 0x8000;
			else
				sprites[i].attribut = sprites[i].attribut & 0x7FFF;
			tmp_spr_traj += 12;
		}

		SPR_update(sprites, SPRITE_COUNT);

		RSE_updateLineWriter();		

		vblCount += 1;
	}
}

