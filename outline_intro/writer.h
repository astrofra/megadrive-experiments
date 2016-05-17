#include "genesis.h"

extern u16 writer_state;
extern u16 writer_switch;
extern u16 current_string_idx;
extern u16 current_string_len;
extern u16 current_char_idx;
extern u16 current_plan;
extern u16 current_char_x;
extern u16 current_char_y;
extern u16 writer_timer;
extern u16 writer_options;
extern u16 writer_display_duration;
extern u16 x_offset;

#ifndef RSE_WRITER
#define RSE_WRITER

#define FONT_PUNCT_OFFSET 36
#define FONT_LINE_OFFSET ((432 >> 3))

/*
	States of the text writer
*/
#define WRT_CENTER_CUR_LINE 0
#define WRT_WRITE_CUR_LINE 1
#define WRT_WAIT 2
#define WRT_CLEAR_LINE 3
#define WRT_IDLE_MODE 16

/*
	Writer options
	/!\ NOT IMPLEMENTED YET
*/
#define WRT_OPT_WRITE_TO_PLAN_A		1
#define WRT_OPT_AUTO_LINE_FEED 		(1 << 1)
#define WRT_OPT_AUTO_NEXT_STRING	(1 << 2)
#define WRT_OPT_AUTO_RESTART		(1 << 3)
#define WRT_OPT_HALF_SPEED			(1 << 4)

#define WRT_HAS_OPTION(OPT) (OPT & writer_options)

u16 RSE_writerSetup(void);
void RSE_writerSetInitialY(u16 initial_y);
void RSE_writerRestart(void);
u8 RSE_writerIsDone(void);
u16 RSE_writerDrawString(char *str);
void RSE_writerUpdateLine(void);
void RSE_writerUpdateMultiLine(void);
u16 RSE_writerSetOption(u16 option);
u16 RSE_writerUnsetOption(u16 option);
void RSE_writerSetXOffset(u16 offset);

#endif
