// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_VERTEX_H
#define PB_VERTEX_H

#include "PbPoint.h"
#include "PbVector.h"
#include <vector>

class PbVertex : public PbPoint {
    public:
        PbVertex();
        PbVertex(double x, double y, double z);

        virtual ~PbVertex() {}

        void setNormal(PbVector norm) {normal = norm;}
        void setNormal(double n_x, double n_y, double n_z);

        void incrementNormal(PbVector n);
        void incrementNormal(double n_x, double n_y, double n_z);

        PbVector getNormal() {return normal;}
        double getNormal_x() {return normal.get_x();}
        double getNormal_y() {return normal.get_y();}
        double getNormal_z() {return normal.get_z();}

        void normalize() {normal.normalize();}

private:
        std::vector<PbVertex> edgesVector;
        PbVector normal;
};

#endif // PB_VERTEX_H
