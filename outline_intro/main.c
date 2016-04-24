#include "genesis.h"
#include <gfx.h>
#include "writer.h"
#include "transition_helper.h"

/* 
Resistance 2016

Code : Fra
Music : Nainain
Gfx : ...
Framework : SGDK
*/

u8 RSE_LogoScreen(void);
void RSE_physics_simulation(void);

u16 vramIndex;
u16 fontIndex;
char *demo_strings;

int main()
{
	vramIndex = TILE_USERINDEX;

	RSE_turn_screen_to_black();

	/*	
		Load the font tiles
		that will be used during all the demo
	*/
	fontIndex = RSE_writerSetup();

	/* RSE Logo */
	RSE_LogoScreen();

	/* Demo !!! */
	RSE_physics_simulation();
}
