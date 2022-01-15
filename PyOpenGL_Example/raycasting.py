from random import randrange, uniform

from point import Point
from ray import Ray
from utils import *


class Raycasting:
    def __init__(self, scene, camera, dist_plane, height, width, nlines, ncols) -> None:
        self.camera = camera
        self.dist_plane = dist_plane
        self.width_frame = width/ncols
        self.height_frame = height/nlines
        self.point_init = Point(-width*0.5 + self.width_frame*0.5,
                                height*0.5 - 0.5*self.height_frame, -self.dist_plane)
        self.height = height
        self.width = width
        self.nlines = nlines
        self.ncols = ncols
        self.matrix = [[[0.5, 0.5, 0.5]
                        for a in range(nlines)] for b in range(ncols)]

    def create_matrix(self):
        for line in range(0, self.nlines):
            y = self.point_init.y - line * self.height_frame
            for col in range(0, self.ncols):
                x = self.point_init.x - line * self.width_frame
                # Create ray to Perspective
                ray = Ray(Point(0,0,0), Point(x,y,-self.dist_plane))
                print(ray.direction.matrix)
                # Calculate intersection with scene list
                # If intersection att matrix
                self.matrix[line][col] = [
                    uniform(0, 1), uniform(0, 1), uniform(0, 1)]
        return self.matrix
