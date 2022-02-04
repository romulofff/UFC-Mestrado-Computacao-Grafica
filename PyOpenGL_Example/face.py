import numpy as np

from plane import Plane
from point import Point
from utils import *


class Face:
    def __init__(self, p1: Point, p2: Point, p3: Point, material):
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
        e1 = Point.from_matrix(self.p2.matrix - self.p1.matrix)
        e2 = Point.from_matrix(self.p3.matrix - self.p1.matrix)
        self.normal = cross_product(e1, e2)
        self.n =normalize_vector(self.normal)
        self.plane = Plane(self.p1, self.n)
        self.material = material

    def get_center_camera(self, camera):
        center_x = self.p1.x + self.p2.x + self.p3.x / 3
        center_y = self.p1.y + self.p2.y + self.p3.y / 3
        center_z = self.p1.z + self.p2.z + self.p3.z / 3
        self.center = Point(center_x, center_y, center_z)
        self.center_camera = Point.from_matrix(
            point_matrix_mult(self.center, camera.world_to_camera))

    def collide_ray(self, ray):
        # print("COLLIDING RAYS")
        eq = Point.from_matrix(ray.first_point.matrix - self.p1.matrix)
        eq = dot(eq, self.n)

        if eq != 0:
            return -1, Point(0,0,0), Point(0,0,0)

        vec = Point.from_matrix(self.p1.matrix - ray.first_point.matrix)
        product0 = dot(vec, self.n)
        product1 = dot(ray.direction, self.n)

        if(product1 == 0):
            return -1, Point(0,0,0), Point(0,0,0)

        t_int = product0/product1

        p_int = Point.from_matrix(
            ray.first_point.matrix + t_int * ray.direction.matrix)
        
        valid_point = self._validate(p_int)
        if valid_point:
            aux = Point.from_matrix(p_int.matrix - self.center_camera.matrix)
            normal_collide_point = Point.from_matrix(aux.matrix - (dot(aux, self.n) * self.n.matrix))
            

            return dist_point(p_int, ray.last_point), p_int, normal_collide_point
        else: return -1, Point(0,0,0), Point(0,0,0)

    def _validate(self, p_int):
        A_ksi = cross_product(Point.from_matrix(self.p1.matrix - p_int.matrix),
                              Point.from_matrix(self.p2.matrix - p_int.matrix))
        A_ksi = dot(A_ksi, self.n)

        if A_ksi < 0:
            return False

        A_eta = cross_product(Point.from_matrix(self.p2.matrix - p_int.matrix),
                              Point.from_matrix(self.p3.matrix - p_int.matrix))
        A_eta = dot(A_eta, self.n)

        if A_eta < 0:
            return False

        A_zeta = cross_product(Point.from_matrix
            (self.p3.matrix - p_int.matrix), Point.from_matrix(self.p1.matrix - p_int.matrix))
        A_zeta = dot(A_zeta, self.n)

        if A_zeta < 0:
            return False
        else:
            return True
