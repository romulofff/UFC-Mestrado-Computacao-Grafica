from collider import Collider
from point import Point
from ray import Ray
from utils import *
from cluster_aabb import Cluster_AABB
from cluster_sphere import ClusterSphere


class Raycasting:
    def __init__(self, lights, scene, camera, dist_plane, height, width, nlines, ncols, projection) -> None:
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
        self.projection = projection

    def create_matrix(self):
        for line in range(0, self.nlines):
            y = self.point_init.y - line * self.height_frame
            for col in range(0, self.ncols):
                x = self.point_init.x + col * self.width_frame
                # Create ray to Perspective
                ray = Ray(Point(0, 0, 0), Point(
                    x, y, -self.dist_plane), self.projection, self.camera, alpha=45)
                # Calculate intersection with scene list
                # for objects in self.scene:
                #     if isinstance(objects, list):
                #         for obj in objects:
                #             # print(obj)
                #             if(self.collider.collide(ray, obj)):
                #                 self.matrix[line][col] = [1.0, 1.0, 1.0]
                #                 break

                #     elif(self.collider.collide(ray, objects)):
                #         self.matrix[line][col] = [1.0, 1.0, 1.0]
                #         break
                current_dist = 7879878978979
                for objects in self.scene:
                    if isinstance(objects, list):
                        for obj in objects:
                            dist_object, collision_point, normal_collide_point = self.collider.collide(
                                ray, obj)
                            if (dist_object < current_dist and dist_object >= 0):
                                current_dist = dist_object
                                color = [0, 0, 0]
                                for light in self.lights:
                                    light_color = light.calculate_color(
                                        obj, collision_point, ray, normal_collide_point)
                                    color = [
                                        color[0] + light_color[0], color[1] + light_color[1], color[2] + light_color[2]]
                                    #self.matrix[line][col] = light.calculate_color(objects,collision_point, ray)
                                    self.matrix[line][col] = color
                    elif isinstance(objects, ClusterSphere):
                        if objects.collision_ray(ray):
                            for teste in objects.list_objects:
                                dist_object, collision_point, normal_collide_point = self.collider.collide(ray, teste)
                                if (dist_object < current_dist and dist_object >= 0 and dist_object < 500):
                                # if (dist_object < current_dist and dist_object >= 0):
                                    current_dist = dist_object
                                    color = [0, 0, 0]
                                    for light in self.lights:
                                        light_color = light.calculate_color(
                                            teste, collision_point, ray, normal_collide_point)
                                        color = [color[0] + light_color[0], color[1] + light_color[1], color[2] + light_color[2]]
                                        self.matrix[line][col] = color
                    # else:
                    #     dist_object, collision_point, normal_collide_point = self.collider.collide(ray, objects)
                    #     if (dist_object < current_dist and dist_object >= 0):
                    #         current_dist = dist_object
                    #         color = [0, 0, 0]
                    #         for light in self.lights:
                    #             light_color = light.calculate_color(
                    #                 objects, collision_point, ray, normal_collide_point)
                    #             color = [color[0] + light_color[0], color[1] + light_color[1], color[2] + light_color[2]]
                    #             self.matrix[line][col] = color

        print("finish")
        return self.matrix
