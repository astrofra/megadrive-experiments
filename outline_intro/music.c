#include "genesis.h"
#include "resources.h"

void play_music(void)
{
	SND_startPlay_XGM(malabar_bumper);
	SND_setMusicTempo_XGM(50);
}

void stop_music(void)
{	SND_stopPlay_XGM();	}
