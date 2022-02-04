from point import Point
from utils import *
from camera import Camera


class Ray:
    def __init__(self, first_point, last_point, projection, camera=None) -> None:
        self.first_point = first_point
        self.last_point = last_point
        if projection ==  'perspective':
            self.direction = normalize_vector(
                Point.from_matrix(last_point.matrix - first_point.matrix))
        elif projection == 'orthographic':
            self.direction = normalize_vector(Point.from_matrix(-1*camera.vector_k.matrix))

        #self.direction_measure = Point.from_matrix(self.direction.matrix * measure)
