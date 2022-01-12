import math
from random import randrange, uniform

import numpy as np
import OpenGL
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *


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


def cross_product(point_a, point_b):
    x = point_a[0, 1]*point_b[0, 2] - point_a[0, 2] * point_b[0, 1]
    y = point_a[0, 2]*point_b[0, 0] - point_a[0, 0] * point_b[0, 2]
    z = point_a[0, 0]*point_b[0, 1] - point_a[0, 1] * point_b[0, 0]
    return np.matrix([x, y, z])


def normalize_vector(vector):
    norm = np.sqrt(np.square(vector).sum())
    return vector / norm


def dot(vector1, vector2):
    return vector1[0, 0] * vector2[0, 0] + vector1[0, 1] * vector2[0, 1] + vector1[0, 2] * vector2[0, 2]


w, h = 800, 600
matrix = [[[uniform(0, 1), uniform(0, 1), uniform(0, 1)]
           for a in range(h)] for b in range(w)]


class camera:
    def __init__(self, point_xyz, lookat, view_up, sagital_point_xyz):
        self.point_xyz = point_xyz
        self.sagital_point_xyz = sagital_point_xyz
        self.vector_k = self.origin_cordinates_k(point_xyz, lookat)
        self.vector_i = self.origin_cordinates_i(point_xyz, lookat, view_up)
        self.vector_j = normalize_vector(
            cross_product(self.vector_k, self.vector_i))
        self.world_to_camera = np.matrix([[self.vector_i[0, 0], self.vector_i[0, 1], self.vector_i[0, 2], -(dot(self.vector_i, self.point_xyz))],
                                         [self.vector_j[0, 0], self.vector_j[0, 1],
                                             self.vector_j[0, 2], -(dot(self.vector_j, self.point_xyz))],
                                         [self.vector_k[0, 0], self.vector_k[0, 1],
                                             self.vector_k[0, 2], -(dot(self.vector_k, self.point_xyz))],
                                         [0, 0, 0, 1]]
                                         )

    def origin_cordinates_k(self, point_xyz, lookat):
        vector_k = point_xyz - lookat
        vector_k = normalize_vector(vector_k)
        return vector_k

    def origin_cordinates_i(self, point_xyz, lookat, view_up):
        v_up = view_up - point_xyz
        vector_i = cross_product(v_up, self.vector_k)
        vector_i = normalize_vector(vector_i)
        return vector_i


view = camera(point_xyz=np.matrix([10, 10, 10]), lookat=np.matrix(
    [2, 0, 0]), view_up=np.matrix([0, 2, 0]), sagital_point_xyz=np.matrix([2, 2, 2]))
print(view.world_to_camera)


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
