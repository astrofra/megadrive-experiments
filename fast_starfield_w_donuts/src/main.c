#include <genesis.h>
#include <gfx.h>

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

static void fastStarFieldFX()
{
	u16 vramIndex = TILE_USERINDEX;
	s16 i, ns, s, ind;
	static Object objects[256];
	Sprite *sprites[256];

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, 0);
	VDP_clearPlan(PLAN_B, 0);
	VDP_setPlanSize(32, 32);

	/* Draw the foreground */
	VDP_drawImageEx(PLAN_B, &starfield, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, TRUE, FALSE);
	vramIndex += starfield.tileset->numTile; 	

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

	SYS_enableInts();

	/*	Start !!!! */
	s = 0;
	while (TRUE)
	{
		VDP_waitVSync();
		BMP_showFPS(1);

		/* 	Scroll the starfield */
		VDP_setHorizontalScrollLine(PLAN_B, 2, scroll_PLAN_B, TABLE_LEN, TRUE);
		for(i = 0; i < TABLE_LEN; i++)
			scroll_PLAN_B[i] = (scroll_PLAN_B[i] + scroll_speed[i]) & 0xFF;

		/*	Animate the donuts */
		for(i = 0; i < MAX_DONUT; i++)
		{
			// sprites[i]->x = (cosFix16(s + (i << 5)) << 1) + 160 - 16 + 0x80;
			// sprites[i]->y = sinFix16(s + (i << 5)) + 112 - 16 + 0x80;
			SPR_setPosition(sprites[i], (cosFix16(s + (i << 5)) << 1) + 160 - 16, sinFix16(s + (i << 5)) + 112 - 16);
			SPR_setVRAMTileIndex(sprites[i], tileIndexes[((s >> 4) + i) & 0x7]);
			// SPR_setFrame(sprites[i], ((s >> 4) + i) & 0x7);
		}

		s += 4;	
		SPR_update(sprites, MAX_DONUT);
	}
}
