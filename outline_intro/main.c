#include "genesis.h"
#include <gfx.h>

#define NUM_COLUMNS     	64
#define NUM_ROWS        	28
#define NUM_LINES       	NUM_ROWS * 8
#define SPOTLIGHT_WIDTH		1
#define NUM_SPOTLIGHTS		NUM_COLUMNS / SPOTLIGHT_WIDTH
#define VRAM_POS_TILE_VOID	TILE_SYSTEMINDEX
#define LOGO_W				256
#define LOGO_H				56

void RSE_LogoScreen(void);

int main()
{
	RSE_LogoScreen();
}

void RSE_turn_screen_to_white(void)
{
	/* Turn whole palette to white */
	u16 i;
	for(i = 0; i < 63; i++)
	{
		VDP_setPaletteColor(i, 0xFFF);
	}

}

void RSE_turn_screen_to_black(void)
{
	/* Turn whole palette to white */
	u16 i;
	for(i = 0; i < 63; i++)
	{
		VDP_setPaletteColor(i, 0x000);
	}

}

void RSE_pause(u16 frames)
{
	while(--frames > 0)
		VDP_waitVSync();
}

void RSE_LogoScreen(void)
{
	u16 vblCount = 0, i;
	u16 vramIndex = TILE_USERINDEX;
	s16 tile_scroll_h[1024];
	Sprite sprites[16];

	void inline DrawSpotlights(void)
	{
	    u16 row, column;
	    u16 tile_spotlight;

	    for(row = 0; row < NUM_ROWS; row++)
		    for(column = 0; column < NUM_SPOTLIGHTS; column++)
			    for(tile_spotlight = 0; tile_spotlight < SPOTLIGHT_WIDTH; tile_spotlight++)
			    {
			       VDP_setTileMapXY( APLAN, TILE_ATTR_FULL(PAL0, column%2, 0, 0, VRAM_POS_TILE_VOID),
			          (column * SPOTLIGHT_WIDTH) + tile_spotlight, row);
			    }
	}

	SYS_disableInts();
	VDP_setPlanSize(64, 32);
	RSE_turn_screen_to_black();
	VDP_setScreenWidth320();
	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);	
	SPR_init(257);
    SPR_initSprite(&sprites[0], &logo_rse_top_9bits, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	SPR_setPosition(&sprites[0], (VDP_getScreenWidth() - LOGO_W) >> 1, (VDP_getScreenHeight() - LOGO_H) >> 1);
    SPR_update(sprites, 1);		
	VDP_setHilightShadow(1); 
	VDP_drawImageEx(BPLAN, &logo_rse_bottom_9bits, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 50), ((VDP_getScreenWidth() - LOGO_W) >> 4), (VDP_getScreenHeight() - LOGO_H) >> 4, FALSE, TRUE);
	DrawSpotlights();
	// VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	SYS_enableInts();

	RSE_pause(15);

	for(i = 0; i < 1024; i++)
		tile_scroll_h[i] = sinFix16(i << 2) / 2;

	/* Fade to the logo's palette */
	VDP_fadePalTo(PAL1, logo_rse_bottom_9bits.palette->data, 32, FALSE);

	VDP_setPalette(PAL2, logo_rse_top_9bits.palette->data);

	while (TRUE)
	{
		VDP_waitVSync();
		VDP_setHorizontalScrollLine(PLAN_A, (VDP_getScreenHeight() - LOGO_H) / 2, tile_scroll_h + (vblCount & 511), 80, TRUE);		
		vblCount++;
	}
}
