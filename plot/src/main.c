#include <genesis.h>
void sinPlot();
void testPlot();

int main(){
	sinPlot();
	//testPlot();
	return 0;
}
void testPlot(){
	VDP_setScreenWidth256();
	BMP_init(TRUE, 0, FALSE);
	fix16 x = 0;
	fix16 y = 0;
	u16 vblCount = 0;
	while (1){
		VDP_waitVSync();
		vblCount++;
		BMP_waitWhileFlipRequestPending();
		x = cosFix16(vblCount << 2);
		y = sinFix16(vblCount << 2);
		x += 1;
		BMP_setPixel(x, y, 0xFF);
		BMP_flip(1);
		BMP_waitWhileFlipRequestPending();
		BMP_setPixel(x, y, 0xFF);
		BMP_flip(1);
	}
}
void sinPlot(){
	VDP_setScreenWidth256();
	BMP_init(TRUE, 0, FALSE);
	fix16 x = 0;
	fix16 y = 0;
	u16 vblCount = 0;
	while (1){
		VDP_waitVSync();
		vblCount++;
		BMP_waitWhileFlipRequestPending();
		y = cosFix16(vblCount << 5);
		x += 1;
		BMP_setPixel(x, (y + 100), 0xFF);
		BMP_flip(1);
		BMP_waitWhileFlipRequestPending();
		BMP_setPixel(x, (y + 100), 0xFF);
		BMP_flip(1);
	}
}
