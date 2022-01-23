from utils import *

class PointLight:
    def __init__(self, point,rgb) -> None:
        self.point = point
        self.rgb = rgb

    def calculate_color(self,object_scene, collision_point):
        intensity_ambient = [object_scene.material.ambient[0]*self.rgb[0],object_scene.material.ambient[1]*self.rgb[1],object_scene.material.ambient[2]*self.rgb[2]]
        intensity_difuse = self.calculate_difuse(object_scene, collision_point)

        return [intensity_ambient[0]+intensity_difuse[0],intensity_ambient[1]+intensity_difuse[1],intensity_ambient[2]+intensity_difuse[2]]

    def calculate_difuse(self,object_scene, collision_point):
        n = self.calculate_normal_sphere(object_scene, collision_point)
        l = self.calculate_L(object_scene, collision_point)
        cross = dot(n,l)
        intensity = [object_scene.material.difuse[0]*self.rgb[0]*cross,
                     object_scene.material.difuse[1]*self.rgb[1]*cross,
                     object_scene.material.difuse[2]*self.rgb[2]*cross]
        return intensity

    def calculate_normal_sphere(self,sphere, collision_point):
        return Point.from_matrix((collision_point.matrix - sphere.center.matrix) / sphere.radius)

    def calculate_L(self,sphere, collision_point):
        return normalize_vector(Point.from_matrix(self.point.matrix - collision_point.matrix))
    



        
