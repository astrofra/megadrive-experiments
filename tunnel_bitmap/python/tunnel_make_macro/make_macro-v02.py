import codecs
from sgdk_trigo import *

circle_res = 8      #8
circles_max = 1    #10

lines_max = (circle_res * circles_max) * 3
pixels_max = 256

#macro_file = codecs.open("..\..\src-v02\/tunnel_macro.h", "w")
macro_file = codecs.open("../../src-v02/tunnel_macro.h", "w")

macro_file.write("#ifndef TUNNEL_MACRO_H\n")
macro_file.write("#define TUNNEL_MACRO_H\n\n")

macro_file.write("#define PIXELS_MAX    " + str(pixels_max) + "\n")
macro_file.write("#define LINES_MAX     " + str(lines_max) + "\n")
macro_file.write("\n")

macro_file.write("#define RSE_recordPixel(A,B,C) v_cache[v_cache_index].pt.x = A; v_cache[v_cache_index].pt.y = B; v_cache[v_cache_index].col = C; v_cache_index++;\n\n")

macro_file.write("#define CIRCLES_SETPIX     \\\n")

for i in range (circles_max):
    macro_file.write("                          RSE_recordPixel(circle0" + str(i) + ".x + circle0" + str(i) + ".xOffset + (sinFix32(i) / circle0" + str(i) + ".size), (circle0" + str(i) + ".y + circle0" + str(i) + ".yOffset + cosFix32(i) / circle0" + str(i) + ".size), circle0" + str(i) + ".color);\\\n")
macro_file.write("                  \\\n")
macro_file.write("\n")

macro_file.write("#define circlesDotPrecalc	u16 i = 0; v_cache_index = 0;\\\n")

i = 0
while i < 1024:
    macro_file.write("                                  CIRCLES_SETPIX\\\n")
    macro_file.write("                                  i +=" + str(i) + ";\\\n")
    i = i + (1024 / circle_res)
macro_file.write("                                  CIRCLES_SETPIX\n")
macro_file.write("\n")

#macro_file.write("#define circlesLinePrecalc\\\n")


i = 0
for i in range (circles_max):
    if i == 0:
        macro_file.write("#define circlesMake\\\n")
        macro_file.write("                      circle circle00")
    else:
        macro_file.write(",circle0" + str(i))
    if i == circles_max - 1:
        macro_file.write(";\\\n")
i = 0
for i in range (circles_max):
    if i == 0:
        macro_file.write("                      circle0" + str(i) + ".x = ")
    else:
        macro_file.write("circle0" + str(i) + ".x = ")
    if i == circles_max - 1:
        macro_file.write("80;")
macro_file.write("          \\\n")

i = 0
for i in range (circles_max):
    if i == 0:
        macro_file.write("                      circle0" + str(i) + ".y = ")
    else:
        macro_file.write("circle0" + str(i) + ".y = ")
    if i == circles_max - 1:
        macro_file.write("80;")
macro_file.write("          \\\n")

i = 0
for i in range (circles_max):
    if i == 0:
        macro_file.write("                      circle0" + str(i) + ".xOffset = ")
    else:
        macro_file.write("circle0" + str(i) + ".xOffset = ")
    if i == circles_max - 1:
        macro_file.write("20;")
macro_file.write("          \\\n")

i = 0
for i in range (circles_max):
    if i == 0:
        macro_file.write("                      circle0" + str(i) + ".yOffset = ")
    else:
        macro_file.write("circle0" + str(i) + ".yOffset = ")
    if i == circles_max - 1:
        macro_file.write("20;")
macro_file.write("          \\\n")

i = 0
for i in range (circles_max):
    if i == 0:
        macro_file.write("                      circle0" + str(i) + ".color = ")
    else:
        macro_file.write("circle0" + str(i) + ".color = ")
    if i == circles_max - 1:
        macro_file.write("0xF;")
macro_file.write("          \\\n")

i = 0



macro_file.write("          \\\n")
macro_file.write("\n")

macro_file.write("#define circlesSizeSub    ")
i = 0
for i in range (circles_max):
    macro_file.write("circle0" + str(i) + ".size--;")
macro_file.write("\n")


macro_file.write("#endif\n")