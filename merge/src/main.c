#include "genesis.h"

#define NEXTSEQPREPA                            \
                MEM_init();                     \
				SYS_disableInts();              \
				VDP_clearPlan(APLAN, 1);        \
				VDP_clearPlan(BPLAN, 1);        \
				VDP_init();                     \
				VDP_setHInterrupt(0);           \
				SYS_enableInts();               \
                display_memFree(4000);          \
                                                \


void display_memFree(u16 displayTimeMs){
    char free_memStr[6];
    int free_mem = MEM_getFree();
    intToStr(free_mem, free_memStr, 6);
    VDP_drawText("FREE MEM :", 10, 9);
    VDP_drawText(free_memStr, 10, 10);
    VDP_waitVSync();
    waitMs(displayTimeMs);
    VDP_drawText("          ", 10, 9);
    VDP_drawText("          ", 10, 10);
}


void main_starfield_2d(u16 vbl_to_exit);
void main_logo(u16 vbl_to_exit);
void main_axelay_fx(u16 vbl_to_exit);
void main_underwater_starfield_fx(u16 vbl_to_exit);
void main_boing_ball_fx(u16 vbl_to_exit);
void main_twisted_metal(u16 vbl_to_exit);
void main_tunnel(u16 vbl_to_exit);
void main_vector_balls(u16 vbl_to_exit);

//logo
//Underwater starfield
//Pirate Boing Ball
//Twister
//Tunnel FX
//Axelay FX
//Vector Balls

int main(){
    main_logo(100); //exit after x vbl after fade
    NEXTSEQPREPA
    main_underwater_starfield_fx(500);
    NEXTSEQPREPA
    main_boing_ball_fx(500);
    NEXTSEQPREPA
    main_twisted_metal(500);
    NEXTSEQPREPA
    main_tunnel(250);
    NEXTSEQPREPA
    main_axelay_fx(400);
    NEXTSEQPREPA
    main_vector_balls(300);
    NEXTSEQPREPA
    main_logo(100);
	NEXTSEQPREPA
	VDP_drawText("END", 10, 10);
	while(1){
		VDP_waitVSync();
	}
	return 0;
}
