#include <genesis.h>
#include <gfx.h>
#include "resources.h"
#include "sprites_traj.h"
#include "demo_strings.h"

#define SPRITE_COUNT 50
#define HBLANK_STEP 50
#define FONT_PUNCT_OFFSET 36

static void RSE_xmasIntro();

int main(){
	JOY_init();
	RSE_xmasIntro();
	return 0;
}

static u16 inline charToTileIndex(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (u16)(c - 'A'); 

	if (c >= '0' && c <= '9')
		return (u16)(c - '0');

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

static void inline drawCharTiles(u16 char_idx, u16 x)
{
	x <<= 1;
	char_idx <<= 1;
	VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + char_idx, x, 22);
	VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + char_idx + 1, x + 1, 22);
	VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + char_idx + 96, x, 23);
	VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + char_idx + 1 + 96, x + 1, 23);	
}

static void RSE_xmasIntro()
{
	u32 hscrollInc = 0;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	short i;
	Sprite sprites[SPRITE_COUNT];
	u16 *tmp_spr_traj;
	u16 current_string_idx;
	u16 current_char_idx;
	u16 current_char_x;

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
				drawCharTiles(i, current_char_x);
		}

		current_char_x++;
		current_char_idx++;

		return TRUE;
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
	VDP_drawImageEx(APLAN, &rse_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 7, FALSE, FALSE);
	vramIndex += rse_logo.tileset->numTile;	    

	for(i = 0; i < SPRITE_COUNT; i++)
		SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));

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

	while (1)
	{
		hscrollInc = 0;
		VDP_waitVSync();
		VDP_setHorizontalScroll(PLAN_B, -vblCount);
		// VDP_setHorizontalScroll(PLAN_A, sinFix16(vblCount << 2));

		tmp_spr_traj = spr_traj + ((vblCount << 1) & (SPRT_TABLE_LEN - 1));
		for(i = 0; i < SPRITE_COUNT; i++)
		{
			sprites[i].x = *(tmp_spr_traj++);
			sprites[i].y = *(tmp_spr_traj++);
			tmp_spr_traj += 12;
		}

		SPR_update(sprites, SPRITE_COUNT);

		drawString(demo_strings[current_string_idx]);

		vblCount += 1;
	}
}
