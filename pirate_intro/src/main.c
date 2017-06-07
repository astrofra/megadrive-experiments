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
void main_logo(void);
void shieldAnimFX(void);
void flat3DCubeFX(void);
void displayBarbTitleFX(void);
void displayBarbPictureFX(void);
void flamesWavesFX(void);
void ankouScreenFX(void);
void RSE_Starfield_3D_Spr(void);

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

		// RSE_turn_screen_to_black();

		// main_logo();

		// RSE_pause(RSE_FRAMES(16));

		// play_music();

		// displayBarbTitleFX();

		// fontIndex = RSE_writerSetup();

		// fastVectorBallFX();

		// flat3DCubeFX();

		// ankouScreenFX();

		// flamesWavesFX();

		// shieldAnimFX();

		RSE_Starfield_3D_Spr();

		stop_music();

		RSE_pause(RSE_FRAMES(20));

		RSE_clearAll();
	}
}
