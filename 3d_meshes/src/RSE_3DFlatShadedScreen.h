#include "genesis.h"

#define MAX_POINTS  256

#define PART_3D_LOAD_MESH(mesh_name) \
    mesh_coord = mesh_name ## _coord; \
    mesh_poly_ind = mesh_name ## _poly_ind; \
    mesh_line_ind = mesh_name ## _line_ind; \
    mesh_face_norm = mesh_name ## _face_norm; \
    vtx_count = mesh_name ## _VTX_COUNT; \
    poly_count = mesh_name ## _FACE_COUNT;