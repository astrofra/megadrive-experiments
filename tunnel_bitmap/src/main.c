#include <genesis.h>


//#define DOT_TUNNEL_ON
#define WIRE_TUNNEL_ON
#include "tunnel_macro.h"

static void tunnelA();

int main(){
	tunnelA();
	return 0;
}

//	-------------------------------------------------------------------
//			TUNNEL A
// --------------------------------------------------------------------


#ifdef DOT_TUNNEL_ON
	#define PIXELS_MAX	256 
#endif


void tunnelA(){
	#ifdef DOT_TUNNEL_ON
	u16 v_cache_index = 0;
	Pixel v_cache[PIXELS_MAX];
	#endif
	#ifdef WIRE_TUNNEL_ON
	Line l_cache[LINES_MAX];
	#endif

	typedef struct circle circle;
	struct circle{
		s16 x;
		s16 y;
		u16 xOffset;
		u16 yOffset;
		s16 size;
		u16 color;
	};

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

	//from smallest to largest
	circle *circlesSort[10] = { &circle00, &circle01, &circle02, &circle03, &circle04, &circle05, &circle06, &circle07, &circle08, &circle09 };


	VDP_setScreenWidth256();
	BMP_init(TRUE, 0, FALSE);

	#define circlesXoffsetAdd	circle00.xOffset++;circle01.xOffset++;circle02.xOffset++;circle03.xOffset++;circle04.xOffset++;circle05.xOffset++;circle06.xOffset++;circle07.xOffset++;circle08.xOffset++;circle09.xOffset++;
	#define circlesXoffsetSub	circle00.xOffset--;circle01.xOffset--;circle02.xOffset--;circle03.xOffset--;circle04.xOffset--;circle05.xOffset--;circle06.xOffset--;circle07.xOffset--;circle08.xOffset--;circle09.xOffset--;
	#define circlesYoffsetAdd	circle00.yOffset++;circle01.yOffset++;circle02.yOffset++;circle03.yOffset++;circle04.yOffset++;circle05.yOffset++;circle06.yOffset++;circle07.yOffset++;circle08.yOffset++;circle09.yOffset++;
	#define circlesYoffsetSub	circle00.yOffset--;circle01.yOffset--;circle02.yOffset--;circle03.yOffset--;circle04.yOffset--;circle05.yOffset--;circle06.yOffset--;circle07.yOffset--;circle08.yOffset--;circle09.yOffset--;
	#define circlesSizeSub		circle00.size--;circle01.size--;circle02.size--;circle03.size--;circle04.size--;circle05.size--;circle06.size--;circle07.size--;circle08.size--;circle09.size--;
	
	#ifdef WIRE_TUNNEL_ON
	static inline void linesDrawFunc(){
		u16 i = 0;
		for (i = 0; i < LINES_MAX; i++){
			BMP_drawLine(&l_cache[i]);
		}
	}

	static inline void linePrecalcFunc(){
		u16 i = 0;
		u16 j = 0;
		u16 l_cache_index = 0;
		for (i = 0; i <= 8; i++){
			for (j = 0; j < 1024; j += CIRCLE_RES){
				l_cache[l_cache_index].col = 0xFF;
				l_cache[l_cache_index].pt1.x = l_cache[l_cache_index + 1].pt1.x = circlesSort[i]->x + circlesSort[i]->xOffset + (sinFix32(j) / circlesSort[i]->size);
				l_cache[l_cache_index].pt1.y = l_cache[l_cache_index + 1].pt1.y = circlesSort[i]->y + circlesSort[i]->yOffset + (cosFix32(j) / circlesSort[i]->size);
				l_cache[l_cache_index].pt2.x = circlesSort[i + 1]->x + circlesSort[i + 1]->xOffset + (sinFix32(j) / circlesSort[i + 1]->size);
				l_cache[l_cache_index].pt2.y = circlesSort[i + 1]->y + circlesSort[i + 1]->yOffset + (cosFix32(j) / circlesSort[i + 1]->size);
				l_cache_index++;


				l_cache[l_cache_index].pt2.x = circlesSort[i]->x + circlesSort[i]->xOffset + (sinFix32(j + CIRCLE_RES) / circlesSort[i]->size);
				l_cache[l_cache_index].pt2.y = circlesSort[i]->y + circlesSort[i]->yOffset + (cosFix32(j + CIRCLE_RES) / circlesSort[i]->size);
				l_cache[l_cache_index].col = 0xFF;
				l_cache_index++;
			}
		}
	}
	#endif

	u16 vblCount = 0;
	u16 seq = 0;

	while (1){	
		#ifdef DOT_TUNNEL_ON
		circlesPrecalc
		#endif
		#ifdef WIRE_TUNNEL_ON
		//linePrecalcFunc();
		linePrecalc
		#endif
		// ALL PRECA BEFORE WAITFLIPCOMPLETE
		BMP_waitFlipComplete();
		BMP_clear();
		BMP_showFPS(1);
		// DRAW
		#ifdef WIRE_TUNNEL_ON
		linesDraw

		#endif
		#ifdef DOT_TUNNEL_ON
		//Draw the pixel buffer
		BMP_setPixels(v_cache, 256); 
		#endif


		BMP_flip(1);

		circlesSizeSub

		switch (seq){	
		case 0:
			if (vblCount > 20) seq++;
			break;

		case 1:
			if (vblCount > 100) seq++;
			circlesXoffsetSub
			break;

		case 2:
			if (vblCount > 200) seq++;
			circlesXoffsetSub
			circlesYoffsetSub
			break;

		case 3:
			if (vblCount > 220) seq++;
			circlesXoffsetAdd
			break;

		case 4:
			circlesXoffsetAdd
			circlesYoffsetAdd
			break;

		default:
			break;
		}

		//seq = 0;

		if		(circle00.size == 0) { circle00.size = -1; }
		else if (circle01.size == 0) { circle01.size = -1; }
		else if (circle02.size == 0) { circle02.size = -1; }
		else if (circle03.size == 0) { circle03.size = -1; }
		else if (circle04.size == 0) { circle04.size = -1; }
		else if (circle05.size == 0) { circle05.size = -1; }
		else if (circle06.size == 0) { circle06.size = -1; }
		else if (circle07.size == 0) { circle07.size = -1; }
		else if (circle08.size == 0) { circle08.size = -1; }
		else if (circle09.size == 0) { circle09.size = -1; }

		if		(circle00.size == -15) { goto circle00_reset; }
		else if (circle01.size == -15) { goto circle01_reset; }
		else if (circle02.size == -15) { goto circle02_reset; }
		else if (circle03.size == -15) { goto circle03_reset; }
		else if (circle04.size == -15) { goto circle04_reset; }
		else if (circle05.size == -15) { goto circle05_reset; }
		else if (circle06.size == -15) { goto circle06_reset; }
		else if (circle07.size == -15) { goto circle07_reset; }
		else if (circle08.size == -15) { goto circle08_reset; }
		else if (circle09.size == -15) { goto circle09_reset; }
		goto circle_reset_end;

	circle00_reset:
		circle00.size = 101; circle00.xOffset = 20; circle00.yOffset = 20;
		//from smallest to largest
		circlesSort[0] = &circle00; circlesSort[1] = &circle01; circlesSort[2] = &circle02; circlesSort[3] = &circle03; circlesSort[4] = &circle04; circlesSort[5] = &circle05;
		circlesSort[6] = &circle06; circlesSort[7] = &circle07; circlesSort[8] = &circle08; circlesSort[9] = &circle09;
		goto circle_reset_end;

	circle01_reset:
		circle01.size = 101; circle01.xOffset = 20; circle01.yOffset = 20;
		circlesSort[0] = &circle01; circlesSort[1] = &circle02; circlesSort[2] = &circle03; circlesSort[3] = &circle04; circlesSort[4] = &circle05; circlesSort[5] = &circle06;
		circlesSort[6] = &circle07; circlesSort[7] = &circle08; circlesSort[8] = &circle09; circlesSort[9] = &circle00;
		goto circle_reset_end;

	circle02_reset:
		circle02.size = 101; circle02.xOffset = 20; circle02.yOffset = 20;
		circlesSort[0] = &circle02; circlesSort[1] = &circle03; circlesSort[2] = &circle04; circlesSort[3] = &circle05; circlesSort[4] = &circle06; circlesSort[5] = &circle07;
		circlesSort[6] = &circle08; circlesSort[7] = &circle09; circlesSort[8] = &circle00; circlesSort[9] = &circle01;
		goto circle_reset_end;

	circle03_reset:
		circle03.size = 101; circle03.xOffset = 20; circle03.yOffset = 20;
		circlesSort[0] = &circle03; circlesSort[1] = &circle04; circlesSort[2] = &circle05; circlesSort[3] = &circle06; circlesSort[4] = &circle07; circlesSort[5] = &circle08;
		circlesSort[6] = &circle09; circlesSort[7] = &circle00; circlesSort[8] = &circle01; circlesSort[9] = &circle02;
		goto circle_reset_end;

	circle04_reset:
		circle04.size = 101; circle04.xOffset = 20; circle04.yOffset = 20;
		circlesSort[0] = &circle04; circlesSort[1] = &circle05; circlesSort[2] = &circle06; circlesSort[3] = &circle07; circlesSort[4] = &circle08; circlesSort[5] = &circle09;
		circlesSort[6] = &circle00; circlesSort[7] = &circle01; circlesSort[8] = &circle02; circlesSort[9] = &circle03;
		goto circle_reset_end;

	circle05_reset:
		circle05.size = 101; circle05.xOffset = 20; circle05.yOffset = 20;
		circlesSort[0] = &circle05; circlesSort[1] = &circle06; circlesSort[2] = &circle07; circlesSort[3] = &circle08; circlesSort[4] = &circle09; circlesSort[5] = &circle00;
		circlesSort[6] = &circle01; circlesSort[7] = &circle02; circlesSort[8] = &circle03; circlesSort[9] = &circle04;
		goto circle_reset_end;

	circle06_reset:
		circle06.size = 101; circle06.xOffset = 20; circle06.yOffset = 20;
		circlesSort[0] = &circle06; circlesSort[1] = &circle07; circlesSort[2] = &circle08; circlesSort[3] = &circle09; circlesSort[4] = &circle00; circlesSort[5] = &circle01;
		circlesSort[6] = &circle02; circlesSort[7] = &circle03; circlesSort[8] = &circle04; circlesSort[9] = &circle05;
		goto circle_reset_end;

	circle07_reset:
		circle07.size = 101; circle07.xOffset = 20; circle07.yOffset = 20;
		circlesSort[0] = &circle07; circlesSort[1] = &circle08; circlesSort[2] = &circle09; circlesSort[3] = &circle00; circlesSort[4] = &circle01; circlesSort[5] = &circle02;
		circlesSort[6] = &circle03; circlesSort[7] = &circle04; circlesSort[8] = &circle05; circlesSort[9] = &circle06;
		goto circle_reset_end;

	circle08_reset:
		circle08.size = 101; circle08.xOffset = 20; circle08.yOffset = 20;
		circlesSort[0] = &circle08; circlesSort[1] = &circle09; circlesSort[2] = &circle00; circlesSort[3] = &circle01; circlesSort[4] = &circle02; circlesSort[5] = &circle03;
		circlesSort[6] = &circle04; circlesSort[7] = &circle05; circlesSort[8] = &circle06; circlesSort[9] = &circle07;
		goto circle_reset_end;

	circle09_reset:
		circle09.size = 101; circle09.xOffset = 20; circle09.yOffset = 20;
		circlesSort[0] = &circle09; circlesSort[1] = &circle00; circlesSort[2] = &circle01; circlesSort[3] = &circle02; circlesSort[4] = &circle03; circlesSort[5] = &circle04;
		circlesSort[6] = &circle05; circlesSort[7] = &circle06; circlesSort[8] = &circle07; circlesSort[9] = &circle08;
		goto circle_reset_end;

	circle_reset_end:
		if (circle00.size >= 80) { circle00.color = 0; }
		else if (circle00.size >= 70 && circle00.size < 80) { circle00.color = 1; }
		else if (circle00.size >= 60 && circle00.size < 70) { circle00.color = 2; }
		else if (circle00.size >= 50 && circle00.size < 60) { circle00.color = 3; }
		else if (circle00.size >= 40 && circle00.size < 50) { circle00.color = 4; }
		else if (circle00.size >= 30 && circle00.size < 40) { circle00.color = 5; }

		if (circle01.size >= 80) { circle01.color = 0; }
		else if (circle01.size >= 70 && circle01.size < 80) { circle01.color = 1; }
		else if (circle01.size >= 60 && circle01.size < 70) { circle01.color = 2; }
		else if (circle01.size >= 50 && circle01.size < 60) { circle01.color = 3; }
		else if (circle01.size >= 40 && circle01.size < 50) { circle01.color = 4; }
		else if (circle01.size >= 30 && circle01.size < 40) { circle01.color = 5; }

		if (circle02.size >= 80) { circle02.color = 0; }
		else if (circle02.size >= 70 && circle02.size < 80) { circle02.color = 1; }
		else if (circle02.size >= 60 && circle02.size < 70) { circle02.color = 2; }
		else if (circle02.size >= 50 && circle02.size < 60) { circle02.color = 3; }
		else if (circle02.size >= 40 && circle02.size < 50) { circle02.color = 4; }
		else if (circle02.size >= 30 && circle02.size < 40) { circle02.color = 5; }

		if (circle03.size >= 80) { circle03.color = 0; }
		else if (circle03.size >= 70 && circle03.size < 80) { circle03.color = 1; }
		else if (circle03.size >= 60 && circle03.size < 70) { circle03.color = 2; }
		else if (circle03.size >= 50 && circle03.size < 60) { circle03.color = 3; }
		else if (circle03.size >= 40 && circle03.size < 50) { circle03.color = 4; }
		else if (circle03.size >= 30 && circle03.size < 40) { circle03.color = 5; }

		if (circle04.size >= 80) { circle04.color = 0; }
		else if (circle04.size >= 70 && circle04.size < 80) { circle04.color = 1; }
		else if (circle04.size >= 60 && circle04.size < 70) { circle04.color = 2; }
		else if (circle04.size >= 50 && circle04.size < 60) { circle04.color = 3; }
		else if (circle04.size >= 40 && circle04.size < 50) { circle04.color = 4; }
		else if (circle04.size >= 30 && circle04.size < 40) { circle04.color = 5; }

		if (circle05.size >= 80) { circle05.color = 0; }
		else if (circle05.size >= 70 && circle05.size < 80) { circle05.color = 1; }
		else if (circle05.size >= 60 && circle05.size < 70) { circle05.color = 2; }
		else if (circle05.size >= 50 && circle05.size < 60) { circle05.color = 3; }
		else if (circle05.size >= 40 && circle05.size < 50) { circle05.color = 4; }
		else if (circle05.size >= 30 && circle05.size < 40) { circle05.color = 5; }

		if (circle06.size >= 80) { circle06.color = 0; }
		else if (circle06.size >= 70 && circle06.size < 80) { circle06.color = 1; }
		else if (circle06.size >= 60 && circle06.size < 70) { circle06.color = 2; }
		else if (circle06.size >= 50 && circle06.size < 60) { circle06.color = 3; }
		else if (circle06.size >= 40 && circle06.size < 50) { circle06.color = 4; }
		else if (circle06.size >= 30 && circle06.size < 40) { circle06.color = 5; }

		if (circle07.size >= 80) { circle07.color = 0; }
		else if (circle07.size >= 70 && circle07.size < 80) { circle07.color = 1; }
		else if (circle07.size >= 60 && circle07.size < 70) { circle07.color = 2; }
		else if (circle07.size >= 50 && circle07.size < 60) { circle07.color = 3; }
		else if (circle07.size >= 40 && circle07.size < 50) { circle07.color = 4; }
		else if (circle07.size >= 30 && circle07.size < 40) { circle07.color = 5; }

		if (circle08.size >= 80) { circle08.color = 0; }
		else if (circle08.size >= 70 && circle08.size < 80) { circle08.color = 1; }
		else if (circle08.size >= 60 && circle08.size < 70) { circle08.color = 2; }
		else if (circle08.size >= 50 && circle08.size < 60) { circle08.color = 3; }
		else if (circle08.size >= 40 && circle08.size < 50) { circle08.color = 4; }
		else if (circle08.size >= 30 && circle08.size < 40) { circle08.color = 5; }

		if (circle09.size >= 80) { circle09.color = 0; }
		else if (circle09.size >= 70 && circle09.size < 80) { circle09.color = 1; }
		else if (circle09.size >= 60 && circle09.size < 70) { circle09.color = 2; }
		else if (circle09.size >= 50 && circle09.size < 60) { circle09.color = 3; }
		else if (circle09.size >= 40 && circle09.size < 50) { circle09.color = 4; }
		else if (circle09.size >= 30 && circle09.size < 40) { circle09.color = 5; }

		vblCount++;		
	}
}
