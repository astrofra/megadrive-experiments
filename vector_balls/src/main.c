#include <genesis.h>
#include <gfx.h>
#include "ball_coords.h"
#include "quicksort.h"

#define	MAX_VECTOR_BALL 256
#define BALL_COUNT grid_cube_small_VTX_COUNT
#define VECTOR_BALL_ARRAY vb_grid_cube_small_vertex_pos

static void vectorBallFX();

int main(){
	JOY_init();
	vectorBallFX();
	return 0;
}

static void vectorBallFX(){
	u16 loop, j;
	Sprite sprites[MAX_VECTOR_BALL];
	struct  QSORT_ENTRY vball_zsort[MAX_VECTOR_BALL];
	u16 angle = 0;

	static void drawVectorBalls(Sprite *sprites, u16 rx, u16 ry)
	{
		u16 loop;
		short x, y;
		Vect3D_f16 _vtx, t_vtx[BALL_COUNT];
		fix16 _cosx, _sinx, _cosy, _siny, cs, cc, ss, sc;
		u16 distance = 1100;
		u16 x_screen, y_screen;

		/* Get the center of the screen (minus the half width of a vector balls) */
		x_screen = (VDP_getScreenWidth() - 32) >> 1;
		y_screen = (VDP_getScreenHeight() - 32) >> 1;

		/* precalculate the rotation */
		_cosx = cosFix16(rx);
		_sinx = sinFix16(rx);
		_cosy = cosFix16(ry);
		_siny = sinFix16(ry);
		cs = fix16Mul(_cosx, _siny);
		ss = fix16Mul(_siny, _sinx);
		cc = fix16Mul(_cosx, _cosy);
		sc = fix16Mul(_sinx, _cosy);

		/* rotate the vector balls */
		for(loop = 0; loop < BALL_COUNT; loop++)
		{
			_vtx = VECTOR_BALL_ARRAY[loop];

			//	2D rotation (on X and Y axis)
		    t_vtx[loop].x = fix16Add(fix16Mul(_vtx.x, _sinx), fix16Mul(_vtx.y, _cosx));
		    t_vtx[loop].y = fix16Sub(fix16Mul(_vtx.x, cs), fix16Add(fix16Mul(_vtx.y, ss), fix16Mul(_vtx.z, _cosy)));
		    t_vtx[loop].z = fix16Sub(fix16Mul(_vtx.x, cc), fix16Mul(_vtx.y, sc) - fix16Mul(_vtx.z, _siny));

		    //	Fill the sort table
		    vball_zsort[loop].index = loop;
		    vball_zsort[loop].value = t_vtx[loop].z;

		}

		/* Z-sort the vector balls */
		QuickSort(BALL_COUNT, vball_zsort);

		/* Display the vector balls using sprites */
		for(loop = 0; loop < BALL_COUNT; loop++)
		{
			j = vball_zsort[loop].index;

			//	Classic 3D -> 2D projection
		    x = (t_vtx[j].x << 10) / (t_vtx[j].z + distance);
		    y = (t_vtx[j].y << 10) / (t_vtx[j].z + distance);		

			x >>= 3;
			y >>= 3;

			SPR_setPosition(&sprites[loop], x_screen + x, y_screen + y);
		}

		/* Update the whole list of sprites */
		SPR_update(sprites, BALL_COUNT);
	}	
	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	SYS_disableInts();

	/* Set the palette taken from the vector ball sprite */
	VDP_setPalette(PAL2, ball_metal.palette->data);
	SPR_init(MAX_VECTOR_BALL);

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < BALL_COUNT; loop++)
	    SPR_initSprite(&sprites[loop], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));

    SPR_update(sprites, BALL_COUNT);

	SYS_enableInts();

	VDP_setHInterrupt(1);

	while (TRUE){
		VDP_waitVSync();
		drawVectorBalls(sprites, angle & 0x3FF, (angle << 1) & 0x3FF); // 0x3FF = size of SGDK cosine table
		angle++;
	}
}