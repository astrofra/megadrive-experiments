#include <genesis.h>
#include <gfx.h>
#include "resources.h"
#include "sprites_traj.h"
#include "demo_strings.h"
#include "RSE_startingScreen.h"

#define SPRITE_COUNT (6 << 3)	//	Must be a multiple of 8
#define FONT_PUNCT_OFFSET 35
#define FONT_LINE_OFFSET ((504 >> 3) - 1)

#define PLAN_B_TILE_H 20
#define PLAN_A_TILE_H 10

/*
	States of the text writer
*/
#define WRT_CENTER_CUR_LINE 0
#define WRT_WRITE_CUR_LINE 1
#define WRT_WAIT 2
#define WRT_CLEAR_LINE 3

/*	
	States of the sprites animation
*/
#define SPR_RUNNING 0
#define SPR_WAIT_END_FADEOUT 1
#define SPR_CHANGE_TRAJECTORY 2
#define SPR_WAIT_END_FADEIN 3

static void RSE_xmasIntro();

int main()
{
	RSE_startingScreen(10, 10);
	if (SYS_isPAL())
	{
		RSE_guruMeditation();
	}
	else
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

static void RSE_xmasIntro()
{
	u16 vblCount = 0;

	u16 vramIndex = TILE_USERINDEX;
	short i, j, k;
	Sprite sprites[SPRITE_COUNT];
	int sprites_attr[SPRITE_COUNT];
	const u16 *tmp_spr_traj, *current_spr_traj = NULL;

	s16 scroll_PLAN_B[PLAN_B_TILE_H];
	s16 scroll_PLAN_A[PLAN_A_TILE_H];
	s16 scroll_sin_precalc;

	u16 writer_state;
	u16 writer_switch;
	u16 current_string_idx;
	u16 current_string_len;
	u16 current_char_idx;
	u16 current_char_x;
	u16 writer_timer;

	u16 sprite_anim_state;

	static u16 RSE_drawString(char *str)
	{
		char c;
		u16 i, fade, faded_idx;
		for (fade = 0; fade < 3; fade++)
		{
			faded_idx = current_char_idx + fade;
			c = str[faded_idx];

			if (fade == 0 && c == 0)
				return FALSE;

			if (c != ' ')
			{
				i = charToTileIndex(c);
				if (faded_idx < current_string_len && i != 0xFF)
					VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + i + (FONT_LINE_OFFSET * fade), current_char_x + fade, 22);
			}
		}

		current_char_x++;
		current_char_idx++;

		return TRUE;
	}

	static void inline RSE_updateLineWriter(void)
	{
		// SYS_disableInts();
		switch(writer_state)
		{
			case WRT_CENTER_CUR_LINE:
				current_string_len = computeStringLen(demo_strings[current_string_idx]);
				current_char_x = ((320 / 8) - current_string_len) >> 1;
				writer_state = WRT_WRITE_CUR_LINE;
				break;

			case WRT_WRITE_CUR_LINE:
				if (!RSE_drawString(demo_strings[current_string_idx]))
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
		// SYS_enableInts();
	}

	static const u16* RSE_getNextSpriteTrajectories(const u16 *cur_traj)
	{
		if (cur_traj == NULL)
				return spr_traj;
		if (cur_traj == spr_traj)
				return spr_traj_1;
		if (cur_traj == spr_traj_1)
				return spr_traj_bnc;
		if (cur_traj == spr_traj_bnc)
				return spr_traj_2;
		if (cur_traj == spr_traj_2)
				return spr_traj;
	}

	SYS_disableInts();
	// VDP_setEnable(FALSE);

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	/* Load the fond tiles */
	VDP_drawImageEx(BPLAN, &squarish_font, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += squarish_font.tileset->numTile;	

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	/* Draw the foreground */
	VDP_setPalette(PAL1, (u16*)palette_black);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 24, 2, FALSE, FALSE);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 2, FALSE, FALSE);
	vramIndex += ground.tileset->numTile;

	/* Draw the logo */
	VDP_setPalette(PAL0, (u16*)palette_black);
	VDP_drawImageEx(APLAN, &rse_logo, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 7, FALSE, FALSE);
	vramIndex += rse_logo.tileset->numTile;	    

	for(i = 0; i < SPRITE_COUNT; i++)
		SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));

	VDP_setPalette(PAL2, (u16*)palette_black);
	SPR_init(SPRITE_COUNT);

	VDP_setPalette(PAL0, rse_logo.palette->data);
	VDP_setPalette(PAL1, ground.palette->data);
	VDP_setPalette(PAL2, ball_metal.palette->data);

	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

	// VDP_setEnable(TRUE);
	SYS_enableInts();

	SND_startPlay_XGM(midnight);
	SND_setMusicTempo_XGM(50);

	current_string_idx = 0;
	current_char_idx = 0;
	current_char_x = 0;
	writer_timer = 0;
	writer_switch = FALSE;

	for(i = 0; i < SPRITE_COUNT; i++)
		sprites_attr[i] = sprites[i].attribut;

	writer_state = WRT_CENTER_CUR_LINE;

	current_spr_traj = RSE_getNextSpriteTrajectories(current_spr_traj);

	sprite_anim_state = SPR_RUNNING;

	while (TRUE)
	{
		VDP_waitVSync();
		SPR_update(sprites, SPRITE_COUNT);
		VDP_setHorizontalScrollTile(PLAN_B, 2, scroll_PLAN_B, PLAN_B_TILE_H, FALSE);
		VDP_setHorizontalScrollTile(PLAN_A, 7, scroll_PLAN_A, PLAN_A_TILE_H, FALSE);
		
		for(i = 0; i < PLAN_B_TILE_H; i++)
			scroll_PLAN_B[i] = -vblCount;
		for (i = 0, scroll_sin_precalc = sinFix16(vblCount << 2); i < PLAN_A_TILE_H; i++)
			scroll_PLAN_A[i] = scroll_sin_precalc;

		tmp_spr_traj = current_spr_traj + ((vblCount << 1) & (SPRT_TABLE_LEN - 1));

		for(i = 0; i < SPRITE_COUNT; i++)
		{
			sprites[i].x = *(tmp_spr_traj++);
			sprites[i].y = *(tmp_spr_traj++);

			if (sprites[i].y >= SCR_Y_CENTER + 64)
				sprites_attr[i] = sprites_attr[i] & 0x7FFF; // Sprite goes behind
			else
			{
				if (sprites[i].y <= SCR_Y_CENTER - 64)
					sprites_attr[i] = sprites_attr[i] | 0x8000; // Sprite goes in front
			}

			sprites[i].attribut = sprites_attr[i];
			tmp_spr_traj += 12;
		}

		if (writer_switch || writer_state == WRT_CLEAR_LINE)
			RSE_updateLineWriter();

		writer_switch = !writer_switch;	

		vblCount += 1;
		switch(sprite_anim_state)
		{
			case SPR_RUNNING:
				if ((vblCount & ((SPRT_TABLE_LEN >> 2) - 1)) == 0)
				{
					j = 0;
					k = 0;
					sprite_anim_state = SPR_WAIT_END_FADEOUT;
				}
				break;

			case SPR_WAIT_END_FADEOUT:
				if (j >= SPRITE_COUNT)
				{
					j = 0;
					k++;
				}

				if (k >= 4)
					sprite_anim_state = SPR_CHANGE_TRAJECTORY;
				else
				{
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
				}
				break;

			case SPR_CHANGE_TRAJECTORY:
				current_spr_traj = RSE_getNextSpriteTrajectories(current_spr_traj);
				j = 0;
				k = 3;
				sprite_anim_state = SPR_WAIT_END_FADEIN;
				break;

			case SPR_WAIT_END_FADEIN:
				if (j >= SPRITE_COUNT)
				{
					j = 0;
					k--;
				}

				if (k < 0)
					sprite_anim_state = SPR_RUNNING;
				else
				{
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
					SPR_setFrame(&sprites[j++], k);
				}
				break;
		}
	}
}