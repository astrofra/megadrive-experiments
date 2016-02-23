#ifndef TUNNEL_MACRO_H
#define TUNNEL_MACRO_H

#define CIRCLE_RES 55

#ifdef WIRE_TUNNEL_ON
  #define LINES_MAX 304
#endif

#ifdef DOT_TUNNEL_ON
#define RSE_recordPixel(A,B,C) v_cache[v_cache_index].pt.x = A; v_cache[v_cache_index].pt.y = B; v_cache[v_cache_index].col = C; v_cache_index++;

#define CIRCLES_SETPIX     \
                          RSE_recordPixel(circle00.x + circle00.xOffset + (sinFix32(i) / circle00.size), (circle00.y + circle00.yOffset + cosFix32(i) / circle00.size), circle00.color);\
                          RSE_recordPixel(circle01.x + circle01.xOffset + (sinFix32(i) / circle01.size), (circle01.y + circle01.yOffset + cosFix32(i) / circle01.size), circle01.color);\
                          RSE_recordPixel(circle02.x + circle02.xOffset + (sinFix32(i) / circle02.size), (circle02.y + circle02.yOffset + cosFix32(i) / circle02.size), circle02.color);\
                          RSE_recordPixel(circle03.x + circle03.xOffset + (sinFix32(i) / circle03.size), (circle03.y + circle03.yOffset + cosFix32(i) / circle03.size), circle03.color);\
                          RSE_recordPixel(circle04.x + circle04.xOffset + (sinFix32(i) / circle04.size), (circle04.y + circle04.yOffset + cosFix32(i) / circle04.size), circle04.color);\
                          RSE_recordPixel(circle05.x + circle05.xOffset + (sinFix32(i) / circle05.size), (circle05.y + circle05.yOffset + cosFix32(i) / circle05.size), circle05.color);\
                          RSE_recordPixel(circle06.x + circle06.xOffset + (sinFix32(i) / circle06.size), (circle06.y + circle06.yOffset + cosFix32(i) / circle06.size), circle06.color);\
                          RSE_recordPixel(circle07.x + circle07.xOffset + (sinFix32(i) / circle07.size), (circle07.y + circle07.yOffset + cosFix32(i) / circle07.size), circle07.color);\
                          RSE_recordPixel(circle08.x + circle08.xOffset + (sinFix32(i) / circle08.size), (circle08.y + circle08.yOffset + cosFix32(i) / circle08.size), circle08.color);\
                          RSE_recordPixel(circle09.x + circle09.xOffset + (sinFix32(i) / circle09.size), (circle09.y + circle09.yOffset + cosFix32(i) / circle09.size), circle09.color);
#endif

#ifdef DOT_TUNNEL_ON
#define circlesPrecalc	u16 i = 0; v_cache_index = 0;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                  CIRCLES_SETPIX\
                                  i += CIRCLE_RES;\
                                      CIRCLES_SETPIX
#endif

