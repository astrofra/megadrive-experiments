#include <genesis.h>
#include <gfx.h>
#include "edges.h"

#define	MAX_VECTOR_BALL 64
#define BALL_COUNT cube_VTX_COUNT
#define VECTOR_BALL_ARRAY vb_cube_vertex_pos

static void fastCubeFX();

int main(){
	fastCubeFX();
	return 0;
}

#define DRAW_MIDDLE_SPRITE(idx, x1, y1, x2, y2) \
{	\
	u16 x3, y3;	\
	x3 = (x1 + x2) >> 1;	\
	y3 = (y1 + y2) >> 1;	\
	\
    sprites[idx].x = x3;	\
    sprites[idx].y = y3;	\
    idx++;	\
	\
    sprites[idx].x = (x1 + x3) >> 1;	\
    sprites[idx].y = (y1 + y3) >> 1;	\
    idx++;	\
	\
    sprites[idx].x = (x2 + x3) >> 1;	\
    sprites[idx].y = (y2 + y3) >> 1;	\
    idx++;	\
};

static void fastCubeFX(){
	u16 loop, j;
	Sprite sprites[MAX_VECTOR_BALL];
	u16 angle = 0;

	static void drawDots(Sprite *sprites, u16 rx, u16 ry)
	{
		u16 loop;
		short x, y, z, xc, yc, zc;
		Vect3D_f16 _vtx, t_vtx[BALL_COUNT];
		Vect2D_s16 t_vtx_2d[BALL_COUNT];
		;
		fix16 _cosx, _sinx, _cosy, _siny, cs, cc, ss, sc;
		u16 distance = 1100;
		short x_screen, y_screen;

		/* Get the center of the screen (minus the half width of a vector balls) */
		x_screen = (VDP_getScreenWidth() - 32) >> 1;
		x_screen += 0x80;
		y_screen = (VDP_getScreenHeight() - 32) >> 1;
		y_screen += 0x80;

		xc = cosFix32(rx << 4) >> 2;
		yc = sinFix32(rx << 3) >> 2;
		zc = sinFix32(rx << 2) >> 2;

		/* precalculate the rotation */
		_cosx = cosFix32(rx);
		_sinx = sinFix32(rx);
		_cosy = cosFix32(ry);
		_siny = sinFix32(ry);
		cs = fix32Mul(_cosx, _siny);
		ss = fix32Mul(_siny, _sinx);
		cc = fix32Mul(_cosx, _cosy);
		sc = fix32Mul(_sinx, _cosy);

		/* rotate the vector balls */
		u16 prev_x, prev_y;

		for(loop = 0; loop < BALL_COUNT; loop++)
		{
			_vtx = VECTOR_BALL_ARRAY[loop];

			//	2D rotation (on X and Y axis)
		    t_vtx[loop].x = fix32Add(fix32Mul(_vtx.x, _sinx), fix32Mul(_vtx.y, _cosx));
		    t_vtx[loop].y = fix32Sub(fix32Mul(_vtx.x, cs), fix32Add(fix32Mul(_vtx.y, ss), fix32Mul(_vtx.z, _cosy)));
		    t_vtx[loop].z = fix32Sub(fix32Mul(_vtx.x, cc), fix32Mul(_vtx.y, sc) - fix32Mul(_vtx.z, _siny));

		    t_vtx[loop].x += xc;
		    t_vtx[loop].y += yc;
		    t_vtx[loop].z += zc;

			/* Display the vector balls using sprites */
			//	Classic 3D -> 2D projection
			t_vtx_2d[loop].x = x_screen + (((t_vtx[loop].x << 10) / (t_vtx[loop].z + distance)) >> 3);
			t_vtx_2d[loop].y = y_screen + (((t_vtx[loop].y << 10) / (t_vtx[loop].z + distance)) >> 3);
		}

		for(loop = 0; loop < BALL_COUNT; loop++)
		{
	        sprites[loop].x = t_vtx_2d[loop].x;
	        sprites[loop].y = t_vtx_2d[loop].y;			
		}

		/* Face #0 */
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[0].x, t_vtx_2d[0].y, t_vtx_2d[1].x, t_vtx_2d[1].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[1].x, t_vtx_2d[1].y, t_vtx_2d[2].x, t_vtx_2d[2].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[2].x, t_vtx_2d[2].y, t_vtx_2d[3].x, t_vtx_2d[3].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[0].x, t_vtx_2d[0].y, t_vtx_2d[3].x, t_vtx_2d[3].y);

		/* Face #1 */
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[4].x, t_vtx_2d[4].y, t_vtx_2d[5].x, t_vtx_2d[5].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[6].x, t_vtx_2d[6].y, t_vtx_2d[5].x, t_vtx_2d[5].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[6].x, t_vtx_2d[6].y, t_vtx_2d[7].x, t_vtx_2d[7].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[4].x, t_vtx_2d[4].y, t_vtx_2d[7].x, t_vtx_2d[7].y);

		/* Vertical edges */
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[0].x, t_vtx_2d[0].y, t_vtx_2d[4].x, t_vtx_2d[4].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[1].x, t_vtx_2d[1].y, t_vtx_2d[5].x, t_vtx_2d[5].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[2].x, t_vtx_2d[2].y, t_vtx_2d[6].x, t_vtx_2d[6].y);
		DRAW_MIDDLE_SPRITE(loop, t_vtx_2d[3].x, t_vtx_2d[3].y, t_vtx_2d[7].x, t_vtx_2d[7].y);

		/* Update the whole list of sprites */
		SPR_update(sprites, loop);
	}	

	SYS_disableInts();
	
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	/* Set the palette taken from the vector ball sprite */
	VDP_setPalette(PAL2, fast_cube_dot.palette->data);
	SPR_init(MAX_VECTOR_BALL);

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < MAX_VECTOR_BALL; loop++)
	    SPR_initSprite(&sprites[loop], &fast_cube_dot, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));

    SPR_update(sprites, MAX_VECTOR_BALL);

	SYS_enableInts();

	while (TRUE){
		VDP_waitVSync();
		BMP_showFPS(1);
		drawDots(sprites, angle, angle << 2);
		angle++;
	}
}