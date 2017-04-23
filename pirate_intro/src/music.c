#include "genesis.h"
#include "resources.h"

void play_intro_sound(void)
{
	SND_startPlay_XGM(logo_boot_music);
	SND_setMusicTempo_XGM(50);
}

void play_music(void)
{
	SND_startPlay_XGM(vgm_music);
	SND_setMusicTempo_XGM(50);
}

void stop_music(void)
{	SND_stopPlay_XGM();	}
