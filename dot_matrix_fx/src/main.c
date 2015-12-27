#include <genesis.h>
#include <gfx.h>
#include "img_seq.h"

#define UNPACK_2 TILE_BITS
#define UNPACK_3 (TILE_BITS * 2)
#define UNPACK_4 (TILE_BITS * 3)

#define MASK_1 ((1 << TILE_BITS) - 1)
#define MASK_2 ((1 << (TILE_BITS * 2)) - 1)
#define MASK_3 ((1 << (TILE_BITS * 3)) - 1)
#define MASK_4 ((1 << (TILE_BITS * 4)) - 1)


static void RSE_gridTileAnimation();

int main()
{
	RSE_gridTileAnimation();
	return 0;
}

static void RSE_gridTileAnimation()
{
	u16 vblCount = 0;
	u16 vramIndex = TILE_USERINDEX;

	static void drawDotMatrix(void)
	{
		u16 i = 0, j = 0, k, luma, unpacked_luma;
		k = 0;
		while(k < tore_tunnel_IMG_LEN)
		{
			k++;
			luma = tore_tunnel_seq[k + (vblCount * tore_tunnel_IMG_LEN)];
			unpacked_luma = luma & MASK_1;
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + unpacked_luma, i++, j);
			unpacked_luma = (luma & MASK_2) >> UNPACK_2;
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + unpacked_luma, i++, j);
			unpacked_luma = (luma & MASK_3) >> UNPACK_3;
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + unpacked_luma, i++, j);
			unpacked_luma = (luma & MASK_4) >> UNPACK_4;
			VDP_setTileMapXY(VDP_PLAN_A, TILE_USERINDEX + unpacked_luma, i++, j);
			if (i >= 40)
			{
				i = 0;
				j++;
			}
		}
	}
	// 				VDP_setTileMapXY(VDP_PLAN_A, 0, current_char_x, 22);

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(64, 32);

	/* Load the fond tiles */
	VDP_drawImageEx(APLAN, &pat_round, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += pat_round.tileset->numTile;

	// VDP_clearPlan(APLAN, 0);
	// VDP_clearPlan(BPLAN, 0);

	VDP_setPalette(PAL0, pat_round.palette->data);

	SYS_enableInts();

	while (TRUE)
	{
		// BMP_showFPS(0);
		VDP_waitVSync();
		drawDotMatrix();
		vblCount++;
		if (vblCount >= tore_tunnel_IMG_COUNT)
			vblCount = 0;


	}
}