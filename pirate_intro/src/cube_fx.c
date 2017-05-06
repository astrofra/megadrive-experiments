#include <genesis.h>
#include <gfx.h>
#include "ball_coords.h"
#include "quicksort.h"
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;
static u16 barb_blue_pal[64];

void flat3DCubeFX(void)
{
	u16 i, cube_phase;
	s16 x_cube, y_cube;
	u16 cube_frame, sec_frame_step;
	Sprite *sprites[2];

	cube_frame = 0;
	sec_frame_step = 4;
	cube_phase = 256;

	SPR_init(0,0,0);
	VDP_setHilightShadow(1);

	for(i = 0; i < 64; i++)
		barb_blue_pal[i] = barb_pic_2_front.palette->data[0];

	VDP_setPalette(PAL2, palette_black);

	sprites[0] = SPR_addSprite(&cube_anim, 0, 0, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
	sprites[1] = SPR_addSprite(&cube_shadow, 0, 0, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, 0));
	SPR_setFrame(sprites[0], 0);
	SPR_setFrame(sprites[1], 0);

	while(cube_phase < 1024)
	{
		VDP_waitVSync();
		updateScrollText();

		x_cube = (sinFix16((cube_phase * 5) >> 1)) + 160 - 64;
		y_cube = ((cosFix16(cube_phase << 1) * 3) >> 2) + 96 - 64;

		SPR_setPosition(sprites[0], x_cube, y_cube);
		SPR_setFrame(sprites[0], (cube_frame >> 1) & 127);

		SPR_setPosition(sprites[1], x_cube + 32 + (y_cube >> 3), (y_cube >> 3) + 190);
		SPR_setFrame(sprites[1], (cube_frame >> 2) & 63);

		SPR_update(sprites, 2);

		cube_frame++;
		cube_phase += 2;

		if (cube_phase == 256 + 32)
			VDP_fadePalTo(PAL2, palette_white, RSE_FRAMES(4), TRUE);
		if (cube_phase == 256 + 32 + 10)
			VDP_fadePalTo(PAL2, sky.palette->data, RSE_FRAMES(16), TRUE);
 
		if (cube_phase == 1024 - 20)
			VDP_fadeAllTo(barb_blue_pal, 16, TRUE); // VDP_fadeOut(1, 63, 32, TRUE);
	}

	/* clean everything */

	RSE_turn_screen_to_color(0xF0F);

	RSE_resetScrolling();

	SYS_disableInts();

	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);

	SYS_enableInts();

	SPR_end();

	vramIndex = TILE_USERINDEX;
}