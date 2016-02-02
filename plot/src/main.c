#include <genesis.h>
void tunnelA();
void tunnelPreca();

int main(){
	tunnelA();
	//tunnelPreca();
	return 0;
}

//	-------------------------------------------------------------------
//			TUNNEL A
// --------------------------------------------------------------------
#define CIRCLE_RES	55 //50

#define CIRCLES_SETPIX 		BMP_setPixel(circle00.x + circle00.xOffset + (sinFix32(i) / circle00.size), (circle00.y + circle00.yOffset + cosFix32(i) / circle00.size), circle00.color); \
							BMP_setPixel(circle01.x + circle01.xOffset + (sinFix32(i) / circle01.size), (circle01.y + circle01.yOffset + cosFix32(i) / circle01.size), circle01.color); \
							BMP_setPixel(circle02.x + circle02.xOffset + (sinFix32(i) / circle02.size), (circle02.y + circle02.yOffset + cosFix32(i) / circle02.size), circle02.color); \
							BMP_setPixel(circle03.x + circle03.xOffset + (sinFix32(i) / circle03.size), (circle03.y + circle03.yOffset + cosFix32(i) / circle03.size), circle03.color); \
							BMP_setPixel(circle04.x + circle04.xOffset + (sinFix32(i) / circle04.size), (circle04.y + circle04.yOffset + cosFix32(i) / circle04.size), circle04.color); \
							BMP_setPixel(circle05.x + circle05.xOffset + (sinFix32(i) / circle05.size), (circle05.y + circle05.yOffset + cosFix32(i) / circle05.size), circle05.color); \
							BMP_setPixel(circle06.x + circle06.xOffset + (sinFix32(i) / circle06.size), (circle06.y + circle06.yOffset + cosFix32(i) / circle06.size), circle06.color); \
							BMP_setPixel(circle07.x + circle07.xOffset + (sinFix32(i) / circle07.size), (circle07.y + circle07.yOffset + cosFix32(i) / circle07.size), circle07.color); \
							BMP_setPixel(circle08.x + circle08.xOffset + (sinFix32(i) / circle08.size), (circle08.y + circle08.yOffset + cosFix32(i) / circle08.size), circle08.color); \
							BMP_setPixel(circle09.x + circle09.xOffset + (sinFix32(i) / circle09.size), (circle09.y + circle09.yOffset + cosFix32(i) / circle09.size), circle09.color); \


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

	static inline void LINES_SET(circle circle00, circle circle01, circle circle02, circle circle03, circle circle04, circle circle05, circle circle06, circle circle07, circle circle08, circle circle09){
		u16 i = 0;
		for (i = 1; i < 1024; i += CIRCLE_RES){
			Line l;
			Vect2D_s16 start, end;
			start.x = circle00.x + circle00.xOffset + (sinFix32(i) / circle00.size);
			start.y = circle00.y + circle00.yOffset + (cosFix32(i) / circle00.size);
			end.x = circle01.x + circle01.xOffset + (sinFix32(i) / circle01.size);
			end.y = circle01.y + circle01.yOffset + (cosFix32(i) / circle01.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle00.color;
			BMP_drawLine(&l);

			start.x = circle01.x + circle01.xOffset + (sinFix32(i) / circle01.size);
			start.y = circle01.y + circle01.yOffset + (cosFix32(i) / circle01.size);
			end.x = circle02.x + circle01.xOffset + (sinFix32(i) / circle02.size);
			end.y = circle02.y + circle01.yOffset + (cosFix32(i) / circle02.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle01.color;
			BMP_drawLine(&l);

			start.x = circle02.x + circle02.xOffset + (sinFix32(i) / circle02.size);
			start.y = circle02.y + circle02.yOffset + (cosFix32(i) / circle02.size);
			end.x = circle03.x + circle03.xOffset + (sinFix32(i) / circle03.size);
			end.y = circle03.y + circle03.yOffset + (cosFix32(i) / circle03.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle02.color;
			BMP_drawLine(&l);

			start.x = circle03.x + circle03.xOffset + (sinFix32(i) / circle03.size);
			start.y = circle03.y + circle03.yOffset + (cosFix32(i) / circle03.size);
			end.x = circle04.x + circle04.xOffset + (sinFix32(i) / circle04.size);
			end.y = circle04.y + circle04.yOffset + (cosFix32(i) / circle04.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle03.color;
			BMP_drawLine(&l);

			start.x = circle04.x + circle04.xOffset + (sinFix32(i) / circle04.size);
			start.y = circle04.y + circle04.yOffset + (cosFix32(i) / circle04.size);
			end.x = circle05.x + circle05.xOffset + (sinFix32(i) / circle05.size);
			end.y = circle05.y + circle05.yOffset + (cosFix32(i) / circle05.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle04.color;
			BMP_drawLine(&l);

			start.x = circle05.x + circle05.xOffset + (sinFix32(i) / circle05.size);
			start.y = circle05.y + circle05.yOffset + (cosFix32(i) / circle05.size);
			end.x = circle06.x + circle06.xOffset + (sinFix32(i) / circle06.size);
			end.y = circle06.y + circle06.yOffset + (cosFix32(i) / circle06.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle05.color;
			BMP_drawLine(&l);

			start.x = circle06.x + circle06.xOffset + (sinFix32(i) / circle06.size);
			start.y = circle06.y + circle06.yOffset + (cosFix32(i) / circle06.size);
			end.x = circle07.x + circle07.xOffset + (sinFix32(i) / circle07.size);
			end.y = circle07.y + circle07.yOffset + (cosFix32(i) / circle07.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle06.color;
			BMP_drawLine(&l);

			start.x = circle07.x + circle07.xOffset + (sinFix32(i) / circle07.size);
			start.y = circle07.y + circle07.yOffset + (cosFix32(i) / circle07.size);
			end.x = circle08.x + circle08.xOffset + (sinFix32(i) / circle08.size);
			end.y = circle08.y + circle08.yOffset + (cosFix32(i) / circle08.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle07.color;
			BMP_drawLine(&l);

			start.x = circle08.x + circle08.xOffset + (sinFix32(i) / circle08.size);
			start.y = circle08.y + circle08.yOffset + (cosFix32(i) / circle08.size);
			end.x = circle09.x + circle09.xOffset + (sinFix32(i) / circle09.size);
			end.y = circle09.y + circle09.yOffset + (cosFix32(i) / circle09.size);
			l.pt1 = start;
			l.pt2 = end;
			l.col = circle08.color;
			BMP_drawLine(&l);

		}
	}


	// make circles structures
	circle circle00, circle01, circle02, circle03, circle04, circle05, circle06, circle07, circle08, circle09;
	circle00.x = circle01.x = circle02.x = circle03.x = circle04.x = circle05.x = circle06.x = circle07.x = circle08.x = circle09.x = 80;
	circle00.y = circle01.y = circle02.y = circle03.y = circle04.y = circle05.y = circle06.y = circle07.y = circle08.y = circle09.y = 80;
	circle00.xOffset = circle01.xOffset = circle02.xOffset = circle03.xOffset = circle04.xOffset = circle05.xOffset = circle06.xOffset = circle07.xOffset = circle08.xOffset = circle09.xOffset = 20;
	circle00.yOffset = circle01.yOffset = circle02.yOffset = circle03.yOffset = circle04.yOffset = circle05.yOffset = circle06.yOffset = circle07.yOffset = circle08.yOffset = circle09.yOffset = 20;

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

	circle00.color = circle01.color = circle02.color = circle03.color = circle04.color = circle05.color = circle06.color = circle07.color = circle08.color = circle09.color = 1;

	VDP_setScreenWidth256();
	BMP_init(TRUE, 0, FALSE);

	#define circlesDraw		u16 i = 0; \
							for (i = 1; i < 1024; i += CIRCLE_RES){ \
								CIRCLES_SETPIX \
							} \


	#define circlesXoffsetAdd	circle00.xOffset++;circle01.xOffset++;circle02.xOffset++;circle03.xOffset++;circle04.xOffset++;circle05.xOffset++;circle06.xOffset++;circle07.xOffset++;circle08.xOffset++;circle09.xOffset++;
	#define circlesXoffsetSub	circle00.xOffset--;circle01.xOffset--;circle02.xOffset--;circle03.xOffset--;circle04.xOffset--;circle05.xOffset--;circle06.xOffset--;circle07.xOffset--;circle08.xOffset--;circle09.xOffset--;
	#define circlesYoffsetAdd	circle00.yOffset++;circle01.yOffset++;circle02.yOffset++;circle03.yOffset++;circle04.yOffset++;circle05.yOffset++;circle06.yOffset++;circle07.yOffset++;circle08.yOffset++;circle09.yOffset++;
	#define circlesYoffsetSub	circle00.yOffset--;circle01.yOffset--;circle02.yOffset--;circle03.yOffset--;circle04.yOffset--;circle05.yOffset--;circle06.yOffset--;circle07.yOffset--;circle08.yOffset--;circle09.yOffset--;
	#define circlesSizeSub		circle00.size--;circle01.size--;circle02.size--;circle03.size--;circle04.size--;circle05.size--;circle06.size--;circle07.size--;circle08.size--;circle09.size--;

	u16 vblCount = 0;
	u16 seq = 0;

	while (1){		
		BMP_clear();
		BMP_showFPS(1);

		circlesDraw

		//WIREFRAME
		//LINES_SET(circle00, circle01, circle02, circle03, circle04, circle05, circle06, circle07, circle08, circle09);


		circlesSizeSub

		switch (seq)
		{
		case 1:
			circlesXoffsetSub
			break;

		case 2:
			circlesXoffsetSub
			circlesYoffsetSub
			break;

		case 3:
			circlesXoffsetAdd
			break;

		case 4:
			circlesXoffsetAdd
			circlesYoffsetAdd
			break;

		default:
			break;
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

		if (vblCount > 20 && seq == 0) seq++; 
		if (vblCount > 100 && seq == 1) seq++;
		if (vblCount > 200 && seq == 2) seq++;
		if (vblCount > 220 && seq == 3) seq++;

		vblCount++;
		//seq = 0;
		BMP_flip(1);
		BMP_waitFlipComplete();
	}
}
