#include <genesis.h>
#include "circlesTab.h"
void testLine();
void vmd();
void tunnelA();
void tunnelPreca();

int main(){
	//testLine();
	//vmd();
	tunnelA();
	//tunnelPreca();
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
#define CIRCLE_RES	50 //50
#define CIRCLES_SETPIX 		BMP_setPixel(circle00->x + circle00->xOffset + (sinFix32(i) / circle00->size), (circle00->y + circle00->yOffset + cosFix32(i) / circle00->size), circle00->color); \
							BMP_setPixel(circle01->x + circle01->xOffset + (sinFix32(i) / circle01->size), (circle01->y + circle01->yOffset + cosFix32(i) / circle01->size), circle01->color); \
							BMP_setPixel(circle02->x + circle02->xOffset + (sinFix32(i) / circle02->size), (circle02->y + circle02->yOffset + cosFix32(i) / circle02->size), circle02->color); \
							BMP_setPixel(circle03->x + circle03->xOffset + (sinFix32(i) / circle03->size), (circle03->y + circle03->yOffset + cosFix32(i) / circle03->size), circle03->color); \
							BMP_setPixel(circle04->x + circle04->xOffset + (sinFix32(i) / circle04->size), (circle04->y + circle04->yOffset + cosFix32(i) / circle04->size), circle04->color); \
							BMP_setPixel(circle05->x + circle05->xOffset + (sinFix32(i) / circle05->size), (circle05->y + circle05->yOffset + cosFix32(i) / circle05->size), circle05->color); \
							BMP_setPixel(circle06->x + circle06->xOffset + (sinFix32(i) / circle06->size), (circle06->y + circle06->yOffset + cosFix32(i) / circle06->size), circle06->color); \
							BMP_setPixel(circle07->x + circle07->xOffset + (sinFix32(i) / circle07->size), (circle07->y + circle07->yOffset + cosFix32(i) / circle07->size), circle07->color); \
							BMP_setPixel(circle08->x + circle08->xOffset + (sinFix32(i) / circle08->size), (circle08->y + circle08->yOffset + cosFix32(i) / circle08->size), circle08->color); \
							BMP_setPixel(circle09->x + circle09->xOffset + (sinFix32(i) / circle09->size), (circle09->y + circle09->yOffset + cosFix32(i) / circle09->size), circle09->color); \
							BMP_setPixel(circle10->x + circle10->xOffset + (sinFix32(i) / circle10->size), (circle10->y + circle10->yOffset + cosFix32(i) / circle10->size), circle10->color);

void tunnelA(){
	typedef struct circle circle;
	struct circle{
		u16 x;
		u16 y;
		u16 xOffset;
		u16 yOffset;
		u16 size;
		u16 color;
	};

	// make circles structures
	circle circle00, circle01, circle02, circle03, circle04, circle05, circle06, circle07, circle08, circle09, circle10;
	circle00.x = circle01.x = circle02.x = circle03.x = circle04.x = circle05.x = circle06.x = circle07.x = circle08.x = circle09.x = circle10.x = 80;
	circle00.y = circle01.y = circle02.y = circle03.y = circle04.y = circle05.y = circle06.y = circle07.y = circle08.y = circle09.y = circle10.y = 80;
	circle00.xOffset = circle01.xOffset = circle02.xOffset = circle03.xOffset = circle04.xOffset = circle05.xOffset = circle06.xOffset = circle07.xOffset = circle08.xOffset = circle09.xOffset = circle10.xOffset = 20;
	circle00.yOffset = circle01.yOffset = circle02.yOffset = circle03.yOffset = circle04.yOffset = circle05.yOffset = circle06.yOffset = circle07.yOffset = circle08.yOffset = circle09.yOffset = circle09.yOffset = 20;

	circle00.size = 101;
	circle01.size = 91;
	circle02.size = 81;
	circle03.size = 71;
	circle04.size = 61;
	circle05.size = 51;
	circle06.size = 41;
	circle07.size = 31;
	circle08.size = 21;
	circle09.size = 11;
	circle10.size = 1;

	circle00.color = circle01.color = circle02.color = circle03.color = circle04.color = circle05.color = circle06.color = circle07.color = circle08.color = circle09.color = circle10.color = 1;

	VDP_setScreenWidth256();
	BMP_init(TRUE, 0, FALSE);

	static void circleDraw(circle *circle00, circle *circle01, circle *circle02, circle *circle03, circle *circle04, circle *circle05, circle *circle06, circle *circle07, circle *circle08, circle *circle09, circle *circle10){
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
		circle09.xOffset++;
		circle10.xOffset++;
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
		circle09.xOffset--;
		circle10.xOffset--;
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
		circle09.yOffset++;
		circle10.yOffset++;
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
		circle09.yOffset--;
		circle10.yOffset--;
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
		circle09.size--;
		circle10.size--;
	}


	u16 vblCount = 0;
	u16 seq = 0;


	while (1){
		BMP_clear();
		BMP_showFPS(1);

		circleDraw(&circle00, &circle01, &circle02, &circle03, &circle04, &circle05, &circle06, &circle07, &circle08, &circle09, &circle10);
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
		if (circle09.size == 0){ circle09.size = 100; circle09.xOffset = 20; circle09.yOffset = 20; }
		if (circle10.size == 0){ circle10.size = 100; circle10.xOffset = 20; circle10.yOffset = 20; }

		if (circle00.size >= 80) { circle00.color = 0; }
		if (circle00.size > 70 && circle00.size < 80) { circle00.color = 1; }
		if (circle00.size > 60 && circle00.size < 70) { circle00.color = 2; }
		if (circle00.size > 50 && circle00.size < 60) { circle00.color = 3; }
		if (circle00.size > 40 && circle00.size < 50) { circle00.color = 4; }
		if (circle00.size > 30 && circle00.size < 40) { circle00.color = 5; }

		if (circle01.size >= 80) { circle01.color = 0; }
		if (circle01.size > 70 && circle01.size < 80) { circle01.color = 1; }
		if (circle01.size > 60 && circle01.size < 70) { circle01.color = 2; }
		if (circle01.size > 50 && circle01.size < 60) { circle01.color = 3; }
		if (circle01.size > 40 && circle01.size < 50) { circle01.color = 4; }
		if (circle01.size > 30 && circle01.size < 40) { circle01.color = 5; }

		if (circle02.size >= 80) { circle02.color = 0; }
		if (circle02.size > 70 && circle02.size < 80) { circle02.color = 1; }
		if (circle02.size > 60 && circle02.size < 70) { circle02.color = 2; }
		if (circle02.size > 50 && circle02.size < 60) { circle02.color = 3; }
		if (circle02.size > 40 && circle02.size < 50) { circle02.color = 4; }
		if (circle02.size > 30 && circle02.size < 40) { circle02.color = 5; }

		if (circle03.size >= 80) { circle03.color = 0; }
		if (circle03.size > 70 && circle03.size < 80) { circle03.color = 1; }
		if (circle03.size > 60 && circle03.size < 70) { circle03.color = 2; }
		if (circle03.size > 50 && circle03.size < 60) { circle03.color = 3; }
		if (circle03.size > 40 && circle03.size < 50) { circle03.color = 4; }
		if (circle03.size > 30 && circle03.size < 40) { circle03.color = 5; }

		if (circle04.size >= 80) { circle04.color = 0; }
		if (circle04.size > 70 && circle04.size < 80) { circle04.color = 1; }
		if (circle04.size > 60 && circle04.size < 70) { circle04.color = 2; }
		if (circle04.size > 50 && circle04.size < 60) { circle04.color = 3; }
		if (circle04.size > 40 && circle04.size < 50) { circle04.color = 4; }
		if (circle04.size > 30 && circle04.size < 40) { circle04.color = 5; }

		if (circle05.size >= 80) { circle05.color = 0; }
		if (circle05.size > 70 && circle05.size < 80) { circle05.color = 1; }
		if (circle05.size > 60 && circle05.size < 70) { circle05.color = 2; }
		if (circle05.size > 50 && circle05.size < 60) { circle05.color = 3; }
		if (circle05.size > 40 && circle05.size < 50) { circle05.color = 4; }
		if (circle05.size > 30 && circle05.size < 40) { circle05.color = 5; }

		if (circle06.size >= 80) { circle06.color = 0; }
		if (circle06.size > 70 && circle06.size < 80) { circle06.color = 1; }
		if (circle06.size > 60 && circle06.size < 70) { circle06.color = 2; }
		if (circle06.size > 50 && circle06.size < 60) { circle06.color = 3; }
		if (circle06.size > 40 && circle06.size < 50) { circle06.color = 4; }
		if (circle06.size > 30 && circle06.size < 40) { circle06.color = 5; }

		if (circle07.size >= 80) { circle07.color = 0; }
		if (circle07.size > 70 && circle07.size < 80) { circle07.color = 1; }
		if (circle07.size > 60 && circle07.size < 70) { circle07.color = 2; }
		if (circle07.size > 50 && circle07.size < 60) { circle07.color = 3; }
		if (circle07.size > 40 && circle07.size < 50) { circle07.color = 4; }
		if (circle07.size > 30 && circle07.size < 40) { circle07.color = 5; }

		if (circle08.size >= 80) { circle08.color = 0; }
		if (circle08.size > 70 && circle08.size < 80) { circle08.color = 1; }
		if (circle08.size > 60 && circle08.size < 70) { circle08.color = 2; }
		if (circle08.size > 50 && circle08.size < 60) { circle08.color = 3; }
		if (circle08.size > 40 && circle08.size < 50) { circle08.color = 4; }
		if (circle08.size > 30 && circle08.size < 40) { circle08.color = 5; }

		if (circle09.size >= 80) { circle09.color = 0; }
		if (circle09.size > 70 && circle09.size < 80) { circle09.color = 1; }
		if (circle09.size > 60 && circle09.size < 70) { circle09.color = 2; }
		if (circle09.size > 50 && circle09.size < 60) { circle09.color = 3; }
		if (circle09.size > 40 && circle09.size < 50) { circle09.color = 4; }
		if (circle09.size > 30 && circle09.size < 40) { circle09.color = 5; }

		if (circle10.size >= 80) { circle10.color = 0; }
		if (circle10.size > 70 && circle10.size < 80) { circle10.color = 1; }
		if (circle10.size > 60 && circle10.size < 70) { circle10.color = 2; }
		if (circle10.size > 50 && circle10.size < 60) { circle10.color = 3; }
		if (circle10.size > 40 && circle10.size < 50) { circle10.color = 4; }
		if (circle10.size > 30 && circle10.size < 40) { circle10.color = 5; }

		if (vblCount > 20 && seq == 0) seq++; 
		if (vblCount > 100 && seq == 1) seq++;
		if (vblCount > 200 && seq == 2) seq++;
		if (vblCount > 220 && seq == 3) seq++;

		vblCount++;
		BMP_flip(1);
		BMP_waitFlipComplete();
	}
}

#include <kdebug.h>
void tunnelPreca(){
#define CIRCLES_SETPIX	BMP_setPixel(circle00->x + circle00->xOffset + circleTab_x[circle00->size - 1][i], (circle00->y + circle00->yOffset + circleTab_y[circle00->size - 2][i]), 0xFF); \
						BMP_setPixel(circle01->x + circle01->xOffset + circleTab_x[circle01->size - 1][i], (circle01->y + circle01->yOffset + circleTab_y[circle01->size - 2][i]), 0xFF); \
						BMP_setPixel(circle02->x + circle02->xOffset + circleTab_x[circle02->size - 1][i], (circle02->y + circle02->yOffset + circleTab_y[circle02->size - 2][i]), 0xFF); \
						BMP_setPixel(circle03->x + circle03->xOffset + circleTab_x[circle03->size - 1][i], (circle03->y + circle03->yOffset + circleTab_y[circle03->size - 2][i]), 0xFF); \
						BMP_setPixel(circle04->x + circle04->xOffset + circleTab_x[circle04->size - 1][i], (circle04->y + circle04->yOffset + circleTab_y[circle04->size - 2][i]), 0xFF); \
						BMP_setPixel(circle05->x + circle05->xOffset + circleTab_x[circle05->size - 1][i], (circle05->y + circle05->yOffset + circleTab_y[circle05->size - 2][i]), 0xFF); \
						BMP_setPixel(circle06->x + circle06->xOffset + circleTab_x[circle06->size - 1][i], (circle06->y + circle06->yOffset + circleTab_y[circle06->size - 2][i]), 0xFF); \
						BMP_setPixel(circle07->x + circle07->xOffset + circleTab_x[circle07->size - 1][i], (circle07->y + circle07->yOffset + circleTab_y[circle07->size - 2][i]), 0xFF); \
						BMP_setPixel(circle08->x + circle08->xOffset + circleTab_x[circle08->size - 1][i], (circle08->y + circle08->yOffset + circleTab_y[circle08->size - 2][i]), 0xFF);

	typedef struct circle circle;
	struct circle{
		u16 x;
		u16 y;
		u16 xOffset;
		u16 yOffset;
		u16 size;
	};

	void circlesAllDraw(){
		u16 i = 0;
		u16 j = 50;
		for(j = 0; j < 80; j++){
			for (i = 0; i < 21; i++){
				BMP_setPixel(100 + circleTab_x[j][i], 100 + circleTab_y[j][i], 0xFF);
			}
		}
	}

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

	static void circleDraw(circle *circle00, circle *circle01, circle *circle02, circle *circle03, circle *circle04, circle *circle05, circle *circle06, circle *circle07, circle *circle08){
		//BMP_setPixel(circle00->x + circle00->xOffset + (sinFix32(i) / circle00->size), (circle00->y + circle00->yOffset + cosFix32(i) / circle00->size), 0xFF);
		//BMP_setPixel(circle00->x + circle00->xOffset + circleTab_x[circle00->size - 1][0], (circle00->y + circle00->yOffset + circleTab_y[circle00->size - 2][0]), 0xFF);
		u16 i = 0;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;
		CIRCLES_SETPIX
			i++;

	}

	static inline void circlesDraw(){
		circleDraw(&circle00, &circle01, &circle02, &circle03, &circle04, &circle05, &circle06, &circle07, &circle08);
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

	BMP_init(TRUE, 0, FALSE);

	while (1){
		BMP_clear();
		//circlesAllDraw();
		circlesDraw();
		//circle00.size--;
		circlesSizeSub();
		VDP_waitVSync();
		BMP_showFPS(1);

		if (circle00.size == 0){ circle00.size = 100; circle00.xOffset = 20; circle00.yOffset = 20; }
		if (circle01.size == 0){ circle01.size = 100; circle01.xOffset = 20; circle01.yOffset = 20; }
		if (circle02.size == 0){ circle02.size = 100; circle02.xOffset = 20; circle02.yOffset = 20; }
		if (circle03.size == 0){ circle03.size = 100; circle03.xOffset = 20; circle03.yOffset = 20; }
		if (circle04.size == 0){ circle04.size = 100; circle04.xOffset = 20; circle04.yOffset = 20; }
		if (circle05.size == 0){ circle05.size = 100; circle05.xOffset = 20; circle05.yOffset = 20; }
		if (circle06.size == 0){ circle06.size = 100; circle06.xOffset = 20; circle06.yOffset = 20; }
		if (circle07.size == 0){ circle07.size = 100; circle07.xOffset = 20; circle07.yOffset = 20; }
		if (circle08.size == 0){ circle08.size = 100; circle08.xOffset = 20; circle08.yOffset = 20; }
		BMP_flip(1);
		BMP_waitFlipComplete();
	}
}

