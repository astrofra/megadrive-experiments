#include <genesis.h>
#include "gfx.h"
#include "RSE_startingScreen.h"
#ifdef VISUALPAD_ON
#include "visualPad.h"
#endif
#ifdef KONAMICODE_ON
#include "music.h"
#endif

#ifdef KONAMICODE_ON
u16 konamiCodeUpdate(u16 *buttonSeq){
	u16 r = 0;
	u16 joyState = 0;
	joyState = JOY_readJoypad(JOY_1);
	if (JOY_readJoypad(JOY_1) == 0){ buttonSeq[11] = FALSE; }
	//Si on lit zero on est en etat release //isPress = FALSE
	switch (buttonSeq[0]) {
	case 0: //UP
		if (joyState == BUTTON_UP && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[1] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 1: //UP
		if (joyState == BUTTON_UP && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[2] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 2: //DOWN
		if (joyState == BUTTON_DOWN && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[3] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 3: //DOWN
		if (joyState == BUTTON_DOWN && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[4] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 4: //LEFT
		if (joyState == BUTTON_LEFT && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[5] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 5: //RIGHT
		if (joyState == BUTTON_RIGHT && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[6] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 6: //LEFT
		if (joyState == BUTTON_LEFT && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[7] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 7: //RIGHT
		if (joyState == BUTTON_RIGHT && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[8] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 8: //B
		if (joyState == BUTTON_B && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[9] = TRUE;
			buttonSeq[11] = TRUE;
		}
		break;
	case 9: //A
		if (joyState == BUTTON_A && buttonSeq[11] == FALSE){
			buttonSeq[0]++;
			buttonSeq[10] = TRUE;
			buttonSeq[11] = TRUE;
			r = TRUE;
		}
		break;

	default:
		break;
	}
	return r;
}
#endif

void RSE_startingScreen(u16 fadeSpeed, u16 fadeSpeed2){
	SYS_disableInts();
	VDP_setScreenWidth320();
	SPR_init(64);
	VDP_setPaletteColors(0, (u16*)palette_black, 64);
	VDP_setPalette(PAL0, palette_grey);
	#ifdef VISUALPAD_ON
	VDP_setPalette(PAL3, visualpadpad_sprite.palette->data);
	#endif
	VDP_drawImageEx(APLAN, &logostart_image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 50), 8, 10, FALSE, TRUE);
	SYS_enableInts();

	const u16 palLogoStartFade1[16] =  {0x000,0x000,0x000,0x000,0x620,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade2[16] =  {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x820,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade3[16] =  {0x000,0x000,0x000,0x000,0x000,0xc40,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade4[16] =  {0x000,0x000,0xe40,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade5[16] =  {0x000,0xe62,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade6[16] =  {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xe84,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade7[16] =  {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xe86,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade8[16] =  {0x000,0x000,0x000,0x000,0x000,0x000,0xea8,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade9[16] =  {0x000,0x000,0x000,0xeca,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade10[16] = {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xecc,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade11[16] = {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xeee,0x000,0x000,0x000,0x000,0x000};
	const u16 palLogoStartFade12[16] = {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xeee,0x000,0x000,0x000};
	//----------------------------------------------------------
	const u16 palLogoStartFade20[16] = {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xeee,0x000,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade21[16] = {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xeee,0x000,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade22[16] = {0x000,0x000,0x000,0x000,0x000,0x000,0x000,0xecc,0x000,0x000,0xeee,0x000,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade23[16] = {0x000,0x000,0x000,0xeca,0x000,0x000,0x000,0xecc,0x000,0x000,0xeee,0x000,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade24[16] = {0x000,0x000,0x000,0xeca,0x000,0x000,0xea8,0xecc,0x000,0x000,0xeee,0x000,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade25[16] = {0x000,0x000,0x000,0xeca,0x000,0x000,0xea8,0xecc,0xe86,0x000,0xeee,0x000,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade26[16] = {0x000,0x000,0x000,0xeca,0x000,0x000,0xea8,0xecc,0xe86,0x000,0xeee,0xe84,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade27[16] = {0x000,0xe62,0x000,0xeca,0x000,0x000,0xea8,0xecc,0xe86,0x000,0xeee,0xe84,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade28[16] = {0x000,0xe62,0xe40,0xeca,0x000,0x000,0xea8,0xecc,0xe86,0x000,0xeee,0xe84,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade29[16] = {0x000,0xe62,0xe40,0xeca,0x000,0xc40,0xea8,0xecc,0xe86,0x000,0xeee,0xe84,0xeee,0x000,0x000,0x000};
	const u16 palLogoStartFade30[16] = {0x000,0xe62,0xe40,0xeca,0x000,0xc40,0xea8,0xecc,0xe86,0x820,0xeee,0xe84,0xeee,0x000,0x000,0x000};
	u16 endLoop = 0;
	u16 sequencer = 0;

	while(!endLoop){
		{
			switch(sequencer){
				case 0:
					VDP_fadePalTo(PAL1, palLogoStartFade1,fadeSpeed, 1);
					sequencer++;
					break;
				case 1:
					VDP_fadePalTo(PAL1, palLogoStartFade2,fadeSpeed, 1);
					sequencer++;
					break;
				case 2:
					VDP_fadePalTo(PAL1, palLogoStartFade3,fadeSpeed, 1);
					sequencer++;
					break;
				case 3:
					VDP_fadePalTo(PAL1, palLogoStartFade4,fadeSpeed, 1);
					sequencer++;
					break;
				case 4:
					VDP_fadePalTo(PAL1, palLogoStartFade5,fadeSpeed, 1);
					sequencer++;
					break;
				case 5:
					VDP_fadePalTo(PAL1, palLogoStartFade6,fadeSpeed, 1);
					sequencer++;
					break;
				case 6:
					VDP_fadePalTo(PAL1, palLogoStartFade7,fadeSpeed, 1);
					sequencer++;
					break;
				case 7:
					VDP_fadePalTo(PAL1, palLogoStartFade8,fadeSpeed, 1);
					sequencer++;
					break;
				case 8:
					VDP_fadePalTo(PAL1, palLogoStartFade9,fadeSpeed, 1);
					sequencer++;
					break;
				case 9:
					VDP_fadePalTo(PAL1, palLogoStartFade10,fadeSpeed, 1);
					sequencer++;
					break;
				case 10:
					VDP_fadePalTo(PAL1, palLogoStartFade11,fadeSpeed, 1);
					sequencer++;
					break;
				case 11:
					VDP_fadePalTo(PAL1, palLogoStartFade12,fadeSpeed, 1);
					sequencer++;
					break;
				case 12:
					VDP_fadePalTo(PAL1, palLogoStartFade20,fadeSpeed2, 1);
					sequencer++;
					break;
				case 13:
					VDP_fadePalTo(PAL1, palLogoStartFade21,fadeSpeed2, 1);
					sequencer++;
					break;
				case 14:
					VDP_fadePalTo(PAL1, palLogoStartFade22,fadeSpeed2, 1);
					sequencer++;
					break;
				case 15:
					VDP_fadePalTo(PAL1, palLogoStartFade23,fadeSpeed2, 1);
					sequencer++;
					break;
				case 16:
					VDP_fadePalTo(PAL1, palLogoStartFade24,fadeSpeed2, 1);
					sequencer++;
					break;
				case 17:
					VDP_fadePalTo(PAL1, palLogoStartFade25,fadeSpeed2, 1);
					sequencer++;
					break;
				case 18:
					VDP_fadePalTo(PAL1, palLogoStartFade26,fadeSpeed2, 1);
					sequencer++;
					break;
				case 19:
					VDP_fadePalTo(PAL1, palLogoStartFade27,fadeSpeed2, 1);
					sequencer++;
					break;
				case 20:
					VDP_fadePalTo(PAL1, palLogoStartFade28,fadeSpeed2, 1);
					sequencer++;
					break;
				case 21:
					VDP_fadePalTo(PAL1, palLogoStartFade29,fadeSpeed2, 1);
					sequencer++;
					break;
				case 22:
					VDP_fadePalTo(PAL1, palLogoStartFade30,fadeSpeed2, 1);
					sequencer++;
					break;
				case 23:
					VDP_fadePalTo(PAL1, logostart_image.palette->data,fadeSpeed2, 1);
					sequencer++;
					break;
				default:
					break;
			}
			// startTimer(0);
		}
		VDP_waitVSync();
	}
	VDP_clearPlan(VDP_PLAN_A,1);
	VDP_clearPlan(VDP_PLAN_B,1);
}
