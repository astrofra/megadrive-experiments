#include <genesis.h>
#include <gfx.h>

#define PLAN_MAX_X 64
#define PLAN_MAX_Y 64

static void rogMainScreen();

int main(){
	JOY_init();
	rogMainScreen();
	return 0;
}

static void rogMainScreen(){
	u16 x,y;
	u16 scroll_phase = 0;
	u16 vramIndex = TILE_USERINDEX;
	// Sprite sprites[16];
	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 64);
	SYS_disableInts();

	/* Draw the background */
	VDP_setPalette(PAL1, fish.palette->data);
	for (x = 0; x < PLAN_MAX_X; x += 2)
		for (y = 0; y < PLAN_MAX_Y; y += 2)
			VDP_drawImageEx(BPLAN, &fish, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), x, y, FALSE, FALSE);
	vramIndex += fish.tileset->numTile;

	/* Draw the foreground */
	VDP_setPalette(PAL0, cat.palette->data);
	VDP_drawImageEx(APLAN, &cat, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (VDP_getScreenWidth() - 108) >> 4 , (VDP_getScreenHeight() - 192) >> 3, FALSE, FALSE);
	vramIndex += cat.tileset->numTile;

	VDP_loadTileData(fish.tileset->tiles, vramIndex, 4, 1);

	/* Sprites */
	// VDP_setPalette(PAL2, pirate_logo.palette->data);
	// SPR_init(257);
 //    SPR_initSprite(&sprites[0], &pirate_logo, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	// SPR_setPosition(&sprites[0], (VDP_getScreenWidth() - 128) >> 1, (VDP_getScreenHeight() - 128) >> 1);
 //    SPR_update(sprites, 1);

	SYS_enableInts();

	VDP_setHInterrupt(1);

	vramIndex = 0;

	while (1){
		VDP_waitVSync();
		BMP_showFPS(1);
	
		scroll_phase++;

		x = fix16Mul(cosFix16(scroll_phase << 1), FIX16(3.0));
		y = fix16Mul(sinFix16(scroll_phase << 2), FIX16(2.0));

		x >>= 2;
		y >>= 2;

		VDP_setHorizontalScroll(PLAN_B, x);
		VDP_setVerticalScroll(PLAN_B, y + 16);

		// VDP_drawImageEx(APLAN, &fish, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (scroll_phase & 0x20) << 1, 20, FALSE, FALSE);
		// VDP_setTileMapXY(VDP_PLAN_A, 16 + (scroll_phase & 0x1), scroll_phase, 2); // (scroll_phase & 0x20) << 1, 2);
		// SPR_setPosition(&sprites[0], ((VDP_getScreenWidth() - 128) >> 1)						/* Horiz. center */
		// 							+ (tcos[(vblCount << 2) & (COSINE_TABLE_LEN - 1)] >> 5), 	/* plus horiz. sine motion */
		// 							(VDP_getScreenHeight() - 128) >> 1);						/* Vert. center */		
	}
}
