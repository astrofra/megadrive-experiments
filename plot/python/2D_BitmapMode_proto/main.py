import codecs
from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *

class Vec2:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Vec4:
    def __init__(self, x, y, w, z):
        self.x = x
        self.y = y
        self.w = w
        self.z = z


# ---------------------------------MEGADRIVE ABSTRACT

class VMD:
    def __init__(self):
        self.pixels = [Vec2(0, 0)]
        self.lines = [Vec4(0, 0, 0, 0)]
        self.mainc = codecs.open("main.c", "w")
        self.mainc.write("#include <genesis.h>\n")

    def c(self, code):
        self.mainc.write(code + "\n")

    def reset_pixels(self):
        self.pixels = [Vec2(0, 0)]

    def add_pixel(self, x, y):
        self.pixels.append(Vec2(x, y))

    def add_line(self, x, y, w, z):
        self.lines.append(Vec4(x, y, w, z))

    @staticmethod
    def get_xres():
        return 320

    @staticmethod
    def get_yres():
        return 224

# ---------------------------------GL

def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, width / height, 0.1, 100)
    glMatrixMode(GL_MODELVIEW)


def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glViewport(0, 0, VMD.get_xres(), VMD.get_yres())
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0.0, VMD.get_xres(), VMD.get_yres(), 0.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    # draw pixels
    for pixel in VMD.pixels:
        draw_pixel(pixel.x, pixel.y)

    # draw lines
    for line in VMD.lines:
        draw_line(line.x, line.y, line.w, line.z)

    glutSwapBuffers()
    glutPostRedisplay()


def draw_pixel(x, y):
    glBegin(GL_POINTS)
    glVertex2i(x, y)
    glEnd()


def draw_line(x, y, w, z):
    glBegin(GL_LINES)
    glVertex2i(x, y)
    glVertex2i(w, z)
    glEnd()


def render():
    glutInit()
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(VMD.get_xres(), VMD.get_yres())
    windowname = glutCreateWindow("BITMAP MODE")
    glutReshapeFunc(reshape)
    glutDisplayFunc(draw)
    glutMainLoop()


# -------------------------------------- SGDK ABSTRACT

def VDP_setScreenWidth256():
    VMD.c('   VDP_setScreenWidth256();')


def VDP_setPalette(num, pal):
    VMD.c('   VDP_setPalette(' + str(num) + ', ' + pal + ');')


def BMP_setPixel(x, y, col):
    VMD.c('    BMP_setPixel(' + str(x) + ',' + str(y) + ',' + str(col) + ');')
    VMD.add_pixel(x, y)

class Line():
    def __init__(self, x, y, w, z):
        self.x = x
        self.y = y
        self.w = w
        self.z = z

    def BMP_drawLine(self):
        VMD.c('     Line l;')
        VMD.c('     Vect2D_s16 start, end;')
        VMD.c('     start.x = ' + str(self.x) + ';')
        VMD.c('     start.y = ' + str(self.y) + ';')
        VMD.c('     end.x = ' + str(self.w) + ';')
        VMD.c('     end.y = ' + str(self.z) + ';')
        VMD.c('     l.pt1 = start;')
        VMD.c('     l.pt2 = end;')
        VMD.c('     l.col = 0xFF;')
        VMD.c('     BMP_drawLine(&l);')
        VMD.add_line(self.x, self.y, self.w, self.z)


# ------------------------------------------- MAIN

def main():
    palette_green = "palette_green"

    VMD.c("int main(){")
    VDP_setScreenWidth256()
    VDP_setPalette(0, palette_green)
    VMD.c("	BMP_init(TRUE, 0, FALSE);")


    VMD.c("     while(1){")
    BMP_setPixel(10, 10, 0xFF)
    BMP_setPixel(20, 10, 0xFF)
    BMP_setPixel(30, 10, 0xFF)

    l = Line(50, 50, 100, 100)
    l.BMP_drawLine()
    VMD.c("     		BMP_flip(1);")
    VMD.c("             BMP_waitFlipComplete();")
    VMD.c("         }")
    VMD.c("     }")
    render()

# ---------------------------ENTRY

VMD = VMD()
main()
