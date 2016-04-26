#include <genesis.h>
#include <gfx.h>
#include "twister_fx.h"

s16 twister_jump_table[TWISTER_TABLE_SIZE];

void initTwisterFx(void)
{
	s16 i, j;

	for(i = 0, j = 0; i < TWISTER_TABLE_SIZE; i++)
	{
		j = sinFix16(i << 2) >> 2;
		twister_jump_table[i] = j;
	}

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}

void updateTwisterFx(u16 vcount_init, u16 duration)
{
	u16 vcount;

    vu16 *pw;
    vu32 *pl;

    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

	static void hBlank(){
		// VDP_setVerticalScroll(PLAN_A, scroll_jump_table[(GET_VCOUNTER + vcount) & ((TWISTER_TABLE_SIZE >> 2) - 1)] + (64 + sinFix16(vcount << 1)) << 1);

	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = twister_jump_table[(GET_VCOUNTER + vcount) & ((TWISTER_TABLE_SIZE >> 2) - 1)];		
	}

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank);

	vcount = vcount_init;
	while (vcount < duration)
	{
		VDP_waitVSync();
		vcount++;
	}	
}

void disableTwisterFx(void)
{
	VDP_setHInterrupt(0);
	// SYS_setHIntCallback(NULL);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}
