import math
from random import randrange, uniform

import numpy as np
import OpenGL
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from cluster_aabb import Cluster_AABB
from cluster_sphere import ClusterSphere
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
from matrix_transformation import *
from obj_reader import *


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


    w, h, lines, cols = 800, 800, 200, 200


    point_xyz = Point(-2, -2, 5)
    lookat = Point(0, 0, -0)
    view_up = Point(0, 1.0, 0.0)

    point_xyz1 = Point(0, 80, -50)
    lookat1 = Point(0, 1, -50)
    view_up1 = Point(0, 1.0, 0.1)

    view = Camera(point_xyz=point_xyz,
                  lookat=lookat, view_up=view_up)

    
    # Materials
    bronze = Material([0.2125, 0.1275, 0.054],[0.714, 0.4284, 0.18144],[0.393548, 0.271906, 0.166721],10)
    obsidian = Material([0.05375, 0.05, 0.06625],[0.18275, 0.17, 0.22525],[0.332741, 0.328634, 0.346435], 0)
    chrome = Material([0.25, 0.25, 0.25],[0.4, 0.4, 0.4],[0.774597, 0.774597, 0.774597],0)
    teste = Material([0.1, 0.1, 0.1],[0.1, 0.1, 0.1],[0.1, 0.1, 0.1],0)
    gold = Material([0.24725, 0.1995, 0.0745],[0.75164, 0.60648, 0.22648],[0.628281, 0.555802, 0.366065],8)
    silver = Material([0.19225, 0.19225, 0.19225], [0.50754, 0.50754, 0.50754], [0.508273, 0.508273, 0.508273], 0)
    ruby = Material([0.1745, 0.01175, 0.01175], [0.61424, 0.04136, 0.04136], [0.727811, 0.626959, 0.626959], 1)
    emerald = Material([0.0215, 0.1745, 0.0215], [0.07568, 0.61424, 0.07568], [0.633, 0.727811, 0.633], 0.6)
    brass = Material([0.329412, 0.223529, 0.027451], [0.780392, 0.568627, 0.113725], [0.992157, 0.941176, 0.807843], 0.21794872)
    red_rubber = Material([0.05, 0.0, 0.0], [0.5, 0.4, 0.4], [0.7, 0.04, 0.04], .078125)
    black_rubber = Material([0.02, 0.02, 0.02], [0.01, 0.01, 0.01], [0.4, 0.4, 0.4], .078125)
    yellow_rubber = Material([0.05, 0.05, 0.0], [0.0, 0.5, 0.4], [0.7, 0.07, 0.04], .078125)
    white_rubber = Material([0.05, 0.05, 0.05], [0.5, 0.5, 0.5], [0.7, 0.07, 0.07], .078125)
    green_rubber = Material([0.0,	0.05,	0.0],	[0.4,	0.5,	0.4],	[0.04,	0.7,	0.04],	0.078125)
    turquoise = Material([0.1, 0.18725, 0.1745], [0.396, 0.74151, 0.69102],  [0.297254, 0.30829, 0.306678], 0.1)
    cyan_plastic = Material([0.0,0.1,0.06],	[0.0,0.50980392,0.50980392],[0.50196078,0.50196078,0.50196078],	0.25)
    green_plastic =	Material([0.0, 0.0, 0.0], [0.1, 0.35, 0.1],	[0.45, 0.55, 0.45],	0.25)
    red_plastic	= Material([0.0,0.0,0.0],	[0.5,0.0,0.0],	[0.7,0.6,0.6],	0.25)

    # Lights
    light_ambient = AmbientLight([0.0,0.0,0.8])

    point_light = PointLight(Point(-120.0,120.0,0.0), [0.3,0.3,0.3])
    point_light.get_point_camera(view)

    point_light1 = PointLight(Point(120.0,120.0,-50.0), [0.3,0.3,0.3])
    point_light1.get_point_camera(view)

    point_light2 = PointLight(Point(25.0,0.0,-30.0), [0.9,0.9,0.9])
    point_light2.get_point_camera(view)

    directional_point_light = DirectionalPointLight(Point(0,0,0), [0.3,0.3,0.3], Point(0.0,0.0,-1.0))
    directional_point_light.get_point_camera(view)

    spot_light = SpotLight(Point(-15.0,-10.0,-90.0), [1.0,1.0,0.0], Point(0.0,1.0, 0.0), 50)
    spot_light.get_point_camera(view)

    lights = [light_ambient,point_light, point_light1, point_light2, directional_point_light]

    # Objects 
    cylinder = Cylinder(Point(30, 15, -50), 10, 15, Point(0.0, 1.0, 1.0), bronze)
    cylinder.get_center_camera(view)
    print(cylinder.center_camera.matrix)
    
    sphere = Sphere(Point(-15.0, 15.0, -50.0), 12, bronze)
    sphere.get_center_camera(view)
    # print(sphere.center_camera.matrix)
    
    # sphere1 = Sphere(Point(0.0, 10.0, -60), 9, ruby)
    # sphere1.get_center_camera(view)
    
    # cone = Cone(Point(0, 0, -50), 9, 18, Point(0.0, 1.0, 0.0), silver)
    # cone.get_center_camera(view)
    # print(cone.center_camera.matrix)
    # cone1 = Cone(Point(-25, 0, -50), 9, 18, Point(0.0, 1.0, 0.7), bronze)
    # cone1.get_center_camera(view)
    cone2 = Cone(Point(25, 0, -50), 9, 18, Point(0.0, 1.0, -0.7), bronze)
    cone2.get_center_camera(view)

    plane = Plane(Point(0,-370,-50), Point(0,1,0.0),silver)
    plane1 = Plane(Point(-370,0,-50), Point(1,0,0.0),chrome)
    plane2 = Plane(Point(370,0,-50), Point(-1,0,0.0),ruby)
    plane3 = Plane(Point(0,0,-450), Point(0,0,-1.0),obsidian)

    test_object = read_faces_from_obj('obj/1face.obj', bronze)
    for obj in test_object:
        obj.get_center_camera(view)
        print(obj.center_camera.matrix)
    # scene = [sphere1]
    # scene = [cone, cone1, cone2]
    objects_scene = [sphere]

    cluster1 = ClusterSphere(Point(30.0, 30.0, -50.0),25, [cone2, cylinder])
    cluster1.get_center_camera(view)

    cluster = ClusterSphere(Point(-15.0, 15.0, -50.0),15, objects_scene)
    cluster.get_center_camera(view)

    scene = [cluster, cluster1]
    # scene = [cylinder]

    # RayCast
    teste_ray = Raycasting(lights,scene, view, w/2, w, h, lines, cols,'perspective')

    # print(view.world_to_camera)

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
