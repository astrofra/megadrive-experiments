#include "genesis.h"
#include <gfx.h>

void RSE_LogoScreen(void);
void RSE_physics_simulation(void);

int main()
{
	/* RSE Logo */
	RSE_LogoScreen();

	/* Demo !!! */
	RSE_physics_simulation();
}
