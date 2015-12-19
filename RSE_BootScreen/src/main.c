#include <genesis.h>
#include "gfx.h"
#include "RSE_startingScreen.h"

int main(){
	RSE_startingScreen(10, 10);
	while (1){
		VDP_waitVSync();
	}
	return 0;
}
