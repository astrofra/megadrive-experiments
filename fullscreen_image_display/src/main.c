#include <genesis.h>
#include <gfx.h>

static void displayFullScreenPicture();

int main(){
	displayFullScreenPicture();
	return 0;
}

static void displayFullScreenPicture(){
	u16 vramIndex = TILE_USERINDEX;

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);
	SYS_disableInts();

	/* Draw the background */	
	VDP_drawImageEx(BPLAN, &shikasta_tilemap, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
	vramIndex += shikasta_tilemap.tileset->numTile;

	SYS_enableInts();

	while (1){
		VDP_waitVSync();
	}
}