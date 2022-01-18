from point import Point
from utils import *


class Ray:
    def __init__(self, first_point, last_point, measure) -> None:
        self.first_point = first_point
        self.last_point = last_point
        self.direction = normalize_vector(
            Point.from_matrix(last_point.matrix - first_point.matrix))
        #self.direction_measure = Point.from_matrix(self.direction.matrix * measure)
        self.measure = measure
