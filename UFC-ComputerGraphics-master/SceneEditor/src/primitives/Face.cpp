/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "Face.h"
#include "AffineSpace.h"

Face :: Face()
{
    vertexVector.push_back( new Vertex(0.0, 0.0, 0.0) );
    vertexVector.push_back( new Vertex(1.0, 0.0, 0.0) );
    vertexVector.push_back( new Vertex(0.0, 1.0, 0.0) );

    normal.set_xyz(0.0, 0.0, 1.0);
    center = calculateCenter();
}

Face :: Face(Vertex* v1, Vertex* v2, Vertex* v3)
{
    vertexVector.push_back(v1);
    vertexVector.push_back(v2);
    vertexVector.push_back(v3);

    normal = calculateNormal();
    center = calculateCenter();
}

Face :: Face(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4)
{
    vertexVector.push_back(v1);
    vertexVector.push_back(v2);
    vertexVector.push_back(v3);
    vertexVector.push_back(v4);

    normal = calculateNormal();
    center = calculateCenter();
}

void Face :: setVertexV1(Vertex* v1)
{
    vertexVector[0] = v1;
    normal = calculateNormal();
    center = calculateCenter();
}

void Face :: setVertexV2(Vertex* v2)
{
    vertexVector[1] = v2;
    normal = calculateNormal();
    center = calculateCenter();
}

void Face :: setVertexV3(Vertex* v3)
{
    vertexVector[2] = v3;
    normal = calculateNormal();
    center = calculateCenter();
}

void Face :: setVertexV4(Vertex* v4)
{
    vertexVector[3] = v4;
    normal = calculateNormal();
    center = calculateCenter();
}

void Face :: setVertices(Vertex* v1, Vertex* v2, Vertex* v3)
{
    vertexVector[0] = v1;
    vertexVector[1] = v2;
    vertexVector[2] = v3;

    normal = calculateNormal();
    center = calculateCenter();
}

void Face :: setVertices(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4)
{
    vertexVector[0] = v1;
    vertexVector[1] = v2;
    vertexVector[2] = v3;
    vertexVector[3] = v4;

    normal = calculateNormal();
    center = calculateCenter();
}

double Face :: getU(int faceNum)
{
    if (faceNum == 0)
        return u1;
    if (faceNum == 1)
        return u2;
    if (faceNum == 2)
        return u3;
    return u4;
}

double Face :: getV(int faceNum)
{
    if (faceNum == 0)
        return v1;
    if (faceNum == 1)
        return v2;
    if (faceNum == 2)
        return v3;
    return v4;
}

void Face :: setUVCoordinates(double u1, double v1, double u2, double v2, double u3, double v3)
{
    this->u1 = u1;
    this->u2 = u2;
    this->u3 = u3;

    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

void Face :: setUVCoordinates(double u1, double v1, double u2, double v2, double u3, double v3, double u4, double v4)
{
    this->u1 = u1;
    this->u2 = u2;
    this->u3 = u3;
    this->u4 = u4;

    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->v4 = v4;
}

Vector Face :: calculateNormal()
{
    Vector i, j, n;

    Vertex v1 = *(vertexVector[0]);
    Vertex v2 = *(vertexVector[1]);
    Vertex v3 = *(vertexVector[2]);

    i = pointsSubtraction(v2, v1);
    i.normalize();

    j = pointsSubtraction(v3, v1);
    j.normalize();

    n = crossProduct(i, j);

    return n;
}

Vertex Face :: calculateCenter()
{
    Vertex v1 = *(vertexVector[0]);
    Vertex v2 = *(vertexVector[1]);
    Vertex v3 = *(vertexVector[2]);

    double aux_x = (v1.get_x() + v2.get_x() + v3.get_x()) / 3.0;
    double aux_y = (v1.get_y() + v2.get_y() + v3.get_y()) / 3.0;
    double aux_z = (v1.get_z() + v2.get_z() + v3.get_z()) / 3.0;

    Vertex center(aux_x, aux_y, aux_z);

    return center;
}
