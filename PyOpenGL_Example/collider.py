from cilinder import Cilinder
from cone import Cone
from cube import Cube
from sphere import Sphere
from utils import *


class Collider:
    def __init__(self) -> None:
        pass

    def collide(self, ray, objects):
        for object in objects:
            if isinstance(object, Sphere):
                return self._collision_ray_sphere(ray, object)
            elif isinstance(object, Cilinder):
                return self._collision_ray_cilinder(ray, object)
            elif isinstance(object, Cube):
                return self._collision_ray_cube(ray, object)
            elif isinstance(object, Cone):
                return self._collision_ray_cone(ray, object)
            else:
                return self._collision_ray_object(ray, object)

    def _collision_ray_sphere(self, ray, sphere):
        v = Point.from_matrix(ray.first_point.matrix -
                              sphere.center_camera.matrix)
        a = ray.measure**2 * dot(ray.direction, ray.direction)
        b = ray.measure * dot(ray.direction, v)
        c = dot(v, v) - sphere.radius**2
        delta = 4*b**2 - 4*a*c
        if delta >= 0:
            return True
        if delta < 0:
            return False

    def _collision_ray_cilinder(self, ray, object):
        pass

    def _collision_ray_cube(self, ray, object):
        pass

    def _collision_ray_cone(self, ray, object):
        pass

    def _collision_ray_object(self, ray, object):
        # Collide Ray with generic object.
        pass