#include <genesis.h>

/*
	States of the text writer
*/
#define WRT_CENTER_CUR_LINE 0
#define WRT_WRITE_CUR_LINE 1
#define WRT_WAIT 2
#define WRT_CLEAR_LINE 3

#define FONT_PUNCT_OFFSET 36
#define FONT_LINE_OFFSET ((504 >> 3) - 1)

#define PLAN_B_TILE_H 20
#define PLAN_A_TILE_H 10

u16 inline computeStringLen(char *str);
u16 inline charToTileIndex(char c);
u16 RSE_drawString(char *str);
void inline RSE_updateLineWriter(void);

extern u16 writer_state;
extern u16 writer_switch;
extern u16 current_string_idx;
extern u16 current_string_len;
extern u16 current_char_idx;
extern u16 current_char_x;
extern u16 writer_timer;