#ifdef WIRE_TUNNEL_ON
#define linePrecalc \
                  l_cache[0].col = circlesSort[0]->color;\
                  l_cache[0].pt1.x = l_cache[1].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (0 / circlesSort[0]->size);\
                  l_cache[0].pt1.y = l_cache[1].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (1024 / circlesSort[0]->size);\
                  l_cache[0].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (0 / circlesSort[1]->size);\
                  l_cache[0].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (1024 / circlesSort[1]->size);\
                  \
                  l_cache[1].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (339 / circlesSort[0]->size);\
                  l_cache[1].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (966 / circlesSort[0]->size);\
                  l_cache[1].col = circlesSort[0]->color;\
                  \
                  l_cache[2].col = circlesSort[0]->color;\
                  l_cache[2].pt1.x = l_cache[3].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (339 / circlesSort[0]->size);\
                  l_cache[2].pt1.y = l_cache[3].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (966 / circlesSort[0]->size);\
                  l_cache[2].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (339 / circlesSort[1]->size);\
                  l_cache[2].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (966 / circlesSort[1]->size);\
                  \
                  l_cache[3].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (640 / circlesSort[0]->size);\
                  l_cache[3].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (799 / circlesSort[0]->size);\
                  l_cache[3].col = circlesSort[0]->color;\
                  \
                  l_cache[4].col = circlesSort[0]->color;\
                  l_cache[4].pt1.x = l_cache[5].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (640 / circlesSort[0]->size);\
                  l_cache[4].pt1.y = l_cache[5].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (799 / circlesSort[0]->size);\
                  l_cache[4].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (640 / circlesSort[1]->size);\
                  l_cache[4].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (799 / circlesSort[1]->size);\
                  \
                  l_cache[5].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (868 / circlesSort[0]->size);\
                  l_cache[5].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (543 / circlesSort[0]->size);\
                  l_cache[5].col = circlesSort[0]->color;\
                  \
                  l_cache[6].col = circlesSort[0]->color;\
                  l_cache[6].pt1.x = l_cache[7].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (868 / circlesSort[0]->size);\
                  l_cache[6].pt1.y = l_cache[7].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (543 / circlesSort[0]->size);\
                  l_cache[6].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (868 / circlesSort[1]->size);\
                  l_cache[6].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (543 / circlesSort[1]->size);\
                  \
                  l_cache[7].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (999 / circlesSort[0]->size);\
                  l_cache[7].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (224 / circlesSort[0]->size);\
                  l_cache[7].col = circlesSort[0]->color;\
                  \
                  l_cache[8].col = circlesSort[0]->color;\
                  l_cache[8].pt1.x = l_cache[9].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (999 / circlesSort[0]->size);\
                  l_cache[8].pt1.y = l_cache[9].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (224 / circlesSort[0]->size);\
                  l_cache[8].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (999 / circlesSort[1]->size);\
                  l_cache[8].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (224 / circlesSort[1]->size);\
                  \
                  l_cache[9].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (1017 / circlesSort[0]->size);\
                  l_cache[9].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-119 / circlesSort[0]->size);\
                  l_cache[9].col = circlesSort[0]->color;\
                  \
                  l_cache[10].col = circlesSort[0]->color;\
                  l_cache[10].pt1.x = l_cache[11].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (1017 / circlesSort[0]->size);\
                  l_cache[10].pt1.y = l_cache[11].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-119 / circlesSort[0]->size);\
                  l_cache[10].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (1017 / circlesSort[1]->size);\
                  l_cache[10].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-119 / circlesSort[1]->size);\
                  \
                  l_cache[11].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (920 / circlesSort[0]->size);\
                  l_cache[11].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-449 / circlesSort[0]->size);\
                  l_cache[11].col = circlesSort[0]->color;\
                  \
                  l_cache[12].col = circlesSort[0]->color;\
                  l_cache[12].pt1.x = l_cache[13].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (920 / circlesSort[0]->size);\
                  l_cache[12].pt1.y = l_cache[13].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-449 / circlesSort[0]->size);\
                  l_cache[12].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (920 / circlesSort[1]->size);\
                  l_cache[12].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-449 / circlesSort[1]->size);\
                  \
                  l_cache[13].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (720 / circlesSort[0]->size);\
                  l_cache[13].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-729 / circlesSort[0]->size);\
                  l_cache[13].col = circlesSort[0]->color;\
                  \
                  l_cache[14].col = circlesSort[0]->color;\
                  l_cache[14].pt1.x = l_cache[15].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (720 / circlesSort[0]->size);\
                  l_cache[14].pt1.y = l_cache[15].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-729 / circlesSort[0]->size);\
                  l_cache[14].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (720 / circlesSort[1]->size);\
                  l_cache[14].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-729 / circlesSort[1]->size);\
                  \
                  l_cache[15].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (438 / circlesSort[0]->size);\
                  l_cache[15].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-926 / circlesSort[0]->size);\
                  l_cache[15].col = circlesSort[0]->color;\
                  \
                  l_cache[16].col = circlesSort[0]->color;\
                  l_cache[16].pt1.x = l_cache[17].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (438 / circlesSort[0]->size);\
                  l_cache[16].pt1.y = l_cache[17].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-926 / circlesSort[0]->size);\
                  l_cache[16].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (438 / circlesSort[1]->size);\
                  l_cache[16].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-926 / circlesSort[1]->size);\
                  \
                  l_cache[17].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (107 / circlesSort[0]->size);\
                  l_cache[17].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-1018 / circlesSort[0]->size);\
                  l_cache[17].col = circlesSort[0]->color;\
                  \
                  l_cache[18].col = circlesSort[0]->color;\
                  l_cache[18].pt1.x = l_cache[19].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (107 / circlesSort[0]->size);\
                  l_cache[18].pt1.y = l_cache[19].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-1018 / circlesSort[0]->size);\
                  l_cache[18].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (107 / circlesSort[1]->size);\
                  l_cache[18].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-1018 / circlesSort[1]->size);\
                  \
                  l_cache[19].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-237 / circlesSort[0]->size);\
                  l_cache[19].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-996 / circlesSort[0]->size);\
                  l_cache[19].col = circlesSort[0]->color;\
                  \
                  l_cache[20].col = circlesSort[0]->color;\
                  l_cache[20].pt1.x = l_cache[21].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-237 / circlesSort[0]->size);\
                  l_cache[20].pt1.y = l_cache[21].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-996 / circlesSort[0]->size);\
                  l_cache[20].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-237 / circlesSort[1]->size);\
                  l_cache[20].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-996 / circlesSort[1]->size);\
                  \
                  l_cache[21].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-553 / circlesSort[0]->size);\
                  l_cache[21].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-862 / circlesSort[0]->size);\
                  l_cache[21].col = circlesSort[0]->color;\
                  \
                  l_cache[22].col = circlesSort[0]->color;\
                  l_cache[22].pt1.x = l_cache[23].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-553 / circlesSort[0]->size);\
                  l_cache[22].pt1.y = l_cache[23].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-862 / circlesSort[0]->size);\
                  l_cache[22].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-553 / circlesSort[1]->size);\
                  l_cache[22].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-862 / circlesSort[1]->size);\
                  \
                  l_cache[23].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-807 / circlesSort[0]->size);\
                  l_cache[23].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-630 / circlesSort[0]->size);\
                  l_cache[23].col = circlesSort[0]->color;\
                  \
                  l_cache[24].col = circlesSort[0]->color;\
                  l_cache[24].pt1.x = l_cache[25].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-807 / circlesSort[0]->size);\
                  l_cache[24].pt1.y = l_cache[25].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-630 / circlesSort[0]->size);\
                  l_cache[24].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-807 / circlesSort[1]->size);\
                  l_cache[24].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-630 / circlesSort[1]->size);\
                  \
                  l_cache[25].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-970 / circlesSort[0]->size);\
                  l_cache[25].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-327 / circlesSort[0]->size);\
                  l_cache[25].col = circlesSort[0]->color;\
                  \
                  l_cache[26].col = circlesSort[0]->color;\
                  l_cache[26].pt1.x = l_cache[27].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-970 / circlesSort[0]->size);\
                  l_cache[26].pt1.y = l_cache[27].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (-327 / circlesSort[0]->size);\
                  l_cache[26].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-970 / circlesSort[1]->size);\
                  l_cache[26].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-327 / circlesSort[1]->size);\
                  \
                  l_cache[27].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-1024 / circlesSort[0]->size);\
                  l_cache[27].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (13 / circlesSort[0]->size);\
                  l_cache[27].col = circlesSort[0]->color;\
                  \
                  l_cache[28].col = circlesSort[0]->color;\
                  l_cache[28].pt1.x = l_cache[29].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-1024 / circlesSort[0]->size);\
                  l_cache[28].pt1.y = l_cache[29].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (13 / circlesSort[0]->size);\
                  l_cache[28].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-1024 / circlesSort[1]->size);\
                  l_cache[28].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (13 / circlesSort[1]->size);\
                  \
                  l_cache[29].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-962 / circlesSort[0]->size);\
                  l_cache[29].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (351 / circlesSort[0]->size);\
                  l_cache[29].col = circlesSort[0]->color;\
                  \
                  l_cache[30].col = circlesSort[0]->color;\
                  l_cache[30].pt1.x = l_cache[31].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-962 / circlesSort[0]->size);\
                  l_cache[30].pt1.y = l_cache[31].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (351 / circlesSort[0]->size);\
                  l_cache[30].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-962 / circlesSort[1]->size);\
                  l_cache[30].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (351 / circlesSort[1]->size);\
                  \
                  l_cache[31].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-792 / circlesSort[0]->size);\
                  l_cache[31].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (650 / circlesSort[0]->size);\
                  l_cache[31].col = circlesSort[0]->color;\
                  \
                  l_cache[32].col = circlesSort[0]->color;\
                  l_cache[32].pt1.x = l_cache[33].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-792 / circlesSort[0]->size);\
                  l_cache[32].pt1.y = l_cache[33].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (650 / circlesSort[0]->size);\
                  l_cache[32].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-792 / circlesSort[1]->size);\
                  l_cache[32].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (650 / circlesSort[1]->size);\
                  \
                  l_cache[33].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-532 / circlesSort[0]->size);\
                  l_cache[33].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (875 / circlesSort[0]->size);\
                  l_cache[33].col = circlesSort[0]->color;\
                  \
                  l_cache[34].col = circlesSort[0]->color;\
                  l_cache[34].pt1.x = l_cache[35].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-532 / circlesSort[0]->size);\
                  l_cache[34].pt1.y = l_cache[35].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (875 / circlesSort[0]->size);\
                  l_cache[34].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-532 / circlesSort[1]->size);\
                  l_cache[34].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (875 / circlesSort[1]->size);\
                  \
                  l_cache[35].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-212 / circlesSort[0]->size);\
                  l_cache[35].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (1002 / circlesSort[0]->size);\
                  l_cache[35].col = circlesSort[0]->color;\
                  \
                  l_cache[36].col = circlesSort[0]->color;\
                  l_cache[36].pt1.x = l_cache[37].pt1.x = circlesSort[0]->x + circlesSort[0]->xOffset + (-212 / circlesSort[0]->size);\
                  l_cache[36].pt1.y = l_cache[37].pt1.y = circlesSort[0]->y + circlesSort[0]->yOffset + (1002 / circlesSort[0]->size);\
                  l_cache[36].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-212 / circlesSort[1]->size);\
                  l_cache[36].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (1002 / circlesSort[1]->size);\
                  \
                  l_cache[37].pt2.x = circlesSort[0]->x + circlesSort[0]->xOffset + (132 / circlesSort[0]->size);\
                  l_cache[37].pt2.y = circlesSort[0]->y + circlesSort[0]->yOffset + (1016 / circlesSort[0]->size);\
                  l_cache[37].col = circlesSort[0]->color;\
                  \
                  l_cache[38].col = circlesSort[1]->color;\
                  l_cache[38].pt1.x = l_cache[39].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (0 / circlesSort[1]->size);\
                  l_cache[38].pt1.y = l_cache[39].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (1024 / circlesSort[1]->size);\
                  l_cache[38].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (0 / circlesSort[2]->size);\
                  l_cache[38].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (1024 / circlesSort[2]->size);\
                  \
                  l_cache[39].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (339 / circlesSort[1]->size);\
                  l_cache[39].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (966 / circlesSort[1]->size);\
                  l_cache[39].col = circlesSort[1]->color;\
                  \
                  l_cache[40].col = circlesSort[1]->color;\
                  l_cache[40].pt1.x = l_cache[41].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (339 / circlesSort[1]->size);\
                  l_cache[40].pt1.y = l_cache[41].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (966 / circlesSort[1]->size);\
                  l_cache[40].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (339 / circlesSort[2]->size);\
                  l_cache[40].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (966 / circlesSort[2]->size);\
                  \
                  l_cache[41].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (640 / circlesSort[1]->size);\
                  l_cache[41].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (799 / circlesSort[1]->size);\
                  l_cache[41].col = circlesSort[1]->color;\
                  \
                  l_cache[42].col = circlesSort[1]->color;\
                  l_cache[42].pt1.x = l_cache[43].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (640 / circlesSort[1]->size);\
                  l_cache[42].pt1.y = l_cache[43].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (799 / circlesSort[1]->size);\
                  l_cache[42].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (640 / circlesSort[2]->size);\
                  l_cache[42].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (799 / circlesSort[2]->size);\
                  \
                  l_cache[43].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (868 / circlesSort[1]->size);\
                  l_cache[43].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (543 / circlesSort[1]->size);\
                  l_cache[43].col = circlesSort[1]->color;\
                  \
                  l_cache[44].col = circlesSort[1]->color;\
                  l_cache[44].pt1.x = l_cache[45].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (868 / circlesSort[1]->size);\
                  l_cache[44].pt1.y = l_cache[45].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (543 / circlesSort[1]->size);\
                  l_cache[44].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (868 / circlesSort[2]->size);\
                  l_cache[44].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (543 / circlesSort[2]->size);\
                  \
                  l_cache[45].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (999 / circlesSort[1]->size);\
                  l_cache[45].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (224 / circlesSort[1]->size);\
                  l_cache[45].col = circlesSort[1]->color;\
                  \
                  l_cache[46].col = circlesSort[1]->color;\
                  l_cache[46].pt1.x = l_cache[47].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (999 / circlesSort[1]->size);\
                  l_cache[46].pt1.y = l_cache[47].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (224 / circlesSort[1]->size);\
                  l_cache[46].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (999 / circlesSort[2]->size);\
                  l_cache[46].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (224 / circlesSort[2]->size);\
                  \
                  l_cache[47].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (1017 / circlesSort[1]->size);\
                  l_cache[47].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-119 / circlesSort[1]->size);\
                  l_cache[47].col = circlesSort[1]->color;\
                  \
                  l_cache[48].col = circlesSort[1]->color;\
                  l_cache[48].pt1.x = l_cache[49].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (1017 / circlesSort[1]->size);\
                  l_cache[48].pt1.y = l_cache[49].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-119 / circlesSort[1]->size);\
                  l_cache[48].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (1017 / circlesSort[2]->size);\
                  l_cache[48].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-119 / circlesSort[2]->size);\
                  \
                  l_cache[49].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (920 / circlesSort[1]->size);\
                  l_cache[49].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-449 / circlesSort[1]->size);\
                  l_cache[49].col = circlesSort[1]->color;\
                  \
                  l_cache[50].col = circlesSort[1]->color;\
                  l_cache[50].pt1.x = l_cache[51].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (920 / circlesSort[1]->size);\
                  l_cache[50].pt1.y = l_cache[51].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-449 / circlesSort[1]->size);\
                  l_cache[50].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (920 / circlesSort[2]->size);\
                  l_cache[50].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-449 / circlesSort[2]->size);\
                  \
                  l_cache[51].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (720 / circlesSort[1]->size);\
                  l_cache[51].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-729 / circlesSort[1]->size);\
                  l_cache[51].col = circlesSort[1]->color;\
                  \
                  l_cache[52].col = circlesSort[1]->color;\
                  l_cache[52].pt1.x = l_cache[53].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (720 / circlesSort[1]->size);\
                  l_cache[52].pt1.y = l_cache[53].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-729 / circlesSort[1]->size);\
                  l_cache[52].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (720 / circlesSort[2]->size);\
                  l_cache[52].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-729 / circlesSort[2]->size);\
                  \
                  l_cache[53].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (438 / circlesSort[1]->size);\
                  l_cache[53].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-926 / circlesSort[1]->size);\
                  l_cache[53].col = circlesSort[1]->color;\
                  \
                  l_cache[54].col = circlesSort[1]->color;\
                  l_cache[54].pt1.x = l_cache[55].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (438 / circlesSort[1]->size);\
                  l_cache[54].pt1.y = l_cache[55].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-926 / circlesSort[1]->size);\
                  l_cache[54].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (438 / circlesSort[2]->size);\
                  l_cache[54].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-926 / circlesSort[2]->size);\
                  \
                  l_cache[55].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (107 / circlesSort[1]->size);\
                  l_cache[55].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-1018 / circlesSort[1]->size);\
                  l_cache[55].col = circlesSort[1]->color;\
                  \
                  l_cache[56].col = circlesSort[1]->color;\
                  l_cache[56].pt1.x = l_cache[57].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (107 / circlesSort[1]->size);\
                  l_cache[56].pt1.y = l_cache[57].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-1018 / circlesSort[1]->size);\
                  l_cache[56].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (107 / circlesSort[2]->size);\
                  l_cache[56].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-1018 / circlesSort[2]->size);\
                  \
                  l_cache[57].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-237 / circlesSort[1]->size);\
                  l_cache[57].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-996 / circlesSort[1]->size);\
                  l_cache[57].col = circlesSort[1]->color;\
                  \
                  l_cache[58].col = circlesSort[1]->color;\
                  l_cache[58].pt1.x = l_cache[59].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-237 / circlesSort[1]->size);\
                  l_cache[58].pt1.y = l_cache[59].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-996 / circlesSort[1]->size);\
                  l_cache[58].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-237 / circlesSort[2]->size);\
                  l_cache[58].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-996 / circlesSort[2]->size);\
                  \
                  l_cache[59].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-553 / circlesSort[1]->size);\
                  l_cache[59].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-862 / circlesSort[1]->size);\
                  l_cache[59].col = circlesSort[1]->color;\
                  \
                  l_cache[60].col = circlesSort[1]->color;\
                  l_cache[60].pt1.x = l_cache[61].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-553 / circlesSort[1]->size);\
                  l_cache[60].pt1.y = l_cache[61].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-862 / circlesSort[1]->size);\
                  l_cache[60].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-553 / circlesSort[2]->size);\
                  l_cache[60].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-862 / circlesSort[2]->size);\
                  \
                  l_cache[61].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-807 / circlesSort[1]->size);\
                  l_cache[61].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-630 / circlesSort[1]->size);\
                  l_cache[61].col = circlesSort[1]->color;\
                  \
                  l_cache[62].col = circlesSort[1]->color;\
                  l_cache[62].pt1.x = l_cache[63].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-807 / circlesSort[1]->size);\
                  l_cache[62].pt1.y = l_cache[63].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-630 / circlesSort[1]->size);\
                  l_cache[62].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-807 / circlesSort[2]->size);\
                  l_cache[62].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-630 / circlesSort[2]->size);\
                  \
                  l_cache[63].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-970 / circlesSort[1]->size);\
                  l_cache[63].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-327 / circlesSort[1]->size);\
                  l_cache[63].col = circlesSort[1]->color;\
                  \
                  l_cache[64].col = circlesSort[1]->color;\
                  l_cache[64].pt1.x = l_cache[65].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-970 / circlesSort[1]->size);\
                  l_cache[64].pt1.y = l_cache[65].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (-327 / circlesSort[1]->size);\
                  l_cache[64].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-970 / circlesSort[2]->size);\
                  l_cache[64].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-327 / circlesSort[2]->size);\
                  \
                  l_cache[65].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-1024 / circlesSort[1]->size);\
                  l_cache[65].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (13 / circlesSort[1]->size);\
                  l_cache[65].col = circlesSort[1]->color;\
                  \
                  l_cache[66].col = circlesSort[1]->color;\
                  l_cache[66].pt1.x = l_cache[67].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-1024 / circlesSort[1]->size);\
                  l_cache[66].pt1.y = l_cache[67].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (13 / circlesSort[1]->size);\
                  l_cache[66].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-1024 / circlesSort[2]->size);\
                  l_cache[66].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (13 / circlesSort[2]->size);\
                  \
                  l_cache[67].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-962 / circlesSort[1]->size);\
                  l_cache[67].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (351 / circlesSort[1]->size);\
                  l_cache[67].col = circlesSort[1]->color;\
                  \
                  l_cache[68].col = circlesSort[1]->color;\
                  l_cache[68].pt1.x = l_cache[69].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-962 / circlesSort[1]->size);\
                  l_cache[68].pt1.y = l_cache[69].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (351 / circlesSort[1]->size);\
                  l_cache[68].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-962 / circlesSort[2]->size);\
                  l_cache[68].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (351 / circlesSort[2]->size);\
                  \
                  l_cache[69].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-792 / circlesSort[1]->size);\
                  l_cache[69].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (650 / circlesSort[1]->size);\
                  l_cache[69].col = circlesSort[1]->color;\
                  \
                  l_cache[70].col = circlesSort[1]->color;\
                  l_cache[70].pt1.x = l_cache[71].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-792 / circlesSort[1]->size);\
                  l_cache[70].pt1.y = l_cache[71].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (650 / circlesSort[1]->size);\
                  l_cache[70].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-792 / circlesSort[2]->size);\
                  l_cache[70].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (650 / circlesSort[2]->size);\
                  \
                  l_cache[71].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-532 / circlesSort[1]->size);\
                  l_cache[71].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (875 / circlesSort[1]->size);\
                  l_cache[71].col = circlesSort[1]->color;\
                  \
                  l_cache[72].col = circlesSort[1]->color;\
                  l_cache[72].pt1.x = l_cache[73].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-532 / circlesSort[1]->size);\
                  l_cache[72].pt1.y = l_cache[73].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (875 / circlesSort[1]->size);\
                  l_cache[72].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-532 / circlesSort[2]->size);\
                  l_cache[72].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (875 / circlesSort[2]->size);\
                  \
                  l_cache[73].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-212 / circlesSort[1]->size);\
                  l_cache[73].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (1002 / circlesSort[1]->size);\
                  l_cache[73].col = circlesSort[1]->color;\
                  \
                  l_cache[74].col = circlesSort[1]->color;\
                  l_cache[74].pt1.x = l_cache[75].pt1.x = circlesSort[1]->x + circlesSort[1]->xOffset + (-212 / circlesSort[1]->size);\
                  l_cache[74].pt1.y = l_cache[75].pt1.y = circlesSort[1]->y + circlesSort[1]->yOffset + (1002 / circlesSort[1]->size);\
                  l_cache[74].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-212 / circlesSort[2]->size);\
                  l_cache[74].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (1002 / circlesSort[2]->size);\
                  \
                  l_cache[75].pt2.x = circlesSort[1]->x + circlesSort[1]->xOffset + (132 / circlesSort[1]->size);\
                  l_cache[75].pt2.y = circlesSort[1]->y + circlesSort[1]->yOffset + (1016 / circlesSort[1]->size);\
                  l_cache[75].col = circlesSort[1]->color;\
                  \
                  l_cache[76].col = circlesSort[2]->color;\
                  l_cache[76].pt1.x = l_cache[77].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (0 / circlesSort[2]->size);\
                  l_cache[76].pt1.y = l_cache[77].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (1024 / circlesSort[2]->size);\
                  l_cache[76].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (0 / circlesSort[3]->size);\
                  l_cache[76].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (1024 / circlesSort[3]->size);\
                  \
                  l_cache[77].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (339 / circlesSort[2]->size);\
                  l_cache[77].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (966 / circlesSort[2]->size);\
                  l_cache[77].col = circlesSort[2]->color;\
                  \
                  l_cache[78].col = circlesSort[2]->color;\
                  l_cache[78].pt1.x = l_cache[79].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (339 / circlesSort[2]->size);\
                  l_cache[78].pt1.y = l_cache[79].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (966 / circlesSort[2]->size);\
                  l_cache[78].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (339 / circlesSort[3]->size);\
                  l_cache[78].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (966 / circlesSort[3]->size);\
                  \
                  l_cache[79].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (640 / circlesSort[2]->size);\
                  l_cache[79].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (799 / circlesSort[2]->size);\
                  l_cache[79].col = circlesSort[2]->color;\
                  \
                  l_cache[80].col = circlesSort[2]->color;\
                  l_cache[80].pt1.x = l_cache[81].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (640 / circlesSort[2]->size);\
                  l_cache[80].pt1.y = l_cache[81].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (799 / circlesSort[2]->size);\
                  l_cache[80].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (640 / circlesSort[3]->size);\
                  l_cache[80].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (799 / circlesSort[3]->size);\
                  \
                  l_cache[81].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (868 / circlesSort[2]->size);\
                  l_cache[81].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (543 / circlesSort[2]->size);\
                  l_cache[81].col = circlesSort[2]->color;\
                  \
                  l_cache[82].col = circlesSort[2]->color;\
                  l_cache[82].pt1.x = l_cache[83].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (868 / circlesSort[2]->size);\
                  l_cache[82].pt1.y = l_cache[83].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (543 / circlesSort[2]->size);\
                  l_cache[82].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (868 / circlesSort[3]->size);\
                  l_cache[82].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (543 / circlesSort[3]->size);\
                  \
                  l_cache[83].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (999 / circlesSort[2]->size);\
                  l_cache[83].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (224 / circlesSort[2]->size);\
                  l_cache[83].col = circlesSort[2]->color;\
                  \
                  l_cache[84].col = circlesSort[2]->color;\
                  l_cache[84].pt1.x = l_cache[85].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (999 / circlesSort[2]->size);\
                  l_cache[84].pt1.y = l_cache[85].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (224 / circlesSort[2]->size);\
                  l_cache[84].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (999 / circlesSort[3]->size);\
                  l_cache[84].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (224 / circlesSort[3]->size);\
                  \
                  l_cache[85].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (1017 / circlesSort[2]->size);\
                  l_cache[85].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-119 / circlesSort[2]->size);\
                  l_cache[85].col = circlesSort[2]->color;\
                  \
                  l_cache[86].col = circlesSort[2]->color;\
                  l_cache[86].pt1.x = l_cache[87].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (1017 / circlesSort[2]->size);\
                  l_cache[86].pt1.y = l_cache[87].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-119 / circlesSort[2]->size);\
                  l_cache[86].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (1017 / circlesSort[3]->size);\
                  l_cache[86].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-119 / circlesSort[3]->size);\
                  \
                  l_cache[87].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (920 / circlesSort[2]->size);\
                  l_cache[87].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-449 / circlesSort[2]->size);\
                  l_cache[87].col = circlesSort[2]->color;\
                  \
                  l_cache[88].col = circlesSort[2]->color;\
                  l_cache[88].pt1.x = l_cache[89].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (920 / circlesSort[2]->size);\
                  l_cache[88].pt1.y = l_cache[89].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-449 / circlesSort[2]->size);\
                  l_cache[88].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (920 / circlesSort[3]->size);\
                  l_cache[88].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-449 / circlesSort[3]->size);\
                  \
                  l_cache[89].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (720 / circlesSort[2]->size);\
                  l_cache[89].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-729 / circlesSort[2]->size);\
                  l_cache[89].col = circlesSort[2]->color;\
                  \
                  l_cache[90].col = circlesSort[2]->color;\
                  l_cache[90].pt1.x = l_cache[91].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (720 / circlesSort[2]->size);\
                  l_cache[90].pt1.y = l_cache[91].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-729 / circlesSort[2]->size);\
                  l_cache[90].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (720 / circlesSort[3]->size);\
                  l_cache[90].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-729 / circlesSort[3]->size);\
                  \
                  l_cache[91].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (438 / circlesSort[2]->size);\
                  l_cache[91].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-926 / circlesSort[2]->size);\
                  l_cache[91].col = circlesSort[2]->color;\
                  \
                  l_cache[92].col = circlesSort[2]->color;\
                  l_cache[92].pt1.x = l_cache[93].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (438 / circlesSort[2]->size);\
                  l_cache[92].pt1.y = l_cache[93].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-926 / circlesSort[2]->size);\
                  l_cache[92].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (438 / circlesSort[3]->size);\
                  l_cache[92].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-926 / circlesSort[3]->size);\
                  \
                  l_cache[93].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (107 / circlesSort[2]->size);\
                  l_cache[93].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-1018 / circlesSort[2]->size);\
                  l_cache[93].col = circlesSort[2]->color;\
                  \
                  l_cache[94].col = circlesSort[2]->color;\
                  l_cache[94].pt1.x = l_cache[95].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (107 / circlesSort[2]->size);\
                  l_cache[94].pt1.y = l_cache[95].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-1018 / circlesSort[2]->size);\
                  l_cache[94].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (107 / circlesSort[3]->size);\
                  l_cache[94].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-1018 / circlesSort[3]->size);\
                  \
                  l_cache[95].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-237 / circlesSort[2]->size);\
                  l_cache[95].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-996 / circlesSort[2]->size);\
                  l_cache[95].col = circlesSort[2]->color;\
                  \
                  l_cache[96].col = circlesSort[2]->color;\
                  l_cache[96].pt1.x = l_cache[97].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-237 / circlesSort[2]->size);\
                  l_cache[96].pt1.y = l_cache[97].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-996 / circlesSort[2]->size);\
                  l_cache[96].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-237 / circlesSort[3]->size);\
                  l_cache[96].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-996 / circlesSort[3]->size);\
                  \
                  l_cache[97].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-553 / circlesSort[2]->size);\
                  l_cache[97].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-862 / circlesSort[2]->size);\
                  l_cache[97].col = circlesSort[2]->color;\
                  \
                  l_cache[98].col = circlesSort[2]->color;\
                  l_cache[98].pt1.x = l_cache[99].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-553 / circlesSort[2]->size);\
                  l_cache[98].pt1.y = l_cache[99].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-862 / circlesSort[2]->size);\
                  l_cache[98].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-553 / circlesSort[3]->size);\
                  l_cache[98].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-862 / circlesSort[3]->size);\
                  \
                  l_cache[99].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-807 / circlesSort[2]->size);\
                  l_cache[99].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-630 / circlesSort[2]->size);\
                  l_cache[99].col = circlesSort[2]->color;\
                  \
                  l_cache[100].col = circlesSort[2]->color;\
                  l_cache[100].pt1.x = l_cache[101].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-807 / circlesSort[2]->size);\
                  l_cache[100].pt1.y = l_cache[101].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-630 / circlesSort[2]->size);\
                  l_cache[100].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-807 / circlesSort[3]->size);\
                  l_cache[100].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-630 / circlesSort[3]->size);\
                  \
                  l_cache[101].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-970 / circlesSort[2]->size);\
                  l_cache[101].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-327 / circlesSort[2]->size);\
                  l_cache[101].col = circlesSort[2]->color;\
                  \
                  l_cache[102].col = circlesSort[2]->color;\
                  l_cache[102].pt1.x = l_cache[103].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-970 / circlesSort[2]->size);\
                  l_cache[102].pt1.y = l_cache[103].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (-327 / circlesSort[2]->size);\
                  l_cache[102].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-970 / circlesSort[3]->size);\
                  l_cache[102].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-327 / circlesSort[3]->size);\
                  \
                  l_cache[103].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-1024 / circlesSort[2]->size);\
                  l_cache[103].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (13 / circlesSort[2]->size);\
                  l_cache[103].col = circlesSort[2]->color;\
                  \
                  l_cache[104].col = circlesSort[2]->color;\
                  l_cache[104].pt1.x = l_cache[105].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-1024 / circlesSort[2]->size);\
                  l_cache[104].pt1.y = l_cache[105].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (13 / circlesSort[2]->size);\
                  l_cache[104].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-1024 / circlesSort[3]->size);\
                  l_cache[104].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (13 / circlesSort[3]->size);\
                  \
                  l_cache[105].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-962 / circlesSort[2]->size);\
                  l_cache[105].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (351 / circlesSort[2]->size);\
                  l_cache[105].col = circlesSort[2]->color;\
                  \
                  l_cache[106].col = circlesSort[2]->color;\
                  l_cache[106].pt1.x = l_cache[107].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-962 / circlesSort[2]->size);\
                  l_cache[106].pt1.y = l_cache[107].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (351 / circlesSort[2]->size);\
                  l_cache[106].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-962 / circlesSort[3]->size);\
                  l_cache[106].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (351 / circlesSort[3]->size);\
                  \
                  l_cache[107].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-792 / circlesSort[2]->size);\
                  l_cache[107].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (650 / circlesSort[2]->size);\
                  l_cache[107].col = circlesSort[2]->color;\
                  \
                  l_cache[108].col = circlesSort[2]->color;\
                  l_cache[108].pt1.x = l_cache[109].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-792 / circlesSort[2]->size);\
                  l_cache[108].pt1.y = l_cache[109].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (650 / circlesSort[2]->size);\
                  l_cache[108].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-792 / circlesSort[3]->size);\
                  l_cache[108].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (650 / circlesSort[3]->size);\
                  \
                  l_cache[109].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-532 / circlesSort[2]->size);\
                  l_cache[109].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (875 / circlesSort[2]->size);\
                  l_cache[109].col = circlesSort[2]->color;\
                  \
                  l_cache[110].col = circlesSort[2]->color;\
                  l_cache[110].pt1.x = l_cache[111].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-532 / circlesSort[2]->size);\
                  l_cache[110].pt1.y = l_cache[111].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (875 / circlesSort[2]->size);\
                  l_cache[110].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-532 / circlesSort[3]->size);\
                  l_cache[110].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (875 / circlesSort[3]->size);\
                  \
                  l_cache[111].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-212 / circlesSort[2]->size);\
                  l_cache[111].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (1002 / circlesSort[2]->size);\
                  l_cache[111].col = circlesSort[2]->color;\
                  \
                  l_cache[112].col = circlesSort[2]->color;\
                  l_cache[112].pt1.x = l_cache[113].pt1.x = circlesSort[2]->x + circlesSort[2]->xOffset + (-212 / circlesSort[2]->size);\
                  l_cache[112].pt1.y = l_cache[113].pt1.y = circlesSort[2]->y + circlesSort[2]->yOffset + (1002 / circlesSort[2]->size);\
                  l_cache[112].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-212 / circlesSort[3]->size);\
                  l_cache[112].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (1002 / circlesSort[3]->size);\
                  \
                  l_cache[113].pt2.x = circlesSort[2]->x + circlesSort[2]->xOffset + (132 / circlesSort[2]->size);\
                  l_cache[113].pt2.y = circlesSort[2]->y + circlesSort[2]->yOffset + (1016 / circlesSort[2]->size);\
                  l_cache[113].col = circlesSort[2]->color;\
                  \
                  l_cache[114].col = circlesSort[3]->color;\
                  l_cache[114].pt1.x = l_cache[115].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (0 / circlesSort[3]->size);\
                  l_cache[114].pt1.y = l_cache[115].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (1024 / circlesSort[3]->size);\
                  l_cache[114].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (0 / circlesSort[4]->size);\
                  l_cache[114].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (1024 / circlesSort[4]->size);\
                  \
                  l_cache[115].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (339 / circlesSort[3]->size);\
                  l_cache[115].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (966 / circlesSort[3]->size);\
                  l_cache[115].col = circlesSort[3]->color;\
                  \
                  l_cache[116].col = circlesSort[3]->color;\
                  l_cache[116].pt1.x = l_cache[117].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (339 / circlesSort[3]->size);\
                  l_cache[116].pt1.y = l_cache[117].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (966 / circlesSort[3]->size);\
                  l_cache[116].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (339 / circlesSort[4]->size);\
                  l_cache[116].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (966 / circlesSort[4]->size);\
                  \
                  l_cache[117].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (640 / circlesSort[3]->size);\
                  l_cache[117].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (799 / circlesSort[3]->size);\
                  l_cache[117].col = circlesSort[3]->color;\
                  \
                  l_cache[118].col = circlesSort[3]->color;\
                  l_cache[118].pt1.x = l_cache[119].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (640 / circlesSort[3]->size);\
                  l_cache[118].pt1.y = l_cache[119].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (799 / circlesSort[3]->size);\
                  l_cache[118].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (640 / circlesSort[4]->size);\
                  l_cache[118].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (799 / circlesSort[4]->size);\
                  \
                  l_cache[119].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (868 / circlesSort[3]->size);\
                  l_cache[119].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (543 / circlesSort[3]->size);\
                  l_cache[119].col = circlesSort[3]->color;\
                  \
                  l_cache[120].col = circlesSort[3]->color;\
                  l_cache[120].pt1.x = l_cache[121].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (868 / circlesSort[3]->size);\
                  l_cache[120].pt1.y = l_cache[121].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (543 / circlesSort[3]->size);\
                  l_cache[120].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (868 / circlesSort[4]->size);\
                  l_cache[120].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (543 / circlesSort[4]->size);\
                  \
                  l_cache[121].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (999 / circlesSort[3]->size);\
                  l_cache[121].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (224 / circlesSort[3]->size);\
                  l_cache[121].col = circlesSort[3]->color;\
                  \
                  l_cache[122].col = circlesSort[3]->color;\
                  l_cache[122].pt1.x = l_cache[123].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (999 / circlesSort[3]->size);\
                  l_cache[122].pt1.y = l_cache[123].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (224 / circlesSort[3]->size);\
                  l_cache[122].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (999 / circlesSort[4]->size);\
                  l_cache[122].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (224 / circlesSort[4]->size);\
                  \
                  l_cache[123].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (1017 / circlesSort[3]->size);\
                  l_cache[123].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-119 / circlesSort[3]->size);\
                  l_cache[123].col = circlesSort[3]->color;\
                  \
                  l_cache[124].col = circlesSort[3]->color;\
                  l_cache[124].pt1.x = l_cache[125].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (1017 / circlesSort[3]->size);\
                  l_cache[124].pt1.y = l_cache[125].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-119 / circlesSort[3]->size);\
                  l_cache[124].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (1017 / circlesSort[4]->size);\
                  l_cache[124].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-119 / circlesSort[4]->size);\
                  \
                  l_cache[125].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (920 / circlesSort[3]->size);\
                  l_cache[125].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-449 / circlesSort[3]->size);\
                  l_cache[125].col = circlesSort[3]->color;\
                  \
                  l_cache[126].col = circlesSort[3]->color;\
                  l_cache[126].pt1.x = l_cache[127].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (920 / circlesSort[3]->size);\
                  l_cache[126].pt1.y = l_cache[127].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-449 / circlesSort[3]->size);\
                  l_cache[126].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (920 / circlesSort[4]->size);\
                  l_cache[126].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-449 / circlesSort[4]->size);\
                  \
                  l_cache[127].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (720 / circlesSort[3]->size);\
                  l_cache[127].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-729 / circlesSort[3]->size);\
                  l_cache[127].col = circlesSort[3]->color;\
                  \
                  l_cache[128].col = circlesSort[3]->color;\
                  l_cache[128].pt1.x = l_cache[129].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (720 / circlesSort[3]->size);\
                  l_cache[128].pt1.y = l_cache[129].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-729 / circlesSort[3]->size);\
                  l_cache[128].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (720 / circlesSort[4]->size);\
                  l_cache[128].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-729 / circlesSort[4]->size);\
                  \
                  l_cache[129].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (438 / circlesSort[3]->size);\
                  l_cache[129].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-926 / circlesSort[3]->size);\
                  l_cache[129].col = circlesSort[3]->color;\
                  \
                  l_cache[130].col = circlesSort[3]->color;\
                  l_cache[130].pt1.x = l_cache[131].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (438 / circlesSort[3]->size);\
                  l_cache[130].pt1.y = l_cache[131].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-926 / circlesSort[3]->size);\
                  l_cache[130].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (438 / circlesSort[4]->size);\
                  l_cache[130].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-926 / circlesSort[4]->size);\
                  \
                  l_cache[131].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (107 / circlesSort[3]->size);\
                  l_cache[131].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-1018 / circlesSort[3]->size);\
                  l_cache[131].col = circlesSort[3]->color;\
                  \
                  l_cache[132].col = circlesSort[3]->color;\
                  l_cache[132].pt1.x = l_cache[133].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (107 / circlesSort[3]->size);\
                  l_cache[132].pt1.y = l_cache[133].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-1018 / circlesSort[3]->size);\
                  l_cache[132].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (107 / circlesSort[4]->size);\
                  l_cache[132].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-1018 / circlesSort[4]->size);\
                  \
                  l_cache[133].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-237 / circlesSort[3]->size);\
                  l_cache[133].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-996 / circlesSort[3]->size);\
                  l_cache[133].col = circlesSort[3]->color;\
                  \
                  l_cache[134].col = circlesSort[3]->color;\
                  l_cache[134].pt1.x = l_cache[135].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-237 / circlesSort[3]->size);\
                  l_cache[134].pt1.y = l_cache[135].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-996 / circlesSort[3]->size);\
                  l_cache[134].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-237 / circlesSort[4]->size);\
                  l_cache[134].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-996 / circlesSort[4]->size);\
                  \
                  l_cache[135].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-553 / circlesSort[3]->size);\
                  l_cache[135].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-862 / circlesSort[3]->size);\
                  l_cache[135].col = circlesSort[3]->color;\
                  \
                  l_cache[136].col = circlesSort[3]->color;\
                  l_cache[136].pt1.x = l_cache[137].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-553 / circlesSort[3]->size);\
                  l_cache[136].pt1.y = l_cache[137].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-862 / circlesSort[3]->size);\
                  l_cache[136].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-553 / circlesSort[4]->size);\
                  l_cache[136].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-862 / circlesSort[4]->size);\
                  \
                  l_cache[137].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-807 / circlesSort[3]->size);\
                  l_cache[137].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-630 / circlesSort[3]->size);\
                  l_cache[137].col = circlesSort[3]->color;\
                  \
                  l_cache[138].col = circlesSort[3]->color;\
                  l_cache[138].pt1.x = l_cache[139].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-807 / circlesSort[3]->size);\
                  l_cache[138].pt1.y = l_cache[139].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-630 / circlesSort[3]->size);\
                  l_cache[138].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-807 / circlesSort[4]->size);\
                  l_cache[138].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-630 / circlesSort[4]->size);\
                  \
                  l_cache[139].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-970 / circlesSort[3]->size);\
                  l_cache[139].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-327 / circlesSort[3]->size);\
                  l_cache[139].col = circlesSort[3]->color;\
                  \
                  l_cache[140].col = circlesSort[3]->color;\
                  l_cache[140].pt1.x = l_cache[141].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-970 / circlesSort[3]->size);\
                  l_cache[140].pt1.y = l_cache[141].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (-327 / circlesSort[3]->size);\
                  l_cache[140].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-970 / circlesSort[4]->size);\
                  l_cache[140].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-327 / circlesSort[4]->size);\
                  \
                  l_cache[141].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-1024 / circlesSort[3]->size);\
                  l_cache[141].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (13 / circlesSort[3]->size);\
                  l_cache[141].col = circlesSort[3]->color;\
                  \
                  l_cache[142].col = circlesSort[3]->color;\
                  l_cache[142].pt1.x = l_cache[143].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-1024 / circlesSort[3]->size);\
                  l_cache[142].pt1.y = l_cache[143].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (13 / circlesSort[3]->size);\
                  l_cache[142].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-1024 / circlesSort[4]->size);\
                  l_cache[142].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (13 / circlesSort[4]->size);\
                  \
                  l_cache[143].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-962 / circlesSort[3]->size);\
                  l_cache[143].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (351 / circlesSort[3]->size);\
                  l_cache[143].col = circlesSort[3]->color;\
                  \
                  l_cache[144].col = circlesSort[3]->color;\
                  l_cache[144].pt1.x = l_cache[145].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-962 / circlesSort[3]->size);\
                  l_cache[144].pt1.y = l_cache[145].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (351 / circlesSort[3]->size);\
                  l_cache[144].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-962 / circlesSort[4]->size);\
                  l_cache[144].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (351 / circlesSort[4]->size);\
                  \
                  l_cache[145].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-792 / circlesSort[3]->size);\
                  l_cache[145].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (650 / circlesSort[3]->size);\
                  l_cache[145].col = circlesSort[3]->color;\
                  \
                  l_cache[146].col = circlesSort[3]->color;\
                  l_cache[146].pt1.x = l_cache[147].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-792 / circlesSort[3]->size);\
                  l_cache[146].pt1.y = l_cache[147].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (650 / circlesSort[3]->size);\
                  l_cache[146].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-792 / circlesSort[4]->size);\
                  l_cache[146].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (650 / circlesSort[4]->size);\
                  \
                  l_cache[147].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-532 / circlesSort[3]->size);\
                  l_cache[147].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (875 / circlesSort[3]->size);\
                  l_cache[147].col = circlesSort[3]->color;\
                  \
                  l_cache[148].col = circlesSort[3]->color;\
                  l_cache[148].pt1.x = l_cache[149].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-532 / circlesSort[3]->size);\
                  l_cache[148].pt1.y = l_cache[149].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (875 / circlesSort[3]->size);\
                  l_cache[148].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-532 / circlesSort[4]->size);\
                  l_cache[148].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (875 / circlesSort[4]->size);\
                  \
                  l_cache[149].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-212 / circlesSort[3]->size);\
                  l_cache[149].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (1002 / circlesSort[3]->size);\
                  l_cache[149].col = circlesSort[3]->color;\
                  \
                  l_cache[150].col = circlesSort[3]->color;\
                  l_cache[150].pt1.x = l_cache[151].pt1.x = circlesSort[3]->x + circlesSort[3]->xOffset + (-212 / circlesSort[3]->size);\
                  l_cache[150].pt1.y = l_cache[151].pt1.y = circlesSort[3]->y + circlesSort[3]->yOffset + (1002 / circlesSort[3]->size);\
                  l_cache[150].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-212 / circlesSort[4]->size);\
                  l_cache[150].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (1002 / circlesSort[4]->size);\
                  \
                  l_cache[151].pt2.x = circlesSort[3]->x + circlesSort[3]->xOffset + (132 / circlesSort[3]->size);\
                  l_cache[151].pt2.y = circlesSort[3]->y + circlesSort[3]->yOffset + (1016 / circlesSort[3]->size);\
                  l_cache[151].col = circlesSort[3]->color;\
                  \
                  l_cache[152].col = circlesSort[4]->color;\
                  l_cache[152].pt1.x = l_cache[153].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (0 / circlesSort[4]->size);\
                  l_cache[152].pt1.y = l_cache[153].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (1024 / circlesSort[4]->size);\
                  l_cache[152].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (0 / circlesSort[5]->size);\
                  l_cache[152].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (1024 / circlesSort[5]->size);\
                  \
                  l_cache[153].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (339 / circlesSort[4]->size);\
                  l_cache[153].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (966 / circlesSort[4]->size);\
                  l_cache[153].col = circlesSort[4]->color;\
                  \
                  l_cache[154].col = circlesSort[4]->color;\
                  l_cache[154].pt1.x = l_cache[155].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (339 / circlesSort[4]->size);\
                  l_cache[154].pt1.y = l_cache[155].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (966 / circlesSort[4]->size);\
                  l_cache[154].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (339 / circlesSort[5]->size);\
                  l_cache[154].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (966 / circlesSort[5]->size);\
                  \
                  l_cache[155].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (640 / circlesSort[4]->size);\
                  l_cache[155].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (799 / circlesSort[4]->size);\
                  l_cache[155].col = circlesSort[4]->color;\
                  \
                  l_cache[156].col = circlesSort[4]->color;\
                  l_cache[156].pt1.x = l_cache[157].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (640 / circlesSort[4]->size);\
                  l_cache[156].pt1.y = l_cache[157].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (799 / circlesSort[4]->size);\
                  l_cache[156].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (640 / circlesSort[5]->size);\
                  l_cache[156].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (799 / circlesSort[5]->size);\
                  \
                  l_cache[157].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (868 / circlesSort[4]->size);\
                  l_cache[157].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (543 / circlesSort[4]->size);\
                  l_cache[157].col = circlesSort[4]->color;\
                  \
                  l_cache[158].col = circlesSort[4]->color;\
                  l_cache[158].pt1.x = l_cache[159].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (868 / circlesSort[4]->size);\
                  l_cache[158].pt1.y = l_cache[159].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (543 / circlesSort[4]->size);\
                  l_cache[158].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (868 / circlesSort[5]->size);\
                  l_cache[158].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (543 / circlesSort[5]->size);\
                  \
                  l_cache[159].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (999 / circlesSort[4]->size);\
                  l_cache[159].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (224 / circlesSort[4]->size);\
                  l_cache[159].col = circlesSort[4]->color;\
                  \
                  l_cache[160].col = circlesSort[4]->color;\
                  l_cache[160].pt1.x = l_cache[161].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (999 / circlesSort[4]->size);\
                  l_cache[160].pt1.y = l_cache[161].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (224 / circlesSort[4]->size);\
                  l_cache[160].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (999 / circlesSort[5]->size);\
                  l_cache[160].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (224 / circlesSort[5]->size);\
                  \
                  l_cache[161].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (1017 / circlesSort[4]->size);\
                  l_cache[161].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-119 / circlesSort[4]->size);\
                  l_cache[161].col = circlesSort[4]->color;\
                  \
                  l_cache[162].col = circlesSort[4]->color;\
                  l_cache[162].pt1.x = l_cache[163].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (1017 / circlesSort[4]->size);\
                  l_cache[162].pt1.y = l_cache[163].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-119 / circlesSort[4]->size);\
                  l_cache[162].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (1017 / circlesSort[5]->size);\
                  l_cache[162].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-119 / circlesSort[5]->size);\
                  \
                  l_cache[163].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (920 / circlesSort[4]->size);\
                  l_cache[163].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-449 / circlesSort[4]->size);\
                  l_cache[163].col = circlesSort[4]->color;\
                  \
                  l_cache[164].col = circlesSort[4]->color;\
                  l_cache[164].pt1.x = l_cache[165].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (920 / circlesSort[4]->size);\
                  l_cache[164].pt1.y = l_cache[165].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-449 / circlesSort[4]->size);\
                  l_cache[164].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (920 / circlesSort[5]->size);\
                  l_cache[164].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-449 / circlesSort[5]->size);\
                  \
                  l_cache[165].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (720 / circlesSort[4]->size);\
                  l_cache[165].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-729 / circlesSort[4]->size);\
                  l_cache[165].col = circlesSort[4]->color;\
                  \
                  l_cache[166].col = circlesSort[4]->color;\
                  l_cache[166].pt1.x = l_cache[167].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (720 / circlesSort[4]->size);\
                  l_cache[166].pt1.y = l_cache[167].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-729 / circlesSort[4]->size);\
                  l_cache[166].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (720 / circlesSort[5]->size);\
                  l_cache[166].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-729 / circlesSort[5]->size);\
                  \
                  l_cache[167].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (438 / circlesSort[4]->size);\
                  l_cache[167].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-926 / circlesSort[4]->size);\
                  l_cache[167].col = circlesSort[4]->color;\
                  \
                  l_cache[168].col = circlesSort[4]->color;\
                  l_cache[168].pt1.x = l_cache[169].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (438 / circlesSort[4]->size);\
                  l_cache[168].pt1.y = l_cache[169].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-926 / circlesSort[4]->size);\
                  l_cache[168].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (438 / circlesSort[5]->size);\
                  l_cache[168].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-926 / circlesSort[5]->size);\
                  \
                  l_cache[169].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (107 / circlesSort[4]->size);\
                  l_cache[169].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-1018 / circlesSort[4]->size);\
                  l_cache[169].col = circlesSort[4]->color;\
                  \
                  l_cache[170].col = circlesSort[4]->color;\
                  l_cache[170].pt1.x = l_cache[171].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (107 / circlesSort[4]->size);\
                  l_cache[170].pt1.y = l_cache[171].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-1018 / circlesSort[4]->size);\
                  l_cache[170].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (107 / circlesSort[5]->size);\
                  l_cache[170].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-1018 / circlesSort[5]->size);\
                  \
                  l_cache[171].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-237 / circlesSort[4]->size);\
                  l_cache[171].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-996 / circlesSort[4]->size);\
                  l_cache[171].col = circlesSort[4]->color;\
                  \
                  l_cache[172].col = circlesSort[4]->color;\
                  l_cache[172].pt1.x = l_cache[173].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-237 / circlesSort[4]->size);\
                  l_cache[172].pt1.y = l_cache[173].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-996 / circlesSort[4]->size);\
                  l_cache[172].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-237 / circlesSort[5]->size);\
                  l_cache[172].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-996 / circlesSort[5]->size);\
                  \
                  l_cache[173].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-553 / circlesSort[4]->size);\
                  l_cache[173].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-862 / circlesSort[4]->size);\
                  l_cache[173].col = circlesSort[4]->color;\
                  \
                  l_cache[174].col = circlesSort[4]->color;\
                  l_cache[174].pt1.x = l_cache[175].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-553 / circlesSort[4]->size);\
                  l_cache[174].pt1.y = l_cache[175].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-862 / circlesSort[4]->size);\
                  l_cache[174].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-553 / circlesSort[5]->size);\
                  l_cache[174].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-862 / circlesSort[5]->size);\
                  \
                  l_cache[175].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-807 / circlesSort[4]->size);\
                  l_cache[175].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-630 / circlesSort[4]->size);\
                  l_cache[175].col = circlesSort[4]->color;\
                  \
                  l_cache[176].col = circlesSort[4]->color;\
                  l_cache[176].pt1.x = l_cache[177].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-807 / circlesSort[4]->size);\
                  l_cache[176].pt1.y = l_cache[177].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-630 / circlesSort[4]->size);\
                  l_cache[176].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-807 / circlesSort[5]->size);\
                  l_cache[176].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-630 / circlesSort[5]->size);\
                  \
                  l_cache[177].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-970 / circlesSort[4]->size);\
                  l_cache[177].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-327 / circlesSort[4]->size);\
                  l_cache[177].col = circlesSort[4]->color;\
                  \
                  l_cache[178].col = circlesSort[4]->color;\
                  l_cache[178].pt1.x = l_cache[179].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-970 / circlesSort[4]->size);\
                  l_cache[178].pt1.y = l_cache[179].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (-327 / circlesSort[4]->size);\
                  l_cache[178].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-970 / circlesSort[5]->size);\
                  l_cache[178].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-327 / circlesSort[5]->size);\
                  \
                  l_cache[179].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-1024 / circlesSort[4]->size);\
                  l_cache[179].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (13 / circlesSort[4]->size);\
                  l_cache[179].col = circlesSort[4]->color;\
                  \
                  l_cache[180].col = circlesSort[4]->color;\
                  l_cache[180].pt1.x = l_cache[181].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-1024 / circlesSort[4]->size);\
                  l_cache[180].pt1.y = l_cache[181].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (13 / circlesSort[4]->size);\
                  l_cache[180].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-1024 / circlesSort[5]->size);\
                  l_cache[180].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (13 / circlesSort[5]->size);\
                  \
                  l_cache[181].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-962 / circlesSort[4]->size);\
                  l_cache[181].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (351 / circlesSort[4]->size);\
                  l_cache[181].col = circlesSort[4]->color;\
                  \
                  l_cache[182].col = circlesSort[4]->color;\
                  l_cache[182].pt1.x = l_cache[183].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-962 / circlesSort[4]->size);\
                  l_cache[182].pt1.y = l_cache[183].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (351 / circlesSort[4]->size);\
                  l_cache[182].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-962 / circlesSort[5]->size);\
                  l_cache[182].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (351 / circlesSort[5]->size);\
                  \
                  l_cache[183].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-792 / circlesSort[4]->size);\
                  l_cache[183].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (650 / circlesSort[4]->size);\
                  l_cache[183].col = circlesSort[4]->color;\
                  \
                  l_cache[184].col = circlesSort[4]->color;\
                  l_cache[184].pt1.x = l_cache[185].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-792 / circlesSort[4]->size);\
                  l_cache[184].pt1.y = l_cache[185].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (650 / circlesSort[4]->size);\
                  l_cache[184].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-792 / circlesSort[5]->size);\
                  l_cache[184].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (650 / circlesSort[5]->size);\
                  \
                  l_cache[185].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-532 / circlesSort[4]->size);\
                  l_cache[185].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (875 / circlesSort[4]->size);\
                  l_cache[185].col = circlesSort[4]->color;\
                  \
                  l_cache[186].col = circlesSort[4]->color;\
                  l_cache[186].pt1.x = l_cache[187].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-532 / circlesSort[4]->size);\
                  l_cache[186].pt1.y = l_cache[187].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (875 / circlesSort[4]->size);\
                  l_cache[186].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-532 / circlesSort[5]->size);\
                  l_cache[186].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (875 / circlesSort[5]->size);\
                  \
                  l_cache[187].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-212 / circlesSort[4]->size);\
                  l_cache[187].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (1002 / circlesSort[4]->size);\
                  l_cache[187].col = circlesSort[4]->color;\
                  \
                  l_cache[188].col = circlesSort[4]->color;\
                  l_cache[188].pt1.x = l_cache[189].pt1.x = circlesSort[4]->x + circlesSort[4]->xOffset + (-212 / circlesSort[4]->size);\
                  l_cache[188].pt1.y = l_cache[189].pt1.y = circlesSort[4]->y + circlesSort[4]->yOffset + (1002 / circlesSort[4]->size);\
                  l_cache[188].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-212 / circlesSort[5]->size);\
                  l_cache[188].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (1002 / circlesSort[5]->size);\
                  \
                  l_cache[189].pt2.x = circlesSort[4]->x + circlesSort[4]->xOffset + (132 / circlesSort[4]->size);\
                  l_cache[189].pt2.y = circlesSort[4]->y + circlesSort[4]->yOffset + (1016 / circlesSort[4]->size);\
                  l_cache[189].col = circlesSort[4]->color;\
                  \
                  l_cache[190].col = circlesSort[5]->color;\
                  l_cache[190].pt1.x = l_cache[191].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (0 / circlesSort[5]->size);\
                  l_cache[190].pt1.y = l_cache[191].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (1024 / circlesSort[5]->size);\
                  l_cache[190].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (0 / circlesSort[6]->size);\
                  l_cache[190].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (1024 / circlesSort[6]->size);\
                  \
                  l_cache[191].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (339 / circlesSort[5]->size);\
                  l_cache[191].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (966 / circlesSort[5]->size);\
                  l_cache[191].col = circlesSort[5]->color;\
                  \
                  l_cache[192].col = circlesSort[5]->color;\
                  l_cache[192].pt1.x = l_cache[193].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (339 / circlesSort[5]->size);\
                  l_cache[192].pt1.y = l_cache[193].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (966 / circlesSort[5]->size);\
                  l_cache[192].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (339 / circlesSort[6]->size);\
                  l_cache[192].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (966 / circlesSort[6]->size);\
                  \
                  l_cache[193].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (640 / circlesSort[5]->size);\
                  l_cache[193].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (799 / circlesSort[5]->size);\
                  l_cache[193].col = circlesSort[5]->color;\
                  \
                  l_cache[194].col = circlesSort[5]->color;\
                  l_cache[194].pt1.x = l_cache[195].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (640 / circlesSort[5]->size);\
                  l_cache[194].pt1.y = l_cache[195].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (799 / circlesSort[5]->size);\
                  l_cache[194].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (640 / circlesSort[6]->size);\
                  l_cache[194].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (799 / circlesSort[6]->size);\
                  \
                  l_cache[195].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (868 / circlesSort[5]->size);\
                  l_cache[195].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (543 / circlesSort[5]->size);\
                  l_cache[195].col = circlesSort[5]->color;\
                  \
                  l_cache[196].col = circlesSort[5]->color;\
                  l_cache[196].pt1.x = l_cache[197].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (868 / circlesSort[5]->size);\
                  l_cache[196].pt1.y = l_cache[197].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (543 / circlesSort[5]->size);\
                  l_cache[196].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (868 / circlesSort[6]->size);\
                  l_cache[196].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (543 / circlesSort[6]->size);\
                  \
                  l_cache[197].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (999 / circlesSort[5]->size);\
                  l_cache[197].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (224 / circlesSort[5]->size);\
                  l_cache[197].col = circlesSort[5]->color;\
                  \
                  l_cache[198].col = circlesSort[5]->color;\
                  l_cache[198].pt1.x = l_cache[199].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (999 / circlesSort[5]->size);\
                  l_cache[198].pt1.y = l_cache[199].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (224 / circlesSort[5]->size);\
                  l_cache[198].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (999 / circlesSort[6]->size);\
                  l_cache[198].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (224 / circlesSort[6]->size);\
                  \
                  l_cache[199].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (1017 / circlesSort[5]->size);\
                  l_cache[199].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-119 / circlesSort[5]->size);\
                  l_cache[199].col = circlesSort[5]->color;\
                  \
                  l_cache[200].col = circlesSort[5]->color;\
                  l_cache[200].pt1.x = l_cache[201].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (1017 / circlesSort[5]->size);\
                  l_cache[200].pt1.y = l_cache[201].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-119 / circlesSort[5]->size);\
                  l_cache[200].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (1017 / circlesSort[6]->size);\
                  l_cache[200].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-119 / circlesSort[6]->size);\
                  \
                  l_cache[201].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (920 / circlesSort[5]->size);\
                  l_cache[201].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-449 / circlesSort[5]->size);\
                  l_cache[201].col = circlesSort[5]->color;\
                  \
                  l_cache[202].col = circlesSort[5]->color;\
                  l_cache[202].pt1.x = l_cache[203].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (920 / circlesSort[5]->size);\
                  l_cache[202].pt1.y = l_cache[203].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-449 / circlesSort[5]->size);\
                  l_cache[202].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (920 / circlesSort[6]->size);\
                  l_cache[202].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-449 / circlesSort[6]->size);\
                  \
                  l_cache[203].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (720 / circlesSort[5]->size);\
                  l_cache[203].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-729 / circlesSort[5]->size);\
                  l_cache[203].col = circlesSort[5]->color;\
                  \
                  l_cache[204].col = circlesSort[5]->color;\
                  l_cache[204].pt1.x = l_cache[205].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (720 / circlesSort[5]->size);\
                  l_cache[204].pt1.y = l_cache[205].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-729 / circlesSort[5]->size);\
                  l_cache[204].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (720 / circlesSort[6]->size);\
                  l_cache[204].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-729 / circlesSort[6]->size);\
                  \
                  l_cache[205].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (438 / circlesSort[5]->size);\
                  l_cache[205].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-926 / circlesSort[5]->size);\
                  l_cache[205].col = circlesSort[5]->color;\
                  \
                  l_cache[206].col = circlesSort[5]->color;\
                  l_cache[206].pt1.x = l_cache[207].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (438 / circlesSort[5]->size);\
                  l_cache[206].pt1.y = l_cache[207].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-926 / circlesSort[5]->size);\
                  l_cache[206].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (438 / circlesSort[6]->size);\
                  l_cache[206].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-926 / circlesSort[6]->size);\
                  \
                  l_cache[207].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (107 / circlesSort[5]->size);\
                  l_cache[207].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-1018 / circlesSort[5]->size);\
                  l_cache[207].col = circlesSort[5]->color;\
                  \
                  l_cache[208].col = circlesSort[5]->color;\
                  l_cache[208].pt1.x = l_cache[209].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (107 / circlesSort[5]->size);\
                  l_cache[208].pt1.y = l_cache[209].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-1018 / circlesSort[5]->size);\
                  l_cache[208].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (107 / circlesSort[6]->size);\
                  l_cache[208].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-1018 / circlesSort[6]->size);\
                  \
                  l_cache[209].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-237 / circlesSort[5]->size);\
                  l_cache[209].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-996 / circlesSort[5]->size);\
                  l_cache[209].col = circlesSort[5]->color;\
                  \
                  l_cache[210].col = circlesSort[5]->color;\
                  l_cache[210].pt1.x = l_cache[211].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-237 / circlesSort[5]->size);\
                  l_cache[210].pt1.y = l_cache[211].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-996 / circlesSort[5]->size);\
                  l_cache[210].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-237 / circlesSort[6]->size);\
                  l_cache[210].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-996 / circlesSort[6]->size);\
                  \
                  l_cache[211].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-553 / circlesSort[5]->size);\
                  l_cache[211].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-862 / circlesSort[5]->size);\
                  l_cache[211].col = circlesSort[5]->color;\
                  \
                  l_cache[212].col = circlesSort[5]->color;\
                  l_cache[212].pt1.x = l_cache[213].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-553 / circlesSort[5]->size);\
                  l_cache[212].pt1.y = l_cache[213].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-862 / circlesSort[5]->size);\
                  l_cache[212].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-553 / circlesSort[6]->size);\
                  l_cache[212].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-862 / circlesSort[6]->size);\
                  \
                  l_cache[213].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-807 / circlesSort[5]->size);\
                  l_cache[213].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-630 / circlesSort[5]->size);\
                  l_cache[213].col = circlesSort[5]->color;\
                  \
                  l_cache[214].col = circlesSort[5]->color;\
                  l_cache[214].pt1.x = l_cache[215].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-807 / circlesSort[5]->size);\
                  l_cache[214].pt1.y = l_cache[215].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-630 / circlesSort[5]->size);\
                  l_cache[214].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-807 / circlesSort[6]->size);\
                  l_cache[214].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-630 / circlesSort[6]->size);\
                  \
                  l_cache[215].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-970 / circlesSort[5]->size);\
                  l_cache[215].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-327 / circlesSort[5]->size);\
                  l_cache[215].col = circlesSort[5]->color;\
                  \
                  l_cache[216].col = circlesSort[5]->color;\
                  l_cache[216].pt1.x = l_cache[217].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-970 / circlesSort[5]->size);\
                  l_cache[216].pt1.y = l_cache[217].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (-327 / circlesSort[5]->size);\
                  l_cache[216].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-970 / circlesSort[6]->size);\
                  l_cache[216].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-327 / circlesSort[6]->size);\
                  \
                  l_cache[217].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-1024 / circlesSort[5]->size);\
                  l_cache[217].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (13 / circlesSort[5]->size);\
                  l_cache[217].col = circlesSort[5]->color;\
                  \
                  l_cache[218].col = circlesSort[5]->color;\
                  l_cache[218].pt1.x = l_cache[219].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-1024 / circlesSort[5]->size);\
                  l_cache[218].pt1.y = l_cache[219].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (13 / circlesSort[5]->size);\
                  l_cache[218].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-1024 / circlesSort[6]->size);\
                  l_cache[218].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (13 / circlesSort[6]->size);\
                  \
                  l_cache[219].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-962 / circlesSort[5]->size);\
                  l_cache[219].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (351 / circlesSort[5]->size);\
                  l_cache[219].col = circlesSort[5]->color;\
                  \
                  l_cache[220].col = circlesSort[5]->color;\
                  l_cache[220].pt1.x = l_cache[221].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-962 / circlesSort[5]->size);\
                  l_cache[220].pt1.y = l_cache[221].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (351 / circlesSort[5]->size);\
                  l_cache[220].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-962 / circlesSort[6]->size);\
                  l_cache[220].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (351 / circlesSort[6]->size);\
                  \
                  l_cache[221].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-792 / circlesSort[5]->size);\
                  l_cache[221].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (650 / circlesSort[5]->size);\
                  l_cache[221].col = circlesSort[5]->color;\
                  \
                  l_cache[222].col = circlesSort[5]->color;\
                  l_cache[222].pt1.x = l_cache[223].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-792 / circlesSort[5]->size);\
                  l_cache[222].pt1.y = l_cache[223].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (650 / circlesSort[5]->size);\
                  l_cache[222].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-792 / circlesSort[6]->size);\
                  l_cache[222].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (650 / circlesSort[6]->size);\
                  \
                  l_cache[223].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-532 / circlesSort[5]->size);\
                  l_cache[223].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (875 / circlesSort[5]->size);\
                  l_cache[223].col = circlesSort[5]->color;\
                  \
                  l_cache[224].col = circlesSort[5]->color;\
                  l_cache[224].pt1.x = l_cache[225].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-532 / circlesSort[5]->size);\
                  l_cache[224].pt1.y = l_cache[225].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (875 / circlesSort[5]->size);\
                  l_cache[224].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-532 / circlesSort[6]->size);\
                  l_cache[224].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (875 / circlesSort[6]->size);\
                  \
                  l_cache[225].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-212 / circlesSort[5]->size);\
                  l_cache[225].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (1002 / circlesSort[5]->size);\
                  l_cache[225].col = circlesSort[5]->color;\
                  \
                  l_cache[226].col = circlesSort[5]->color;\
                  l_cache[226].pt1.x = l_cache[227].pt1.x = circlesSort[5]->x + circlesSort[5]->xOffset + (-212 / circlesSort[5]->size);\
                  l_cache[226].pt1.y = l_cache[227].pt1.y = circlesSort[5]->y + circlesSort[5]->yOffset + (1002 / circlesSort[5]->size);\
                  l_cache[226].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-212 / circlesSort[6]->size);\
                  l_cache[226].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (1002 / circlesSort[6]->size);\
                  \
                  l_cache[227].pt2.x = circlesSort[5]->x + circlesSort[5]->xOffset + (132 / circlesSort[5]->size);\
                  l_cache[227].pt2.y = circlesSort[5]->y + circlesSort[5]->yOffset + (1016 / circlesSort[5]->size);\
                  l_cache[227].col = circlesSort[5]->color;\
                  \
                  l_cache[228].col = circlesSort[6]->color;\
                  l_cache[228].pt1.x = l_cache[229].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (0 / circlesSort[6]->size);\
                  l_cache[228].pt1.y = l_cache[229].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (1024 / circlesSort[6]->size);\
                  l_cache[228].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (0 / circlesSort[7]->size);\
                  l_cache[228].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (1024 / circlesSort[7]->size);\
                  \
                  l_cache[229].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (339 / circlesSort[6]->size);\
                  l_cache[229].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (966 / circlesSort[6]->size);\
                  l_cache[229].col = circlesSort[6]->color;\
                  \
                  l_cache[230].col = circlesSort[6]->color;\
                  l_cache[230].pt1.x = l_cache[231].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (339 / circlesSort[6]->size);\
                  l_cache[230].pt1.y = l_cache[231].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (966 / circlesSort[6]->size);\
                  l_cache[230].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (339 / circlesSort[7]->size);\
                  l_cache[230].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (966 / circlesSort[7]->size);\
                  \
                  l_cache[231].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (640 / circlesSort[6]->size);\
                  l_cache[231].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (799 / circlesSort[6]->size);\
                  l_cache[231].col = circlesSort[6]->color;\
                  \
                  l_cache[232].col = circlesSort[6]->color;\
                  l_cache[232].pt1.x = l_cache[233].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (640 / circlesSort[6]->size);\
                  l_cache[232].pt1.y = l_cache[233].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (799 / circlesSort[6]->size);\
                  l_cache[232].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (640 / circlesSort[7]->size);\
                  l_cache[232].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (799 / circlesSort[7]->size);\
                  \
                  l_cache[233].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (868 / circlesSort[6]->size);\
                  l_cache[233].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (543 / circlesSort[6]->size);\
                  l_cache[233].col = circlesSort[6]->color;\
                  \
                  l_cache[234].col = circlesSort[6]->color;\
                  l_cache[234].pt1.x = l_cache[235].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (868 / circlesSort[6]->size);\
                  l_cache[234].pt1.y = l_cache[235].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (543 / circlesSort[6]->size);\
                  l_cache[234].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (868 / circlesSort[7]->size);\
                  l_cache[234].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (543 / circlesSort[7]->size);\
                  \
                  l_cache[235].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (999 / circlesSort[6]->size);\
                  l_cache[235].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (224 / circlesSort[6]->size);\
                  l_cache[235].col = circlesSort[6]->color;\
                  \
                  l_cache[236].col = circlesSort[6]->color;\
                  l_cache[236].pt1.x = l_cache[237].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (999 / circlesSort[6]->size);\
                  l_cache[236].pt1.y = l_cache[237].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (224 / circlesSort[6]->size);\
                  l_cache[236].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (999 / circlesSort[7]->size);\
                  l_cache[236].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (224 / circlesSort[7]->size);\
                  \
                  l_cache[237].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (1017 / circlesSort[6]->size);\
                  l_cache[237].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-119 / circlesSort[6]->size);\
                  l_cache[237].col = circlesSort[6]->color;\
                  \
                  l_cache[238].col = circlesSort[6]->color;\
                  l_cache[238].pt1.x = l_cache[239].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (1017 / circlesSort[6]->size);\
                  l_cache[238].pt1.y = l_cache[239].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-119 / circlesSort[6]->size);\
                  l_cache[238].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (1017 / circlesSort[7]->size);\
                  l_cache[238].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-119 / circlesSort[7]->size);\
                  \
                  l_cache[239].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (920 / circlesSort[6]->size);\
                  l_cache[239].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-449 / circlesSort[6]->size);\
                  l_cache[239].col = circlesSort[6]->color;\
                  \
                  l_cache[240].col = circlesSort[6]->color;\
                  l_cache[240].pt1.x = l_cache[241].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (920 / circlesSort[6]->size);\
                  l_cache[240].pt1.y = l_cache[241].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-449 / circlesSort[6]->size);\
                  l_cache[240].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (920 / circlesSort[7]->size);\
                  l_cache[240].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-449 / circlesSort[7]->size);\
                  \
                  l_cache[241].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (720 / circlesSort[6]->size);\
                  l_cache[241].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-729 / circlesSort[6]->size);\
                  l_cache[241].col = circlesSort[6]->color;\
                  \
                  l_cache[242].col = circlesSort[6]->color;\
                  l_cache[242].pt1.x = l_cache[243].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (720 / circlesSort[6]->size);\
                  l_cache[242].pt1.y = l_cache[243].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-729 / circlesSort[6]->size);\
                  l_cache[242].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (720 / circlesSort[7]->size);\
                  l_cache[242].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-729 / circlesSort[7]->size);\
                  \
                  l_cache[243].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (438 / circlesSort[6]->size);\
                  l_cache[243].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-926 / circlesSort[6]->size);\
                  l_cache[243].col = circlesSort[6]->color;\
                  \
                  l_cache[244].col = circlesSort[6]->color;\
                  l_cache[244].pt1.x = l_cache[245].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (438 / circlesSort[6]->size);\
                  l_cache[244].pt1.y = l_cache[245].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-926 / circlesSort[6]->size);\
                  l_cache[244].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (438 / circlesSort[7]->size);\
                  l_cache[244].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-926 / circlesSort[7]->size);\
                  \
                  l_cache[245].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (107 / circlesSort[6]->size);\
                  l_cache[245].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-1018 / circlesSort[6]->size);\
                  l_cache[245].col = circlesSort[6]->color;\
                  \
                  l_cache[246].col = circlesSort[6]->color;\
                  l_cache[246].pt1.x = l_cache[247].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (107 / circlesSort[6]->size);\
                  l_cache[246].pt1.y = l_cache[247].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-1018 / circlesSort[6]->size);\
                  l_cache[246].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (107 / circlesSort[7]->size);\
                  l_cache[246].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-1018 / circlesSort[7]->size);\
                  \
                  l_cache[247].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-237 / circlesSort[6]->size);\
                  l_cache[247].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-996 / circlesSort[6]->size);\
                  l_cache[247].col = circlesSort[6]->color;\
                  \
                  l_cache[248].col = circlesSort[6]->color;\
                  l_cache[248].pt1.x = l_cache[249].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-237 / circlesSort[6]->size);\
                  l_cache[248].pt1.y = l_cache[249].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-996 / circlesSort[6]->size);\
                  l_cache[248].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-237 / circlesSort[7]->size);\
                  l_cache[248].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-996 / circlesSort[7]->size);\
                  \
                  l_cache[249].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-553 / circlesSort[6]->size);\
                  l_cache[249].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-862 / circlesSort[6]->size);\
                  l_cache[249].col = circlesSort[6]->color;\
                  \
                  l_cache[250].col = circlesSort[6]->color;\
                  l_cache[250].pt1.x = l_cache[251].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-553 / circlesSort[6]->size);\
                  l_cache[250].pt1.y = l_cache[251].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-862 / circlesSort[6]->size);\
                  l_cache[250].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-553 / circlesSort[7]->size);\
                  l_cache[250].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-862 / circlesSort[7]->size);\
                  \
                  l_cache[251].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-807 / circlesSort[6]->size);\
                  l_cache[251].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-630 / circlesSort[6]->size);\
                  l_cache[251].col = circlesSort[6]->color;\
                  \
                  l_cache[252].col = circlesSort[6]->color;\
                  l_cache[252].pt1.x = l_cache[253].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-807 / circlesSort[6]->size);\
                  l_cache[252].pt1.y = l_cache[253].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-630 / circlesSort[6]->size);\
                  l_cache[252].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-807 / circlesSort[7]->size);\
                  l_cache[252].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-630 / circlesSort[7]->size);\
                  \
                  l_cache[253].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-970 / circlesSort[6]->size);\
                  l_cache[253].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-327 / circlesSort[6]->size);\
                  l_cache[253].col = circlesSort[6]->color;\
                  \
                  l_cache[254].col = circlesSort[6]->color;\
                  l_cache[254].pt1.x = l_cache[255].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-970 / circlesSort[6]->size);\
                  l_cache[254].pt1.y = l_cache[255].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (-327 / circlesSort[6]->size);\
                  l_cache[254].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-970 / circlesSort[7]->size);\
                  l_cache[254].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-327 / circlesSort[7]->size);\
                  \
                  l_cache[255].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-1024 / circlesSort[6]->size);\
                  l_cache[255].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (13 / circlesSort[6]->size);\
                  l_cache[255].col = circlesSort[6]->color;\
                  \
                  l_cache[256].col = circlesSort[6]->color;\
                  l_cache[256].pt1.x = l_cache[257].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-1024 / circlesSort[6]->size);\
                  l_cache[256].pt1.y = l_cache[257].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (13 / circlesSort[6]->size);\
                  l_cache[256].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-1024 / circlesSort[7]->size);\
                  l_cache[256].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (13 / circlesSort[7]->size);\
                  \
                  l_cache[257].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-962 / circlesSort[6]->size);\
                  l_cache[257].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (351 / circlesSort[6]->size);\
                  l_cache[257].col = circlesSort[6]->color;\
                  \
                  l_cache[258].col = circlesSort[6]->color;\
                  l_cache[258].pt1.x = l_cache[259].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-962 / circlesSort[6]->size);\
                  l_cache[258].pt1.y = l_cache[259].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (351 / circlesSort[6]->size);\
                  l_cache[258].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-962 / circlesSort[7]->size);\
                  l_cache[258].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (351 / circlesSort[7]->size);\
                  \
                  l_cache[259].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-792 / circlesSort[6]->size);\
                  l_cache[259].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (650 / circlesSort[6]->size);\
                  l_cache[259].col = circlesSort[6]->color;\
                  \
                  l_cache[260].col = circlesSort[6]->color;\
                  l_cache[260].pt1.x = l_cache[261].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-792 / circlesSort[6]->size);\
                  l_cache[260].pt1.y = l_cache[261].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (650 / circlesSort[6]->size);\
                  l_cache[260].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-792 / circlesSort[7]->size);\
                  l_cache[260].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (650 / circlesSort[7]->size);\
                  \
                  l_cache[261].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-532 / circlesSort[6]->size);\
                  l_cache[261].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (875 / circlesSort[6]->size);\
                  l_cache[261].col = circlesSort[6]->color;\
                  \
                  l_cache[262].col = circlesSort[6]->color;\
                  l_cache[262].pt1.x = l_cache[263].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-532 / circlesSort[6]->size);\
                  l_cache[262].pt1.y = l_cache[263].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (875 / circlesSort[6]->size);\
                  l_cache[262].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-532 / circlesSort[7]->size);\
                  l_cache[262].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (875 / circlesSort[7]->size);\
                  \
                  l_cache[263].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-212 / circlesSort[6]->size);\
                  l_cache[263].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (1002 / circlesSort[6]->size);\
                  l_cache[263].col = circlesSort[6]->color;\
                  \
                  l_cache[264].col = circlesSort[6]->color;\
                  l_cache[264].pt1.x = l_cache[265].pt1.x = circlesSort[6]->x + circlesSort[6]->xOffset + (-212 / circlesSort[6]->size);\
                  l_cache[264].pt1.y = l_cache[265].pt1.y = circlesSort[6]->y + circlesSort[6]->yOffset + (1002 / circlesSort[6]->size);\
                  l_cache[264].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-212 / circlesSort[7]->size);\
                  l_cache[264].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (1002 / circlesSort[7]->size);\
                  \
                  l_cache[265].pt2.x = circlesSort[6]->x + circlesSort[6]->xOffset + (132 / circlesSort[6]->size);\
                  l_cache[265].pt2.y = circlesSort[6]->y + circlesSort[6]->yOffset + (1016 / circlesSort[6]->size);\
                  l_cache[265].col = circlesSort[6]->color;\
                  \
                  l_cache[266].col = circlesSort[7]->color;\
                  l_cache[266].pt1.x = l_cache[267].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (0 / circlesSort[7]->size);\
                  l_cache[266].pt1.y = l_cache[267].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (1024 / circlesSort[7]->size);\
                  l_cache[266].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (0 / circlesSort[8]->size);\
                  l_cache[266].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (1024 / circlesSort[8]->size);\
                  \
                  l_cache[267].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (339 / circlesSort[7]->size);\
                  l_cache[267].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (966 / circlesSort[7]->size);\
                  l_cache[267].col = circlesSort[7]->color;\
                  \
                  l_cache[268].col = circlesSort[7]->color;\
                  l_cache[268].pt1.x = l_cache[269].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (339 / circlesSort[7]->size);\
                  l_cache[268].pt1.y = l_cache[269].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (966 / circlesSort[7]->size);\
                  l_cache[268].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (339 / circlesSort[8]->size);\
                  l_cache[268].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (966 / circlesSort[8]->size);\
                  \
                  l_cache[269].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (640 / circlesSort[7]->size);\
                  l_cache[269].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (799 / circlesSort[7]->size);\
                  l_cache[269].col = circlesSort[7]->color;\
                  \
                  l_cache[270].col = circlesSort[7]->color;\
                  l_cache[270].pt1.x = l_cache[271].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (640 / circlesSort[7]->size);\
                  l_cache[270].pt1.y = l_cache[271].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (799 / circlesSort[7]->size);\
                  l_cache[270].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (640 / circlesSort[8]->size);\
                  l_cache[270].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (799 / circlesSort[8]->size);\
                  \
                  l_cache[271].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (868 / circlesSort[7]->size);\
                  l_cache[271].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (543 / circlesSort[7]->size);\
                  l_cache[271].col = circlesSort[7]->color;\
                  \
                  l_cache[272].col = circlesSort[7]->color;\
                  l_cache[272].pt1.x = l_cache[273].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (868 / circlesSort[7]->size);\
                  l_cache[272].pt1.y = l_cache[273].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (543 / circlesSort[7]->size);\
                  l_cache[272].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (868 / circlesSort[8]->size);\
                  l_cache[272].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (543 / circlesSort[8]->size);\
                  \
                  l_cache[273].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (999 / circlesSort[7]->size);\
                  l_cache[273].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (224 / circlesSort[7]->size);\
                  l_cache[273].col = circlesSort[7]->color;\
                  \
                  l_cache[274].col = circlesSort[7]->color;\
                  l_cache[274].pt1.x = l_cache[275].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (999 / circlesSort[7]->size);\
                  l_cache[274].pt1.y = l_cache[275].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (224 / circlesSort[7]->size);\
                  l_cache[274].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (999 / circlesSort[8]->size);\
                  l_cache[274].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (224 / circlesSort[8]->size);\
                  \
                  l_cache[275].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (1017 / circlesSort[7]->size);\
                  l_cache[275].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-119 / circlesSort[7]->size);\
                  l_cache[275].col = circlesSort[7]->color;\
                  \
                  l_cache[276].col = circlesSort[7]->color;\
                  l_cache[276].pt1.x = l_cache[277].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (1017 / circlesSort[7]->size);\
                  l_cache[276].pt1.y = l_cache[277].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-119 / circlesSort[7]->size);\
                  l_cache[276].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (1017 / circlesSort[8]->size);\
                  l_cache[276].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-119 / circlesSort[8]->size);\
                  \
                  l_cache[277].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (920 / circlesSort[7]->size);\
                  l_cache[277].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-449 / circlesSort[7]->size);\
                  l_cache[277].col = circlesSort[7]->color;\
                  \
                  l_cache[278].col = circlesSort[7]->color;\
                  l_cache[278].pt1.x = l_cache[279].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (920 / circlesSort[7]->size);\
                  l_cache[278].pt1.y = l_cache[279].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-449 / circlesSort[7]->size);\
                  l_cache[278].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (920 / circlesSort[8]->size);\
                  l_cache[278].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-449 / circlesSort[8]->size);\
                  \
                  l_cache[279].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (720 / circlesSort[7]->size);\
                  l_cache[279].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-729 / circlesSort[7]->size);\
                  l_cache[279].col = circlesSort[7]->color;\
                  \
                  l_cache[280].col = circlesSort[7]->color;\
                  l_cache[280].pt1.x = l_cache[281].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (720 / circlesSort[7]->size);\
                  l_cache[280].pt1.y = l_cache[281].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-729 / circlesSort[7]->size);\
                  l_cache[280].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (720 / circlesSort[8]->size);\
                  l_cache[280].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-729 / circlesSort[8]->size);\
                  \
                  l_cache[281].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (438 / circlesSort[7]->size);\
                  l_cache[281].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-926 / circlesSort[7]->size);\
                  l_cache[281].col = circlesSort[7]->color;\
                  \
                  l_cache[282].col = circlesSort[7]->color;\
                  l_cache[282].pt1.x = l_cache[283].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (438 / circlesSort[7]->size);\
                  l_cache[282].pt1.y = l_cache[283].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-926 / circlesSort[7]->size);\
                  l_cache[282].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (438 / circlesSort[8]->size);\
                  l_cache[282].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-926 / circlesSort[8]->size);\
                  \
                  l_cache[283].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (107 / circlesSort[7]->size);\
                  l_cache[283].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-1018 / circlesSort[7]->size);\
                  l_cache[283].col = circlesSort[7]->color;\
                  \
                  l_cache[284].col = circlesSort[7]->color;\
                  l_cache[284].pt1.x = l_cache[285].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (107 / circlesSort[7]->size);\
                  l_cache[284].pt1.y = l_cache[285].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-1018 / circlesSort[7]->size);\
                  l_cache[284].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (107 / circlesSort[8]->size);\
                  l_cache[284].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-1018 / circlesSort[8]->size);\
                  \
                  l_cache[285].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-237 / circlesSort[7]->size);\
                  l_cache[285].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-996 / circlesSort[7]->size);\
                  l_cache[285].col = circlesSort[7]->color;\
                  \
                  l_cache[286].col = circlesSort[7]->color;\
                  l_cache[286].pt1.x = l_cache[287].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-237 / circlesSort[7]->size);\
                  l_cache[286].pt1.y = l_cache[287].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-996 / circlesSort[7]->size);\
                  l_cache[286].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-237 / circlesSort[8]->size);\
                  l_cache[286].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-996 / circlesSort[8]->size);\
                  \
                  l_cache[287].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-553 / circlesSort[7]->size);\
                  l_cache[287].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-862 / circlesSort[7]->size);\
                  l_cache[287].col = circlesSort[7]->color;\
                  \
                  l_cache[288].col = circlesSort[7]->color;\
                  l_cache[288].pt1.x = l_cache[289].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-553 / circlesSort[7]->size);\
                  l_cache[288].pt1.y = l_cache[289].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-862 / circlesSort[7]->size);\
                  l_cache[288].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-553 / circlesSort[8]->size);\
                  l_cache[288].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-862 / circlesSort[8]->size);\
                  \
                  l_cache[289].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-807 / circlesSort[7]->size);\
                  l_cache[289].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-630 / circlesSort[7]->size);\
                  l_cache[289].col = circlesSort[7]->color;\
                  \
                  l_cache[290].col = circlesSort[7]->color;\
                  l_cache[290].pt1.x = l_cache[291].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-807 / circlesSort[7]->size);\
                  l_cache[290].pt1.y = l_cache[291].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-630 / circlesSort[7]->size);\
                  l_cache[290].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-807 / circlesSort[8]->size);\
                  l_cache[290].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-630 / circlesSort[8]->size);\
                  \
                  l_cache[291].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-970 / circlesSort[7]->size);\
                  l_cache[291].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-327 / circlesSort[7]->size);\
                  l_cache[291].col = circlesSort[7]->color;\
                  \
                  l_cache[292].col = circlesSort[7]->color;\
                  l_cache[292].pt1.x = l_cache[293].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-970 / circlesSort[7]->size);\
                  l_cache[292].pt1.y = l_cache[293].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (-327 / circlesSort[7]->size);\
                  l_cache[292].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-970 / circlesSort[8]->size);\
                  l_cache[292].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (-327 / circlesSort[8]->size);\
                  \
                  l_cache[293].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-1024 / circlesSort[7]->size);\
                  l_cache[293].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (13 / circlesSort[7]->size);\
                  l_cache[293].col = circlesSort[7]->color;\
                  \
                  l_cache[294].col = circlesSort[7]->color;\
                  l_cache[294].pt1.x = l_cache[295].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-1024 / circlesSort[7]->size);\
                  l_cache[294].pt1.y = l_cache[295].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (13 / circlesSort[7]->size);\
                  l_cache[294].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-1024 / circlesSort[8]->size);\
                  l_cache[294].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (13 / circlesSort[8]->size);\
                  \
                  l_cache[295].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-962 / circlesSort[7]->size);\
                  l_cache[295].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (351 / circlesSort[7]->size);\
                  l_cache[295].col = circlesSort[7]->color;\
                  \
                  l_cache[296].col = circlesSort[7]->color;\
                  l_cache[296].pt1.x = l_cache[297].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-962 / circlesSort[7]->size);\
                  l_cache[296].pt1.y = l_cache[297].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (351 / circlesSort[7]->size);\
                  l_cache[296].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-962 / circlesSort[8]->size);\
                  l_cache[296].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (351 / circlesSort[8]->size);\
                  \
                  l_cache[297].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-792 / circlesSort[7]->size);\
                  l_cache[297].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (650 / circlesSort[7]->size);\
                  l_cache[297].col = circlesSort[7]->color;\
                  \
                  l_cache[298].col = circlesSort[7]->color;\
                  l_cache[298].pt1.x = l_cache[299].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-792 / circlesSort[7]->size);\
                  l_cache[298].pt1.y = l_cache[299].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (650 / circlesSort[7]->size);\
                  l_cache[298].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-792 / circlesSort[8]->size);\
                  l_cache[298].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (650 / circlesSort[8]->size);\
                  \
                  l_cache[299].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-532 / circlesSort[7]->size);\
                  l_cache[299].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (875 / circlesSort[7]->size);\
                  l_cache[299].col = circlesSort[7]->color;\
                  \
                  l_cache[300].col = circlesSort[7]->color;\
                  l_cache[300].pt1.x = l_cache[301].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-532 / circlesSort[7]->size);\
                  l_cache[300].pt1.y = l_cache[301].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (875 / circlesSort[7]->size);\
                  l_cache[300].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-532 / circlesSort[8]->size);\
                  l_cache[300].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (875 / circlesSort[8]->size);\
                  \
                  l_cache[301].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-212 / circlesSort[7]->size);\
                  l_cache[301].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (1002 / circlesSort[7]->size);\
                  l_cache[301].col = circlesSort[7]->color;\
                  \
                  l_cache[302].col = circlesSort[7]->color;\
                  l_cache[302].pt1.x = l_cache[303].pt1.x = circlesSort[7]->x + circlesSort[7]->xOffset + (-212 / circlesSort[7]->size);\
                  l_cache[302].pt1.y = l_cache[303].pt1.y = circlesSort[7]->y + circlesSort[7]->yOffset + (1002 / circlesSort[7]->size);\
                  l_cache[302].pt2.x = circlesSort[8]->x + circlesSort[8]->xOffset + (-212 / circlesSort[8]->size);\
                  l_cache[302].pt2.y = circlesSort[8]->y + circlesSort[8]->yOffset + (1002 / circlesSort[8]->size);\
                  \
                  l_cache[303].pt2.x = circlesSort[7]->x + circlesSort[7]->xOffset + (132 / circlesSort[7]->size);\
                  l_cache[303].pt2.y = circlesSort[7]->y + circlesSort[7]->yOffset + (1016 / circlesSort[7]->size);\
                  l_cache[303].col = circlesSort[7]->color;\
                  \

#endif

#endif
