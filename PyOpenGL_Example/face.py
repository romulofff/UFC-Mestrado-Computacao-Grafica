import numpy as np

from plane import Plane
from point import Point
from utils import cross_product


class Face:
    def __init__(self, p1: Point, p2: Point, p3: Point):
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
        e1 = Point.from_matrix(self.p2.matrix - self.p1.matrix)
        e2 = Point.from_matrix(self.p3.matrix - self.p1.matrix)
        self.normal = cross_product(e1, e2)
        self.n = normalize_vector(self.normal)
        self.plane = Plane(self.p1, self.normal)

    def collide_ray(self, ray):
        print("COLLIDING RAYS")
        eq = ray.first_point.matrix - self.p1.matrix
        eq = dot(eq, self.n)

        if eq != 0:
            return False

        vec = Point.from_matrix(self.point.matrix - ray.first_point.matrix)
        product0 = dot(vec, self.normal)
        product1 = dot(ray.direction, self.normal)

        if(product1 == 0):
            return None

        t_int = product0/product1

        p_int = Point.from_matrix(
            ray.first_point.matrix + t_int * ray.direction.matrix)
        
        return self._validate(p_int)

    def _validate(self, p_int):
        A_ksi = cross_product((self.p1.matrix - p_int.matrix),
                              (self.p2.matrix - p_int.matrix))
        A_ksi = dot(A_ksi.matrix, self.n)

        if A_ksi < 0:
            return False

        A_eta = cross_product((self.p2.matrix - p_int.matrix),
                              (self.p3.matrix - p_int.matrix))
        A_eta = dot(A_eta.matrix, self.n)

        if A_eta < 0:
            return False

        A_zeta = cross_product(
            (self.p3.matrix - p_int.matrix), (self.p1.matrix - p_int.matrix))
        A_zeta = dot(A_zeta.matrix, self.n)

        if A_zeta < 0:
            return False
        else:
            return True
