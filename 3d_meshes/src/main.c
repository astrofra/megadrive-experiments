//-----------------------------------------------
// 3D flat shaded routine with depth sort
// Based on SGDK's 3D samples
// Fra^Resistance
//-----------------------------------------------

#include "genesis.h"
#include "meshs.h"
#include "quicksort.h"

#define MAX_POINTS  512
#define ASSERT_VALUE 253

extern Mat3D_f16 MatInv;
extern Mat3D_f16 Mat;

Vect3D_f16 pts_3D[MAX_POINTS];
Vect2D_s16 pts_2D[MAX_POINTS];

Rotation3D rotation;
Translation3D translation;
Transformation3D transformation;

Vect3D_f16 rotstep;

fix16 camdist;

u16 zsort_switch;

const Vect3D_f16 *mesh_coord;
const u16 *mesh_poly_ind;
const u16 *mesh_line_ind;
const Vect3D_f16 *mesh_face_norm;

struct  QSORT_ENTRY poly_zsort[metacube_FACE_COUNT];

void updatePointsPos();
void drawPoints(u8 col);
void handleJoyEvent(u16 joy, u16 changed, u16 state);

#define PART_3D_LOAD_MESH(mesh_name) \
    mesh_coord = mesh_name ## _coord; \
    mesh_poly_ind = mesh_name ## _poly_ind; \
    mesh_line_ind = mesh_name ## _line_ind; \
    mesh_face_norm = mesh_name ## _face_norm;

int main()
{
    char str[16];

    VDP_setScreenWidth256();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);

    // speed up controller checking
    JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
    JOY_setSupport(PORT_2, JOY_SUPPORT_OFF);

    JOY_setEventHandler(handleJoyEvent);

    BMP_init(TRUE, PAL0, FALSE);

    camdist = FIX16(15);

    M3D_reset();
    M3D_setCamDistance(camdist);
    M3D_setLightEnabled(1);
    M3D_setLightXYZ(FIX16(0.9), FIX16(0.9), FIX16(-0.9));

    // allocate translation and rotation structure
    M3D_setTransform(&transformation, &translation, &rotation);
    M3D_setTranslation(&transformation, FIX16(0), FIX16(0), FIX16(20));
    M3D_setRotation(&transformation, FIX16(0.0), FIX16(0.0), FIX16(0.0));

    rotstep.x = FIX16(0.05);
    rotstep.y = FIX16(0.05);

    // set the current mesh
    PART_3D_LOAD_MESH(metacube);
    // mesh_coord = metacube_coord;
    // mesh_poly_ind = metacube_poly_ind;
    // mesh_line_ind = metacube_line_ind;
    // mesh_face_norm = metacube_face_norm;

    zsort_switch = 0;

    while (1)
    {
        M3D_setCamDistance(camdist);

        // do work here
        rotation.x += rotstep.x;
        rotation.y += rotstep.y;
        rotation.z += rotstep.z;
        transformation.rebuildMat = 1;

        updatePointsPos();

        // ensure previous flip buffer request has been started
        BMP_waitWhileFlipRequestPending();
        BMP_showFPS(1);

        BMP_clear();

        drawPoints(0xFF);

        BMP_drawText("trans z:", 0, 2);
        fix16ToStr(translation.z, str, 2);
        BMP_drawText(str, 10, 2);
        BMP_drawText("cam dist:", 0, 3);
        fix16ToStr(camdist, str, 2);
        BMP_drawText(str, 11, 3);

        BMP_flip(1);
    }
}

void updatePointsPos()
{
    // transform 3D point
    M3D_transform(&transformation, mesh_coord, pts_3D, metacube_VTX_COUNT);
    // project 3D point (f16) to 2D point (s16)
    M3D_project_s16(pts_3D, pts_2D, metacube_VTX_COUNT);
}

void drawPoints(u8 col)
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

	        z_sum = fix16Add(fix16Add(pts_3D[poly_ind[j]].z, pts_3D[poly_ind[j+1]].z), fix16Add(pts_3D[poly_ind[j+2]].z, pts_3D[poly_ind[j+3]].z));
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

        *pt_dst++ = pts_2D[*poly_ind++];
        *pt_dst++ = pts_2D[*poly_ind++];
        *pt_dst++ = pts_2D[*poly_ind++];
        *pt_dst = pts_2D[*poly_ind++];

        //	If the polygon is facing the camera
        if (!BMP_isPolygonCulled(v, 4))
        {
        	//	Compute the lighting of the polygon
	        norm = &mesh_face_norm[poly_zsort[i].index];
            dp = fix16Mul(transformation.lightInv.x, norm->x) +
				fix16Mul(transformation.lightInv.y, norm->y) +
				fix16Mul(transformation.lightInv.z, norm->z);

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
