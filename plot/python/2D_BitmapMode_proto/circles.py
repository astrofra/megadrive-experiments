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
    global circleSize
    SGDK.c("while(1){")
    SGDK.BMP_clear()
    SGDK.BMP_showFPS(1)
    circle(100, 100, circleSize,      30) #plus petit
    circle(100, 100, circleSize - 40, 30)
    circle(100, 100, circleSize - 60, 30)

    SGDK.c("circle(100, 100, circleSize, 30);")
    SGDK.c("circle(100, 100, circleSize - 40, 30);")
    SGDK.c("circle(100, 100, circleSize - 60, 30);")

    circleSize = SGDK.sub(circleSize, "circleSize", 1)
    vblCount = SGDK.add(vblCount, "vblCount", 1)
    SGDK.BMP_flip(1)
    SGDK.BMP_waitFlipComplete()
    SGDK.c("}")
    SGDK.c("}")
    SGDK.end()  # stop writing in main.c file

# /////////////////////////////////////////////////////////////
#                       MAIN
# /////////////////////////////////////////////////////////////

SGDK = SGDK()
SGDK.c('int main(){')
SGDK.VDP_setScreenWidth256()
SGDK.BMP_init(SGDK.TRUE, 0, SGDK.FALSE)
vblCount = SGDK.setVar("u16", "vblCount", 0)
circleSize = SGDK.setVar("u16", "circleSize", 100)
SGDK.c("void circle(u16 x, u16 y, u16 size, u16 plotRes){")
SGDK.c("if(size == 0) size = 1;")
SGDK.c("u16 i = 0; for(i = 0; i < 1024; i += plotRes){")
SGDK.c("BMP_setPixel(x + (sinFix32(i) / size), (y + cosFix32(i) / size), 0xFF);")
SGDK.c("}")
SGDK.c("}")
render()

