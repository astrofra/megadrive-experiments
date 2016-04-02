#ifndef MAIN_TUNNEL_H
#define MAIN_TUNNEL_H

#define CIRCLE_MAX	5	//5
#define CIRCLE_RES	9	//9
#define PIXEL_MAX	45	//CIRCLE_MAX x CIRCLE_RES 45
#define LINE_MAX	45	//CIRCLE_MAX x CIRCLE_RES 45

#define _PIXEL_ON	0
#define _LINE_ON	1

typedef struct Circle_ Circle_;
struct Circle_{
    s16 x;
    s16 y;
    s16 size;
    u16 col;
    u16	res;
};

void main_tunnel(u16 vbl_to_exit);

#endif
