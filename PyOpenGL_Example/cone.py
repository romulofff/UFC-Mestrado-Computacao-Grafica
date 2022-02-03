from camera import Camera
from plane import Plane
from point import Point
from utils import *


class Cone:
    def __init__(self, center, radius, height, n, material, vertex=None) -> None:
        self.vertex = vertex
        self.n = normalize_vector(n)
        self.height = height
        self.radius = radius
        self.center = center
        self.material = material
        self.base = Plane(self.center, self.n)

    def get_center_camera(self, camera):
        self.center_camera = Point.from_matrix(
            point_matrix_mult(self.center, camera.world_to_camera))

    def valid_point_cone(self, vertex: Point, p_int: Point):
        v_aux = Point.from_matrix(vertex.matrix - p_int.matrix)
        escalar_aux = dot(v_aux, self.n)
        if escalar_aux < 0.00000000001 and escalar_aux > 0.00000000001:
            escalar_aux = 0
        if escalar_aux >= 0 and escalar_aux <= self.height:
            return True
        else: return False


if __name__ == '__main__':

    point_xyz = Point(0, 0, 0)
    lookat = Point(0, 0, -1)
    view_up = Point(0, 1, 0)
    view = Camera(point_xyz=point_xyz,
                  lookat=lookat, view_up=view_up)

    cone = Cone(Point(5, 5, 1), 30, 5, None)
    cone.get_center_camera(view)
    print(cone.center_camera.matrix)
