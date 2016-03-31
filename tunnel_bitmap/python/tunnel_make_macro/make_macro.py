import codecs
from sgdk_trigo import *

circle_res = 55 #55
lines_max = 304 #300


macro_file = codecs.open("..\..\src\/tunnel_macro.h", "w")
macro_file.write("#ifndef TUNNEL_MACRO_H\n")
macro_file.write("#define TUNNEL_MACRO_H\n\n")

macro_file.write("#define CIRCLE_RES " + str(circle_res) + "\n\n")

macro_file.write("#ifdef WIRE_TUNNEL_ON\n")
macro_file.write("  #define LINES_MAX " + str(lines_max) + "\n")
macro_file.write("#endif\n\n")

macro_file.write("#ifdef DOT_TUNNEL_ON\n")
macro_file.write("#define RSE_recordPixel(A,B,C) v_cache[v_cache_index].pt.x = A; v_cache[v_cache_index].pt.y = B; v_cache[v_cache_index].col = C; v_cache_index++;\n\n")

macro_file.write("#define CIRCLES_SETPIX     \\\n")
macro_file.write("                          RSE_recordPixel(circle00.x + circle00.xOffset + (sinFix32(i) / circle00.size), (circle00.y + circle00.yOffset + cosFix32(i) / circle00.size), circle00.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle01.x + circle01.xOffset + (sinFix32(i) / circle01.size), (circle01.y + circle01.yOffset + cosFix32(i) / circle01.size), circle01.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle02.x + circle02.xOffset + (sinFix32(i) / circle02.size), (circle02.y + circle02.yOffset + cosFix32(i) / circle02.size), circle02.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle03.x + circle03.xOffset + (sinFix32(i) / circle03.size), (circle03.y + circle03.yOffset + cosFix32(i) / circle03.size), circle03.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle04.x + circle04.xOffset + (sinFix32(i) / circle04.size), (circle04.y + circle04.yOffset + cosFix32(i) / circle04.size), circle04.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle05.x + circle05.xOffset + (sinFix32(i) / circle05.size), (circle05.y + circle05.yOffset + cosFix32(i) / circle05.size), circle05.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle06.x + circle06.xOffset + (sinFix32(i) / circle06.size), (circle06.y + circle06.yOffset + cosFix32(i) / circle06.size), circle06.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle07.x + circle07.xOffset + (sinFix32(i) / circle07.size), (circle07.y + circle07.yOffset + cosFix32(i) / circle07.size), circle07.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle08.x + circle08.xOffset + (sinFix32(i) / circle08.size), (circle08.y + circle08.yOffset + cosFix32(i) / circle08.size), circle08.color);\\\n")
macro_file.write("                          RSE_recordPixel(circle09.x + circle09.xOffset + (sinFix32(i) / circle09.size), (circle09.y + circle09.yOffset + cosFix32(i) / circle09.size), circle09.color);\n")
macro_file.write("#endif\n\n")


macro_file.write("#ifdef DOT_TUNNEL_ON\n")
macro_file.write("#define circlesPrecalc	u16 i = 0; v_cache_index = 0;\\\n")

i = 0
while i < 1024:
    macro_file.write("                                  CIRCLES_SETPIX\\\n")
    macro_file.write("                                  i += CIRCLE_RES;\\\n")
    i = i + circle_res
macro_file.write("                                      CIRCLES_SETPIX\n")
macro_file.write("#endif\n\n")

macro_file.write("#ifdef WIRE_TUNNEL_ON\n")
macro_file.write("#define linePrecalc \\\n")

i = 0
j = 0
l_cache_index = 0
for i in range(9): #9
    for j in range(0, 1024, circle_res):
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].col = circlesSort[" + str(i) + "]->color;\\\n")
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].pt1.x = l_cache[" + str(l_cache_index + 1) + "].pt1.x = circlesSort[" + str(i) + "]->x + circlesSort[" + str(i) + "]->xOffset + (" + str(sinFix32(j)) + " / circlesSort[" + str(i) + "]->size);\\\n")
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].pt1.y = l_cache[" + str(l_cache_index + 1) + "].pt1.y = circlesSort[" + str(i) + "]->y + circlesSort[" + str(i) + "]->yOffset + (" + str(cosFix32(j)) + " / circlesSort[" + str(i) + "]->size);\\\n")
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].pt2.x = circlesSort[" + str(i + 1) + "]->x + circlesSort[" + str(i + 1) + "]->xOffset + ("+ str(sinFix32(j)) + " / circlesSort[" + str(i + 1) + "]->size);\\\n")
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].pt2.y = circlesSort[" + str(i + 1) + "]->y + circlesSort[" + str(i + 1) + "]->yOffset + ("+ str(cosFix32(j)) + " / circlesSort[" + str(i + 1) + "]->size);\\\n")
        l_cache_index += 1
        macro_file.write("                  \\\n")
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].pt2.x = circlesSort[" + str(i) + "]->x + circlesSort[" + str(i) + "]->xOffset + (" + str(sinFix32(j + circle_res)) + " / circlesSort[" + str(i) + "]->size);\\\n")
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].pt2.y = circlesSort[" + str(i) + "]->y + circlesSort[" + str(i) + "]->yOffset + (" + str(cosFix32(j + circle_res)) + " / circlesSort[" + str(i) + "]->size);\\\n")
        macro_file.write("                  l_cache[" + str(l_cache_index) + "].col = circlesSort[" + str(i) + "]->color;\\\n")
        l_cache_index += 1
        macro_file.write("                  \\\n")
macro_file.write("\n")
macro_file.write("#endif\n\n")

macro_file.write("#ifdef WIRE_TUNNEL_ON\n")
macro_file.write("#define linesDraw\\\n")
for i in range(lines_max):
    macro_file.write("      BMP_drawLine(&l_cache[" + str(i) + "]);\\\n")
macro_file.write("                  \\\n")
macro_file.write("\n")
macro_file.write("#endif\n")

macro_file.write("#endif\n")







