#include <genesis.h>
#include <gfx.h>
#include "transition_helper.h"
#include "writer.h"
#include "demo_strings.h"
#include "music.h"

extern u16 vramIndex;
extern u16 fontIndex;
extern u8 framerate;

void waitForUserRestart(void)
{
	u16 i, j, button;

	SYS_disableInts();
	VDP_setPlanSize(64, 32);
	SYS_enableInts();
	SYS_enableInts();

	/*	
		Prepare text writer
	*/
	current_char_y = (224 >> 4) - 1;
	RSE_writerSetInitialY(current_char_y);
	RSE_writerUnsetOption(WRT_OPT_WRITE_TO_PLAN_A);
	RSE_writerSetOption(WRT_OPT_AUTO_RESTART);
	RSE_writerSetOption(WRT_OPT_HALF_SPEED);
	RSE_writerSetOption(WRT_OPT_AUTO_NEXT_STRING);
	RSE_writerSetDisplayDuration(RSE_FRAMES(writer_display_duration));
	RSE_writerSetXOffset(0);
	VDP_setPalette(PAL0, oddball_fonts.palette->data);
	VDP_setPalette(PAL1, oddball_fonts.palette->data);
	demo_strings = (char **)strings_end;

	button = 0;
	while (!button)
	{
		VDP_waitVSync();
		RSE_writerUpdateLine();

		for(i = 0; i < 2; i++)
			if (JOY_readJoypad(i) & (BUTTON_A | BUTTON_B | BUTTON_C | BUTTON_START))
				button = 1;
	}

	stop_music();
	VDP_fadeOut(1, 63, 64, TRUE);

	j = 0;
	while (j < 64)
	{
		VDP_waitVSync();
		RSE_writerUpdateLine();
		j++;
	}	
}