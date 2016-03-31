#ifndef TUNNEL_MACRO_H
#define TUNNEL_MACRO_H

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
                          RSE_recordPixel(circle09.x + circle09.xOffset + (sinFix32(i) / circle09.size), (circle09.y + circle09.yOffset + cosFix32(i) / circle09.size), circle09.color);\
                  \
#endif

#ifdef DOT_TUNNEL_ON
#define circlesPrecalc	u16 i = 0; v_cache_index = 0;\
                                  CIRCLES_SETPIX\
                                  i +=0;\
                                  CIRCLES_SETPIX\
                                  i +=128;\
                                  CIRCLES_SETPIX\
                                  i +=256;\
                                  CIRCLES_SETPIX\
                                  i +=384;\
                                  CIRCLES_SETPIX\
                                  i +=512;\
                                  CIRCLES_SETPIX\
                                  i +=640;\
                                  CIRCLES_SETPIX\
                                  i +=768;\
                                  CIRCLES_SETPIX\
                                  i +=896;\
                                      CIRCLES_SETPIX
#endif

#ifdef WIRE_TUNNEL_ON
#define linePrecalc \
#endif
#endif
