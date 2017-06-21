#include "genesis.h"
#include "easing_table.h"

#ifndef TRANSITION_HELPER
#define TRANSITION_HELPER

typedef struct
{
    Vect2D_f16 pos;
    Vect2D_f16 mov;
    u16 timer;
} Object;

#define RSE_FRAMES(A) ((A*60)/framerate)

const u16 palette_white[64];
const u16 palette_white_bg[64];

void RSE_turn_screen_to_white(void);
void RSE_turn_screen_to_black(void);
void RSE_turn_screen_to_color(u16 col);
void RSE_pause(u16 frames);
void RSE_clearTileRowB(u16 row);
void RSE_clearTileRowBWithPrio(u16 row);
void RSE_clearTileRowA(u16 row);
void RSE_clearTileRowAWithPrio(u16 row);
void RSE_resetScrolling(void);
void RSE_clearAll(void);

#endif
