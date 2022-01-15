from point import Point
from utils import *

class Ray:
    def __init__(self,frist_point, last_point) -> None:
        self.frist_point = frist_point
        self.last_point = last_point
        self.direction = normalize_vector(Point.from_matrix(last_point.matrix - frist_point.matrix))


