#include <genesis.h>

int main(){
	VDP_clearPlan(APLAN,0);
	VDP_clearPlan(BPLAN,0);
	VDP_setScreenWidth320();
	char hcounterStr[6];

	while (1){
		VDP_waitVSync();
		intToStr(GET_HCOUNTER, hcounterStr, 6);
		//TODO implementation of SGDK Hinterruption callback 
		VDP_drawText(hcounterStr,  0, 0);
	}
	return 0;
}
