#include <genesis.h>
#include <gfx.h>
#include "transition_helper.h"

static void displayFullScreenPicture();

int main(){
	displayFullScreenPicture();
	return 0;
}

u16 framerate = 60;
u16 vramIndex = TILE_USERINDEX;

static void displayFullScreenPicture(){
	s16 i,j,k;
	u16 tmp_tile_index;

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	/* Draw the background */	
	// VDP_drawImageEx(BPLAN, &pic00, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
	// vramIndex += pic00.tileset->numTile;
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setVerticalScroll(PLAN_B, 0);
	VDP_setVerticalScroll(PLAN_A, 0);
	VDP_setHorizontalScroll(PLAN_B, 0);
	VDP_setHorizontalScroll(PLAN_A, 0);	

	SYS_enableInts();

	// vramIndex = 0;
	VDP_waitDMACompletion();

	while (1){
		/* Pic 0 */
		// tmp_tile_index = curTileInd;
		SYS_disableInts();
		VDP_drawImageEx(APLAN, &pic00, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
		SYS_enableInts();
		RSE_pause(RSE_FRAMES(1*60));

		RSE_pause(RSE_FRAMES(2*60));

		VDP_fadeOut(1, 63, 16, FALSE);
		RSE_turn_screen_to_black();		
		VDP_waitDMACompletion();
		for(i = 0; i  < 224 >> 3; i++)
		{
			VDP_waitVSync();
			RSE_clearTileRowB(i);
			RSE_clearTileRowA(i);
		}		

		/* Pic 1 */

		// curTileInd = tmp_tile_index;
		SYS_disableInts();
		VDP_drawImageEx(APLAN, &pic01a, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 12 >> 3, TRUE, TRUE);
		VDP_waitDMACompletion();
		VDP_drawImageEx(BPLAN, &pic01b, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex + pic01a.tileset->numTile), 0, 12 >> 3, TRUE, TRUE);
		SYS_enableInts();

		RSE_pause(RSE_FRAMES(3*60));
		VDP_fadeOut(1, 63, 16, FALSE);
		RSE_turn_screen_to_black();		
		VDP_waitDMACompletion();
		for(i = 0; i  < 224 >> 3; i++)
		{
			VDP_waitVSync();
			RSE_clearTileRowB(i);
			RSE_clearTileRowA(i);
		}		

		/* Pic 2 */

		// curTileInd = tmp_tile_index;
		SYS_disableInts();
		VDP_drawImageEx(APLAN, &pic02a, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), (320 - 256) >> 4, 0, TRUE, TRUE);
		VDP_waitDMACompletion();
		VDP_drawImageEx(BPLAN, &pic02b, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex + pic02a.tileset->numTile), (320 - 256) >> 4, 0, TRUE, TRUE);
		SYS_enableInts();

		RSE_pause(RSE_FRAMES(3*60));
		VDP_fadeOut(1, 63, 16, FALSE);
		RSE_turn_screen_to_black();		
		VDP_waitDMACompletion();
		for(i = 0; i  < 224 >> 3; i++)
		{
			VDP_waitVSync();
			RSE_clearTileRowB(i);
			RSE_clearTileRowA(i);
		}		

		/* Pic 9 */

		// curTileInd = tmp_tile_index;
		SYS_disableInts();
		VDP_drawImageEx(APLAN, &pic09, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
		SYS_enableInts();

		RSE_pause(RSE_FRAMES(3*60));
		VDP_fadeOut(1, 63, 16, FALSE);
		RSE_turn_screen_to_black();		
		VDP_waitDMACompletion();
		for(i = 0; i  < 224 >> 3; i++)
		{
			VDP_waitVSync();
			RSE_clearTileRowB(i);
			RSE_clearTileRowA(i);
		}		
	}
}