#include "genesis.h"

#define NEXTSEQPREPA							\
				SYS_disableInts();				\
				VDP_clearPlan(APLAN, 1);		\
				VDP_clearPlan(BPLAN, 1);		\
				/*MEM_init();*/						\
				VDP_init();						\
				VDP_setHInterrupt(0);			\
				SYS_enableInts();				\
												\


void main_starfield_2d(u16 vbl_to_exit);
void main_logo(u16 vbl_to_exit);
void main_axelay_fx(u16 vbl_to_exit);
void main_bitmap_stretch_fx(u16 vbl_to_exit);


int main(){
	main_logo(100); //exit after x vbl after fade
	NEXTSEQPREPA
	main_starfield_2d(150);
	NEXTSEQPREPA
	main_axelay_fx(400);
	NEXTSEQPREPA
	main_bitmap_stretch_fx(400);
	NEXTSEQPREPA
	VDP_drawText("END", 10, 10);
	while(1){
		VDP_waitVSync();
	}
	return 0;
}
