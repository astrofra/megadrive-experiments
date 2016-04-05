#include <genesis.h>
#ifndef MAIN_STARFIELD_2D_H
#define MAIN_STARFIELD_2D_H

#define MAX_STAR					512
#define BMP_CELLWIDTH_SFT           5
#define BMP_PITCH_SFT               (BMP_CELLWIDTH_SFT + 2)
#define BMP_PITCH                   (1 << BMP_PITCH_SFT)

typedef struct
{
	Vect2D_u16 pos;
	Vect2D_u16 mov;
	u16 col;
} _star;

void main_starfield_2d(u16 vbl_to_exit);

#endif
