from collider import Collider
from point import Point
from ray import Ray
from utils import *


class Raycasting:
    def __init__(self, lights, scene, camera, dist_plane, height, width, nlines, ncols) -> None:
        self.lights = lights
        self.camera = camera
        self.scene = scene
        self.dist_plane = dist_plane
        self.width_frame = width/ncols
        self.height_frame = height/nlines
        self.point_init = Point(-width*0.5 + self.width_frame*0.5,
                                height*0.5 - 0.5*self.height_frame, -self.dist_plane)
        self.height = height
        self.width = width
        self.nlines = nlines
        self.ncols = ncols
        self.matrix = [[[0.0, 0.0, 0.0]
                        for a in range(nlines)] for b in range(ncols)]
        self.collider = Collider()

    def create_matrix(self):
        for line in range(0, self.nlines):
            y = self.point_init.y - line * self.height_frame
            for col in range(0, self.ncols):
                x = self.point_init.x + col * self.width_frame
                # Create ray to Perspective
                ray = Ray(Point(0, 0, 0), Point(x, y, -self.dist_plane), 6)
                #ray = Ray(self.camera.point_xyz, Point(x, y, -self.dist_plane), 6)
                # Calculate intersection with scene list
                # for objects in self.scene:
                #     if(self.collider.collide(ray, objects)):
                #         self.matrix[line][col] = [1.0, 1.0, 1.0]
                #         break
                current_dist = 7879878978979
                for objects in self.scene:
                    dist_object,collision_point, normal_collide_point= self.collider.collide(ray, objects)
                    if (dist_object < current_dist and dist_object >= 0):
                        current_dist = dist_object
                        color = [0,0,0]
                        for light in self.lights:
                            light_color = light.calculate_color(objects,collision_point, ray,normal_collide_point)
                            color = [color[0] + light_color[0], color[1] + light_color[1], color[2] + light_color[2]]
                            #self.matrix[line][col] = light.calculate_color(objects,collision_point, ray)
                            self.matrix[line][col] = color
        print("finish")
        return self.matrix
