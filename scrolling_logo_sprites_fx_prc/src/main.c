#include <genesis.h>
#include <gfx.h>
#include "resources.h"
#include "sprites_traj.h"

#define SPRITE_COUNT 50
#define HBLANK_STEP 50

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
	Sprite sprites[SPRITE_COUNT];
	u16 *tmp_spr_traj;

	/*	Hblank-based water fx */
	static void hBlank(){
		hscrollInc++;
		if (hscrollInc < (200 / HBLANK_STEP))
			VDP_setHorizontalScroll(PLAN_A, sinFix16(vblCount << 2));
		else
			VDP_setHorizontalScroll(PLAN_A, 0);
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

	while (1){
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

		VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + vblCount, vblCount, 22);

		vblCount += 1;
	}
}
