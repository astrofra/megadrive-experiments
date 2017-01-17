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
void displayRSILogoFX(void);
void flat3DCubeFX(void);
void displayBarbTitleFX(void);
void displayBarbPictureFX(void);
void circleWavesFX(void);

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

		play_music();

		RSE_turn_screen_to_black();

		displayRSILogoFX();

		displayBarbTitleFX();

		fontIndex = RSE_writerSetup();

		fastVectorBallFX();

		flat3DCubeFX();

		displayBarbPictureFX();

		circleWavesFX();

		stop_music();

		RSE_pause(RSE_FRAMES(20));

		RSE_clearAll();
	}
}
