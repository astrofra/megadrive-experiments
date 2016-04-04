#include "genesis.h"
#include <gfx.h>

#define MAX_STAR  48
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
void RSE_Starfield_3D_Spr(void);

int main()
{
	RSE_Starfield_3D_Spr();
}

void RSE_Starfield_3D_Spr(void)
{
	u16 loop;
	_star stars[MAX_STAR];
	s16 numstars;

	Sprite sprites[MAX_STAR];
	short x_screen, y_screen;

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

	/*	Draw the stars */
	static void inline updateAndDrawStar(_star *part, s16 num)
	{
		char str[32];

		_star *p;
		s16 i, maxy;
		u16 off, x, y;
		// int div_a_min, div_a_max;
		// int div_b_min, div_b_max;

		i = num;
		maxy = BMP_HEIGHT;
		p = part;

		x_screen = (VDP_getScreenWidth() - 32) >> 1;
		x_screen += 0x80;
		y_screen = (VDP_getScreenHeight() - 32) >> 1;
		y_screen += 0x80;	

		// div_a_min = 0;
		// div_a_max = 0;
		// div_b_min = 0;
		// div_b_max = 0;			

		while(i--)
		{
			p->z += p->mov;
			if (p->z > (STARFIELD_SIZE >> 1) + STARFIELD_DIST)
				p->z -= ((STARFIELD_SIZE >> 1) - STARFIELD_DIST);

			if (p->z != 0)
			{

				x = (p->x << 5) / p->z;
				y = (p->y << 5) / p->z;

				// if (div_a_min < p->x << 5)
				// 	div_a_min = p->x << 5;
				// else
				// if (div_a_max >= p->x << 5)
				// 	div_a_max = p->x << 5;

				// if (div_b_min < p->z)
				// 	div_b_min = p->z;
				// else
				// if (div_b_max >= p->z)
				// 	div_b_max = p->z;


				sprites[i].x = x_screen + x;
				sprites[i].y = y_screen + y;
			}
			p++;
		}

		SPR_update(sprites, MAX_STAR);

		// intToStr(div_a_min, str, 4);
		// BMP_drawText(str, 0, 0);
		// intToStr(div_a_max, str, 4);
		// BMP_drawText(str, 12, 0);

		// intToStr(div_b_min, str, 4);
		// BMP_drawText(str, 0, 1);
		// intToStr(div_b_max, str, 4);
		// BMP_drawText(str, 12, 1);		
	};

	SYS_disableInts();

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	VDP_setPalette(PAL2, sprite_stars.palette->data);
	SPR_init(MAX_STAR);	

	/*	Initialize the needed amount of sprites */
	for(loop = 0; loop < MAX_STAR; loop++)
	{
		SPR_initSprite(&sprites[loop], &sprite_stars, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
		SPR_setFrame(&sprites[loop], loop % 3);
	}

	SPR_update(sprites, MAX_STAR);

	SYS_enableInts();	

	/* Initialise stars */
	baseposx = BMP_WIDTH >> 1;
	baseposy = BMP_HEIGHT >> 1;

	initStar(MAX_STAR);

	/* Main loop */
	while(TRUE)
	{
		VDP_waitVSync();

		// can now draw text
		BMP_showFPS(0);

		// calculates stars position
		// draw stars
		updateAndDrawStar(stars, numstars);
	}
}
