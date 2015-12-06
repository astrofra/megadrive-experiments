#include <genesis.h>
#include <gfx.h>
#include "cosine_table.h"

static void vectorBallFX();

int main(){
	JOY_init();
	vectorBallFX();
	return 0;
}

static void vectorBallFX(){
	Sprite sprites[16];
	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	SYS_disableInts();

	/* Sprites */
	VDP_setPalette(PAL2, ball_metal.palette->data);
	SPR_init(256);
    SPR_initSprite(&sprites[0], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	SPR_setPosition(&sprites[0], (VDP_getScreenWidth() - 32) >> 1, (VDP_getScreenHeight() - 32) >> 1);
    SPR_update(sprites, 1);

	SYS_enableInts();

	VDP_setHInterrupt(1);

	while (TRUE){
		VDP_waitVSync();
	}
}