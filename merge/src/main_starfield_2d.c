#include "genesis.h"
#include "main_starfield_2d.h"


// #define STD_SETPIXEL


// static void initStar(s16 num);
// static void updateStar(_star *part_pos, s16 num);
// static void drawStar(_star *part_pos, s16 num, u8 col);


void main_starfield_2d(u16 vbl_to_exit)
{
	u16 vblCount = 0;
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
#ifdef STD_SETPIXEL
	        p->pos.y = random() & 0xFF;
#else        
	        p->pos.y = (random() & 0xFF) * BMP_PITCH;
#endif
	        p->mov.x = (random() & 0x3) + 1;
	        p->mov.y = 0;
	        p->col = p->mov.x << 1;
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

	        if (p->pos.x >= BMP_WIDTH)
	            p->pos.x -= BMP_WIDTH;

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
#ifdef STD_SETPIXEL
	        BMP_setPixel(p->pos.x, p->pos.y, p->col);
#else
	        off = p->pos.y + (p->pos.x >> 1);
	        bmp_buffer_write[off] = p->col;
#endif
	        p++;
	        pos++;
	    }
	};

	SYS_disableInts();
    VDP_setScreenWidth256();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);
	SYS_enableInts();
	
    BMP_init(1, 0, 0);
	
    /* Initialise stars */
    baseposx = BMP_WIDTH >> 1;
    baseposy = BMP_HEIGHT >> 1;

    initStar(MAX_STAR);

    /* Main loop */
    while(vblCount < vbl_to_exit)
    {
		vblCount++;
		bmp_buffer_write = BMP_getWritePointer(0,0);

        // calculates stars position
        updateStar(stars, numstars);

        // can now draw text
        BMP_showFPS(0);

        // clear bitmap
        BMP_clear();

        // ensure previous flip buffer request has been started
        BMP_waitWhileFlipRequestPending();

        // draw stars
		drawStar(stars, numstars);

        // swap buffer
        BMP_flip(1);
        // buffer_flipped != buffer_flipped;
    }
	BMP_end();
}
