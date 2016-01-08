#include <genesis.h>
#include <gfx.h>
#include "resources.h"

#define	TABLE_LEN 160
#define PERSPECTIVE_STEP 6
#define BALL_COUNT 58

static void beastScrollingFX();

int main(){
	JOY_init();
	beastScrollingFX();
	return 0;
}

static void beastScrollingFX(){
	u32 hscrollInc = 0;
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	short i;
	Sprite sprites[BALL_COUNT];

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	/* Draw the foreground */
	VDP_setPalette(PAL1, ground.palette->data);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 4, FALSE, FALSE);
	VDP_drawImageEx(BPLAN, &ground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 24, 4, FALSE, FALSE);
	vramIndex += ground.tileset->numTile;

	VDP_setPalette(PAL0, rse_logo.palette->data);
	VDP_drawImageEx(APLAN, &rse_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 6, FALSE, FALSE);
	vramIndex += rse_logo.tileset->numTile;	    	

	for(i = 0; i < BALL_COUNT; i++)
		SPR_initSprite(&sprites[i], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));

	VDP_setPalette(PAL2, ball_metal.palette->data);
	SPR_init(BALL_COUNT);

	SYS_enableInts();

	SND_startPlay_XGM(midnight);

	while (1){
		hscrollInc = 0;
		VDP_waitVSync();
		VDP_setHorizontalScroll(PLAN_B, -vblCount);
		VDP_setHorizontalScroll(PLAN_A, sinFix16(vblCount << 2));

		for(i = 0; i < BALL_COUNT; i++)
		{
			// SPR_setPosition(&sprites[i], 160 + sinFix16((vblCount << 2) + (i << 5)), 100 + cosFix16((vblCount << 3) + (i << 3)));
			sprites[i].x = (160 + 0x80) + sinFix16((vblCount << 2) + (i << 5));
			sprites[i].y = (100 + 0x80) + cosFix16((vblCount << 3) + (i << 3));
		}

		SPR_update(sprites, BALL_COUNT);
		vblCount += 1;
	}
}
