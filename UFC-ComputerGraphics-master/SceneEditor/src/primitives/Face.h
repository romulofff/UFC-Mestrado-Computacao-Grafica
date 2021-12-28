/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef FACE_H
#define FACE_H

#include "Vertex.h"
#include "Vector.h"
#include <vector>

class Face {
    public:
        // constructors and destructor
        Face();
        Face(Vertex* v1, Vertex* v2, Vertex* v3);
        Face(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4);

        virtual ~Face() {}

        // setters, all bellow automatically update center and normal
        void setVertexV1(Vertex* v1);
        void setVertexV2(Vertex* v2);
        void setVertexV3(Vertex* v3);
        void setVertexV4(Vertex* v4);

        void setVertices(Vertex* v1, Vertex* v2, Vertex* v3);
        void setVertices(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4);

        // three and four vertice respectively
        void setUVCoordinates(double u1, double v1,
                              double u2, double v2,
                              double u3, double v3);
        void setUVCoordinates(double u1, double v1,
                              double u2, double v2,
                              double u3, double v3,
                              double u4, double v4);

        // getters
        Vertex getCenter() {return center;}
        Vector getNormal() {return normal;}

        // get uv coordinates of faceNum'th vertice
        double getU(int faceNum);
        double getV(int faceNum);

        // get vertexVector
        std::vector<Vertex*>& getVertexVector() {return vertexVector;}

    protected:
        std::vector<Vertex*> vertexVector;
        Vertex center;
        Vector normal;
        double u1, u2, u3, u4, v1, v2, v3, v4; // UV coordinates for vertices

        Vector calculateNormal();
        Vertex calculateCenter();
};

#endif // FACE_H
