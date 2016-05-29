#include <genesis.h>
#include <gfx.h>
#include "ball_coords.h"
#include "quicksort.h"
#include "writer.h"
#include "transition_helper.h"

#define	MAX_VECTOR_BALL 256
#define BALL_COUNT grid_cube_small_VTX_COUNT
#define VECTOR_BALL_ARRAY vb_grid_cube_small_vertex_pos

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void RSE_vectorBallFX()
{
	u16 loop, j;
	u16 zsort_switch = 0;
	Sprite sprites[MAX_VECTOR_BALL];
	struct  QSORT_ENTRY vball_zsort[MAX_VECTOR_BALL];
	u16 angle;

	static void drawVectorBalls(Sprite *sprites, u16 rx, u16 ry)
	{
		u16 loop;
		short x, y, z, xc, yc, zc;
		Vect3D_f16 _vtx, t_vtx[BALL_COUNT];
		fix16 _cosx, _sinx, _cosy, _siny, cs, cc, ss, sc;
		u16 distance = 1100;
		short x_screen, y_screen;

		/* Get the center of the screen (minus the half width of a vector balls) */
		x_screen = (VDP_getScreenWidth() - 32) >> 1;
		x_screen += 0x80;
		y_screen = (VDP_getScreenHeight() - 32) >> 1;
		y_screen += 0x80;

		xc = cosFix32(rx << 3) >> 2;
		yc = sinFix32(rx << 2) >> 2;
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
		}

		/* Z-sort the vector balls */
		if (zsort_switch == 0)
		{
			for(loop = 0; loop < BALL_COUNT; loop++)
			{
			    //	Fill the sort table
			    vball_zsort[loop].index = loop;
			    vball_zsort[loop].value = t_vtx[loop].z;
			}

			QuickSort(BALL_COUNT, vball_zsort);
		}

		//	Count 16 frames until the next depth sort
		zsort_switch++;
		zsort_switch &= 0x1F;

		/* Display the vector balls using sprites */
		for(loop = 0; loop < BALL_COUNT; loop++)
		{
			j = vball_zsort[loop].index;

			//	Classic 3D -> 2D projection
		    x = (t_vtx[j].x << 10) / (t_vtx[j].z + distance);
		    y = (t_vtx[j].y << 10) / (t_vtx[j].z + distance);		

			x >>= 3;
			y >>= 3;

			z = t_vtx[j].z;
			if (z < FIX32(0.0))
				z = FIX32(0.0);

			z >>= 5;

			if (z > 7)
				z = 7;

	        sprites[loop].x = x_screen + x;
	        sprites[loop].y = y_screen + y;
			// SPR_setPosition(&sprites[loop], x_screen + x, y_screen + y);
			SPR_setFrame(&sprites[loop], z + 21);
		}

		/* Update the whole list of sprites */
		SPR_update(sprites, BALL_COUNT);
	}	

	SYS_disableInts();
	/* Set the palette taken from the vector ball sprite */
	VDP_setPalette(PAL2, ball_metal.palette->data);
	SPR_init(MAX_VECTOR_BALL);

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < BALL_COUNT; loop++)
	{
	    SPR_initSprite(&sprites[loop], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));
		SPR_setAlwaysVisible(&sprites[loop], TRUE);
	}

 //    SPR_update(sprites, BALL_COUNT);

	SYS_enableInts();

	// VDP_waitVSync();

	vramIndex = fontIndex;

	SYS_disableInts();

	VDP_drawImageEx(BPLAN, &vball_bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &vball_fg, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex + vball_bg.tileset->numTile), 0, 0, FALSE, FALSE);

	VDP_setPalette(PAL0, vball_bg.palette->data);
	VDP_setPalette(PAL1, vball_fg.palette->data);
	// VDP_setPalette(PAL2, ball_metal.palette->data);
	// VDP_setPalette(PAL3, ball_metal.palette->data);

	SYS_enableInts();

	angle = 0;

	while (angle < RSE_FRAMES(60 * 8))
	{
		VDP_waitVSync();
		drawVectorBalls(sprites, angle, angle << 1);
		angle++;
	}

	VDP_fadeOut(1, 63, 32, TRUE);

	j = 0;
	while (j < RSE_FRAMES(40))
	{
		VDP_waitVSync();
		// drawVectorBalls(sprites, angle, angle << 1);
		angle++;
		j++;
	}	

	SPR_end();
	RSE_resetScrolling();
	RSE_writerSetXOffset(0);

	RSE_turn_screen_to_black();

	for(j = 0; j  < 224 >> 3; j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(j);
		RSE_clearTileRowA(j);
	}	
}