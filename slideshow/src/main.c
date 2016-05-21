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

	while (1){
		SYS_disableInts();
		VDP_drawImageEx(APLAN, &pic00, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
		SYS_enableInts();
		RSE_pause(RSE_FRAMES(1*60));

		// k = RSE_FRAMES(240 - 224);
		// for(i = 0; i < k; i++)
		// {
		// 	VDP_waitVSync();
		// 	// j = easing_table[i * 1024 / k];
		// 	// j = (j * k) >> 11;
		// 	VDP_setVerticalScroll(PLAN_A, k);
		// }

		RSE_pause(RSE_FRAMES(2*60));

		VDP_fadeOut(1, 63, 16, FALSE);
		RSE_turn_screen_to_black();
		VDP_clearPlan(APLAN, 0);
		VDP_clearPlan(BPLAN, 0);		

		SYS_disableInts();
		VDP_drawImageEx(APLAN, &pic09, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, 0, TRUE, TRUE);
		SYS_enableInts();

		RSE_pause(RSE_FRAMES(3*60));
		VDP_fadeOut(1, 63, 16, FALSE);
		RSE_turn_screen_to_black();
		VDP_clearPlan(APLAN, 0);
		VDP_clearPlan(BPLAN, 0);	
	}
}