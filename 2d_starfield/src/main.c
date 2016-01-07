#include "genesis.h"


#define MAX_STAR  256

typedef struct
{
    Vect2D_u16 pos;
    Vect2D_u16 mov;
    u16 col;
} _star;

_star stars[MAX_STAR];

s16 numstars;

fix16 baseposx;
fix16 baseposy;

static void initStar(s16 num);
static void updateStar(_star *part_pos, s16 num);
static void drawStar(_star *part_pos, s16 num, u8 col);

int main()
{
    char col;

    VDP_setScreenWidth256();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);

    BMP_init(1, 0, 0);

    col = 0xFF;

    /* Initialise stars */
    baseposx = BMP_WIDTH >> 1;
    baseposy = BMP_HEIGHT >> 1;

    initStar(MAX_STAR);

    while(TRUE)
    {
        // calculates stars position
        updateStar(stars, numstars);

        // ensure previous flip buffer request has been started
        BMP_waitWhileFlipRequestPending();

        // can now draw text
        BMP_showFPS(0);

        // clear bitmap
        BMP_clear();

        // draw stars
        drawStar(stars, numstars, col);

        // swap buffer
        BMP_flip(1);
    }
}


static void initStar(s16 num)
{
    _star *p;
    s16 i;

    numstars = num;

    i = num;
    p = stars;
    while(i--)
    {
        p->pos.x = random() % 320;
        p->pos.y = random() & 0xFF;
        p->mov.x = (random() & 0x3) + 1;
        p->mov.y = 0;
        p->col = p->mov.x << 1;
        p++;
    }
}

static void updateStar(_star *part, s16 num)
{
    _star *p;
    s16 i;

    i = num;
    p = part;
    while(i--)
    {

        p->pos.x += p->mov.x;
        p->pos.y += p->mov.y;

        if (p->pos.x >= BMP_WIDTH)
            p->pos.x -= BMP_WIDTH;

        p++;
    }
}

static void drawStar(_star *part, s16 num, u8 col)
{
    Vect2D_u16 part_pos[num];
    _star *p;
    Vect2D_u16 *pos;
    s16 i, maxy;

    i = num;
    maxy = BMP_HEIGHT;
    p = part;
    pos = part_pos;
    while(i--)
    {
        // pos->x = p->pos.x;
        // pos->y = p->pos.y;

        BMP_setPixel(p->pos.x, p->pos.y, p->col);

        p++;
        pos++;
    }

    // BMP_setPixels_V2D(part_pos, col, num);
}
