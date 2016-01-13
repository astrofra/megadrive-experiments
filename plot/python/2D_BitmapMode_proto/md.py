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
        self.timeStart = time.time()
        self.timeDelta = 0.05 #0.20

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

    def vsync(self):
        rt = 0
        if time.time() - self.timeStart > self.timeDelta:
            self.timeStart = time.time()
            rt = 1
        else:
            rt = 0
        return rt

    @staticmethod
    def get_xres():
        return 256

    @staticmethod
    def get_yres():
        return 160


# -------------------------------------- SGDK ABSTRACT

class SGDK():
    def __init__(self):
        self.mainc = codecs.open("main.c", "w")
        self.mainc.write("#include <genesis.h>\n")
        self.TRUE = 'TRUE'
        self.FALSE = 'FALSE'
        self.end_ = 0
        self.writing = 1
        self.palette_green = 'palette_green'
        self.VMD = VMD()

    def c(self, code):
        if self.end_ == 0 and self.writing == 1:
            self.mainc.write(code + "\n")

    def setVar(self, type, varname, value):
        self.c(type + ' ' + varname + ' = ' + str(value) + ";")
        return value

    def add(self, var, cvarname, val):
        rt = var + val
        if self.end_ == 0 and self.writing == 1:
            self.c( cvarname + '+=' + str(val) + ';' )
        return rt

    def VDP_setScreenWidth256(self):
        if self.end_ == 0 and self.writing == 1:
            self.c('VDP_setScreenWidth256();')


    def VDP_setPalette(self, num, pal):
        if self.end_ == 0 and self.writing == 1:
            self.c('VDP_setPalette(' + str(num) + ', ' + pal + ');')


    def BMP_setPixel(self, x, y, col):
        self.VMD.add_pixel(x, y)
        if self.end_ == 0 and self.writing == 1:
            self.c('BMP_setPixel(' + str(x) + ',' + str(y) + ',' + str(col) + ');')

    def BMP_drawLine(self, line):
        self.VMD.add_line(line.x, line.y, line.w, line.z)
        if self.end_ == 0 and self.writing == 1:
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
        sintab16 = [0, 0, 1, 1, 2, 2, 2, 3,3, 4, 4, 4, 5, 5, 5, 6,6, 7, 7, 7, 8, 8, 9, 9,9, 10, 10, 11, 11, 11, 12, 12,      12, 13, 13, 14, 14, 14, 15, 15,16, 16, 16, 17, 17, 17, 18, 18,19, 19, 19, 20, 20, 20, 21, 21,22, 22, 22, 23, 23, 23, 24, 24,
         24, 25, 25, 26, 26, 26, 27, 27,27, 28, 28, 28, 29, 29, 29, 30,30, 31, 31, 31, 32, 32, 32, 33,33, 33, 34, 34, 34, 35, 35, 35,
         36, 36, 36, 37, 37, 37, 37, 38,38, 38, 39, 39, 39, 40, 40, 40,41, 41, 41, 42, 42, 42, 42, 43,43, 43, 44, 44, 44, 44, 45, 45,
         45, 46, 46, 46, 46, 47, 47, 47,47, 48, 48, 48, 48, 49, 49, 49,49, 50, 50, 50, 50, 51, 51, 51,51, 52, 52, 52, 52, 53, 53, 53,
         53, 53, 54, 54, 54, 54, 54, 55,55, 55, 55, 55, 56, 56, 56, 56,56, 57, 57, 57, 57, 57, 58, 58,58, 58, 58, 58, 59, 59, 59, 59,
         59, 59, 59, 60, 60, 60, 60, 60,60, 60, 61, 61, 61, 61, 61, 61,61, 61, 61, 62, 62, 62, 62, 62,62, 62, 62, 62, 62, 63, 63, 63,
         63, 63, 63, 63, 63, 63, 63, 63,63, 63, 63, 63, 64, 64, 64, 64,64, 64, 64, 64, 64, 64, 64, 64,64, 64, 64, 64, 64, 64, 64, 64,
         64, 64, 64, 64, 64, 64, 64, 64,64, 64, 64, 64, 64, 64, 64, 64,64, 64, 64, 64, 64, 63, 63, 63,63, 63, 63, 63, 63, 63, 63, 63,
         63, 63, 63, 63, 62, 62, 62, 62,62, 62, 62, 62, 62, 62, 61, 61,61, 61, 61, 61, 61, 61, 61, 60,60, 60, 60, 60, 60, 60, 59, 59,
         59, 59, 59, 59, 59, 58, 58, 58,58, 58, 58, 57, 57, 57, 57, 57,56, 56, 56, 56, 56, 55, 55, 55,55, 55, 54, 54, 54, 54, 54, 53,
         53, 53, 53, 53, 52, 52, 52, 52,51, 51, 51, 51, 50, 50, 50, 50,49, 49, 49, 49, 48, 48, 48, 48,47, 47, 47, 47, 46, 46, 46, 46,
         45, 45, 45, 44, 44, 44, 44, 43,43, 43, 42, 42, 42, 42, 41, 41,41, 40, 40, 40, 39, 39, 39, 38,38, 38, 37, 37, 37, 37, 36, 36,
         36, 35, 35, 35, 34, 34, 34, 33,33, 33, 32, 32, 32, 31, 31, 31,30, 30, 29, 29, 29, 28, 28, 28,27, 27, 27, 26, 26, 26, 25, 25,
         24, 24, 24, 23, 23, 23, 22, 22,22, 21, 21, 20, 20, 20, 19, 19,19, 18, 18, 17, 17, 17, 16, 16,16, 15, 15, 14, 14, 14, 13, 13,
         12, 12, 12, 11, 11, 11, 10, 10,9, 9, 9, 8, 8, 7, 7, 7,6, 6, 5, 5, 5, 4, 4, 4,3, 3, 2, 2, 2, 1, 1, 0,0, 0, -1, -1, -2, -2, -2, -3,
         -3, -4, -4, -4, -5, -5, -5, -6,-6, -7, -7, -7, -8, -8, -9, -9,-9, -10, -10, -11, -11, -11, -12, -12,-12, -13, -13, -14, -14, -14, -15, -15,
         -16, -16, -16, -17, -17, -17, -18, -18,-19, -19, -19, -20, -20, -20, -21, -21,-22, -22, -22, -23, -23, -23, -24, -24,
         -24, -25, -25, -26, -26, -26, -27, -27,-27, -28, -28, -28, -29, -29, -29, -30,-30, -31, -31, -31, -32, -32, -32, -33,
         -33, -33, -34, -34, -34, -35, -35, -35,-36, -36, -36, -37, -37, -37, -37, -38,-38, -38, -39, -39, -39, -40, -40, -40,
         -41, -41, -41, -42, -42, -42, -42, -43,-43, -43, -44, -44, -44, -44, -45, -45,-45, -46, -46, -46, -46, -47, -47, -47,
         -47, -48, -48, -48, -48, -49, -49, -49,-49, -50, -50, -50, -50, -51, -51, -51,-51, -52, -52, -52, -52, -53, -53, -53,
         -53, -53, -54, -54, -54, -54, -54, -55,-55, -55, -55, -55, -56, -56, -56, -56,-56, -57, -57, -57, -57, -57, -58, -58,
         -58, -58, -58, -58, -59, -59, -59, -59,-59, -59, -59, -60, -60, -60, -60, -60,-60, -60, -61, -61, -61, -61, -61, -61,
         -61, -61, -61, -62, -62, -62, -62, -62,-62, -62, -62, -62, -62, -63, -63, -63,-63, -63, -63, -63, -63, -63, -63, -63,
         -63, -63, -63, -63, -64, -64, -64, -64,-64, -64, -64, -64, -64, -64, -64, -64,-64, -64, -64, -64, -64, -64, -64, -64,
         -64, -64, -64, -64, -64, -64, -64, -64,-64, -64, -64, -64, -64, -64, -64, -64,-64, -64, -64, -64, -64, -63, -63, -63,
         -63, -63, -63, -63, -63, -63, -63, -63,-63, -63, -63, -63, -62, -62, -62, -62,-62, -62, -62, -62, -62, -62, -61, -61,
         -61, -61, -61, -61, -61, -61, -61, -60,-60, -60, -60, -60, -60, -60, -59, -59,-59, -59, -59, -59, -59, -58, -58, -58,
         -58, -58, -58, -57, -57, -57, -57, -57,-56, -56, -56, -56, -56, -55, -55, -55,-55, -55, -54, -54, -54, -54, -54, -53,
         -53, -53, -53, -53, -52, -52, -52, -52,-51, -51, -51, -51, -50, -50, -50, -50,-49, -49, -49, -49, -48, -48, -48, -48,
         -47, -47, -47, -47, -46, -46, -46, -46,-45, -45, -45, -44, -44, -44, -44, -43,-43, -43, -42, -42, -42, -42, -41, -41,
         -41, -40, -40, -40, -39, -39, -39, -38,-38, -38, -37, -37, -37, -37, -36, -36,-36, -35, -35, -35, -34, -34, -34, -33,
         -33, -33, -32, -32, -32, -31, -31, -31,-30, -30, -29, -29, -29, -28, -28, -28,-27, -27, -27, -26, -26, -26, -25, -25,
         -24, -24, -24, -23, -23, -23, -22, -22,-22, -21, -21, -20, -20, -20, -19, -19,-19, -18, -18, -17, -17, -17, -16, -16,
         -16, -15, -15, -14, -14, -14, -13, -13,-12, -12, -12, -11, -11, -11, -10, -10,-9, -9, -9, -8, -8, -7, -7, -7,
         -6, -6, -5, -5, -5, -4, -4, -4,-3, -3, -2, -2, -2, -1, -1, 0]
        if self.end_ == 0 and self.writing == 1:
            self.c('sinFix16(' + value + ');')
        return sintab16[value & 1023]

    def cosFix16(self, value):
        if self.end_ == 0 and self.writing == 1:
            self.c('cosFix16(' + value + ');')
        return self.sinFix16( (value + 256) & 1023 )

    def BMP_clear(self):
        self.VMD.clear()
        if self.end_ == 0 and self.writing == 1:
            self.c('BMP_clear();')

    def BMP_init(self, double_buffer, palette, priority):
        if self.end_ == 0 and self.writing == 1:
            self.c('BMP_init(' + str(double_buffer) + ',' + str(palette) + ',' + str(priority) + ');')

    def BMP_flip(self, async):
        if self.end_ == 0 and self.writing == 1:
            self.c('BMP_flip(' + str(async) + ');')

    def BMP_waitFlipComplete(self):
        if self.end_ == 0 and self.writing == 1:
            self.c('BMP_waitFlipComplete();')

    def VDP_waitVsync(self):
        if self.end_ == 0 and self.writing == 1:
            self.c('VDP_waitVSync();')

    def end(self):
        if self.end_ == 0:
            self.end_ = 1
            self.mainc.close()
            self.mainc = codecs.open("main.c", "r")
            print self.mainc.read()
            self.mainc.close()
