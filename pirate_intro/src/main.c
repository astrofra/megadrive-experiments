#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"
#include "music.h"

/* 
Resistance 2016

Code : Fra
Music : Nainain
Gfx : ...
Framework : SGDK
*/

void fastVectorBallFX(void);

u16 vramIndex;
u16 fontIndex;
u8 framerate;
char *demo_strings;

int main()
{
	framerate = 60;
	if (SYS_isPAL())
		framerate = 50;

	while(TRUE)
	{
		vramIndex = TILE_USERINDEX;

		// play_music();

		RSE_turn_screen_to_black();
		/*	
			Load the font tiles
			that will be used during all the demo
		*/
		// fontIndex = RSE_writerSetup();

		// displayBarbPictureFX();

		// RSE_pause(RSE_FRAMES(20));

		fastVectorBallFX();

		stop_music();

		RSE_pause(RSE_FRAMES(20));

		RSE_clearAll();
	}
}
