from point import Point
from face import Face

def read_vertices_from_obj(objPath):
    points = []
    with open(objPath, 'r') as f:
        for line in f:
            try:
                line = line.replace('v', '')
            except:
                #                 print("Problema na linha")
                continue
            line_ = line.split()
            try:
                points.append(
                    Point(float(line_[0]), float(line_[1]), float(line_[2])))
            except:
                #                 print("Problema no ponto")
                continue
    return points


def read_faces_from_obj(objPath, material):
    vertices = read_vertices_from_obj(objPath)
    # print(vertices)
    faces = []
    with open(objPath, 'r') as f:
        for line in f:
            try:
                line = line.replace('f', '')
            except:
                continue
            line_ = line.split()
            try:
                new_face = Face(
                    vertices[int(line_[0])-1], vertices[int(line_[1])-1], vertices[int(line_[2])-1], material)
                faces.append(new_face)
            except ValueError as e:
                # print(e)
                continue
    # print("FACES:", faces)
    if len(faces) > 0:
        print("Faces reading complete. Total number of faces: {}".format(len(faces)))
    return faces
