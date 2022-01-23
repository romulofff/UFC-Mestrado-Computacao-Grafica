class AmbientLight:
    def __init__(self, rgb) -> None:
        self.rgb = rgb

    def calculate_color(self,material):
        intensity = [material.ambient[0]*self.rgb[0],material.ambient[1]*self.rgb[1],material.ambient[2]*self.rgb[2]]
        return intensity
        
