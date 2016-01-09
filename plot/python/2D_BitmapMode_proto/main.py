from md import *


# ---------------------------------------------------------------------------------------
#                                        OPENGL DRAW
# ---------------------------------------------------------------------------------------
def draw():  # you can write some GL sequence in this fuction if needed
    draw_pre()
    loop()
    for pixel in VMD.pixels:
        draw_pixel(pixel.x, pixel.y)
    for line in VMD.lines:
        draw_line(line.x, line.y, line.w, line.z)
    draw_post()


# ---------------------------------------------------------------------------------------
#                                       END OPENGL DRAW
# ---------------------------------------------------------------------------------------


# /////////////////////////////////////////////////////////////
#                       MAIN
# /////////////////////////////////////////////////////////////

def main():
    palette_green = 'palette_green'

    SGDK.c('int main(){')
    SGDK.VDP_setScreenWidth256()
    SGDK.VDP_setPalette(0, palette_green)
    SGDK.BMP_init(TRUE, 0, FALSE)
    render()


def loop():
    global line001
    SGDK.c('while(1){')
    SGDK.BMP_clear()
    SGDK.BMP_setPixel(10, 10, 0xFF)
    SGDK.BMP_setPixel(20, 10, 0xFF)
    SGDK.BMP_setPixel(30, 10, 0xFF)

    SGDK.BMP_drawLine(line001)

    line001.x += 2
    line001.y += 1
    line001.w += 2
    line001.z += 1

    SGDK.BMP_flip(1);
    SGDK.BMP_waitFlipComplete()
    SGDK.c('}')
    SGDK.c('}')
    SGDK.end()  # stop writing main.c file


# ---------------------------ENTRY
#   GLOBALS
VMD = VMD()
SGDK = SGDK(VMD)
TRUE = SGDK.TRUE
FALSE = SGDK.FALSE
line001 = Vec4(50, 50, 100, 100)
main()
