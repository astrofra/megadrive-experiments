#ifndef RSE_STARTINGSCREEN_H
#define RSE_STARTINGSCREEN_H

//#define KONAMICODE_ON
//#define VISUALPAD_ON

#ifdef KONAMICODE_ON
/* KONAMI CODE */
u16 konamiCodeUpdate(u16 *buttonSeq); //return TRUE when code is complete
#define KONAMICODEINIT		u16 konButtonSeqState[12] = {0,0,0,0,0,0,0,0,0,0,0,0}
#define KONAMICODEUPDATE	konamiCodeUpdate((u16*)&konButtonSeqState)
#endif


void RSE_startingScreen(u16 fadeSpeed, u16 fadeSpeed2);

#endif

