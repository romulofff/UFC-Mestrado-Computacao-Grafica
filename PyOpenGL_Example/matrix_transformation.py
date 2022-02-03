import numpy as np
import math

from utils import *

def translate_vector(x,y,z, point):
    matrix = np.matrix([
                        [1,0,0,x],
                        [0,1,0,y],
                        [0,0,1,z],
                        [0,0,0,1]
                       ])
    return Point.from_matrix(point_matrix_mult(point, matrix))


# def scale_object(x,y,z, object):
#     x_aux = object.center.x*-1
#     y_aux = object.center.y*-1
#     z_aux = object.center.z*-1
#     #object.center = translate_object(x_aux, y_aux, z_aux, object)
#     matrix = np.matrix([
#                         [x,0,0,0],
#                         [0,y,0,0],
#                         [0,0,z,0],
#                         [0,0,0,1]
#                        ])
#     scale =  Point.from_matrix(point_matrix_mult(object.center, matrix))
#     return scale

#     x_aux = x_aux*-1
#     y_aux = y_aux*-1
#     z_aux = z_aux*-1

#     return Point(scale.x + x_aux, scale.y+y_aux, scale.z+z_aux )

def rotate_vector(point, angle, axis):

    angle = math.radians(angle)
    
    cos = math.degrees(math.cos(angle))
    sen = math.degrees(math.sin(angle))
    if axis == 'z':
        matrix = np.matrix([[cos, -sen, 0, 0],
                            [sen,  cos, 0, 0],
                            [0,      0, 1, 0],
                            [0,      0, 0, 1]
                            ])
    elif axis == 'y':
        matrix = np.matrix([[ cos, 0, sen, 0],
                            [   0, 1,   0, 0],
                            [-sen, 0, cos, 0],
                            [   0, 0,   0, 1]
                            ])
    elif axis == 'x':
        matrix = np.matrix([[1,   0,    0, 0],
                            [0, cos, -sen, 0],
                            [0, sen,  cos, 0],
                            [0,   0,    0, 1]
                            ])

    return Point.from_matrix(point_matrix_mult(point, matrix))