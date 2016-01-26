#include <genesis.h>
void testLine();
void vmd();
void tunnelA();

int main(){
	//testLine();
	//vmd();
	tunnelA();
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


//	-------------------------------------------------------------------
//			TUNNEL A
// --------------------------------------------------------------------
#define CIRCLE_RES	50
#define CIRCLES_SETPIX 		BMP_setPixel(circle00->x + circle00->xOffset + (sinFix32(i) / circle00->size), (circle00->y + circle00->yOffset + cosFix32(i) / circle00->size), 0xFF); \
							BMP_setPixel(circle01->x + circle01->xOffset + (sinFix32(i) / circle01->size), (circle01->y + circle01->yOffset + cosFix32(i) / circle01->size), 0xFF); \
							BMP_setPixel(circle02->x + circle02->xOffset + (sinFix32(i) / circle02->size), (circle02->y + circle02->yOffset + cosFix32(i) / circle02->size), 0xFF); \
							BMP_setPixel(circle03->x + circle03->xOffset + (sinFix32(i) / circle03->size), (circle03->y + circle03->yOffset + cosFix32(i) / circle03->size), 0xFF); \
							BMP_setPixel(circle04->x + circle04->xOffset + (sinFix32(i) / circle04->size), (circle04->y + circle04->yOffset + cosFix32(i) / circle04->size), 0xFF); \
							BMP_setPixel(circle05->x + circle05->xOffset + (sinFix32(i) / circle05->size), (circle05->y + circle05->yOffset + cosFix32(i) / circle05->size), 0xFF); \
							BMP_setPixel(circle06->x + circle06->xOffset + (sinFix32(i) / circle06->size), (circle06->y + circle06->yOffset + cosFix32(i) / circle06->size), 0xFF); \
							BMP_setPixel(circle07->x + circle07->xOffset + (sinFix32(i) / circle07->size), (circle07->y + circle07->yOffset + cosFix32(i) / circle07->size), 0xFF); \
							BMP_setPixel(circle08->x + circle08->xOffset + (sinFix32(i) / circle08->size), (circle08->y + circle08->yOffset + cosFix32(i) / circle08->size), 0xFF);


void tunnelA(){
	typedef struct circle circle;
	struct circle{
		u16 x;
		u16 y;
		u16 xOffset;
		u16 yOffset;
		u16 size;
	};

	// make circles structures
	circle circle00, circle01, circle02, circle03, circle04, circle05, circle06, circle07, circle08;
	circle00.x = circle01.x = circle02.x = circle03.x = circle04.x = circle05.x = circle06.x = circle07.x = circle08.x = 80;
	circle00.y = circle01.y = circle02.y = circle03.y = circle04.y = circle05.y = circle06.y = circle07.y = circle08.y = 80;
	circle00.xOffset = circle01.xOffset = circle02.xOffset = circle03.xOffset = circle04.xOffset = circle05.xOffset = circle06.xOffset = circle07.xOffset = circle08.xOffset = 20;
	circle00.yOffset = circle01.yOffset = circle02.yOffset = circle03.yOffset = circle04.yOffset = circle05.yOffset = circle06.yOffset = circle07.yOffset = circle08.yOffset = 20;

	circle00.size = 81;
	circle01.size = 71;
	circle02.size = 61;
	circle03.size = 51;
	circle04.size = 41;
	circle05.size = 31;
	circle06.size = 21;
	circle07.size = 11;
	circle08.size = 1;

	VDP_setScreenWidth256();
	BMP_init(TRUE, 0, FALSE);

	static void circleDraw(circle *circle00, circle *circle01, circle *circle02, circle *circle03, circle *circle04, circle *circle05, circle *circle06, circle *circle07, circle *circle08){
		// no loop for better perf
		u16 i = 0;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
		CIRCLES_SETPIX
		i += CIRCLE_RES;
	}

	static inline void circlesXoffsetAdd(){
		circle00.xOffset++;
		circle01.xOffset++;
		circle02.xOffset++;
		circle03.xOffset++;
		circle04.xOffset++;
		circle05.xOffset++;
		circle06.xOffset++;
		circle07.xOffset++;
		circle08.xOffset++;
	}

	static inline void circlesXoffsetSub(){
		circle00.xOffset--;
		circle01.xOffset--;
		circle02.xOffset--;
		circle03.xOffset--;
		circle04.xOffset--;
		circle05.xOffset--;
		circle06.xOffset--;
		circle07.xOffset--;
		circle08.xOffset--;
	}

	static inline void circlesYoffsetAdd(){
		circle00.yOffset++;
		circle01.yOffset++;
		circle02.yOffset++;
		circle03.yOffset++;
		circle04.yOffset++;
		circle05.yOffset++;
		circle06.yOffset++;
		circle07.yOffset++;
		circle08.yOffset++;
	}

	static inline void circlesYoffsetSub(){
		circle00.yOffset--;
		circle01.yOffset--;
		circle02.yOffset--;
		circle03.yOffset--;
		circle04.yOffset--;
		circle05.yOffset--;
		circle06.yOffset--;
		circle07.yOffset--;
		circle08.yOffset--;
	}

	static inline void circlesSizeSub(){
		circle00.size--;
		circle01.size--;
		circle02.size--;
		circle03.size--;
		circle04.size--;
		circle05.size--;
		circle06.size--;
		circle07.size--;
		circle08.size--;
	}

	static inline void circlesDraw(){
		circleDraw(&circle00, &circle01, &circle02, &circle03, &circle04, &circle05, &circle06, &circle07, &circle08);
	}


	u16 vblCount = 0;
	u16 seq = 0;


	while (1){
		BMP_clear();
		BMP_showFPS(1);

		circlesDraw();
		circlesSizeSub();

		if (seq == 1){
			circlesXoffsetSub();
		}

		if (seq == 2){
			circlesXoffsetSub();
			circlesYoffsetSub();
		}

		if (seq == 3){
			circlesXoffsetAdd();
		}

		if (seq == 4){
			circlesXoffsetAdd();
			circlesYoffsetAdd();
		}

		if (circle00.size == 0){ circle00.size = 100; circle00.xOffset = 20; circle00.yOffset = 20; }
		if (circle01.size == 0){ circle01.size = 100; circle01.xOffset = 20; circle01.yOffset = 20; }
		if (circle02.size == 0){ circle02.size = 100; circle02.xOffset = 20; circle02.yOffset = 20; }
		if (circle03.size == 0){ circle03.size = 100; circle03.xOffset = 20; circle03.yOffset = 20; }
		if (circle04.size == 0){ circle04.size = 100; circle04.xOffset = 20; circle04.yOffset = 20; }
		if (circle05.size == 0){ circle05.size = 100; circle05.xOffset = 20; circle05.yOffset = 20; }
		if (circle06.size == 0){ circle06.size = 100; circle06.xOffset = 20; circle06.yOffset = 20; }
		if (circle07.size == 0){ circle07.size = 100; circle07.xOffset = 20; circle07.yOffset = 20; }
		if (circle08.size == 0){ circle08.size = 100; circle08.xOffset = 20; circle08.yOffset = 20; }

		if (vblCount > 20 && seq == 0) seq++;
		if (vblCount > 100 && seq == 1) seq++;
		if (vblCount > 200 && seq == 2) seq++;
		if (vblCount > 220 && seq == 3) seq++;

		vblCount++;
		BMP_flip(1);
		BMP_waitFlipComplete();
	}
}

