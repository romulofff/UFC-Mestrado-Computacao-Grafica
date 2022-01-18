import math
from random import randrange, uniform

import numpy as np
import OpenGL
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from camera import Camera
from point import Point
from raycasting import Raycasting
from sphere import Sphere


def rotate_vector(vector, angle, axis):
    """
    Vetor de entrada,o tamanho da rotação e o eixo que deve ser girado.
    """
    cos_positive = math.degrees(math.cos(angle))
    sen_positive = math.degrees(math.sen(angle))
    sen_negative = -math.degrees(math.sen(angle))
    if axis == 'z':
        matrix_z = np = [[cos_positive, sen_negative, 0],
                         [sen_positive, cos_positive, 0],
                         [0,            0,            1],
                         ]


def square():
    glBegin(GL_QUADS)
    glVertex2f(100, 100)
    glVertex2f(200, 100)
    glVertex2f(200, 200)
    glVertex2f(100, 200)
    glEnd()


def draw_scene(width, height, nlines, ncols, matrix):
    width_frame = width/ncols
    height_frame = height/nlines
    init_width = -width * 0.5
    init_height = height * 0.5
    for line in range(0, nlines):
        y1 = init_height - height_frame*line
        y2 = init_height - height_frame*(line+1)
        for col in range(0, ncols):
            glColor3f(matrix[line][col][0], matrix[line]
                      [col][1], matrix[line][col][2])
            x1 = init_width + width_frame*col
            x2 = init_width + width_frame*(col+1)
            glBegin(GL_QUADS)
            glVertex2f(x1, y1)
            glVertex2f(x1, y2)
            glVertex2f(x2, y2)
            glVertex2f(x2, y1)
            glEnd()


def iterate():
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-w * 0.5, w*0.5, -h*0.5, h*0.5, 0.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()
    glColor3f(1.0, 0.0, 3.0)
    # square()
    draw_scene(w, h, lines, cols, teste_ray.create_matrix())
    glutSwapBuffers()


if __name__ == '__main__':

    w, h, lines, cols = 500, 500, 250, 250
    point_xyz = Point(0, 0, 0)
    lookat = Point(0, 0, -1)
    view_up = Point(0, 1, 0)
    view = Camera(point_xyz=point_xyz,
                  lookat=lookat, view_up=view_up)
    sphere = Sphere(Point(0, 0, -5), 4)
    sphere.get_center_camera(view)
    teste_ray = Raycasting(sphere, view, 20, w, h, lines, cols)
    print(view.world_to_camera)

    # Initialize a glut instance which will allow us to customize our window
    glutInit()
    glutInitDisplayMode(GLUT_RGBA)  # Set the display mode to be colored
    glutInitWindowSize(w, h)   # Set the width and height of your window
    # Set the position at which this windows should appear
    glutInitWindowPosition(1000, 100)
    # Give your window a title
    wind = glutCreateWindow("OpenGL Coding Practice")
    # Tell OpenGL to call the showScreen method continuously
    glutDisplayFunc(showScreen)
    # Draw any graphics or shapes in the showScreen function at all times
    # glutIdleFunc(showScreen)
    glutMainLoop()  # Keeps the window created above displaying/running in a loop
