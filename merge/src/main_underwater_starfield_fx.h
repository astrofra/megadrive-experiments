#include <genesis.h>
#ifndef MAIN_UNDERWATER_STARFIELD_H
#define MAIN_UNDERWATER_STARFIELD_H

#define MAX_STAR  48
#define STARFIELD_SIZE (0xFF >> 1)
#define STARFIELD_DIST -64

typedef struct
{
	s16 x,y,z;
	u16 mov;
	u16 col;
} _star;

void main_underwater_starfield_fx(u16 vbl_to_exit);

#endif
