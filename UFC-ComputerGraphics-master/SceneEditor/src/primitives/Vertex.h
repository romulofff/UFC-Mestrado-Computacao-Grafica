/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef VERTEX_H
#define VERTEX_H

#include "Point.h"
#include "Vector.h"
#include <vector>

class Vertex : public Point {
    public:
        // constructors and destructor
        Vertex();
        Vertex(double x, double y, double z);

        virtual ~Vertex() {}

        // normal operations
        void setNormal(Vector norm) {normal = norm;}
        void setNormal(double n_x, double n_y, double n_z);

        void incrementNormal(Vector n);
        void incrementNormal(double n_x, double n_y, double n_z);

        Vector getNormal() {return normal;}
        double getNormal_x() {return normal.get_x();}
        double getNormal_y() {return normal.get_y();}
        double getNormal_z() {return normal.get_z();}

        // texture operations
        void setTextureUV(double a, double b) {u = a;v = b;}
        double getU() {return u;}
        double getV() {return v;}

        void normalize() {normal.normalize();}

    private:
        std::vector<Vertex> edgesVector;
        Vector normal;
        double u, v; // texture coordinates
};

#endif // VERTEX_H
