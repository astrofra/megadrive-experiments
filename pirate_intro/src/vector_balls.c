#include <genesis.h>
#include <gfx.h>
#include "ball_coords.h"
#include "quicksort.h"
#include "writer.h"
#include "transition_helper.h"

#define	MAX_VECTOR_BALL 256
#define BALL_COUNT grid_cube_small_VTX_COUNT
#define VECTOR_BALL_ARRAY vb_grid_cube_small_vertex_pos
#define VBALL_DISTANCE 1100

#define VBALL_PHASE_INTRO_SCROLL	0
#define VBALL_PHASE_INTRO_FADE		1
#define VBALL_PHASE_BEGIN			2
#define VBALL_PHASE_FADETOWHITE		3
#define VBALL_PHASE_FADEIN			4
#define VBALL_PHASE_RUN				5
#define VBALL_PHASE_FADEOUT			6
#define VBALL_NEXT_OBJECT			7
#define VBALL_PHASE_QUIT			8

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

static u16 loop, shadow_idx, i, j;
static 	u16 zsort_switch = 0;
static 	Sprite *sprites[MAX_VECTOR_BALL];
static 	struct  QSORT_ENTRY vball_zsort[MAX_VECTOR_BALL];
static 	short xc, yc;
static	short rx, ry;
static 	u16 angle;
static 	u16 sec_angle, sec_angle_step;
static 	u8 vball_phase;
static 	u16 vball_timer;
static 	const Animation *animation;
static 	u16 frameInd;
static	u8 ball_count;
static	Vect3D_f16 *vector_ball_array;
static	u8 object_idx;

static short x, y, z;
static Vect3D_f16 _vtx, t_vtx[MAX_VTX_COUNT];
static fix16 _cosx, _sinx, _cosy, _siny, cs, cc, ss, sc;
// static u16 distance = 1100;
static short x_screen, y_screen, x_screen_shadow, y_screen_shadow;

