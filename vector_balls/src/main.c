#include <genesis.h>
#include <gfx.h>
#include "fp_cosine_table.h"
#include "ball_coords.h"

#define	MAX_VECTOR_BALL 256
#define BALL_COUNT grid_cube_small_VTX_COUNT
#define VECTOR_BALL_ARRAY vb_grid_cube_small_vertex_pos

static void vectorBallFX();

int main(){
	JOY_init();
	vectorBallFX();
	return 0;
}

void drawVectorBalls(Sprite *sprites, u16 rx, u16 ry)
{
	u16 loop;
	short x, y;
	Vect3D_f16 _vtx, t_vtx;
	fix16 _cosx, _sinx, _cosy, _siny, cs, cc, ss, sc;
	u16 distance = 1100;
	u16 x_screen, y_screen;

	x_screen = (VDP_getScreenWidth() - 32) >> 1;
	y_screen = (VDP_getScreenHeight() - 32) >> 1;

	_cosx = cosFix16(rx);
	_sinx = sinFix16(rx);
	_cosy = cosFix16(ry);
	_siny = sinFix16(ry);
	cs = fix16Mul(_cosx, _siny);
	ss = fix16Mul(_siny, _sinx);
	cc = fix16Mul(_cosx, _cosy);
	sc = fix16Mul(_sinx, _cosy);

	for(loop = 0; loop < BALL_COUNT; loop++)
	{
		_vtx = VECTOR_BALL_ARRAY[loop];

		//	1D rotation (on Y axis)
		/*
			//	x' = x cos f - y sin f
			t_vtx.x = fix16Sub(fix16Mul(_vtx.x, _cosy), fix16Mul(_vtx.y, _siny));
			//	y' = y cos f + x sin f
			t_vtx.y = fix16Add(fix16Mul(_vtx.y, _cosy), fix16Mul(_vtx.x, _siny));
			t_vtx.z = _vtx.z;
		*/

		//	2D rotation (on X and Y axis)
	    t_vtx.x = fix16Add(fix16Mul(_vtx.x, _sinx), fix16Mul(_vtx.y, _cosx));
	    t_vtx.y = fix16Sub(fix16Mul(_vtx.x, cs), fix16Add(fix16Mul(_vtx.y, ss), fix16Mul(_vtx.z, _cosy)));
	    t_vtx.z = fix16Sub(fix16Mul(_vtx.x, cc), fix16Mul(_vtx.y, sc) - fix16Mul(_vtx.z, _siny));

	    //	Isometric 2D projection
	    /*
			x = t_vtx.x;
			y = t_vtx.y + (t_vtx.z >> 1);
		*/

		//	Classic 3D -> 2D projection
	    x = (t_vtx.x << 10) / (t_vtx.z + distance);
	    y = (t_vtx.y << 10) / (t_vtx.z + distance);		

		x >>= 3;
		y >>= 3;

		SPR_setPosition(&sprites[loop], x_screen + x, y_screen + y);
	}

	SPR_update(sprites, BALL_COUNT);
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

	for(loop = 0; loop < BALL_COUNT; loop++)
	    SPR_initSprite(&sprites[loop], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	// SPR_setPosition(&sprites[0], (VDP_getScreenWidth() - 32) >> 1, (VDP_getScreenHeight() - 32) >> 1);
    SPR_update(sprites, BALL_COUNT);

	SYS_enableInts();

	VDP_setHInterrupt(1);

	while (TRUE){
		VDP_waitVSync();
		drawVectorBalls(sprites, angle & (FP_COSINE_TABLE_LEN - 1), (angle << 1) & (FP_COSINE_TABLE_LEN - 1));
		angle++;
	}
}