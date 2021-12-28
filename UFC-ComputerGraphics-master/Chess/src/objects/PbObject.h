// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_OBJECT_H
#define PB_OBJECT_H

#include "PbVertex.h"
#include "PbFace.h"
#include "PbMaterial.h"
#include <string>
#include <vector>
#include <list>

class PbObject {
    public:
        PbObject();
        PbObject(std::string objName);
        virtual ~PbObject();

        virtual void draw();

        void loadObject(std::string objName);

        void setId(unsigned int id) {identifier = id;}
        unsigned int getId() {return identifier;}

        void setDrawable(bool b) {drawable = b;}
        bool getDrawable() {return drawable;}

        void setPickable(bool p) {pickable = p;}
        bool getPickable() {return pickable;}

        void drawVerticesNormals(float size);

        std::vector<PbVertex>& getVertexVector() {return vertexVector;}

        PbObject& operator= (const PbObject &o);

protected:
        std::vector<PbVertex> vertexVector;
        std::vector<PbVertex> textureVertexVector;
        std::list<PbFace> faceList;

        PbMaterial *material;

        bool drawable;
        bool pickable;
        unsigned int identifier;
};

#endif // PB_OBJECT_H
