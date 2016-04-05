#include <genesis.h>
#include "main_tunnel.h"

int main(){
	main_tunnel(500);
	VDP_drawText("END", 10, 10);
	while (1){
		VDP_waitVSync();
	}
	return 0;
}