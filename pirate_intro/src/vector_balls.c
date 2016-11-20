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

static u16 loop, shadow_idx, i, j;
static 	u16 zsort_switch = 0;
static 	Sprite *sprites[MAX_VECTOR_BALL];
static 	struct  QSORT_ENTRY vball_zsort[MAX_VECTOR_BALL];
static 	short xc, yc, zc;
static 	u16 angle;
static 	u8 vball_phase = VBALL_PHASE_BEGIN;
static 	u16 vball_timer = 0;
static 	const Animation *animation;
static 	u16 frameInd;

static short x, y, z;
static Vect3D_f16 _vtx, t_vtx[BALL_COUNT];
static fix16 _cosx, _sinx, _cosy, _siny, cs, cc, ss, sc;
// static u16 distance = 1100;
static short x_screen, y_screen, x_screen_shadow, y_screen_shadow;

void fastVectorBallFX()
{
	inline static void drawVectorBalls(u16 rx, u16 ry)
	{
		// u16 loop;

		/* Get the center of the screen (minus the half width of a vector balls) */
		x_screen_shadow = x_screen + 0x30;
		y_screen_shadow = y_screen + 0x60;

		xc = cosFix16(rx << 3) << 1;
		yc = sinFix16(rx << 2);
		zc = sinFix16(rx << 2) << 1;

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
		for(loop = 0, shadow_idx = BALL_COUNT; loop < BALL_COUNT; loop++, shadow_idx++)
		{
			// The balls are processed by Z-order
			// 3D transformation (rotation on X and Y axis)
			j = vball_zsort[loop].index;

			_vtx = VECTOR_BALL_ARRAY[j];

		    t_vtx[j].x = fix16Add(fix16Mul(_vtx.x, _sinx), fix16Mul(_vtx.y, _cosx));
		    t_vtx[j].y = fix16Sub(fix16Mul(_vtx.x, cs), fix16Add(fix16Mul(_vtx.y, ss), fix16Mul(_vtx.z, _cosy)));
		    t_vtx[j].z = fix16Sub(fix16Mul(_vtx.x, cc), fix16Mul(_vtx.y, sc) - fix16Mul(_vtx.z, _siny));

		    t_vtx[j].x += xc;
		    t_vtx[j].y += yc;
		    t_vtx[j].z += zc;

			//	3D -> 2D projection
		    x = (t_vtx[j].x << 7) / (t_vtx[j].z + VBALL_DISTANCE);
		    y = (t_vtx[j].y << 7) / (t_vtx[j].z + VBALL_DISTANCE);

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

		SPR_update(sprites, BALL_COUNT * 2);
	}	

	SYS_disableInts();

	/*
		Screen setup
	*/

	VDP_setPlanSize(64, 32);
	VDP_setHilightShadow(1); 	
	SPR_init(0,0,0);
	vramIndex = 8; // fontIndex;

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < BALL_COUNT; loop++)
	{
	    sprites[loop] = SPR_addSprite(&ball_metal, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
		SPR_setAlwaysVisible(sprites[loop], TRUE);
	}

	for(loop = BALL_COUNT; loop < BALL_COUNT * 2; loop++)
	{
	    sprites[loop] = SPR_addSprite(&ball_shadow, 0, 0, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, 0));
		SPR_setAlwaysVisible(sprites[loop], TRUE);
	}

 //    SPR_update(sprites, BALL_COUNT);

	// for(j = 0; j  < VDP_getPlanHeight(); j++)
	// {
	// 	VDP_waitVSync();
	// 	RSE_clearTileRowB(j);
	// 	RSE_clearTileRowA(j);
	// }

	VDP_drawImageEx(PLAN_A, &checkboard, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, vramIndex), 0, (224 - 96) >> 3, TRUE, TRUE);
	vramIndex += checkboard.tileset->numTile;

	SYS_enableInts();

	angle = 0;
	x_screen = (VDP_getScreenWidth() - 32) >> 1;
	x_screen += 0x80;
	y_screen = (VDP_getScreenHeight() - 32) >> 1;
	y_screen += 0x80;	

	VDP_fadePalTo(PAL2, ball_metal.palette->data, RSE_FRAMES(16), TRUE);

	while(vball_phase < VBALL_PHASE_QUIT)
	{
		VDP_waitVSync();
		BMP_showFPS(0);
		drawVectorBalls(angle, angle << 1);
		// VDP_setHorizontalScroll(PLAN_B, ((xc) >> 6) - 16);
		// VDP_setHorizontalScroll(PLAN_A, ((-xc) >> 4) - 32);		
		angle++;

		// switch(vball_phase)
		// {
		// 	case VBALL_PHASE_BEGIN:
		// 		VDP_fadePalTo(PAL2, ball_metal.palette->data, RSE_FRAMES(16), TRUE);
		// 		vball_timer = 0;
		// 		vball_phase++;
		// 		break;

		// 	case VBALL_PHASE_SPR_FADING:
		// 		vball_timer++;
		// 		if (vball_timer > RSE_FRAMES(16 * 2))
		// 		{
		// 			VDP_fadePalTo(PAL0, vball_bg_a.palette->data, RSE_FRAMES(45), TRUE);
		// 			vball_timer = 0;
		// 			vball_phase++;
		// 		}
		// 		break;				

		// 	case VBALL_PHASE_BG_FADING:
		// 		vball_timer++;
		// 		if (vball_timer > RSE_FRAMES(130))
		// 		{
		// 			VDP_fadePalTo(PAL1, vball_fg_a.palette->data, RSE_FRAMES(32), TRUE);
		// 			vball_timer = 0;
		// 			vball_phase++;
		// 		}
		// 		break;

		// 	case VBALL_PHASE_FG_FADING:
		// 		vball_timer++;
		// 		if (vball_timer > RSE_FRAMES(32 * 2))
		// 		{
		// 			vball_timer = 0;
		// 			vball_phase++;
		// 		}
		// 		break;				

		// 	case VBALL_PHASE_RUN:
		// 		vball_timer++;
		// 		if (vball_timer > RSE_FRAMES(60 * 7))
		// 		{
		// 			VDP_fadeOut(1, 63, RSE_FRAMES(32), TRUE);
		// 			vball_timer = 0;
		// 			vball_phase++;
		// 		}
		// 		break;

		// 	case VBALL_PHASE_FADE:
		// 		vball_timer++;
		// 		if (vball_timer > RSE_FRAMES(32))
		// 		{
		// 			vball_timer = 0;
		// 			vball_phase++;
		// 		}
		// 		break;				
		// }
	}

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