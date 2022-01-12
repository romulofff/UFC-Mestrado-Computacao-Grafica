import numpy as np

class Point:
    def __init__(self, x, y, z) -> None:
        self.x = x
        self.y = y
        self.z = z
        self.matrix = np.matrix([[self.x, self.y, self.z, 1]])
    
    