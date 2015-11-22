//-----------------------------------------------
// 3D flat shaded routine with depth sort
// Based on SGDK's 3D samples
// Fra^Resistance
//-----------------------------------------------

#include "genesis.h"
#include "meshs.h"
#include "quicksort.h"
#include "RSE_3DFlatShadedScreen.h"

extern Mat3D_f16 MatInv;
extern Mat3D_f16 Mat;

u16 zsort_switch;

const Vect3D_f16 *mesh_coord;
const u16 *mesh_poly_ind;
const u16 *mesh_line_ind;
const Vect3D_f16 *mesh_face_norm;
u16 vtx_count;
// u16 poly_count;

struct  QSORT_ENTRY poly_zsort[MAX_POINTS];

void handleJoyEvent(u16 joy, u16 changed, u16 state);
void RSE_3DFlatShadedScreen(void);

int main()
{
	VDP_setScreenWidth256();
	VDP_setHInterrupt(0);
	VDP_setHilightShadow(0);

    // speed up controller checking
    JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
    JOY_setSupport(PORT_2, JOY_SUPPORT_OFF);

    JOY_setEventHandler(handleJoyEvent);

    BMP_init(TRUE, PAL0, FALSE);

	RSE_3DFlatShadedScreen();
}

void inline updatePointsPos(struct rendering_context *ctx)
{
    // transform 3D point
    M3D_transform(&(ctx->transformation), mesh_coord, ctx->pts_3D, vtx_count);
    // project 3D point (f16) to 2D point (s16)
    M3D_project_s16(ctx->pts_3D, ctx->pts_2D, vtx_count);
}

void inline drawPoints(u8 col, struct rendering_context *ctx)
{
    Vect2D_s16 v[4];
    const Vect3D_f16 *norm;
    const u16 *poly_ind;
    u16 i, j;
    fix16 z_sum;

    norm = mesh_face_norm;
    poly_ind = mesh_poly_ind;

	//  Depth sort the polygons
	if (zsort_switch == 0)
	{
		//	Feed an index table with the sum of the Z coordinate
		//	of each polygon in the current mesh
	    for(i = 0; i < metacube_FACE_COUNT; i++)
	    {
	        j = i << 2;
	        poly_zsort[i].index = i;

	        z_sum = fix16Add(fix16Add(ctx->pts_3D[poly_ind[j]].z, ctx->pts_3D[poly_ind[j+1]].z), fix16Add(ctx->pts_3D[poly_ind[j+2]].z, ctx->pts_3D[poly_ind[j+3]].z));
	        poly_zsort[i].value = z_sum;
	    }

	    //	Quicksort the table and order the polygons by depth
	    QuickSort(metacube_FACE_COUNT, poly_zsort);
	}

    //	Count 16 frames until the next depth sort
	zsort_switch++;
	zsort_switch &= 0xF;

    //  Draws the polygons
    i = metacube_FACE_COUNT;

    while(i--)
    {
        Vect2D_s16 *pt_dst = v;
        fix16 dp;
        u8 col = 2;

        poly_ind = &mesh_poly_ind[poly_zsort[i].index << 2];

        *pt_dst++ = ctx->pts_2D[*poly_ind++];
        *pt_dst++ = ctx->pts_2D[*poly_ind++];
        *pt_dst++ = ctx->pts_2D[*poly_ind++];
        *pt_dst = ctx->pts_2D[*poly_ind++];

        //	If the polygon is facing the camera
        if (!BMP_isPolygonCulled(v, 4))
        {
        	//	Compute the lighting of the polygon
	        norm = &mesh_face_norm[poly_zsort[i].index];
            dp = fix16Mul(ctx->transformation.lightInv.x, norm->x) +
				fix16Mul(ctx->transformation.lightInv.y, norm->y) +
				fix16Mul(ctx->transformation.lightInv.z, norm->z);

	        if (dp > 0) col += (dp >> (FIX16_FRAC_BITS - 2));
	            BMP_drawPolygon(v, 4, col | (col << 4));
        }
    }
}

void handleJoyEvent(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (changed & ~state & BUTTON_START)
        {
            // flatDrawing = 1 - flatDrawing;
        }
    }
}

void RSE_3DFlatShadedScreen(void)
{
    char str[16];

    struct rendering_context ctx;

    ctx.camdist = FIX16(15);

    M3D_reset();
    M3D_setCamDistance(ctx.camdist);
    M3D_setLightEnabled(1);
    M3D_setLightXYZ(FIX16(0.9), FIX16(0.9), FIX16(-0.9));

    // allocate translation and rotation structure
    M3D_setTransform(&(ctx.transformation), &(ctx.translation), &(ctx.rotation));
    M3D_setTranslation(&(ctx.transformation), FIX16(0), FIX16(0), FIX16(20));
    M3D_setRotation(&(ctx.transformation), FIX16(0.0), FIX16(0.0), FIX16(0.0));

    ctx.rotstep.x = FIX16(0.05);
    ctx.rotstep.y = FIX16(0.05);

    // set the current mesh
    PART_3D_LOAD_MESH(ctx, metacube);

    zsort_switch = 0;

    while (1)
    {
        M3D_setCamDistance(ctx.camdist);

        // do work here
        ctx.rotation.x += ctx.rotstep.x;
        ctx.rotation.y += ctx.rotstep.y;
        ctx.rotation.z += ctx.rotstep.z;
        ctx.transformation.rebuildMat = 1;

        updatePointsPos(&ctx); // &(ctx.transformation), ctx.pts_3D, ctx.pts_2D);

        // ensure previous flip buffer request has been started
        BMP_waitWhileFlipRequestPending();
        BMP_showFPS(1);

        BMP_clear();

        drawPoints(0xFF, &ctx); // &(ctx.transformation), ctx.pts_3D, ctx.pts_2D);

        BMP_drawText("trans z:", 0, 2);
        fix16ToStr(ctx.translation.z, str, 2);
        BMP_drawText(str, 10, 2);
        BMP_drawText("cam dist:", 0, 3);
        fix16ToStr(ctx.camdist, str, 2);
        BMP_drawText(str, 11, 3);

        BMP_flip(1);
    }	
}
