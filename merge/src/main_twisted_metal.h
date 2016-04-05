#include <genesis.h>
#ifndef MAIN_TWISTED_METAL_H
#define MAIN_TWISTED_METAL_H

#define TWISTER_TABLE_SIZE 1024
#define CST_CTRL_PORT 0xC00004
#define CST_DATA_PORT 0xC00000
#define CST_WRITE_VSRAM_ADDR(adr)   ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x10)

void main_twisted_metal(u16 vbl_to_exit);

#endif
