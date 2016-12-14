#include <genesis.h>
#include <gfx.h>
#include "ball_coords.h"
#include "quicksort.h"
#include "writer.h"
#include "transition_helper.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void flat3DCubeFX(void)
{
	u16 cube_phase;
	s16 x_cube, y_cube;
	u16 cube_frame;
	Sprite *sprites[2];

	cube_frame = 0;
	cube_phase = 0;

	SPR_init(0,0,0);
	VDP_setHilightShadow(1);

	sprites[0] = SPR_addSprite(&cube_anim, 0, 0, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, 0));
	sprites[1] = SPR_addSprite(&cube_shadow, 0, 0, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, 0));
	SPR_setFrame(sprites[0], 0);
	SPR_setFrame(sprites[1], 0);

	// VDP_fadePalTo(PAL2, ball_metal.palette->data, RSE_FRAMES(16), TRUE);

	while(TRUE)
	{
		VDP_waitVSync();
		updateScrollText();

		x_cube = (sinFix16((cube_phase * 5) >> 1)) + 160 - 40;
		y_cube = cosFix16(cube_phase << 1) + 96 - 40;

		SPR_setPosition(sprites[0], x_cube, y_cube);
		SPR_setFrame(sprites[0], (cube_frame >> 2) & 63);

		SPR_setPosition(sprites[1], x_cube + 32, (y_cube >> 3) + 180);
		SPR_setFrame(sprites[1], (cube_frame >> 2) & 63);

		SPR_update(sprites, 2);

		cube_frame++;
		cube_phase += 2;
	}

}