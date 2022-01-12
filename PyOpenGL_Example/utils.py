import numpy as np

from point import Point


def cross_product(point_a, point_b):
    x = point_a.y*point_b.z - point_a.z*point_b.y
    y = point_a.z*point_b.x - point_a.x*point_b.z
    z = point_a.x*point_b.y - point_a.y*point_b.x
    return Point(x, y, z)


def normalize_vector(vector):
    norm = np.sqrt(np.square(vector).sum())
    return vector / norm


def dot(vector1, vector2):
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z


def point_matrix_mult(point: Point, matriz):
    return np.matmul(matriz, point.matrix.transpose())


if __name__ == '__main__':
    p = Point(1, 0, 1)
    matriz = np.matrix([[1, 0, 0, 0], [0, 1, 0, 0],
                       [0, 0, 1, 0], [0, 0, 0, 0]])
    res = point_matrix_mult(p, matriz)
    print(res)
