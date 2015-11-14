#include "genesis.h"

#include "meshs.h"

#define MAX_POINTS  512


Vect3D_f16 pts_3D[MAX_POINTS];
Vect2D_s16 pts_2D[MAX_POINTS];


extern Mat3D_f16 MatInv;
extern Mat3D_f16 Mat;


Vect3D_f16 vtab_3D[MAX_POINTS];
Vect2D_s16 vtab_2D[MAX_POINTS];

Rotation3D rotation;
Translation3D translation;
Transformation3D transformation;

Vect3D_f16 rotstep;

fix16 camdist;

u16 flatDrawing;

const Vect3D_f16 *mesh_coord;
const u16 *mesh_poly_ind;
const u16 *mesh_line_ind;
const Vect3D_f16 *mesh_face_norm;

struct  QSORT_ENTRY poly_zsort[CYLINDER_SUBD_FACE_COUNT];

// Sorting generic structure
struct  QSORT_ENTRY
{
    fix16   value;
    u16    index;
};

//------------------------------------------------------
void    inline QSwap (struct QSORT_ENTRY *a,struct QSORT_ENTRY *b)
//------------------------------------------------------
{   
    struct QSORT_ENTRY t = *a;
    *a = *b;
    *b = t;
}

//----------------------------------------------------
void    inline RecQuickSort (struct QSORT_ENTRY *se, u16 l, u16 r)
//----------------------------------------------------
{
    u16 cr, ls;

    if  ( l >= r )
        return;

    QSwap ( &se[l], &se[(l+r)>>1] );
    ls = l;

    for ( cr = l+1; cr <= r; cr++ )
        if  ( se[cr].value < se[l].value )
            QSwap ( &se[cr], &se[++ls] );

    QSwap ( &se[l], &se[ls] );
    RecQuickSort ( se, l, ls - 1 );
    RecQuickSort ( se, ls + 1, r );
}

//----------------------------------------
void    QuickSort (u16 n,struct QSORT_ENTRY *se)
//----------------------------------------
{
    RecQuickSort (se, 0, n-1);
}


void updatePointsPos();
void drawPoints(u8 col);
void doActionJoy(u8 numjoy, u16 value);
void handleJoyEvent(u16 joy, u16 changed, u16 state);


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
    M3D_setRotation(&transformation, FIX16(0), FIX16(0), FIX16(0));

    flatDrawing = 1;
    rotstep.x = FIX16(0.05);
    rotstep.y = FIX16(0.05);

    // set the current mesh
    mesh_coord = cylinder_subd_coord;
    mesh_poly_ind = cylinder_subd_poly_ind;
    mesh_line_ind = cylinder_subd_line_ind;
    mesh_face_norm = cylinder_subd_face_norm;

    while (1)
    {
        doActionJoy(JOY_1, JOY_readJoypad(JOY_1));

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
    M3D_transform(&transformation, mesh_coord, pts_3D, CYLINDER_SUBD_VTX_COUNT);
    // project 3D point (f16) to 2D point (s16)
    M3D_project_s16(pts_3D, pts_2D, CYLINDER_SUBD_VTX_COUNT);
}

void drawPoints(u8 col)
{
    // if (flatDrawing)
    // {
    Vect2D_s16 v[4];
    const Vect3D_f16 *norm;
    const u16 *poly_ind;
    u16 i, j;

    norm = mesh_face_norm;
    poly_ind = mesh_poly_ind;

    //  Depth sort the polygons
    for(i = 0; i < CYLINDER_SUBD_FACE_COUNT; i++)
    {
        j = i << 2;
        poly_zsort[i].index = i;
        poly_zsort[i].value = fix16Add(fix16Add(mesh_coord[poly_ind[j++]].z, mesh_coord[poly_ind[j++]].z), fix16Add(mesh_coord[poly_ind[j++]].z, mesh_coord[poly_ind[j++]].z));
    }

    QuickSort(CYLINDER_SUBD_FACE_COUNT, &poly_zsort);

    //  Draws the polygons
    i = CYLINDER_SUBD_FACE_COUNT;

    while(i--)
    {
        Vect2D_s16 *pt_dst = v;
        fix16 dp;
        u8 col = 2;

        poly_ind = &mesh_poly_ind[poly_zsort[i].index << 2]; // poly_zsort[i].index];

        *pt_dst++ = pts_2D[*poly_ind++];
        *pt_dst++ = pts_2D[*poly_ind++];
        *pt_dst++ = pts_2D[*poly_ind++];
        *pt_dst = pts_2D[*poly_ind++];

        dp = fix16Mul(transformation.lightInv.x, norm->x) +
             fix16Mul(transformation.lightInv.y, norm->y) +
             fix16Mul(transformation.lightInv.z, norm->z);
        norm++;

        if (dp > 0) col += (dp >> (FIX16_FRAC_BITS - 2));

        if (!BMP_isPolygonCulled(v, 4))
            BMP_drawPolygon(v, 4, col | (col << 4));
    }
}


void doActionJoy(u8 numjoy, u16 value)
{
    if (numjoy == JOY_1)
    {
        if (value & BUTTON_UP)
        {
            if (value & BUTTON_A) translation.y += FIX16(0.2);
            else rotstep.x += FIX16(0.05);
        }

        if (value & BUTTON_DOWN)
        {
            if (value & BUTTON_A) translation.y -= FIX16(0.2);
            else rotstep.x -= FIX16(0.05);
        }

        if (value & BUTTON_LEFT)
        {
            if (value & BUTTON_A) translation.x -= FIX16(0.2);
            else rotstep.y += FIX16(0.05);
        }

        if (value & BUTTON_RIGHT)
        {
            if (value & BUTTON_A) translation.x += FIX16(0.2);
            else rotstep.y -= FIX16(0.05);
        }

        if (value & BUTTON_Y)
        {
            if (value & BUTTON_X) camdist += FIX16(1.0);
            else camdist += FIX16(0.1);
        }

        if (value & BUTTON_Z)
        {
            if (value & BUTTON_X) camdist -= FIX16(1.0);
            else camdist -= FIX16(0.1);
        }

        if (value & BUTTON_B)
        {
            if (value & BUTTON_A) translation.z += FIX16(1);
            else translation.z += FIX16(0.1);
        }

        if (value & BUTTON_C)
        {
            if (value & BUTTON_A) translation.z -= FIX16(1);
            else translation.z -= FIX16(0.1);
        }

        if (value & BUTTON_START)
        {
            rotstep.x = FIX16(0.0);
            rotstep.y = FIX16(0.0);
        }
    }
}

void handleJoyEvent(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (changed & ~state & BUTTON_START)
        {
            flatDrawing = 1 - flatDrawing;
        }
    }
}
