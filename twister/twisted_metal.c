#include <genesis.h>
#include <gfx.h>

#define TWISTER_TABLE_SIZE 1024
#define CST_CTRL_PORT 0xC00004
#define CST_DATA_PORT 0xC00000
#define CST_WRITE_VSRAM_ADDR(adr)   ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x10)

void twistedMetal(void)
{
	u16 vramIndex = TILE_USERINDEX;
	u16 scroll_jump_table[TWISTER_TABLE_SIZE];
	u16 i, vcount = 0;

    vu16 *pw;
    vu32 *pl;

    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

	static void hBlank(){
		// VDP_setVerticalScroll(PLAN_A, scroll_jump_table[(GET_VCOUNTER + vcount) & ((TWISTER_TABLE_SIZE >> 2) - 1)] + (64 + sinFix16(vcount << 1)) << 1);

	    *pl = CST_WRITE_VSRAM_ADDR(0);
	    *pw = scroll_jump_table[(GET_VCOUNTER + vcount) & ((TWISTER_TABLE_SIZE >> 2) - 1)] + (64 + sinFix16(vcount << 1)) << 1;		
	}

	for(i = 0; i < TWISTER_TABLE_SIZE; i++)
		scroll_jump_table[i] = (i * (sinFix16(i << 2) + 64)) >> 7;

	SYS_disableInts();

	/* Set a larger tileplan to be able to scroll */
	VDP_setPlanSize(32, 64);

	VDP_clearPlan(APLAN, 0);
	VDP_clearPlan(BPLAN, 0);

	/* Load the fond tiles */
	VDP_drawImageEx(APLAN, &twister, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 8, 0, FALSE, FALSE);
	VDP_drawImageEx(APLAN, &twister, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 8, 256 / 8, FALSE, FALSE);
	vramIndex += twister.tileset->numTile;

	VDP_setPalette(PAL0, twister.palette->data);

    VDP_setHilightShadow(0);

	SYS_enableInts();

	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank);

	while (TRUE)
	{
		VDP_waitVSync();
		vcount++;
	}	
}