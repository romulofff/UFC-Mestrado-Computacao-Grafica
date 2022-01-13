from random import randrange, uniform

from point import Point
from utils import *


class Raycasting:
    def __init__(self, scene, camera, direction, height, width, nlines, ncols) -> None:
        self.camera = camera
        self.width_frame = width/ncols
        self.height_frame = height/nlines
        self.point_init = Point(-width*0.5 + self.width_frame*0.5,
                                height*0.5 - 0.5*self.height_frame, -direction.matrix)
        self.direction = normalize_vector(direction)
        self.height = height
        self.width = width
        self.nlines = nlines
        self.ncols = ncols
        self.matrix = [[[0.5, 0.5, 0.5]
                        for a in range(nlines)] for b in range(ncols)]

    def create_matrix(self):
        point_ray = Point(0, 0, self.point_init.z)
        for line in range(0, self.nlines):
            point_ray.y = self.point_init.y - line * self.height_frame
            for col in range(0, self.ncols):
                point_ray.x = self.point_init.x - line * self.width_frame
                # Create ray
                # Calculate intersection with scene list
                # If intersection att matrix
                self.matrix[line][col] = [
                    uniform(0, 1), uniform(0, 1), uniform(0, 1)]
        return self.matrix
