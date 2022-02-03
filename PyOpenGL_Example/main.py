import math
from random import randrange, uniform

import numpy as np
import OpenGL
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from camera import Camera
from cylinder import Cylinder
from cone import Cone
from plane import Plane
from point import Point
from raycasting import Raycasting
from sphere import Sphere
from material import Material
from ambient_light import AmbientLight
from point_light import PointLight
from directionoal_point_light import DirectionalPointLight
from spot_light import SpotLight

from utils import *


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

    w, h, lines, cols = 500, 500, 150, 150
    point_xyz = Point(0, 0, 3)
    lookat = Point(0, 0, -1)
    view_up = Point(0, 1, 0)
    view = Camera(point_xyz=point_xyz,
                  lookat=lookat, view_up=view_up)
    
    # Materials
    bronze = Material([0.2125, 0.1275, 0.054],[0.714, 0.4284, 0.18144],[0.393548, 0.271906, 0.166721],0)
    gold = Material([0.24725, 0.1995, 0.0745],[0.75164, 0.60648, 0.22648],[0.628281, 0.555802, 0.366065],2)
    obsidian = Material([0.05375, 0.05, 0.06625],[0.18275, 0.17, 0.22525],[0.332741, 0.328634, 0.346435], 0)
    chrome = Material([0.25, 0.25, 0.25],[0.4, 0.4, 0.4],[0.774597, 0.774597, 0.774597],0)

    # Lights
    light_ambient = AmbientLight([1.0,1.0,1.0])

    point_light = PointLight(Point(0.0,0.0,0.0), [0.5,0.5,0.5])
    point_light.get_point_camera(view)

    directional_point_light = DirectionalPointLight(Point(0,10,-90), [0.1,0.1,0.1], Point(0.0,1.0,1.0))
    directional_point_light.get_point_camera(view)

    spot_light = SpotLight(Point(-40.0,20.0,-50.0), [0.8,0.5,0.5], Point(1.0,-1.0, 0.0), 180)
    spot_light.get_point_camera(view)

    lights = [point_light, directional_point_light, spot_light]

    # Objects 
    cylinder = Cylinder(Point(0, 0, -50), 9, 18, Point(0.0, 0.7, -1.0), bronze)
    cylinder.get_center_camera(view)
    
    sphere = Sphere(Point(-15.0, 15.0, -90.0), 12, bronze)
    sphere.get_center_camera(view)
    print(sphere.center_camera.matrix)
    
    sphere1 = Sphere(Point(0.0, 10.0, -60), 9, gold)
    sphere1.get_center_camera(view)
    
    # cone = Cone(Point(-10,-10,-50), None, Point(-1,0,0), 30, 2, 3, Point(-15,15,-90))
    cone = Cone(Point(0, 0, -50), 9, 18, Point(0.0, 0.7, -1.0))
    cone.get_center_camera(view)

    plane = Plane(Point(0,0,-100), Point(0,0.7,1), obsidian)
    plane1 = Plane(Point(120,0,0), Point(-1,0,0), chrome)

    scene = [cylinder,plane1,plane]
    # scene = [cylinder]
    
    # RayCast
    teste_ray = Raycasting(lights,scene, view, 250, w, h, lines, cols)
    print(view.world_to_camera)

    # OpenGL main loop
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
