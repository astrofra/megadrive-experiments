#include <genesis.h>
void testLine();
void vmd();
int main(){
	//testLine();
	vmd();
	return 0;
}

void vmd(){
	BMP_init(TRUE, 0, FALSE);
	
	while(1){
		BMP_setPixel(10, 10, 0xFF);
		BMP_flip(1);
		BMP_waitFlipComplete();
	}
	
}
void testLine(){
	VDP_setScreenWidth256();
	VDP_setPalette(0, palette_green);
	BMP_init(TRUE, 0, FALSE);
	u16 vblCount = 0;
	u16 i = 0;
	fix16 x = 100;
	fix16 y;
	void draw(){
		for (i = 0; i < 10; i++){
			y = sinFix16( (vblCount + i) << 5);
			fix16 yNext = sinFix16((vblCount + i + 1) << 6);

			//line
			Line l;
			Vect2D_s16 start, end;
			start.x = x + i;
			start.y = y + 100;
			end.x = x + 100;
			end.y = yNext;
			l.pt1 = start;
			l.pt2 = end;
			l.col = 0xFF;
			BMP_drawLine(&l);
		}

	}
	while (1){
		VDP_waitVSync();
		vblCount++;
		BMP_clear();
		BMP_showFPS(1);
		draw();
		BMP_flip(1);
		BMP_waitFlipComplete();
		BMP_clear();
		vblCount++;
		BMP_showFPS(1);
		draw();
		BMP_flip(1);
		BMP_waitFlipComplete();
	}
}
