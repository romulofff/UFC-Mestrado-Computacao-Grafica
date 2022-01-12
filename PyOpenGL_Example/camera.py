import numpy as np

from utils import *

class Camera:
    def __init__(self, point_xyz, lookat, view_up):
        self.point_xyz = point_xyz
        self.vector_k = self.origin_cordinates_k(point_xyz, lookat)
        self.vector_i = self.origin_cordinates_i(point_xyz, view_up)
        self.vector_j = normalize_vector(
            cross_product(self.vector_k, self.vector_i))
        self.world_to_camera = np.matrix([[self.vector_i[0, 0], self.vector_i[0, 1], self.vector_i[0, 2], -(dot(self.vector_i, self.point_xyz))],
                                         [self.vector_j[0, 0], self.vector_j[0, 1],
                                             self.vector_j[0, 2], -(dot(self.vector_j, self.point_xyz))],
                                         [self.vector_k[0, 0], self.vector_k[0, 1],
                                             self.vector_k[0, 2], -(dot(self.vector_k, self.point_xyz))],
                                         [0, 0, 0, 1]]
                                         )

    def origin_cordinates_k(self, point_xyz, lookat):
        vector_k = point_xyz - lookat
        vector_k = normalize_vector(vector_k)
        return vector_k

    def origin_cordinates_i(self, point_xyz, view_up):
        v_up = view_up - point_xyz
        vector_i = cross_product(v_up, self.vector_k)
        vector_i = normalize_vector(vector_i)
        return vector_i