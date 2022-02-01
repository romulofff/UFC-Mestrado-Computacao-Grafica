import math

from cone import Cone
from cube import Cube
from cylinder import Cylinder
from material import Material
from plane import Plane
from point import Point
from sphere import Sphere
from utils import *


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
        v = Point.from_matrix(ray.first_point.matrix -
                              sphere.center_camera.matrix)
        a = dot(ray.direction, ray.direction)
        b = dot(v, ray.direction)
        c = dot(v, v) - sphere.radius**2
        delta = b**2 - a * c
        if delta > 0:
            t1 = (-b + math.sqrt(delta)) / a
            t2 = (-b - math.sqrt(delta)) / a
            p1 = Point.from_matrix(
                ray.first_point.matrix + t1 * ray.direction.matrix)
            p2 = Point.from_matrix(
                ray.first_point.matrix + t2 * ray.direction.matrix)
            if(dist_point(p1, ray.first_point) > dist_point(p2, ray.first_point)):
                p1 = p2
            return True
            return dist_point(p1, ray.first_point), p1
        elif delta == 0:
            t1 = (-b + math.sqrt(delta)) / a
            p1 = Point.from_matrix(
                ray.first_point.matrix + t1 * ray.direction.matrix)
            return True
            # return dist_point(p1, ray.first_point),p1
        else:
            # return -1, Point(0,0,0)
            return False

    def _collision_ray_cylinder(self, ray, cylinder):
        v_aux = Point.from_matrix(
            ray.first_point.matrix - cylinder.center_camera.matrix)
        v = Point.from_matrix(
            v_aux.matrix - dot(v_aux, cylinder.u) * cylinder.u.matrix)
        w = Point.from_matrix(
            ray.direction.matrix - dot(ray.direction, cylinder.u) * cylinder.u.matrix)

        a = dot(w, w)
        b = dot(v, w)
        c = dot(v, v) - cylinder.radius**2

        delta = b**2 - a*c

        if delta < 0:
            return None

        menor_dis = 8000000

        plane_inf = Plane(cylinder.center_camera, cylinder.u)
        norm = cylinder.height * cylinder.u.matrix
        point_sup = Point.from_matrix(norm + cylinder.center_camera.matrix)
        plane_sup = Plane(point_sup, cylinder.u)

        # Interserct base
        p_int1 = plane_inf.collide_ray(ray)
        if p_int1:
            if dist_point(p_int1, cylinder.center_camera) > cylinder.radius:
                p_int1 = None
            else:
                menor_dis = dist_point(ray.first_point, p_int1)

        # Intersect top
        p_int2 = plane_sup.collide_ray(ray)
        if p_int2 and dist_point(p_int2, point_sup) <= cylinder.radius:
            dist2 = dist_point(p_int2, ray.first_point)
            if(p_int1 == None or dist2 < menor_dis):
                p_int1 = p_int2
                menor_dis = dist2

        # Intersect side
        d1 = (-b + math.sqrt(delta))/a
        d2 = (-b - math.sqrt(delta))/a

        p_teste = Point.from_matrix(
            ray.first_point.matrix + d1 * ray.direction.matrix)
        p_teste2 = Point.from_matrix(
            ray.first_point.matrix + d2 * ray.direction.matrix)

        # if p_int1:
        #     if dist_point(p_int1, cylinder.center_camera) < cylinder.radius:
        #         return True
        # if p_int2:
        #     if dist_point(p_int2, point_sup) >= cylinder.radius:
        #         return True

        PB1 = Point.from_matrix(p_teste.matrix - cylinder.center_camera.matrix)
        PB_u1 = dot(PB1, cylinder.u)

        PB2 = Point.from_matrix(
            p_teste2.matrix - cylinder.center_camera.matrix)
        PB_u2 = dot(PB2, cylinder.u)

        if 0 <= PB_u1 and PB_u1 <= cylinder.height:
            dist1 = dist_point(p_teste, ray.first_point)
            if dist1 < menor_dis:
                p_int1 = p_teste
                menor_dis = dist1
        elif 0 <= PB_u2 and PB_u2 <= cylinder.height:
            dist2 = dist_point(p_teste2, ray.first_point)
            if dist2 < menor_dis:
                p_int1 = p_teste2

        return p_int1

    def _collision_ray_cube(self, ray, object):
        pass

    def _collision_ray_cone(self, ray, cone):
        aux = Point.from_matrix(cone.n.matrix * cone.height)
        vertex = Point(cone.center.x+aux.x, cone.center.y +
                       aux.y, cone.center.z+aux.z)

        cos_theta = cone.height / math.sqrt(cone.height**2 + cone.radius**2)
        # p_int1 = cone.base.collide_ray(ray)
        p_int1 = None
        v = Point.from_matrix(vertex.matrix - ray.first_point.matrix)
        a = dot(ray.direction, cone.n)**2 - dot(ray.direction,
                                                ray.direction)*cos_theta**2
        b = dot(v, ray.direction)*cos_theta**2 - \
            dot(v, cone.n)*dot(ray.direction, cone.n)
        c = dot(v, cone.n)**2 - dot(v, v)*cos_theta**2
        delta = b**2 - a * c

        if (delta < 0.00000000001 and delta > -0.00000000001):
            delta = 0
        if (a < 0.00000000001 and a > -0.00000000001):
            a = 0
        if (b < 0.00000000001 and b > -0.00000000001):
            b = 0
        if (c < 0.00000000001 and c > -0.00000000001):
            c = 0

        if delta > 0:
            if a != 0:
                d1 = (-b + math.sqrt(delta)) / a
                d2 = (-b - math.sqrt(delta)) / a
            else:
                d1 = -c / 2*b
                d2 = -c / 2*b

            p_teste = Point.from_matrix(
                ray.first_point.matrix + d1 * ray.direction.matrix)
            p_teste1 = Point.from_matrix(
                ray.first_point.matrix + d2 * ray.direction.matrix)

            t1 = cone.valid_point_cone(vertex, p_teste)
            t2 = cone.valid_point_cone(vertex, p_teste1)

            if t1:
                p_int1 = p_teste
            # elif VERIFICAR INTERSECAO BASE
            if p_int1:
                dist1 = dist_point(p_int1, ray.first_point)
            else:
                dist1 = 0
            if t2:
                if not p_int1 or dist_point(p_teste1, ray.first_point) < dist1:
                    p_int1 = p_teste1
            # elif VERIFICAR INTERSECAO BASE
        elif delta == 0 and (b != 0 and a != 0):
            d1 = (-b + math.sqrt(delta)) / a
            p_teste = Point.from_matrix(
                ray.first_point.matrix + d1 * ray.direction.matrix)
            t1 = cone.valid_point_cone(vertex, p_teste)

            if t1:
                p_int1 = p_teste
            # if VERIFICAR INTERSECAO BASE
        return p_int1

    def _collision_ray_object(self, ray, object):
        # Collide Ray with generic object.
        pass
