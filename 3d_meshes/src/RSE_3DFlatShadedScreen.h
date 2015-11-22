#include "genesis.h"

#define MAX_POINTS  256

#define PART_3D_LOAD_MESH(rendering_context, mesh_name) \
    mesh_coord = mesh_name ## _coord; \
    mesh_poly_ind = mesh_name ## _poly_ind; \
    mesh_line_ind = mesh_name ## _line_ind; \
    mesh_face_norm = mesh_name ## _face_norm; \
    vtx_count = mesh_name ## _VTX_COUNT;
    // poly_count = mesh_name ## _FACE_COUNT;

struct rendering_context
{
    Rotation3D rotation;
	Translation3D translation;
	Transformation3D transformation;
	Vect3D_f16 rotstep;

    Vect3D_f16 pts_3D[MAX_POINTS];
	Vect2D_s16 pts_2D[MAX_POINTS];	

    fix16 camdist;
};
