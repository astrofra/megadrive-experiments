import os
import codecs
import OpenGL
from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *


def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, width / height, 0.1, 100)
    glMatrixMode(GL_MODELVIEW)


def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0)
    glBegin(GL_TRIANGLES)
    glVertex2i(0, 1)
    glVertex2i(-1, 0)
    glVertex2i(1, 0)

    glEnd()
    glutSwapBuffers()
    glutPostRedisplay()


def main():
    glutInit()
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(640, 480)
    windowname = glutCreateWindow("HELLO PY-GL")
    glutReshapeFunc(reshape)
    glutDisplayFunc(draw)
    glutMainLoop()

#-------------------------------------- SGDK ABSTRACT
def VDP_setScreenWidth256():
    mainc = codecs.open('main.c', 'a')
    mainc.write('   VDP_setScreenWidth256();\n')
    mainc.close()

def VDP_setPalette(num, pal):
    mainc = codecs.open('main.c', 'a')
    mainc.write('   VDP_setPalette(' + str(num) + ', ' + pal + ');\n')
    mainc.close()


#------------------------------------------- MAIN

def write_mainc_file():
    palette_green = "palette_green"

    mainc = codecs.open('main.c','w')
    mainc.write("#include <genesis.h>\n\n")
    mainc.write("int main(){\n")

    VDP_setScreenWidth256()
    VDP_setPalette(0, palette_green)

#main()
write_mainc_file()