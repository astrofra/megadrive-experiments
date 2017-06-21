#include "genesis.h"
#include "transition_helper.h"
#include "div_premul.h"
#include <gfx.h>

#define MAX_STAR  80
#define STARFIELD_SIZE (0x40)
#define STARFIELD_DIST -32
#define X_SCREEN_CENTER (((320 - 16) >> 1) + 0x80)
#define Y_SCREEN_CENTER (((224 - 32) >> 1) + 0x80)

typedef struct
{
	s16 x,y,z;
} _star;

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

static u16 tileIndexes[64];

static u16 loop;
static _star stars[MAX_STAR];
static s16 numstars;

void RSE_Starfield_3D_Spr(void)
{
	Sprite *sprites[MAX_STAR];
	Object sp_objects[MAX_STAR];
	u16 ind;

	/*	Initialize the list of stars */
	auto void initStar(s16 num)
	{
		_star *p;
		s16 i;

		numstars = num;

		i = num;
		p = stars;
		while(i--)
		{
			p->x = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE >> 1);
			p->y = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE >> 1);
			p->z = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE >> 1) + STARFIELD_DIST;
			p++;
		}
	};

	/*	Draw the stars */
	auto void inline updateAndDrawStar(_star *part, s16 num)
	{
		_star *p;
		s16 i;
		s16 zp, x, y;

		i = num;
		p = part;

		while(i--)
		{
			p->z++; //  += p->mov;
			if (p->z > (STARFIELD_SIZE >> 1) + STARFIELD_DIST)
			{
				p->z -= ((STARFIELD_SIZE >> 1) - STARFIELD_DIST);
				p->x = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE >> 1);
				p->y = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE >> 1);
			}

			if (p->z != 0)
			{

				x = (p->x << 8);
				y = (p->y << 7);
				zp = p->z - 45;

				if (zp > 0 && zp < DIV_PREMUL_LEN)
					zp = div_table[zp];
				else
				if (zp < 0 && zp > -DIV_PREMUL_LEN)
					zp = -div_table[-zp];
				else
				if (zp < 0)
					zp = -((u16)65535/(u16)(-zp));
				else
					zp = (u16)65535/(u16)(zp);

				x = (x * zp) >> 16;
				y = (y * zp) >> 16;

				sprites[i]->x = X_SCREEN_CENTER + x;
				sprites[i]->y = Y_SCREEN_CENTER + y;
				sprites[i]->status |= 0x0002;
			}
			p++;
		}
// #ifdef RSE_PERFORMANCE_PATCH
// 		SPR_updateQ(sprites, MAX_STAR);
// #else
		SPR_update(sprites, MAX_STAR);
// #endif
	};

	SYS_disableInts();

	VDP_setPlanSize(64, 32);

	vramIndex = TILE_USERINDEX;

	for(loop = 0; loop < 4; loop++)
	{
		VDP_drawImageEx(PLAN_B, &bg_sky, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), loop * 10, (224 - 160) >> 4, FALSE, TRUE);

		SYS_enableInts();
		VDP_waitVSync();
		SYS_disableInts();		
	}
	vramIndex += bg_sky.tileset->numTile;

	VDP_setPalette(PAL0, bg_sky.palette->data);

	VDP_drawImageEx(PLAN_A, &rse_retrowave_logo, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), (320 - 140) >> 4, 4, FALSE, TRUE);
	vramIndex += rse_retrowave_logo.tileset->numTile;

	SYS_enableInts();
	VDP_waitVSync();
	SYS_disableInts();
		
	VDP_setPalette(PAL1, rse_retrowave_logo.palette->data);


	VDP_setPalette(PAL2, sprite_stars.palette->data);
	SPR_init(MAX_STAR,0,0);

    ind = vramIndex;
    for(loop = 0; loop < sprite_stars.animations[0]->numFrame; loop++)
    {
        TileSet* tileset = sprite_stars.animations[0]->frames[loop]->tileset;

        VDP_loadTileSet(tileset, ind, TRUE);
        tileIndexes[loop] = ind;
        ind += tileset->numTile;
    }		

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < MAX_STAR; loop++)
	{
		sprites[loop] = SPR_addSprite(&sprite_stars, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));
		SPR_setAutoTileUpload(sprites[loop], FALSE);
		// SPR_setVRAMTileIndex(sprites[loop], vramIndex);
		sprites[loop]->data = (u32) &sp_objects[loop];
		SPR_setVRAMTileIndex(sprites[loop], tileIndexes[loop & 0x7]);		
		// SPR_setFrame(sprites[loop], loop % 7);
	}

	SPR_update(sprites, MAX_STAR);

	SYS_enableInts();	

	/* Initialise stars */
	initStar(MAX_STAR);

	// VDP_fadePalTo(PAL0, checkboard_green.palette->data, RSE_FRAMES(8), TRUE);

	/* Main loop */
	while(TRUE)
	{
		VDP_waitVSync();

		// can now draw text
		// BMP_showFPS(0);

		// calculates stars position
		// draw stars
		updateAndDrawStar(stars, numstars);
	}
}
