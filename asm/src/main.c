#include <genesis.h>
#include "ASMtest.h"
/* 
	Mixing C\ASM test
	nothing to show yet, but the SGDK Makefile compiling and link well the S file

	My first test is deal with VDP directly in ASM

	SGDK provide the GFX_* macros for low level job with VDP


*/
int main(){
	VDP_setPaletteColors(0, (u16*)palette_black, 64);
	setVDPPalette(); //Call the ASM routine
	while (1){
		VDP_waitVSync();
	}
	return 0;
}
