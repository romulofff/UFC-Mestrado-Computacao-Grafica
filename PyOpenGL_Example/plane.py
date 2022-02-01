import numpy as np
from utils import *


class Plane:
    def __init__(self, point, normal) -> None:
        self.point = point
        self.normal = normalize_vector(normal)
    
    def collide_ray(self, ray):
        vec = Point.from_matrix(self.point.matrix - ray.first_point.matrix)
        product0 = dot(vec,self.normal)
        product1 = dot(ray.direction, self.normal)

        if(product1 == 0):
            return None
        
        t_int = product0/product1

        return Point.from_matrix(ray.first_point.matrix + t_int * ray.direction.matrix)

