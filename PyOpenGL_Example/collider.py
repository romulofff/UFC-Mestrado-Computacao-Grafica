from cylinder import Cylinder
from cone import Cone
from cube import Cube
from sphere import Sphere
from utils import *
import math
from material import Material
from point import Point
from plane import Plane


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
            return True
            return dist_point(p1, ray.first_point),p1
        elif delta ==0:
            t1 = (-b + math.sqrt(delta) ) / a
            p1 = Point.from_matrix(ray.first_point.matrix + t1 * ray.direction.matrix)
            return True
            #return dist_point(p1, ray.first_point),p1
        else:
            #return -1, Point(0,0,0)
            return False


    def _collision_ray_cylinder(self, ray, cylinder):
        v_aux = Point.from_matrix(ray.first_point.matrix - cylinder.center_camera.matrix)
        v = Point.from_matrix(v_aux.matrix - dot(v_aux,cylinder.u) * cylinder.u.matrix)
        w = Point.from_matrix(ray.direction.matrix - dot(ray.direction,cylinder.u) * cylinder.u.matrix)

        a = dot(w,w)
        b = dot(v,w)
        c = dot(v,v) - cylinder.radius**2
    
        delta = b**2 - a*c

        if delta<0:
            return False

        menor_dis = 8000000

        plane_inf = Plane(cylinder.center_camera, cylinder.u)
        point_sup = Point.from_matrix(cylinder.height * cylinder.u.matrix)
        plane_sup = Plane(point_sup, cylinder.u)

        p_int1 = plane_inf.collide_ray(ray)
        p_int2 = plane_sup.collide_ray(ray)

        if p_int1:
            if dist_point(p_int1, cylinder.center_camera) < cylinder.radius:
                return True
        if p_int2:
            if dist_point(p_int2, point_sup) >= cylinder.radius:
                return True
        
        d1 = -b + math.sqrt(delta)/a
        d2 = -b - math.sqrt(delta)/a

        p_teste = Point.from_matrix(ray.first_point.matrix + d1 * ray.direction.matrix)
        p_teste2 = Point.from_matrix(ray.first_point.matrix + d2 * ray.direction.matrix)
        
        PB1 = Point.from_matrix(p_teste.matrix - cylinder.center_camera.matrix)
        PB_u1 = dot(PB1, cylinder.u)

        PB2 = Point.from_matrix(p_teste2.matrix - cylinder.center_camera.matrix)
        PB_u2 = dot(PB2, cylinder.u)


        if 0 <= PB_u1 and PB_u1 <= cylinder.height:
            return True
        elif 0 <= PB_u2 and PB_u2 <= cylinder.height:
            return True

        return False

    def _collision_ray_cube(self, ray, object):
        pass

    def _collision_ray_cone(self, ray, object):
        pass

    def _collision_ray_object(self, ray, object):
        # Collide Ray with generic object.
        pass
