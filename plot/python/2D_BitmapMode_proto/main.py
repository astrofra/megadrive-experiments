import OpenGL
from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *

def reshape(width, height):
	glViewport(0,0,width,height)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	gluPerspective(45,width/height,0.1,100)
	glMatrixMode(GL_MODELVIEW)

def draw():
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()
	gluLookAt(0,0,-10,0,0,0,0,1,0)
	glBegin(GL_TRIANGLES)
	glVertex2i(0,1)
	glVertex2i(-1,0)
	glVertex2i(1,0)

	glEnd()
	glutSwapBuffers()
	glutPostRedisplay()

def main():
	glutInit()
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
	glutInitWindowSize(640,480)
	windowName = glutCreateWindow("HELLO PYGL")
	glutReshapeFunc(reshape)
	glutDisplayFunc(draw)

	glutMainLoop()

main()

