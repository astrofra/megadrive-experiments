#include <genesis.h>
#ifndef MAIN_BOING_BALL_FX_H
#define MAIN_BOING_BALL_FX_H

#define SCR_H ((224 >> 3) << 3)
#define BOARD_Y (((SCR_H - 120) >> 3) - 1)
#define BACK_SPEED 8
#define	TABLE_LEN SCR_H
#define PERSPECTIVE_STEP 64

void main_boing_ball_fx(u16 vbl_to_exit);

#endif
