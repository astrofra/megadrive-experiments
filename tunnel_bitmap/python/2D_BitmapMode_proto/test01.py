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


def loop():
    global plotX
    global plotY
    global vblCount
    global circleRes
    SGDK.c("while(1){")
    SGDK.BMP_clear()

    SGDK.writing = 0
    for i in range(0, 1024 ,circleRes):
        SGDK.BMP_setPixel(100 + SGDK.sinFix16(i), 100 + SGDK.cosFix16(i), 0xFF)
    SGDK.writing = 1

    SGDK.c("u16 i = 0; for (i = 0; i < 1024; i += circleRes){")
    SGDK.c("BMP_setPixel(100 + sinFix16(i), 100 + cosFix16(i), 0xFF);")
    SGDK.c("}")

    circleRes = SGDK.add(circleRes,"circleRes", 1)
    if circleRes > 100:
        circleRes = 1
    SGDK.c("if (circleRes > 100){ circleRes = 1;}")

    SGDK.add(vblCount, "vblCount", 1)
    SGDK.BMP_flip(1)
    SGDK.BMP_waitFlipComplete()
    SGDK.c('}')
    SGDK.c('}')
    SGDK.end()  # stop writing in main.c file


# /////////////////////////////////////////////////////////////
#                       MAIN
# /////////////////////////////////////////////////////////////

SGDK = SGDK()
SGDK.c('int main(){')
SGDK.VDP_setScreenWidth256()
SGDK.BMP_init(SGDK.TRUE, 0, SGDK.FALSE)
vblCount = SGDK.setVar("u16", "vblCount", 0)
plotX = SGDK.setVar("fix16","plotX", 0 )
plotY = SGDK.setVar("fix16","plotY", 0)
circleRes = SGDK.setVar("u16", "circleRes", 1)
render()

