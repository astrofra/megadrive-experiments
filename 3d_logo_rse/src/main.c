//-----------------------------------------------
// 3D flat shaded routine with depth sort
// Based on SGDK's 3D samples
// Fra^Resistance
//-----------------------------------------------

#include "genesis.h"
#include <gfx.h>
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

	u16 logo_state;

	/*	2D poly caches */
	u16 poly_cache_size[3];

	Vect2D_s16 poly_cache_pt_r[logo_r_FACE_COUNT << 2];
	u16 poly_cache_is_quad_r[logo_r_FACE_COUNT];
	u16 poly_cache_col_r[logo_r_FACE_COUNT];

	Vect2D_s16 poly_cache_pt_s[logo_s_FACE_COUNT << 2];
	u16 poly_cache_is_quad_s[logo_s_FACE_COUNT];
	u16 poly_cache_col_s[logo_s_FACE_COUNT];

	Vect2D_s16 poly_cache_pt_e[logo_e_FACE_COUNT << 2];
	u16 poly_cache_is_quad_e[logo_e_FACE_COUNT];
	u16 poly_cache_col_e[logo_e_FACE_COUNT];

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

	u16 cachePoints(u8 col, Vect2D_s16 *poly_cache_pt, u16 *poly_cache_vtx_count, u16 *poly_cache_col)
	{
		Vect2D_s16 v[4];
		const Vect3D_f16 *norm;
		const short *poly_ind;
		u16 i, j;
		fix16 z_sum;

		norm = mesh_face_norm;
		poly_ind = mesh_poly_ind;

		//  Depth sort the polygons
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

		//  Draws the polygons
		i = poly_count;
		j = 0;

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
					// BMP_drawPolygon(v, 4, col | (col << 4));
					RSE_COPY_VECTOR2D(poly_cache_pt[j << 2], v[0]);
					RSE_COPY_VECTOR2D(poly_cache_pt[(j << 2) + 1], v[1]);
					RSE_COPY_VECTOR2D(poly_cache_pt[(j << 2) + 2], v[2]);
					RSE_COPY_VECTOR2D(poly_cache_pt[(j << 2) + 3], v[3]);
					poly_cache_vtx_count[j] = 4;
					poly_cache_col[j] = col | (col << 4);
					j++;
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
					// BMP_drawPolygon(v, 3, col | (col << 4));
					RSE_COPY_VECTOR2D(poly_cache_pt[j << 2], v[0]);
					RSE_COPY_VECTOR2D(poly_cache_pt[(j << 2) + 1], v[1]);
					RSE_COPY_VECTOR2D(poly_cache_pt[(j << 2) + 2], v[2]);
					poly_cache_vtx_count[j] = 3;
					poly_cache_col[j] = col | (col << 4);
					j++;				
				}
			}
		}

		return j;
	}

	void inline drawCache(u16 cache_size, Vect2D_s16 *poly_cache_pt, u16 *poly_cache_vtx_count, u16 *poly_cache_col)
	{
		u16 i;
		for(i = 0; i < cache_size; i++)
			BMP_drawPolygon(&poly_cache_pt[i << 2], poly_cache_vtx_count[i], poly_cache_col[i]);
	}

	camdist = FIX16(11);

	M3D_reset();
	M3D_setCamDistance(camdist);
	M3D_setLightEnabled(1);
	M3D_setLightXYZ(FIX16(-0.5), FIX16(0.5), FIX16(-1.5));

	M3D_setCamDistance(camdist);
	
	/* Prepare Point Cache */
	/* Letter R */
	RSE_LOGO_3D_LOAD_MESH(logo_r);
	M3D_setTransform(&(transformation), &(translation), &(rotation));
	M3D_setTranslation(&(transformation), FIX16(-14), FIX16(0.0), FIX16(25));
	M3D_setRotation(&(transformation), FIX16(-4.0), FIX16(-4.0), FIX16(0.0));
	transformation.rebuildMat = 1;
	updatePointsPos();
	poly_cache_size[0] = cachePoints(0xFF, poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);

	/* Letter S */
	RSE_LOGO_3D_LOAD_MESH(logo_s);
	// M3D_setTransform(&(transformation), &(translation), &(rotation));
	M3D_setTranslation(&(transformation), FIX16(0.0), FIX16(0.0), FIX16(25));
	M3D_setRotation(&(transformation), FIX16(-4.0), FIX16(-4.0), FIX16(0.0));
	transformation.rebuildMat = 1;
	updatePointsPos();
	poly_cache_size[1] = cachePoints(0xFF, poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);

	/* Letter E */
	RSE_LOGO_3D_LOAD_MESH(logo_e);
	// M3D_setTransform(&(transformation), &(translation), &(rotation));
	M3D_setTranslation(&(transformation), FIX16(14), FIX16(0.0), FIX16(25));
	M3D_setRotation(&(transformation), FIX16(-4.0), FIX16(-4.0), FIX16(0.0));
	transformation.rebuildMat = 1;
	updatePointsPos();
	poly_cache_size[2] = cachePoints(0xFF, poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);

	rotation.x = FIX16(-4);
	rotation.y = FIX16(-4);

	// set the current mesh
	RSE_LOGO_3D_LOAD_MESH(logo_r);

	logo_state = 0;
	zsort_switch = 0;
	easing_index = 0;

	while (logo_state < 12)
	{
		// ensure previous flip buffer request has been started
		BMP_waitWhileFlipRequestPending();
		BMP_showFPS(1);

		BMP_clear();

		switch(logo_state)
		{

			/* R */
			case 0:	
				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);
				RSE_LOGO_3D_LOAD_MESH(logo_r);
				M3D_setTranslation(&(transformation), FIX16(-14), FIX16(0.0), FIX16(25));
				M3D_setRotation(&(transformation), FIX16(-4.0), FIX16(-4.0), FIX16(0.0));
				easing_index = 0;
				zsort_switch = 0;
				logo_state++;
				break;

			case 1:
				if (easing_index < EASING_TABLE_LEN)
					rotation.y = fix16Mul(FIX16(-4.0), easing_fix16[EASING_TABLE_LEN - easing_index - 1]) >> 4; /* Shift by >> 4 : rotation by 90°, >> 3 : 180°, >> 2 : 360° */
				else
					logo_state++;

				transformation.rebuildMat = 1;
				updatePointsPos();

				drawPoints(0xFF);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);				

				easing_index += 8;
				break;

			case 2:
				rotation.y = FIX16(0.0);
				transformation.rebuildMat = 1;
				updatePointsPos();

				drawPoints(0xFF);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);

				poly_cache_size[0] = cachePoints(0xFF, poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				logo_state++;
				break;

			case 3:
				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);
				logo_state++;
				break;

			/* S */
			case 4:	
				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);

				RSE_LOGO_3D_LOAD_MESH(logo_s);
				M3D_setTranslation(&(transformation), FIX16(0.0), FIX16(0.0), FIX16(25));
				M3D_setRotation(&(transformation), FIX16(-4.0), FIX16(-4.0), FIX16(0.0));
				easing_index = 0;
				zsort_switch = 0;
				logo_state++;
				break;

			case 5:
				if (easing_index < EASING_TABLE_LEN)
					rotation.y = fix16Mul(FIX16(-4.0), easing_fix16[EASING_TABLE_LEN - easing_index - 1]) >> 4; /* Shift by >> 4 : rotation by 90°, >> 3 : 180°, >> 2 : 360° */
				else
					logo_state++;

				transformation.rebuildMat = 1;
				updatePointsPos();

				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawPoints(0xFF);

				easing_index += 8;
				break;

			case 6:
				rotation.y = FIX16(0.0);
				transformation.rebuildMat = 1;
				updatePointsPos();

				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawPoints(0xFF);

				poly_cache_size[1] = cachePoints(0xFF, poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);
				easing_index = 0;
				logo_state++;
				break;

			case 7:
				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);
				logo_state++;
				break;

			/* E */
			case 8:	
				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);

				RSE_LOGO_3D_LOAD_MESH(logo_e);
				M3D_setTranslation(&(transformation), FIX16(14.0), FIX16(0.0), FIX16(25));
				M3D_setRotation(&(transformation), FIX16(-4.0), FIX16(-4.0), FIX16(0.0));
				easing_index = 0;
				zsort_switch = 0;
				logo_state++;
				break;

			case 9:
				if (easing_index < EASING_TABLE_LEN)
					rotation.y = fix16Mul(FIX16(-4.0), easing_fix16[EASING_TABLE_LEN - easing_index - 1]) >> 4; /* Shift by >> 4 : rotation by 90°, >> 3 : 180°, >> 2 : 360° */
				else
					logo_state++;

				transformation.rebuildMat = 1;
				updatePointsPos();

				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawPoints(0xFF);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);

				easing_index += 8;
				break;

			case 10:
				rotation.y = FIX16(0.0);
				transformation.rebuildMat = 1;
				updatePointsPos();

				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawPoints(0xFF);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);

				poly_cache_size[2] = cachePoints(0xFF, poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				easing_index = 0;
				logo_state++;
				break;

			case 11:
				drawCache(poly_cache_size[0], poly_cache_pt_r, poly_cache_is_quad_r, poly_cache_col_r);
				drawCache(poly_cache_size[2], poly_cache_pt_e, poly_cache_is_quad_e, poly_cache_col_e);
				drawCache(poly_cache_size[1], poly_cache_pt_s, poly_cache_is_quad_s, poly_cache_col_s);
				logo_state++;
				break;
		}

		// transformation.rebuildMat = 1;
		// updatePointsPos();

		// BMP_drawText("trans z:", 0, 2);
		// intToStr(logo_state, str, 2);
		// BMP_drawText(str, 10, 2);
		// BMP_drawText("cam dist:", 0, 3);
		// fix16ToStr(camdist, str, 2);
		// BMP_drawText(str, 11, 3);

		BMP_flip(1);
	}

	BMP_end();
	SYS_disableInts();
	VDP_setScreenWidth320();
	VDP_setPlanSize(64, 32);
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);	
	VDP_setPalette(PAL1, logo_rse_3d.palette->data);
	VDP_drawImageEx(APLAN, &logo_rse_3d, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 50), 0, ((240 - 64) >> 4) - 1, FALSE, TRUE);
	SYS_enableInts();

	while (TRUE);	
}
