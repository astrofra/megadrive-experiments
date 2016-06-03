#include <genesis.h>
#include <gfx.h>
#include "ball_coords.h"
#include "quicksort.h"
#include "writer.h"
#include "transition_helper.h"

#define	MAX_VECTOR_BALL 256
#define BALL_COUNT grid_cube_small_VTX_COUNT
#define VECTOR_BALL_ARRAY vb_grid_cube_small_vertex_pos

#define VBALL_PHASE_BEGIN		0
#define VBALL_PHASE_SPR_FADING	1
#define VBALL_PHASE_BG_FADING	2
#define VBALL_PHASE_FG_FADING	3
#define VBALL_PHASE_RUN			4
#define VBALL_PHASE_FADE		5
#define VBALL_PHASE_QUIT		6

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void RSE_vectorBallFX()
{
	u16 loop, i, j;
	u16 zsort_switch = 0;
	Sprite sprites[MAX_VECTOR_BALL];
	struct  QSORT_ENTRY vball_zsort[MAX_VECTOR_BALL];
	short xc, yc, zc;
	u16 angle;
	u8 vball_phase = VBALL_PHASE_BEGIN;
	u16 vball_timer = 0;

	static void drawVectorBalls(Sprite *sprites, u16 rx, u16 ry)
	{
		u16 loop;
		short x, y, z;
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

	VDP_setPlanSize(64, 32);
	SPR_init(MAX_VECTOR_BALL);

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < BALL_COUNT; loop++)
	{
	    SPR_initSprite(&sprites[loop], &ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0));
		SPR_setAlwaysVisible(&sprites[loop], TRUE);
	}

 //    SPR_update(sprites, BALL_COUNT);

	SYS_enableInts();

	for(j = 0; j  < VDP_getPlanHeight(); j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(j);
		RSE_clearTileRowA(j);
	}

	vramIndex = 8; // fontIndex;

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &vball_bg_a, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += vball_bg_a.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &vball_bg_a2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 56 >> 3, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += vball_bg_a2.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &vball_bg_b, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 224 >> 4, FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += vball_bg_b.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(BPLAN, &vball_bg_b2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, (224 >> 4) + (56 >> 3), FALSE, TRUE);
	SYS_enableInts();
	VDP_waitDMACompletion();
	VDP_waitVSync();
	vramIndex += vball_bg_b2.tileset->numTile;

	SYS_disableInts();
	VDP_drawImageEx(APLAN, &vball_fg_a, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 136) >> 3, FALSE, TRUE);

	SYS_enableInts();

	angle = 0;

	while(vball_phase < VBALL_PHASE_QUIT)
	{
		VDP_waitVSync();
		drawVectorBalls(sprites, angle, angle << 1);
		VDP_setHorizontalScroll(PLAN_B, ((xc) >> 6) - 16);
		VDP_setHorizontalScroll(PLAN_A, ((-xc) >> 4) - 32);		
		angle++;

		switch(vball_phase)
		{
			case VBALL_PHASE_BEGIN:
				VDP_fadePalTo(PAL2, ball_metal.palette->data, RSE_FRAMES(16), TRUE);
				vball_timer = 0;
				vball_phase++;
				break;

			case VBALL_PHASE_SPR_FADING:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(16 * 2))
				{
					VDP_fadePalTo(PAL0, vball_bg_a.palette->data, RSE_FRAMES(45), TRUE);
					vball_timer = 0;
					vball_phase++;
				}
				break;				

			case VBALL_PHASE_BG_FADING:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(130))
				{
					VDP_fadePalTo(PAL1, vball_fg_a.palette->data, RSE_FRAMES(32), TRUE);
					vball_timer = 0;
					vball_phase++;
				}
				break;

			case VBALL_PHASE_FG_FADING:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(32 * 2))
				{
					vball_timer = 0;
					vball_phase++;
				}
				break;				

			case VBALL_PHASE_RUN:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(60 * 8))
				{
					VDP_fadeOut(1, 63, RSE_FRAMES(32), TRUE);
					vball_timer = 0;
					vball_phase++;
				}
				break;

			case VBALL_PHASE_FADE:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(32))
				{
					vball_timer = 0;
					vball_phase++;
				}
				break;				
		}
	}
	// while (angle < RSE_FRAMES(60 * 10))
	// {
	// 	VDP_waitVSync();
	// 	drawVectorBalls(sprites, angle, angle << 1);
	// 	angle++;
	// }

	// VDP_fadeOut(1, 63, 32, TRUE);

	// i = 0;
	// while (i < RSE_FRAMES(40))
	// {
	// 	VDP_waitVSync();
	// 	drawVectorBalls(sprites, angle, angle << 1);
	// 	angle++;
	// 	i++;
	// }	

	SPR_end();
	RSE_resetScrolling();
	RSE_writerSetXOffset(0);

	RSE_turn_screen_to_black();

	for(j = 0; j  < VDP_getPlanHeight(); j++)
	{
		VDP_waitVSync();
		RSE_clearTileRowB(j);
		RSE_clearTileRowA(j);
	}	

	vramIndex = TILE_USERINDEX;
}