from camera import Camera
from point import Point
from utils import *


class Cone:
    def __init__(self, P, vertex, n, theta, height, radius, center=None) -> None:
        self.P = P
        self.vertex = vertex
        self.n = n
        self.theta = theta
        self.height = height
        self.radius = radius
        if center:
            self.vertex = center + height*n
        if 0 > dot((self.vertex - self.P), n) > self.height:
            raise Exception("Invalid Cone data.")

    def get_center_camera(self, camera):
        self.center_camera = Point.from_matrix(
            point_matrix_mult(self.center, camera.world_to_camera))


if __name__ == '__main__':

    point_xyz = Point(0, 0, 0)
    lookat = Point(0, 0, -1)
    view_up = Point(0, 1, 0)
    view = Camera(point_xyz=point_xyz,
                  lookat=lookat, view_up=view_up)

    cone = Cone(Point(5, 5, 1), 30, 5, None)
    cone.get_center_camera(view)
    print(cone.center_camera.matrix)
