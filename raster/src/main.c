#include <genesis.h>
#include <kdebug.h>
#define CHAR_SIZE 4

u16 hInterruptCounter = 0;
u32 hscroll = 0;

void hBlank(){
	hInterruptCounter++;	
	VDP_setHorizontalScroll(PLAN_A, hscroll >> 8);
	//hscroll += 0x30;
	hscroll += 10;
}

int main(){
	VDP_clearPlan(APLAN,0);
	VDP_clearPlan(BPLAN,0);
	VDP_setScreenWidth320();
	char hInterruptCounterStr[CHAR_SIZE];
	
	VDP_drawText("H INTERRUPTION COUNTER :", 0, 5);

	SYS_enableInts();
	VDP_setHInterrupt(1);
	SYS_setHIntCallback(&hBlank); //hBlank function is called on each h interruption
	
	while (1){
		//VDP_waitVSync();
		VDP_setHorizontalScroll(PLAN_A, 0);
		hscroll = 0;
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
