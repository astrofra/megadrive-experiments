#include <genesis.h>
#include <kdebug.h>
#define CHAR_SIZE 4

u16 hInterruptCounter = 0;

void hBlanck(){
	hInterruptCounter++;	
}

int main(){
	VDP_clearPlan(APLAN,0);
	VDP_clearPlan(BPLAN,0);
	VDP_setScreenWidth320();
	char hInterruptCounterStr[CHAR_SIZE];
	
	VDP_drawText("H INTERRUPTION COUNTER :", 0, 5);

	SYS_enableInts();
	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlanck); //hBlanck function is called on each h interruption
	
	while (1){
		//VDP_waitVSync();
		KDebug_Alert("SGDK HCOUNTER");
		KDebug_AlertNumber(GET_HCOUNTER);

		KDebug_Alert("SGDK VCOUNTER");
		KDebug_AlertNumber(GET_VCOUNTER);

		KDebug_Alert("SGDK HVCOUNTER");
		KDebug_AlertNumber(GET_HVCOUNTER);

		uintToStr(hInterruptCounter, hInterruptCounterStr, CHAR_SIZE);
		VDP_drawText(hInterruptCounterStr, 0, 10);		
		KDebug_Alert("----------------------------");
		VDP_waitVSync();
	}
	return 0;
}
