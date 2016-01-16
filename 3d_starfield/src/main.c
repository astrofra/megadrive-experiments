#include "genesis.h"


#define MAX_STAR  128

typedef struct
{
    Vect2D_s16 pos;
    Vect2D_s16 mov;
    u16 col;
} _star;

// static void initStar(s16 num);
// static void updateStar(_star *part_pos, s16 num);
// static void drawStar(_star *part_pos, s16 num, u8 col);
void RSE_Starfield_2D(void);

int main()
{
	RSE_Starfield_2D();
}

void RSE_Starfield_2D(void)
{
	_star stars[MAX_STAR];

	s16 numstars;

	fix16 baseposx;
	fix16 baseposy;

	u8 *bmp_buffer_write = NULL;

	u8 buffer_flipped = FALSE;

	/*	Initialize the list of stars */
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
	        p->mov.x = (p->pos.x - 128) / 20;
	        p->mov.y = (p->pos.y - 100) / 20;
	        p->col = 7;
	        p++;
	    }
	};

	/*	Update the list of stars */
	static void inline updateStar(_star *part, s16 num)
	{
	    _star *p;
	    s16 i;

	    i = num;
	    p = part;
	    while(i--)
	    {

	        p->pos.x += p->mov.x;
	        p->pos.y += p->mov.y;

	        if (p->pos.x >= BMP_WIDTH || p->pos.x < 0 || p->pos.y >= BMP_HEIGHT || p->pos.y < 0)
	        {
	            p->pos.x  = 128 + p->mov.x;
	            p->pos.y  = 100 + p->mov.y;
	        }

	        p++;
	    }
	};

	/*	Draw the stars */
	static void inline drawStar(_star *part, s16 num)
	{
	    Vect2D_u16 part_pos[num];
	    _star *p;
	    Vect2D_u16 *pos;
	    s16 i, maxy;
	    u16 off;

	    i = num;
	    maxy = BMP_HEIGHT;
	    p = part;
	    pos = part_pos;

	    while(i--)
	    {
	        BMP_setPixel(p->pos.x, p->pos.y, p->col);
	        p++;
	        pos++;
	    }
	};

    VDP_setScreenWidth256();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);

    BMP_init(1, 0, 0);

    /* Initialise stars */
    baseposx = BMP_WIDTH >> 1;
    baseposy = BMP_HEIGHT >> 1;

    initStar(MAX_STAR);

    /* Main loop */
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
		drawStar(stars, numstars);

        // swap buffer
        BMP_flip(1);
    }
}
