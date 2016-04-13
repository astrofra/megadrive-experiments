#include <genesis.h>

#ifndef MAIN_TUNNEL_H
#define MAIN_TUNNEL_H

//______________________
//   CIRCLE
//----------------------
/*
#define CIRCLE_MAX	6
#define CIRCLE_RES	9
#define PIXEL_MAX	54	//CIRCLE_MAX x CIRCLE_RES
#define LINE_MAX	54	//CIRCLE_MAX x CIRCLE_RES
*/

//----------------------
//  TRIANGLE
//----------------------

///*
#define CIRCLE_MAX  6
#define CIRCLE_RES  3
#define PIXEL_MAX   18
#define LINE_MAX    18
//*/

//----------------------
//   CARRE
//----------------------
/*
#define CIRCLE_MAX  6
#define CIRCLE_RES  4
#define PIXEL_MAX   24
#define LINE_MAX    24
*/

#define CIRCLE_XOFFSET  0
#define CIRCLE_YOFFSET  0

 
#define _PIXEL_ON	0
#define _LINE_ON	1

typedef struct Circle_ Circle_;
struct Circle_{
	s16 x;
	s16 y;
    s16 xOffset;
    s16 yOffset;
	s16 size;
	u16 col;
	u16	res;
};

void main_tunnel(u16 vbl_to_exit);

#endif
