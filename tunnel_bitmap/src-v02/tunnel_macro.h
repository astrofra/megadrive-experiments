#ifndef TUNNEL_MACRO_H
#define TUNNEL_MACRO_H

#define PIXELS_MAX    256
#define LINES_MAX     24

#define RSE_recordPixel(A,B,C) v_cache[v_cache_index].pt.x = A; v_cache[v_cache_index].pt.y = B; v_cache[v_cache_index].col = C; v_cache_index++;

#define CIRCLES_SETPIX     \
                          RSE_recordPixel(circle00.x + circle00.xOffset + (sinFix32(i) / circle00.size), (circle00.y + circle00.yOffset + cosFix32(i) / circle00.size), circle00.color);\
                  \

#define circlesDotPrecalc	u16 i = 0; v_cache_index = 0;\
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

#define circlesMake\
                      circle circle00;\
                      circle00.x = 80;          \
                      circle00.y = 80;          \
                      circle00.xOffset = 20;          \
                      circle00.yOffset = 20;          \
                      circle00.color = 0xF;          \
          \

#define circlesSizeSub    circle00.size--;
#endif
