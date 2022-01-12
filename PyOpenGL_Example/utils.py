import numpy as np

def cross_product(point_a, point_b):
    x = point_a[0, 1]*point_b[0, 2] - point_a[0, 2] * point_b[0, 1]
    y = point_a[0, 2]*point_b[0, 0] - point_a[0, 0] * point_b[0, 2]
    z = point_a[0, 0]*point_b[0, 1] - point_a[0, 1] * point_b[0, 0]
    return np.matrix([x, y, z])


def normalize_vector(vector):
    norm = np.sqrt(np.square(vector).sum())
    return vector / norm


def dot(vector1, vector2):
    return vector1[0, 0] * vector2[0, 0] + vector1[0, 1] * vector2[0, 1] + vector1[0, 2] * vector2[0, 2]
