#ifndef TUNNEL_MACRO_H
#define TUNNEL_MACRO_H

#define CIRCLE_RES	55 //55

#ifdef WIRE_TUNNEL_ON
	#define LINES_MAX	300 //300
#endif

#ifdef DOT_TUNNEL_ON
#define RSE_recordPixel(A,B,C) v_cache[v_cache_index].pt.x = A; v_cache[v_cache_index].pt.y = B; v_cache[v_cache_index].col = C; v_cache_index++;

#define CIRCLES_SETPIX		\
							RSE_recordPixel(circle00.x + circle00.xOffset + (sinFix32(i) / circle00.size), (circle00.y + circle00.yOffset + cosFix32(i) / circle00.size), circle00.color); \
							RSE_recordPixel(circle01.x + circle01.xOffset + (sinFix32(i) / circle01.size), (circle01.y + circle01.yOffset + cosFix32(i) / circle01.size), circle01.color); \
							RSE_recordPixel(circle02.x + circle02.xOffset + (sinFix32(i) / circle02.size), (circle02.y + circle02.yOffset + cosFix32(i) / circle02.size), circle02.color); \
							RSE_recordPixel(circle03.x + circle03.xOffset + (sinFix32(i) / circle03.size), (circle03.y + circle03.yOffset + cosFix32(i) / circle03.size), circle03.color); \
							RSE_recordPixel(circle04.x + circle04.xOffset + (sinFix32(i) / circle04.size), (circle04.y + circle04.yOffset + cosFix32(i) / circle04.size), circle04.color); \
							RSE_recordPixel(circle05.x + circle05.xOffset + (sinFix32(i) / circle05.size), (circle05.y + circle05.yOffset + cosFix32(i) / circle05.size), circle05.color); \
							RSE_recordPixel(circle06.x + circle06.xOffset + (sinFix32(i) / circle06.size), (circle06.y + circle06.yOffset + cosFix32(i) / circle06.size), circle06.color); \
							RSE_recordPixel(circle07.x + circle07.xOffset + (sinFix32(i) / circle07.size), (circle07.y + circle07.yOffset + cosFix32(i) / circle07.size), circle07.color); \
							RSE_recordPixel(circle08.x + circle08.xOffset + (sinFix32(i) / circle08.size), (circle08.y + circle08.yOffset + cosFix32(i) / circle08.size), circle08.color); \
							RSE_recordPixel(circle09.x + circle09.xOffset + (sinFix32(i) / circle09.size), (circle09.y + circle09.yOffset + cosFix32(i) / circle09.size), circle09.color);
#endif

#ifdef DOT_TUNNEL_ON
#define circlesPrecalc	u16 i = 0; v_cache_index = 0; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX \
								i += CIRCLE_RES; \
							CIRCLES_SETPIX 
#endif

#ifdef WIRE_TUNNEL_ON
#define linePrecalc \
		u16 i = 0;																																							\
		u16 j = 0;																																							\
		u16 l_cache_index = 0;																																				\
		for (i = 0; i <= 8; i++){																																			\
			for (j = 0; j < 1024; j += CIRCLE_RES){																															\
				l_cache[l_cache_index].col = 0xFF;																															\
				l_cache[l_cache_index].pt1.x = l_cache[l_cache_index + 1].pt1.x = circlesSort[i]->x + circlesSort[i]->xOffset + (sinFix32(j) / circlesSort[i]->size);		\
				l_cache[l_cache_index].pt1.y = l_cache[l_cache_index + 1].pt1.y = circlesSort[i]->y + circlesSort[i]->yOffset + (cosFix32(j) / circlesSort[i]->size);		\
				l_cache[l_cache_index].pt2.x = circlesSort[i + 1]->x + circlesSort[i + 1]->xOffset + (sinFix32(j) / circlesSort[i + 1]->size);								\
				l_cache[l_cache_index].pt2.y = circlesSort[i + 1]->y + circlesSort[i + 1]->yOffset + (cosFix32(j) / circlesSort[i + 1]->size);								\
				l_cache_index++;																																			\
																																											\
																																											\
				l_cache[l_cache_index].pt2.x = circlesSort[i]->x + circlesSort[i]->xOffset + (sinFix32(j + CIRCLE_RES) / circlesSort[i]->size);								\
				l_cache[l_cache_index].pt2.y = circlesSort[i]->y + circlesSort[i]->yOffset + (cosFix32(j + CIRCLE_RES) / circlesSort[i]->size);								\
				l_cache[l_cache_index].col = 0xFF;																															\
				l_cache_index++;																																			\
						}																																								\
				}
#endif

#endif