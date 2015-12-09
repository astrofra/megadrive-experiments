#include <genesis.h>
#include <gfx.h>

static void rogMainScreen();

int main(){
	JOY_init();
	rogMainScreen();
	return 0;
}

static void rogMainScreen(){
	u16 x,y;
	u16 vramIndex = TILE_USERINDEX;
	// Sprite sprites[16];
	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);
	SYS_disableInts();

	/* Draw the background */
	VDP_setPalette(PAL0, fish.palette->data);
	VDP_drawImageEx(APLAN, &fish, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += fish.tileset->numTile;

	/* Draw the foreground */
	VDP_setPalette(PAL1, cat.palette->data);
	VDP_drawImageEx(BPLAN, &cat, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += cat.tileset->numTile;

	/* Sprites */
	// VDP_setPalette(PAL2, pirate_logo.palette->data);
	// SPR_init(257);
 //    SPR_initSprite(&sprites[0], &pirate_logo, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	// SPR_setPosition(&sprites[0], (VDP_getScreenWidth() - 128) >> 1, (VDP_getScreenHeight() - 128) >> 1);
 //    SPR_update(sprites, 1);

	SYS_enableInts();

	VDP_setHInterrupt(1);

	while (1){
		VDP_waitVSync();
		// SPR_setPosition(&sprites[0], ((VDP_getScreenWidth() - 128) >> 1)						/* Horiz. center */
		// 							+ (tcos[(vblCount << 2) & (COSINE_TABLE_LEN - 1)] >> 5), 	/* plus horiz. sine motion */
		// 							(VDP_getScreenHeight() - 128) >> 1);						/* Vert. center */		
	}
}