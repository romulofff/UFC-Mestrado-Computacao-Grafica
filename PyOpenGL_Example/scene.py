import math
from random import choice, randint, random, randrange, uniform

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
    draw_scene(w, h, lines, cols, raycasting.create_matrix())
    glutSwapBuffers()

def choose_material():
    material = choice(materials)
    return material

def random_point():
    return Point(random(), random(), random())

if __name__ == '__main__':
    w, h, lines, cols = 600, 600, 400, 400

    point_xyz = Point(0, 0, 250)
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
    green_plastic = Material([0.0, 0.0, 0.0], [0.1, 0.35, 0.1],	[0.45, 0.55, 0.45],	0.25)
    red_plastic	= Material([0.0,0.0,0.0],	[0.5,0.0,0.0],	[0.7,0.6,0.6],	0.25)
    materials = [bronze, obsidian, chrome, teste, gold, silver, ruby, emerald, brass, red_rubber, black_rubber, yellow_rubber, white_rubber, green_rubber, turquoise, cyan_plastic, green_plastic, red_plastic]
    
    # Lights
    light_ambient1 = AmbientLight([1.0,1.0,1.0])
    spot_light = SpotLight(Point(-15.0,-10.0,-90.0), [1.0,1.0,1.0], Point(-1.0, 0.0, 0.0), 180)
    spot_light.get_point_camera(view)
    lights = [light_ambient1, spot_light]
                    
    #Objects
    #Objects_Cluster1
    sphere1 = Sphere(Point(-150.0, 150.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Cylinder(Point(-120.0, 150.0, -100.0), 10, 15, random_point(), choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Cylinder(Point(-90.0, 150.0, -100.0), 10, 5, random_point(), choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Cone(Point(-150.0, 120.0, -100.0), 10, randint(5, 15), random_point(), choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-120.0, 120.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Cone(Point(-90.0, 120.0, -100.0), 10, randint(5, 15), random_point(), choose_material())
    sphere6.get_center_camera(view)
    objects_cluster1 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]


    #Objects_Cluster2
    sphere1 = Sphere(Point(-150.0, 80.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-120.0, 80.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(-90.0, 80.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-150.0, 50.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-120.0, 50.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(-90.0, 50.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster2 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]

    #Objects_Cluster3
    sphere1 = Sphere(Point(-150.0, 10.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-120.0, 10.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(-90.0, 10.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-150.0, -20.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-120.0, -20.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(-90.0, -20.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster3 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]

    #Objects_Cluster4
    sphere1 = Sphere(Point(-150.0, -60.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-120.0, -60.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(-90.0, -60.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-150.0, -90.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-120.0, -90.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(-90.0, -90.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster4 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]

    #Objects_Cluster5
    sphere1 = Sphere(Point(-150.0, -130.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-120.0, -130.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(-90.0, -130.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-150.0, -160.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-120.0, -160.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(-90.0, -160.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster5 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]

        #Objects_Cluster6
    sphere1 = Sphere(Point(-60.0, 150.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-30.0, 150.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(00.0, 150.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-60.0, 120.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-30.0, 120.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(0.0, 120.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster6 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]


    #Objects_Cluster7
    sphere1 = Sphere(Point(-60.0, 80.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-30.0, 80.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(0.0, 80.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-60.0, 50.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-30.0, 50.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(0.0, 50.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster7 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]

    #Objects_Cluster8
    sphere1 = Sphere(Point(-60.0, 10.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-30.0, 10.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(0.0, 10.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-60.0, -20.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-30.0, -20.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(0.0, -20.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster8 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]

    #Objects_Cluster9
    sphere1 = Sphere(Point(-60.0, -60.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-30.0, -60.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(-0.0, -60.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-60.0, -90.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-30.0, -90.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(0.0, -90.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster9 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]

    #Objects_Cluster10
    sphere1 = Sphere(Point(-60.0, -130.0, -100.0), 10, choose_material())
    sphere1.get_center_camera(view)
    sphere2 = Sphere(Point(-30.0, -130.0, -100.0), 10, choose_material())
    sphere2.get_center_camera(view)
    sphere3 = Sphere(Point(0.0, -130.0, -100.0), 10, choose_material())
    sphere3.get_center_camera(view)
    sphere4 = Sphere(Point(-60.0, -160.0, -100.0), 10, choose_material())
    sphere4.get_center_camera(view)
    sphere5 = Sphere(Point(-30.0, -160.0, -100.0), 10, choose_material())
    sphere5.get_center_camera(view)
    sphere6 = Sphere(Point(0.0, -160.0, -100.0), 10, choose_material())
    sphere6.get_center_camera(view)
    objects_cluster10 = [sphere1, sphere2, sphere3,sphere4, sphere5, sphere6]


    # Clusters
    cluster1 = ClusterSphere(Point(-120.0, 120.0, -100.0),50, objects_cluster1)
    cluster1.get_center_camera(view)

    cluster2 = ClusterSphere(Point(-120.0, 50.0, -100.0),50, objects_cluster2)
    cluster2.get_center_camera(view)

    cluster3 = ClusterSphere(Point(-120.0, -20.0, -100.0),50, objects_cluster3)
    cluster3.get_center_camera(view)

    cluster4 = ClusterSphere(Point(-120.0, -90.0, -100.0),50, objects_cluster4)
    cluster4.get_center_camera(view)

    cluster5 = ClusterSphere(Point(-120.0, -160.0, -100.0),50, objects_cluster5)
    cluster5.get_center_camera(view)

    cluster6 = ClusterSphere(Point(-30.0, 120.0, -100.0),50, objects_cluster6)
    cluster6.get_center_camera(view)

    cluster7 = ClusterSphere(Point(-30.0, 50.0, -100.0),50, objects_cluster7)
    cluster7.get_center_camera(view)

    cluster8 = ClusterSphere(Point(-30.0, -20.0, -100.0),50, objects_cluster8)
    cluster8.get_center_camera(view)

    cluster9 = ClusterSphere(Point(-30.0, -90.0, -100.0),50, objects_cluster9)
    cluster9.get_center_camera(view)

    cluster10 = ClusterSphere(Point(-30.0, -160.0, -100.0),50, objects_cluster10)
    cluster10.get_center_camera(view)




    # Scene
    scene = [cluster1, cluster2, cluster3, cluster4, cluster5, cluster6, cluster7, cluster8, cluster9, cluster10]
    # print(scene)
    raycasting = Raycasting(lights,scene, view, w, w, h, lines, cols,'perspective')

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
