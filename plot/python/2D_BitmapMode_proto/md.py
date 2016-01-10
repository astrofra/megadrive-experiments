import codecs
import time
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


# ---------------------------------GL

def draw_pre():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glViewport(0, 0, VMD.get_xres(), VMD.get_yres())
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0.0, VMD.get_xres(), VMD.get_yres(), 0.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def draw_post():
    glutSwapBuffers()
    glutPostRedisplay()


def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, width / height, 0.1, 100)
    glMatrixMode(GL_MODELVIEW)


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
    from main import draw
    glutInit()
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(VMD.get_xres(), VMD.get_yres())
    windowname = glutCreateWindow("BITMAP MODE")
    glutReshapeFunc(reshape)
    glutDisplayFunc(draw)
    glutMainLoop()

# ---------------------------------MEGADRIVE ABSTRACT

class VMD():
    def __init__(self):
        self.pixels = [Vec2(0, 0)]
        self.lines = [Vec4(0, 0, 0, 0)]

    def clear_pixels(self):
        self.pixels = [Vec2(0, 0)]

    def clear_lines(self):
        self.lines = [Vec4(0, 0, 0, 0)]

    def add_pixel(self, x, y):
        self.pixels.append(Vec2(x, y))

    def add_line(self, x, y, w, z):
        self.lines.append(Vec4(x, y, w, z))

    def clear(self):
        self.clear_pixels()
        self.clear_lines()

    @staticmethod
    def get_xres():
        return 320

    @staticmethod
    def get_yres():
        return 224


# -------------------------------------- SGDK ABSTRACT

class SGDK():
    def __init__(self, vmd):
        self.mainc = codecs.open("main.c", "w")
        self.mainc.write("#include <genesis.h>\n")
        self.TRUE = 'TRUE'
        self.FALSE = 'FALSE'
        self.end_ = 0
        self.vmd = vmd

    def c(self, code):
        if self.end_ == 0:
            self.mainc.write(code + "\n")

    def VDP_setScreenWidth256(self):
        if self.end_ == 0:
            self.c('VDP_setScreenWidth256();')


    def VDP_setPalette(self, num, pal):
        if self.end_ == 0:
            self.c('VDP_setPalette(' + str(num) + ', ' + pal + ');')


    def BMP_setPixel(self, x, y, col):
        self.vmd.add_pixel(x, y)
        if self.end_ == 0:
            self.c('BMP_setPixel(' + str(x) + ',' + str(y) + ',' + str(col) + ');')

    def BMP_drawLine(self, line):
        self.vmd.add_line(line.x, line.y, line.w, line.z)
        if self.end_ == 0:
            self.c('Line l;')
            self.c('Vect2D_s16 start, end;')
            self.c('start.x = ' + str(line.x) + ';')
            self.c('start.y = ' + str(line.y) + ';')
            self.c('end.x = ' + str(line.w) + ';')
            self.c('end.y = ' + str(line.z) + ';')
            self.c('l.pt1 = start;')
            self.c('l.pt2 = end;')
            self.c('l.col = 0xFF;')
            self.c('BMP_drawLine(&l);')

    def sinFix16(self, value):
        if self.end_ == 0:
            self.c('sinFix16(' + str(value) + ')')

    def BMP_clear(self):
        self.vmd.clear()
        if self.end_ == 0:
            self.c('BMP_clear();')

    def BMP_init(self, double_buffer, palette, priority):
        if self.end_ == 0:
            self.c('BMP_init(' + str(double_buffer) + ',' + str(palette) + ',' + str(priority) + ');')

    def BMP_flip(self, async):
        if self.end_ == 0:
            self.c('BMP_flip(' + str(async) + ');')

    def BMP_waitFlipComplete(self):
        time.sleep(.2)
        if self.end_ == 0:
            self.c('BMP_waitFlipComplete();')

    def end(self):
        self.end_ = 1
        self.mainc.close()
