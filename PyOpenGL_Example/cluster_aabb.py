import numpy as np
from point import Point
from ray import Ray

from utils import *

class Cluster_AABB:
    def __init__(self, center, width, height, depth,list_objects=None) -> None:
        self.center = center
        self.width = width
        self.height = height
        self.depth = depth
        self.min_corner = Point(center.x - width, center.y - height, center.z - depth)
        self.max_corner = Point(center.x + width, center.y + height, center.z + depth)
        self.list_objects = list_objects
        

    def get_center_camera(self, camera):
        self.center_camera = Point.from_matrix(
            point_matrix_mult(self.center, camera.world_to_camera))
        self.min_corner_camera = Point.from_matrix(
            point_matrix_mult(self.min_corner, camera.world_to_camera))
        self.max_corner_camera = Point.from_matrix(
            point_matrix_mult(self.max_corner, camera.world_to_camera))
        print(self.min_corner_camera.matrix)
        print(self.max_corner_camera.matrix)


    def collision_ray(self,ray):
        t1 = (self.min_corner_camera.x - ray.first_point.x)* ray.direction.x
        t2 = (self.max_corner_camera.x - ray.first_point.x)* ray.direction.x

        t3 = (self.min_corner_camera.y - ray.first_point.y)* ray.direction.y
        t4 = (self.max_corner_camera.y - ray.first_point.y)* ray.direction.y

        t5 = (self.min_corner_camera.z - ray.first_point.z)* ray.direction.z
        t6 = (self.max_corner_camera.z - ray.first_point.z)* ray.direction.z

        t_min = max(max(min(t1, t2), min(t3, t4)), min(t5, t6))
        t_max = min(min(max(t1, t2), max(t3, t4)), max(t5, t6))

        if t_max < 0 or t_min > t_max:
            return False
        else:
            return True