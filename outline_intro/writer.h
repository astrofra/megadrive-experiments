#include "genesis.h"

#ifndef RSE_WRITER
#define RSE_WRITER

#define FONT_PUNCT_OFFSET 35
#define FONT_LINE_OFFSET ((504 >> 3))

/*
	States of the text writer
*/
#define WRT_CENTER_CUR_LINE 0
#define WRT_WRITE_CUR_LINE 1
#define WRT_WAIT 2
#define WRT_CLEAR_LINE 3

extern u16 writer_state;
extern u16 writer_switch;
extern u16 current_string_idx;
extern u16 current_string_len;
extern u16 current_char_idx;
extern u16 current_char_x;
extern u16 writer_timer;

u16 RSE_loadFont(void);
u16 RSE_drawString(char *str);
void RSE_updateLineWriter(void);

#endif
