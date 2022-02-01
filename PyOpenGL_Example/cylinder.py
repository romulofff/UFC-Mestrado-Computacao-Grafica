from camera import Camera
from point import Point
from utils import *
from plane import Plane


class Cylinder:
    def __init__(self, center, radius, height, u) -> None:
        self.center = center
        self.radius = radius
        self.height = height
        self.u = normalize_vector(u) 
        self.center_camera = None

    def get_center_camera(self, camera):
        self.center_camera = Point.from_matrix(
            point_matrix_mult(self.center, camera.world_to_camera))


if __name__ == '__main__':

    point_xyz = Point(0, 0, 0)
    lookat = Point(0, 0, -1)
    view_up = Point(0, 1, 0)
    view = Camera(point_xyz=point_xyz,
                  lookat=lookat, view_up=view_up)

    cylinder = Cylinder(Point(5, 5, 1), 30, 5, None)
    cylinder.get_center_camera(view)
    print(cylinder.center_camera.matrix)
