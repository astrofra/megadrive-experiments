from md import *

# ---------------------------------------------------------------------------------------
#                                        OPENGL DRAW
# ---------------------------------------------------------------------------------------
def draw():  # you can write some GL sequence in this function if needed
    draw_pre()
    if SGDK.VMD.vsync():
        loop()
    for pixel in SGDK.VMD.pixels:
        draw_pixel(pixel.x, pixel.y)
    for line in SGDK.VMD.lines:
        draw_line(line.x, line.y, line.w, line.z)
    draw_post()
# ---------------------------------------------------------------------------------------
#                                       END OPENGL DRAW
# ---------------------------------------------------------------------------------------

def circle(x , y, size, plotRes):
    SGDK.writing = 0
    if size == 0:
        size = 1
    for i in range(0, 1024, plotRes):
        SGDK.BMP_setPixel(x + (SGDK.sinFix32(i) / size), (y + SGDK.cosFix32(i) / size), 0xFF)
    SGDK.writing = 1

def loop():
    global vblCount
    global seq
    global circle00Size
    global circle01Size
    global circle02Size
    global circle03Size
    global circle04Size
    global offsetX00
    global offsetX01
    global offsetX02
    global offsetX03
    global offsetX04
    global offsetY00
    global offsetY01
    global offsetY02
    global offsetY03
    global offsetY04

    SGDK.BMP_clear()
    SGDK.BMP_showFPS(1)
    circle(80 + offsetX00, 80 + offsetY00, circle00Size, 50) #plus petit
    circle(80 + offsetX01, 80 + offsetY01, circle01Size, 50)
    circle(80 + offsetX02, 80 + offsetY02, circle02Size, 50)
    circle(80 + offsetX03, 80 + offsetY03, circle03Size, 50)
    circle(80 + offsetX04, 80 + offsetY04, circle04Size, 50)


    circle00Size = SGDK.sub(circle00Size, "circle00Size", 1)
    circle01Size = SGDK.sub(circle01Size, "circle01Size", 1)
    circle02Size = SGDK.sub(circle02Size, "circle02Size", 1)
    circle03Size = SGDK.sub(circle03Size, "circle03Size", 1)
    circle04Size = SGDK.sub(circle04Size, "circle04Size", 1)

    vblCount = SGDK.add(vblCount, "vblCount", 1)

    if seq == 1:
        offsetX00 = SGDK.sub(offsetX00, "offsetX00", 1 )
        offsetX01 = SGDK.sub(offsetX01, "offsetX01", 1 )
        offsetX02 = SGDK.sub(offsetX02, "offsetX02", 1 )
        offsetX03 = SGDK.sub(offsetX03, "offsetX03", 1 )
        offsetX04 = SGDK.sub(offsetX04, "offsetX04", 1 )

    if seq == 2:
        offsetX00 = SGDK.sub(offsetX00, "offsetX00", 1 )
        offsetX01 = SGDK.sub(offsetX01, "offsetX01", 1 )
        offsetX02 = SGDK.sub(offsetX02, "offsetX02", 1 )
        offsetX03 = SGDK.sub(offsetX03, "offsetX03", 1 )
        offsetX04 = SGDK.sub(offsetX04, "offsetX04", 1 )
        offsetY00 = SGDK.sub(offsetY00, "offsetY00", 1 )
        offsetY01 = SGDK.sub(offsetY01, "offsetY01", 1 )
        offsetY02 = SGDK.sub(offsetY02, "offsetY02", 1 )
        offsetY03 = SGDK.sub(offsetY03, "offsetY03", 1 )
        offsetY04 = SGDK.sub(offsetY04, "offsetY04", 1 )

    if circle00Size == 0:
        circle00Size = 121
        offsetX00 = 20
        offsetY00 = 20

    if circle01Size == 0:
        circle01Size = 121
        offsetX01 = 20
        offsetY01 = 20

    if circle02Size == 0:
        circle02Size = 121
        offsetX02 = 20
        offsetY02 = 20

    if circle03Size == 0:
        circle03Size = 121
        offsetX03 = 20
        offsetY03 = 20

    if circle04Size == 0:
        circle04Size = 121
        offsetX04 = 20
        offsetY04 = 20

    if vblCount > 20 and seq == 0:
        seq = SGDK.add(seq, "seq",1)

    if vblCount > 100 and seq == 1:
        seq = SGDK.add(seq, "seq",1)

    SGDK.BMP_flip(1)
    SGDK.BMP_waitFlipComplete()
    SGDK.end()  # stop writing in main.c file

# /////////////////////////////////////////////////////////////
#                       MAIN
# /////////////////////////////////////////////////////////////

SGDK = SGDK()
SGDK.VDP_setScreenWidth256()
SGDK.BMP_init(SGDK.TRUE, 0, SGDK.FALSE)
vblCount = SGDK.setVar("u16", "vblCount", 0)
circle00Size = SGDK.setVar("u16", "circle00Size", 121)
circle01Size = SGDK.setVar("u16", "circle01Size", 91)
circle02Size = SGDK.setVar("u16", "circle02Size", 61)
circle03Size = SGDK.setVar("u16", "circle03Size", 31)
circle04Size = SGDK.setVar("u16", "circle04Size", 1)

offsetX00 = SGDK.setVar("u16", "offsetX00", 20)
offsetX01 = SGDK.setVar("u16", "offsetX01", 20)
offsetX02 = SGDK.setVar("u16", "offsetX02", 20)
offsetX03 = SGDK.setVar("u16", "offsetX03", 20)
offsetX04 = SGDK.setVar("u16", "offsetX04", 20)
offsetX05 = SGDK.setVar("u16", "offsetX05", 20)

offsetY00 = SGDK.setVar("u16", "offsetY00", 20)
offsetY01 = SGDK.setVar("u16", "offsetY01", 20)
offsetY02 = SGDK.setVar("u16", "offsetY02", 20)
offsetY03 = SGDK.setVar("u16", "offsetY03", 20)
offsetY04 = SGDK.setVar("u16", "offsetY04", 20)
offsetY05 = SGDK.setVar("u16", "offsetY05", 20)

seq = SGDK.setVar("u16", "seq", 0)

render()