void fastVectorBallFX()
{
	inline static void drawVectorBalls(u16 constant_angle, u16 accel_angle)
	{
		/* Get the center of the screen (minus the half width of a vector balls) */
		x_screen_shadow = x_screen + 0x30;
		y_screen_shadow = y_screen + 0x60;

		rx = constant_angle;
		ry = constant_angle >> 1;

		xc = cosFix16(rx << 3) << 2;
		yc = sinFix16(rx << 2);

		rx = constant_angle + (accel_angle >> 3);
		ry = constant_angle + (accel_angle >> 2);

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
		for(loop = 0, shadow_idx = ball_count; loop < ball_count; loop++, shadow_idx++)
		{
			// The balls are processed by Z-order
			// 3D transformation (rotation on X and Y axis)
			j = vball_zsort[loop].index;

			_vtx = vector_ball_array[j];

		    t_vtx[j].x = fix16Add(fix16Mul(_vtx.x, _sinx), fix16Mul(_vtx.y, _cosx));
		    t_vtx[j].y = fix16Sub(fix16Mul(_vtx.x, cs), fix16Add(fix16Mul(_vtx.y, ss), fix16Mul(_vtx.z, _cosy)));
		    t_vtx[j].z = fix16Sub(fix16Mul(_vtx.x, cc), fix16Mul(_vtx.y, sc) - fix16Mul(_vtx.z, _siny));

		    t_vtx[j].x += xc;
		    t_vtx[j].y += yc;

			//	Isometric projection
		    x = t_vtx[j].x + (t_vtx[j].z >> 3);
		    y = t_vtx[j].y;

		    x >>= 3;
		    y >>= 3;

			z = t_vtx[j].z;
			if (z < FIX16(0.0))
				z = FIX16(0.0);

			z >>= 6;

			if (z > 8)
				z = 8;

			/* Vector ball */
	        sprites[loop]->x = x_screen + x;
	        sprites[loop]->y = y_screen + y;
	        sprites[loop]->status = sprites[loop]->status | 0x0002;

		    /* shadow */
	        sprites[shadow_idx]->x = x_screen_shadow + x;
	        sprites[shadow_idx]->y = y_screen_shadow + (y >> 2);
	        sprites[shadow_idx]->status = sprites[loop]->status | 0x0002;

		    if (zsort_switch & 0x1)
		    {
			    if (sprites[loop]->seqInd != z)
			    {
			        animation = sprites[loop]->animation;
			        frameInd = animation->sequence[z];

			        sprites[loop]->seqInd = z;

			        if (sprites[loop]->frameInd != frameInd)
			        {
			            sprites[loop]->frameInd = frameInd;
			            sprites[loop]->frame = animation->frames[frameInd];
			            sprites[loop]->status |= 0x0040;
			        }
				}
			}
			else
			{
			    if (sprites[shadow_idx]->seqInd != z)
			    {
			        /* shadow */
			        animation = sprites[shadow_idx]->animation;
			        frameInd = animation->sequence[z];

			        sprites[shadow_idx]->seqInd = z;

			        if (sprites[shadow_idx]->frameInd != frameInd)
			        {
			            sprites[shadow_idx]->frameInd = frameInd;
			            sprites[shadow_idx]->frame = animation->frames[frameInd];
			            sprites[shadow_idx]->status |= 0x0040;
			        }		        
			    }
		    }
		}

		/* Z-sort the vector balls */
		if (zsort_switch == 0)
		{
			for(loop = 0; loop < ball_count; loop++)
			{
			    //	Fill the sort table
			    vball_zsort[loop].index = loop;
			    vball_zsort[loop].value = t_vtx[loop].z;
			}

			QuickSort(ball_count, vball_zsort);
		}

		//	Count 16 frames until the next depth sort
		zsort_switch++;
		zsort_switch &= 0x1F;

		SPR_update(sprites, ball_count << 1);
	}	

	SYS_disableInts();

	/*
		Screen setup
	*/

	VDP_setPlanSize(64, 64);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setVerticalScroll(PLAN_A, -64);
	VDP_setHilightShadow(1);
	SPR_init(0,0,0);
	vramIndex = fontIndex;

	object_idx = 0;
	ball_count = BALL_COUNT;
	vector_ball_array = VECTOR_BALL_ARRAY;	

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < ball_count; loop++)
	{
	    sprites[loop] = SPR_addSprite(&ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
		SPR_setAlwaysVisible(sprites[loop], TRUE);
	}

	for(loop = ball_count; loop < ball_count << 1; loop++)
	{
	    sprites[loop] = SPR_addSprite(&ball_shadow, 0, 0, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, 0));
		SPR_setAlwaysVisible(sprites[loop], TRUE);
	}

	VDP_drawImageEx(PLAN_B, &checkboard_0, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 96) >> 3, FALSE, TRUE);
	vramIndex += checkboard_0.tileset->numTile;
	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &checkboard_1, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 80 >> 3, (224 - 96) >> 3, FALSE, TRUE);
	vramIndex += checkboard_1.tileset->numTile;
	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &checkboard_2, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 160 >> 3, (224 - 96) >> 3, FALSE, TRUE);
	vramIndex += checkboard_2.tileset->numTile;
	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &checkboard_3, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 240 >> 3, (224 - 96) >> 3, FALSE, TRUE);
	vramIndex += checkboard_3.tileset->numTile;
	SYS_enableInts(); VDP_waitVSync(); SYS_disableInts();

	VDP_drawImageEx(PLAN_B, &sky, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, vramIndex), 0, ((224 - 96 - 72) >> 3), FALSE, TRUE);
	vramIndex += sky.tileset->numTile;

	SYS_enableInts();

	angle = 0;
	sec_angle = 0;
	sec_angle_step = 0;

	x_screen = (VDP_getScreenWidth() - 32) >> 1;
	x_screen += 0x80;
 	y_screen = (VDP_getScreenHeight() - 32) >> 1;
	y_screen += 0x80;

	vball_phase = VBALL_PHASE_INTRO_SCROLL;
	vball_timer = 0;

	VDP_fadePalTo(PAL0, checkboard_0.palette->data, RSE_FRAMES(8), TRUE);

	while(vball_phase < VBALL_PHASE_QUIT)
	{
		VDP_waitVSync();
		// BMP_showFPS(0);
		drawVectorBalls(angle, sec_angle);
		updateScrollText();
		angle++;

		if ((angle & 0xFE) == 0)
			sec_angle_step += 25;

		sec_angle += sec_angle_step;
		if (sec_angle_step >= 1)
			sec_angle_step--;

		switch(vball_phase)
		{
			case VBALL_PHASE_INTRO_SCROLL:
				VDP_setVerticalScroll(PLAN_B, (easing_table[vball_timer << 4] >> 4) - 64);
				vball_timer++;

				if (vball_timer > 63)
				{
					VDP_fadePalTo(PAL1, sky.palette->data, RSE_FRAMES(32), TRUE);
					VDP_setVerticalScroll(PLAN_B, 0);
					VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_2TILE);
					vball_timer = 0;
					vball_phase++;					
				}			
				break;

			case VBALL_PHASE_INTRO_FADE:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(40))
				{
					vball_timer = 0;
					vball_phase++;					
				}			
				break;

			case VBALL_PHASE_BEGIN:
				VDP_fadePalTo(PAL2, palette_white, RSE_FRAMES(8), TRUE);
				vball_timer = 0;
				vball_phase++;
				break;

			case VBALL_PHASE_FADETOWHITE:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(8))
				{
					if (object_idx & 0x1)
						VDP_fadePalTo(PAL2, ball_metal.palette->data, RSE_FRAMES(16), TRUE);
					else
						VDP_fadePalTo(PAL2, masiaka_title.palette->data, RSE_FRAMES(16), TRUE);
					vball_timer = 0;
					vball_phase++;
				}
				break;				

			case VBALL_PHASE_FADEIN:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(16))
				{
					vball_timer = 0;
					vball_phase++;
				}
				break;

			case VBALL_PHASE_RUN:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(60 * 8))
				{
					VDP_fadeOut(32, 32 + 15, RSE_FRAMES(32), TRUE);
					vball_timer = 0;
					vball_phase++;
				}
				break;

			case VBALL_PHASE_FADEOUT:
				vball_timer++;
				if (vball_timer > RSE_FRAMES(32))
				{
					vball_timer = 0;
					vball_phase++;
				}
				break;

			case VBALL_NEXT_OBJECT:
				object_idx++;
				zsort_switch = 0;

				if (object_idx >= MAX_VBALL_OBJECTS)
				{
					object_idx = 0;
					vball_phase = VBALL_PHASE_QUIT;
				}
				else
					vball_phase = VBALL_PHASE_BEGIN;

				switch(object_idx)
				{

					case 0:
						ball_count = grid_cube_small_VTX_COUNT;
						vector_ball_array = vb_grid_cube_small_vertex_pos;
						break;

					case 1:
						ball_count = sword_VTX_COUNT;
						vector_ball_array = vb_sword_vertex_pos;
						break;

					case 2:
						ball_count = pyramid_VTX_COUNT;
						vector_ball_array = vb_pyramid_vertex_pos;
						break;						
				}
		}
	}

	SPR_end();
	// RSE_resetScrolling();
	// // RSE_writerSetXOffset(0);

	// RSE_turn_screen_to_black();

	// for(j = 0; j  < VDP_getPlanHeight(); j++)
	// {
	// 	VDP_waitVSync();
	// 	RSE_clearTileRowB(j);
	// 	RSE_clearTileRowA(j);
	// }	

	// vramIndex = TILE_USERINDEX;
}