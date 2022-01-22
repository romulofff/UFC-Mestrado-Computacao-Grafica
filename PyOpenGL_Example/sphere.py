from camera import Camera
from point import Point
from utils import *
from material import Material


class Sphere:
    def __init__(self, center, radius, material) -> None:
        self.center = center
        self.radius = radius
        self.center_camera = None
        self.material = material

    def get_center_camera(self, camera):
        self.center_camera = Point.from_matrix(
            point_matrix_mult(self.center, camera.world_to_camera))


if __name__ == '__main__':

    point_xyz = Point(0, 0, 0)
    lookat = Point(0, 0, -1)
    view_up = Point(0, 1, 0)
    view = Camera(point_xyz=point_xyz,
                  lookat=lookat, view_up=view_up)

    sphere = Sphere(Point(30, 30, 10), 30)
    sphere.get_center_camera(view)
    print(sphere.center_camera.matrix)
