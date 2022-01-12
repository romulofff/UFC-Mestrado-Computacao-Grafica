import math
from random import randrange, uniform

import numpy as np
import OpenGL
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from camera import Camera
from point import Point


def rotate_vector(vector, angle, axis):
    """
    Vetor de entrada,o tamanho da rotação e o eixo que deve ser girado.
    """
    cos_positive = math.degrees(math.cos(angle))
    sen_positive = math.degrees(math.sen(angle))
    sen_negative = -math.degrees(math.sen(angle))
    if axis == 'z':
        matrix_z = np.matrix = [[cos_positive, sen_negative, 0],
                                [sen_positive, cos_positive, 0],
                                [0,            0,            1],
                                ]


def init_matrix():
    for a in range(w):
        for b in range(h):
            glColor3f(matrix[a][b][0], matrix[a][b][1], matrix[a][b][2])
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
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()
    glColor3f(1.0, 0.0, 3.0)
    # square()
    init_matrix()
    glutSwapBuffers()


if __name__ == '__main__':

    w, h = 800, 600
    matrix = [[[uniform(0, 1), uniform(0, 1), uniform(0, 1)]
               for a in range(h)] for b in range(w)]

    point_xyz = Point(10, 10, 10)
    lookat = Point(2, 0, 0)
    view_up = Point(0, 2, 0)
    sagital_point = Point(2, 2, 2)

    view = Camera(point_xyz=point_xyz.matrix,
                  lookat=lookat.matrix, view_up=view_up.matrix)
    print(view.world_to_camera)

    # Initialize a glut instance which will allow us to customize our window
    glutInit()
    glutInitDisplayMode(GLUT_RGBA)  # Set the display mode to be colored
    glutInitWindowSize(w, h)   # Set the width and height of your window
    # Set the position at which this windows should appear
    glutInitWindowPosition(0, 0)
    # Give your window a title
    wind = glutCreateWindow("OpenGL Coding Practice")
    # Tell OpenGL to call the showScreen method continuously
    glutDisplayFunc(showScreen)
    # Draw any graphics or shapes in the showScreen function at all times
    glutIdleFunc(showScreen)
    glutMainLoop()  # Keeps the window created above displaying/running in a loop
