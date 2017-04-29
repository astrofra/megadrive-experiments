#include <genesis.h>
#include <gfx.h>
#include <resources.h>
#include "writer.h"

#define	TABLE_LEN 220
#define MAX_DONUT 16

typedef struct
{
    Vect2D_f16 pos;
    Vect2D_f16 mov;
    u16 timer;
} Object;

static u16 tileIndexes[64];

static void fastStarFieldFX();

s16 scroll_PLAN_B[TABLE_LEN];
u8 scroll_speed[TABLE_LEN];

int main(){
	fastStarFieldFX();
	return 0;
}

u8 figure_mode = 0;
s16 i, ns, s, ind, figure_counter = 0;
static Object objects[256];
Sprite *sprites[256];

static void fastStarFieldFX()
{
	u16 vramIndex = TILE_USERINDEX;
	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);
	VDP_setPlanSize(64, 32);

	/* Load the fond tiles */
	VDP_drawImageEx(PLAN_B, &amiga_font, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += amiga_font.tileset->numTile;		

	/* Draw the foreground */
	VDP_drawImageEx(PLAN_B, &starfield, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, TRUE, FALSE);
	VDP_drawImageEx(PLAN_B, &starfield, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 256 >> 3, 0, TRUE, FALSE);	
	vramIndex += starfield.tileset->numTile; 	

	/* Draw the logo */
	VDP_drawImageEx(PLAN_A, &vip_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), (320 - 256) >> 4, (224 - 144) >> 4, TRUE, FALSE);
	vramIndex += vip_logo.tileset->numTile; 	

	/*	Set the proper scrolling mode (line by line) */
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);

	/*	Create the scrolling offset table */
	s = 1;
	for(i = 0; i < TABLE_LEN; i++)
	{
		scroll_PLAN_B[i] = 0;
		do
		{
			ns = -((random() % 3) + 1);
		}
		while (ns == s);
		scroll_speed[i] = ns;
		s = ns;
	}

	/* Setup the sprites */
	SPR_init(0,0,0);

    ind = vramIndex;
    for(i = 0; i < donut.animations[0]->numFrame; i++)
    {
        TileSet* tileset = donut.animations[0]->frames[i]->tileset;

        VDP_loadTileSet(tileset, ind, TRUE);
        tileIndexes[i] = ind;
        ind += tileset->numTile;
    }

	for(i = 0; i < MAX_DONUT; i++)
	{
	    sprites[i] = SPR_addSprite(&donut, 0, 0, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
		SPR_setAutoTileUpload(sprites[i], FALSE);
		SPR_setVRAMTileIndex(sprites[i], TILE_USERINDEX);
		sprites[i]->data = (u32) &objects[i];    
	}

	// SPR_update(sprites, MAX_DONUT);

	VDP_setPalette(PAL2, donut.palette->data);
	VDP_setPalette(PAL0, vip_logo.palette->data);

	SYS_enableInts();

	/* writer setup */
	current_string_idx = 0;
	current_char_idx = 0;
	current_char_x = 0;
	writer_timer = 0;
	writer_switch = FALSE;

	writer_state = WRT_CENTER_CUR_LINE;		

	SND_startPlay_XGM(maak_music_2);
	SND_setMusicTempo_XGM(50);	

	/*	Start !!!! */
	s = 0;
	while (TRUE)
	{
		VDP_waitVSync();
		// BMP_showFPS(1);

		/* 	Scroll the starfield */
		VDP_setHorizontalScrollLine(PLAN_B, 2, scroll_PLAN_B, TABLE_LEN, TRUE);
		for(i = 0; i < TABLE_LEN; i++)
			scroll_PLAN_B[i] = (scroll_PLAN_B[i] + scroll_speed[i]) & 0xFF;

		/*	Animate the donuts */
		for(i = 0; i < MAX_DONUT; i++)
		{
			// sprites[i]->x = (cosFix16(s + (i << 5)) << 1) + 160 - 16 + 0x80;
			// sprites[i]->y = sinFix16(s + (i << 5)) + 112 - 16 + 0x80;
			
			switch(figure_mode)
			{
				case 0:
					SPR_setPosition(sprites[i], (cosFix16(s + (i << 5)) << 1) + 160 - 16, sinFix16(s + (i << 5)) + 112 - 16);
					break;

				case 1:
					SPR_setPosition(sprites[i], (cosFix16(s + (i << 6)) << 1) + 160 - 16, (sinFix16(s + (i << 5))) + 112 - 16);
					break;

				case 2:
					SPR_setPosition(sprites[i], ((sinFix16((s << 1) + (i << 6))) << 1) + 160 - 16, (cosFix16(s + (i << 5)) << 1) + 112 - 16);
					break;

				case 3:
					SPR_setPosition(sprites[i], (sinFix16(s + (i << 7))) + 160 - 16, (cosFix16((s >> 1) + (i << 4)) << 1) + 112 - 16);
					break;

				case 4:
					SPR_setPosition(sprites[i], (cosFix16((s << 1) + (i << 5)) << 1) + 160 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16);
					break;
			}
			SPR_setVRAMTileIndex(sprites[i], tileIndexes[((s >> 4) + i) & 0x7]);
			// SPR_setFrame(sprites[i], ((s >> 4) + i) & 0x7);
		}

		SPR_update(sprites, MAX_DONUT);

		s += 4;
		figure_counter++;
		if (figure_counter > 512)
		{
			figure_mode++;
			if (figure_mode > 4) figure_mode = 0;

			figure_counter = 0;
		}

		if (writer_switch || writer_state == WRT_CLEAR_LINE)
			RSE_updateLineWriter();

		writer_switch = !writer_switch;			
	}
}
