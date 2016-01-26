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

class circle():
    x = 0
    y = 0
    xOffset = 0
    yOffset = 0
    size = 0

def circleDraw(circle, res):
    for i in range(0, 1024, res):
        SGDK.BMP_setPixel(circle.x + (SGDK.sinFix32(i) / circle.size), (circle.y + SGDK.cosFix32(i) / circle.size), 0xFF)
        print(str(SGDK.sinFix32(i)) + "/" + str(circle.size))

def circleDrawPreca():
    print("Preca")

def circleMakePreca(circle, res, circleTab_x, circleTab_y):
    for i in range(0, 1024, res):
        circleTab_x.append(circle.x + (SGDK.sinFix32(i) / circle.size))
        circleTab_y.append(circle.y + (SGDK.cosFix32(i) / circle.size))


def circleXoffsetAdd():
    circle00.xOffset += 1
    circle01.xOffset += 1
    circle02.xOffset += 1
    circle03.xOffset += 1
    circle04.xOffset += 1
    circle05.xOffset += 1
    circle06.xOffset += 1
    circle07.xOffset += 1
    circle08.xOffset += 1

def circleXoffsetSub():
    circle00.xOffset -= 1
    circle01.xOffset -= 1
    circle02.xOffset -= 1
    circle03.xOffset -= 1
    circle04.xOffset -= 1
    circle05.xOffset -= 1
    circle06.xOffset -= 1
    circle07.xOffset -= 1
    circle08.xOffset -= 1

def circleYoffsetAdd():
    circle00.yOffset += 1
    circle01.yOffset += 1
    circle02.yOffset += 1
    circle03.yOffset += 1
    circle04.yOffset += 1
    circle05.yOffset += 1
    circle06.yOffset += 1
    circle07.yOffset += 1
    circle08.yOffset += 1

def circleYoffsetSub():
    circle00.yOffset -= 1
    circle01.yOffset -= 1
    circle02.yOffset -= 1
    circle03.yOffset -= 1
    circle04.yOffset -= 1
    circle05.yOffset -= 1
    circle06.yOffset -= 1
    circle07.yOffset -= 1
    circle08.yOffset -= 1

def circlesSizeSub():
    circle00.size -= 1
    circle01.size -= 1
    circle02.size -= 1
    circle03.size -= 1
    circle04.size -= 1
    circle05.size -= 1
    circle06.size -= 1
    circle07.size -= 1
    circle08.size -= 1

def circlesDraw():
    circleDraw(circle00, 50)
    circleDraw(circle01, 50)
    circleDraw(circle02, 50)
    circleDraw(circle03, 50)
    circleDraw(circle04, 50)
    circleDraw(circle05, 50)
    circleDraw(circle06, 50)
    circleDraw(circle07, 50)
    circleDraw(circle08, 50)

def loop():
    global circle00
    global circle01
    global circle02
    global circle03
    global circle04
    global circle05
    global circle06
    global circle07
    global circle08
    global vblCount
    global seq

    global circleTab_x
    global circleTab_y

    SGDK.BMP_clear()

    circlesDraw()
    circlesSizeSub()
    #circleMakePreca(circle00, 50, circleTab_x, circleTab_y)

    if circle00.size == 0:
        circle00.size = 100
        circle00.xOffset = 20
        circle00.yOffset = 20

    if circle01.size == 0:
        circle01.size = 100
        circle01.xOffset = 20
        circle01.yOffset = 20

    if circle02.size == 0:
        circle02.size = 100
        circle02.xOffset = 20
        circle02.yOffset = 20

    if circle03.size == 0:
        circle03.size = 100
        circle03.xOffset = 20
        circle03.yOffset = 20

    if circle04.size == 0:
        circle04.size = 100
        circle04.xOffset = 20
        circle04.yOffset = 20

    if circle05.size == 0:
        circle05.size = 100
        circle05.xOffset = 20
        circle05.yOffset = 20

    if circle06.size == 0:
        circle06.size = 100
        circle06.xOffset = 20
        circle06.yOffset = 20

    if circle07.size == 0:
        circle07.size = 100
        circle07.xOffset = 20
        circle07.yOffset = 20

    if circle08.size == 0:
        circle08.size = 100
        circle08.xOffset = 20
        circle08.yOffset = 20

    SGDK.BMP_flip(1)
    SGDK.BMP_waitFlipComplete()

# /////////////////////////////////////////////////////////////
#                       MAIN
# /////////////////////////////////////////////////////////////

SGDK = SGDK()
SGDK.writing = 0
circle00 = circle()
circle01 = circle()
circle02 = circle()
circle03 = circle()
circle04 = circle()
circle05 = circle()
circle06 = circle()
circle07 = circle()
circle08 = circle()

circle00.x = circle01.x = circle02.x = circle03.x = circle04.x = circle05.x = circle06.x = circle07.x = circle08.x = 80
circle00.y = circle01.y = circle02.y = circle03.y = circle04.y = circle05.y = circle06.y = circle07.y = circle08.y = 80
circle00.xOffset = circle01.xOffset = circle02.xOffset = circle03.xOffset = circle04.xOffset = circle05.xOffset = circle06.xOffset = circle07.xOffset = circle08.xOffset = 20
circle00.yOffset = circle01.yOffset = circle02.yOffset = circle03.yOffset = circle04.yOffset = circle05.yOffset = circle06.yOffset = circle07.yOffset = circle08.yOffset = 20

circle00.size = 81
circle01.size = 71
circle02.size = 61
circle03.size = 51
circle04.size = 41
circle05.size = 31
circle06.size = 21
circle07.size = 11
circle08.size = 1

circleTab_x = [0, 0]
circleTab_y = [0, 0]


vblCount = 0
seq = 0

render()

