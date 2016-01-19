#include "genesis.h"


#define MAX_STAR  80
#define STARFIELD_SIZE (0xFF >> 1)
#define STARFIELD_DIST -64

typedef struct
{
    s16 x,y,z;
    u16 mov;
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
	        p->x = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE / 2);
	        p->y = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE / 2);
	        p->z = (random() % STARFIELD_SIZE) - (STARFIELD_SIZE / 2) + STARFIELD_DIST;
	        p->mov = random() % 4 + 1;
	        p->col = (random() % 4 + 1) << 2;
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
	    	p->z += p->mov;
	    	if (p->z > (STARFIELD_SIZE >> 1) + STARFIELD_DIST)
	    		p->z -= ((STARFIELD_SIZE >> 1) - STARFIELD_DIST);

	        p++;
	    }
	};

	/*	Draw the stars */
	static void inline drawStar(_star *part, s16 num)
	{
	    _star *p;
	    s16 i, maxy;
	    u16 off, x, y;

	    i = num;
	    maxy = BMP_HEIGHT;
	    p = part;

	    while(i--)
	    {
	    	if (p->z != 0)
	    	{
		    	x = ((p->x  << 5) / p->z) + 128;
		    	y = ((p->y  << 5) / p->z) + 80;
		        BMP_setPixel(x, y, p->col);
	        }
	        p++;
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
