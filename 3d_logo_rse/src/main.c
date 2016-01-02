//-----------------------------------------------
// 3D flat shaded routine with depth sort
// Based on SGDK's 3D samples
// Fra^Resistance
//-----------------------------------------------

#include "genesis.h"
#include "RSE_logo_meshs.h"
#include "quicksort.h"
#include "RSE_Logo3DScreen.h"
#include "RSE_easing_table.h"

extern Mat3D_f16 MatInv;
extern Mat3D_f16 Mat;

void RSE_Logo3DScreen(void);

int main()
{
	VDP_setScreenWidth256();
	VDP_setHInterrupt(0);
	VDP_setHilightShadow(0);

	BMP_init(TRUE, PAL0, FALSE);

	RSE_Logo3DScreen();
}

void RSE_Logo3DScreen(void)
{
	u16 zsort_switch;

	const Vect3D_f16 *mesh_coord;
	const short *mesh_poly_ind;
	const u16 *mesh_line_ind;
	const Vect3D_f16 *mesh_face_norm;
	u16 vtx_count;
	u16 poly_count;

	u16 easing_index;

	struct  QSORT_ENTRY poly_zsort[RSE_LOGO_3D_MAX_POINTS];

    Rotation3D rotation;
	Translation3D translation;
	Transformation3D transformation;

    fix16 camdist;

	char str[16];

	Vect3D_f16 pts_3D[RSE_LOGO_3D_MAX_POINTS];
	Vect2D_s16 pts_2D[RSE_LOGO_3D_MAX_POINTS];

	void inline updatePointsPos()
	{
		// transform 3D point
		M3D_transform(&(transformation), mesh_coord, pts_3D, vtx_count);
		// project 3D point (f16) to 2D point (s16)
		M3D_project_s16(pts_3D, pts_2D, vtx_count);
	}

	void inline drawPoints(u8 col)
	{
		Vect2D_s16 v[4];
		const Vect3D_f16 *norm;
		const short *poly_ind;
		u16 i, j;
		fix16 z_sum;

		norm = mesh_face_norm;
		poly_ind = mesh_poly_ind;

		//  Depth sort the polygons
		if (zsort_switch == 0)
		{
			//	Feed an index table with the sum of the Z coordinate
			//	of each polygon in the current mesh
			for(i = 0; i < poly_count; i++)
			{
				j = i << 2;
				poly_zsort[i].index = i;

				/*  Is it a quad or a triangle ? */
				if (poly_ind[j+3] != -1)
					z_sum = fix16Add(fix16Add(pts_3D[poly_ind[j]].z, pts_3D[poly_ind[j+1]].z), fix16Add(pts_3D[poly_ind[j+2]].z, pts_3D[poly_ind[j+3]].z));
				else
					z_sum = fix16Add(fix16Add(pts_3D[poly_ind[j]].z, pts_3D[poly_ind[j+1]].z), pts_3D[poly_ind[j+2]].z);

				poly_zsort[i].value = z_sum;
			}

			//	Quicksort the table and order the polygons by depth
			QuickSort(poly_count, poly_zsort);
		}

		//	Count 16 frames until the next depth sort
		zsort_switch++;
		zsort_switch &= 0xF;

		//  Draws the polygons
		i = poly_count;

		while(i--)
		{
			Vect2D_s16 *pt_dst = v;
			fix16 dp;
			u8 col = 2;

			poly_ind = &mesh_poly_ind[poly_zsort[i].index << 2];

			/*  Is it a quad or a triangle ? */
			if (*(poly_ind + 3) != -1)
			{
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
			else
			{
				*pt_dst++ = pts_2D[*poly_ind++];
				*pt_dst++ = pts_2D[*poly_ind++];
				*pt_dst++ = pts_2D[*poly_ind++];

				//	If the polygon is facing the camera
				if (!BMP_isPolygonCulled(v, 3))
				{
					//	Compute the lighting of the polygon
					norm = &mesh_face_norm[poly_zsort[i].index];
					dp = fix16Mul(transformation.lightInv.x, norm->x) +
						fix16Mul(transformation.lightInv.y, norm->y) +
						fix16Mul(transformation.lightInv.z, norm->z);

					if (dp > 0) col += (dp >> (FIX16_FRAC_BITS - 2));
						BMP_drawPolygon(v, 3, col | (col << 4));
				}
			}
		}
	}

	camdist = FIX16(11);

	M3D_reset();
	M3D_setCamDistance(camdist);
	M3D_setLightEnabled(1);
	M3D_setLightXYZ(FIX16(-0.5), FIX16(0.5), FIX16(-1.5));

	// allocate translation and rotation structure
	M3D_setTransform(&(transformation), &(translation), &(rotation));
	M3D_setTranslation(&(transformation), FIX16(-14), FIX16(0), FIX16(25));	// R
	// M3D_setTranslation(&(transformation), FIX16(0), FIX16(0), FIX16(25));	// S
	// M3D_setTranslation(&(transformation), FIX16(14), FIX16(0.0), FIX16(25));	// E
	M3D_setRotation(&(transformation), FIX16(0.0), FIX16(0.0), FIX16(0.0));

	rotation.x = FIX16(-4);
	rotation.y = FIX16(-4);

	// set the current mesh
	RSE_LOGO_3D_LOAD_MESH(logo_r);

	zsort_switch = 0;
	easing_index = 0;

	while (TRUE)
	{
		M3D_setCamDistance(camdist);

		if (easing_index < EASING_TABLE_LEN)
			/* Shift by >> 4 : rotation by 90°, >> 3 : 180°, >> 2 : 360° */
			rotation.y = fix16Mul(FIX16(-4.0), easing_fix16[EASING_TABLE_LEN - easing_index - 1]) >> 4;

		easing_index += 8;

		transformation.rebuildMat = 1;

		updatePointsPos();

		// ensure previous flip buffer request has been started
		BMP_waitWhileFlipRequestPending();
		BMP_showFPS(1);

		BMP_clear();

		drawPoints(0xFF);

		// BMP_drawText("trans z:", 0, 2);
		// fix16ToStr(translation.z, str, 2);
		// BMP_drawText(str, 10, 2);
		// BMP_drawText("cam dist:", 0, 3);
		// fix16ToStr(camdist, str, 2);
		// BMP_drawText(str, 11, 3);

		BMP_flip(1);
	}	
}
