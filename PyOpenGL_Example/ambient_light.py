class AmbientLight:
    def __init__(self, rgb) -> None:
        self.rgb = rgb

    def calculate_color(self,object_scene, collision_point, ray, normal_collide_point):

        intensity_ambient = [object_scene.material.ambient[0]*self.rgb[0],
                             object_scene.material.ambient[1]*self.rgb[1],
                             object_scene.material.ambient[2]*self.rgb[2]]

        return [intensity_ambient[0]+0+0,
                intensity_ambient[1]+0+0,
                intensity_ambient[2]+0+0]
        
