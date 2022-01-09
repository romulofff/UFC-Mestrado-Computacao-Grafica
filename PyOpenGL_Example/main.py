import OpenGL
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from random import randrange, uniform

w,h= 800,600
matrix = [ [ [uniform(0,1),uniform(0,1),uniform(0,1)] for a in range(0,600)] for b in range(0,800)]

def initMatrix():
    for a in range(0,800):
        for b in range(0,600):
            glColor3f(matrix[a][b][0],matrix[a][b][1],matrix[a][b][2])
            glBegin(GL_POINTS)
            glVertex3f(float(a), float(b), 0.0)
            glEnd()
    

def square():
    glBegin(GL_QUADS)
    glVertex2f(100, 100)
    glVertex2f(200, 100)
    glVertex2f(200, 200)
    glVertex2f(100, 200)
    glEnd()

def iterate():
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, w, 0.0, h, 0.0, 1.0)
    glMatrixMode (GL_MODELVIEW)
    glLoadIdentity()

def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()
    glColor3f(1.0, 0.0, 3.0)
    #square()
    initMatrix()
    glutSwapBuffers()

# Initialize a glut instance which will allow us to customize our window
glutInit()
glutInitDisplayMode(GLUT_RGBA)  # Set the display mode to be colored
glutInitWindowSize(w, h)   # Set the width and height of your window
# Set the position at which this windows should appear
glutInitWindowPosition(0, 0)
wind = glutCreateWindow("OpenGL Coding Practice")  # Give your window a title
# Tell OpenGL to call the showScreen method continuously
glutDisplayFunc(showScreen)
# Draw any graphics or shapes in the showScreen function at all times
glutIdleFunc(showScreen)
glutMainLoop()  # Keeps the window created above displaying/running in a loop
