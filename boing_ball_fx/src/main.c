#include <genesis.h>
#include <gfx.h>

#define SCR_H ((224 >> 3) << 3)
#define BOARD_Y (((SCR_H - 120) >> 3) - 1)
#define BACK_SPEED 8
#define	TABLE_LEN SCR_H
#define PERSPECTIVE_STEP 64

static void beastScrollingFX();

int main(){
	beastScrollingFX();
	return 0;
}

static void beastScrollingFX(){
	s16 hscrollInc = 1;
	s16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;
	s16 i, j, k, l;
	s16 scroll_PLAN_B[PERSPECTIVE_STEP][TABLE_LEN];

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(128, 32);

	/* Draw the foreground */
	VDP_setPalette(PAL1, checkboard.palette->data);
	VDP_drawImageEx(BPLAN, &checkboard, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, BOARD_Y, FALSE, FALSE);
	vramIndex += checkboard.tileset->numTile;
	for(i = 0; i < 6; i++)
		VDP_drawImageEx(BPLAN, &checkback, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, i << 1, FALSE, FALSE);

	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);

	SYS_enableInts();

	for(j = 0; j < PERSPECTIVE_STEP; j++)
		for(i = 0; i < TABLE_LEN; i++)
		{
			if (i < (BOARD_Y << 3))
				l = BACK_SPEED;
			else
				l = (i + (BACK_SPEED + 1) - (BOARD_Y << 3));

			k = ((j - (PERSPECTIVE_STEP >> 1)) * l) >> 6;
			scroll_PLAN_B[j][i] = k - (640 >> 2);
		}

	hscrollInc = -1;
	while (1){
		VDP_waitVSync();
		vblCount += hscrollInc;

		if (vblCount >= PERSPECTIVE_STEP)
		{
			vblCount = PERSPECTIVE_STEP - 1;
			hscrollInc = -1;
		}
		else
		if (vblCount < 0)
		{
			vblCount = 0;
			hscrollInc = 1;
		}
		VDP_setHorizontalScrollLine(PLAN_B, 2, scroll_PLAN_B[vblCount], TABLE_LEN, TRUE);
	}
}
