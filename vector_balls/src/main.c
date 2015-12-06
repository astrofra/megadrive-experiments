#include <genesis.h>
#include <gfx.h>
#include "fp_cosine_table.h"
#include "ball_coords.h"

#define	MAX_VECTOR_BALL 256

static void vectorBallFX();

int main(){
	JOY_init();
	vectorBallFX();
	return 0;
}

void drawVectorBalls(Sprite *sprites, u16 angle)
{
	u16 loop;
	short x, y;
	Vect3D_f16 _vtx, t_vtx;
	fix16 _sin, _cos;
	u16 x_screen, y_screen;
	x_screen = (VDP_getScreenWidth() - 32) >> 1;
	y_screen = (VDP_getScreenHeight() - 32) >> 1;

	_cos = cosFix16(angle);
	_sin = sinFix16(angle);

	for(loop = 0; loop < cube_VTX_COUNT; loop++)
	{
		_vtx = vb_cube_vertex_pos[loop];

		//	x' = x cos f - y sin f
		t_vtx.x = fix16Sub(fix16Mul(_vtx.x, _cos), fix16Mul(_vtx.y, _sin));
		//	y' = y cos f + x sin f
		t_vtx.y = fix16Add(fix16Mul(_vtx.y, _cos), fix16Mul(_vtx.x, _sin));

		x = t_vtx.x;
		y = t_vtx.y + (_vtx.z >> 1);

		x >>= 3;
		y >>= 3;

		SPR_setPosition(&sprites[loop], x_screen + x, y_screen + y);
	}

	SPR_update(sprites, cube_VTX_COUNT);
}

static void vectorBallFX(){
	u16 loop;
	Sprite sprites[MAX_VECTOR_BALL];
	u16 angle = 0;
	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);
	/* Set a larger tileplan to be able to scroll */
	SYS_disableInts();

	/* Sprites */
	VDP_setPalette(PAL2, ball_metal.palette->data);
	SPR_init(MAX_VECTOR_BALL);

	for(loop = 0; loop < cube_VTX_COUNT; loop++)
	    SPR_initSprite(&sprites[loop], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	// SPR_setPosition(&sprites[0], (VDP_getScreenWidth() - 32) >> 1, (VDP_getScreenHeight() - 32) >> 1);
    SPR_update(sprites, cube_VTX_COUNT);

	SYS_enableInts();

	VDP_setHInterrupt(1);

	while (TRUE){
		VDP_waitVSync();
		drawVectorBalls(sprites, angle);
		angle = (angle + 1) & (FP_COSINE_TABLE_LEN - 1);
	}
}