from cylinder import Cylinder
from cone import Cone
from cube import Cube
from sphere import Sphere
from utils import *
import math
from material import Material
from point import Point


class Collider:
    def __init__(self) -> None:
        pass

    def collide(self, ray, objects):
        if isinstance(objects, Sphere):
            return self._collision_ray_sphere(ray, objects)
        elif isinstance(objects, Cylinder):
            return self._collision_ray_cylinder(ray, objects)
        elif isinstance(objects, Cube):
            return self._collision_ray_cube(ray, objects)
        elif isinstance(objects, Cone):
            return self._collision_ray_cone(ray, objects)
        else:
            return self._collision_ray_object(ray, objects)

    def _collision_ray_sphere(self, ray, sphere):
        v = Point.from_matrix(ray.first_point.matrix - sphere.center_camera.matrix)
        a = dot(ray.direction, ray.direction)
        b = dot(v, ray.direction)
        c = dot(v,v) - sphere.radius**2
        delta = b**2 - a * c
        if delta>0:
            t1 = (-b + math.sqrt(delta) ) / a
            t2 = (-b - math.sqrt(delta) ) / a
            p1 = Point.from_matrix(ray.first_point.matrix + t1 * ray.direction.matrix)
            p2 = Point.from_matrix(ray.first_point.matrix + t2 * ray.direction.matrix)
            if(dist_point(p1, ray.first_point) > dist_point(p2, ray.first_point)):
                p1 = p2
            #return True
            return dist_point(p1, ray.first_point),p1
        elif delta ==0:
            t1 = (-b + math.sqrt(delta) ) / a
            p1 = Point.from_matrix(ray.first_point.matrix + t1 * ray.direction.matrix)
            #return True
            return dist_point(p1, ray.first_point),p1
        else:
            return -1, Point(0,0,0)


    def _collision_ray_cylinder(self, ray, cylinder):
        pass

    def _collision_ray_cube(self, ray, object):
        pass

    def _collision_ray_cone(self, ray, object):
        pass

    def _collision_ray_object(self, ray, object):
        # Collide Ray with generic object.
        pass
