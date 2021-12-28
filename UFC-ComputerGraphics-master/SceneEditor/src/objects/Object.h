/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "Vertex.h"
#include "Face.h"
#include "Material.h"

#include <vector>
#include <list>
#include <QGLWidget>
#include <QString>
#include <QImage>
#include <QGLFunctions>
#include <stdio.h>

// this struct stores material and when it has to update OpenGL state machine's material
struct usemtl {
    std::string materialName;
    int startFace; // first face which have to be renderized with this material
};

class Object {
    public:
        // constructors and destructor
        Object();
        Object(std::string objName);
        virtual ~Object();

        virtual void draw();

        void loadObject(std::string); // load the complete object with materials and textures
        void createTexture(std::string);

        // setters
        void setDrawable(bool b) {drawable = b;}
        void setPickable(bool p) {pickable = p;}
        void setObjDirectory(std::string);

        // gettes
        bool getDrawable() {return drawable;}
        bool getPickable() {return pickable;}
        std::string getObjDirectory(){return objDirectory;}

        unsigned int getId() {return identifier;}
        std::string getName() {return name;}

        // draw vertices normals in opposite to faces normals
        void drawVerticesNormals();

        // transformation setters
        void setTranslate_x(float t_x) {translate_x = t_x;}
        void setTranslate_y(float t_y) {translate_y = t_y;}
        void setTranslate_z(float t_z) {translate_z = t_z;}

        void setScale_x(float s_x) {scale_x = s_x;}
        void setScale_y(float s_y) {scale_y = s_y;}
        void setScale_z(float s_z) {scale_z = s_z;}

        void setRotateAngleAxis_x(float a_x) {rotateAngle_x = a_x;}
        void setRotateAngleAxis_y(float a_y) {rotateAngle_y = a_y;}
        void setRotateAngleAxis_z(float a_z) {rotateAngle_z = a_z;}

        // transformation getters
        float getTranslate_x() {return translate_x;}
        float getTranslate_y() {return translate_y;}
        float getTranslate_z() {return translate_z;}

        float getScale_x() {return scale_x;}
        float getScale_y() {return scale_y;}
        float getScale_z() {return scale_z;}

        float getRotateAngleAxis_x() {return rotateAngle_x;}
        float getRotateAngleAxis_y() {return rotateAngle_y;}
        float getRotateAngleAxis_z() {return rotateAngle_z;}

        // operator =
        Object& operator= (const Object &o);

protected:
        std::vector<Vertex> vertexVector;
        std::vector<Vertex> textureVertexVector;
        std::vector<Material> materialVector;
        std::vector<usemtl> usemtlVector;
        std::list<Face> faceList;

        QImage texture;
        GLuint texHandle;
        Material *material;
        int vtCount, vnCount; // vt = vertex texture, vn = vertex normal

        std::string name;
        std::string materialFileName;
        std::string objDirectory;

        bool drawable;
        bool pickable;
        unsigned int identifier; // unique object id
        static unsigned int latestId; // starts 0

        // transformation variables
        float translate_x, translate_y, translate_z;
        float scale_x, scale_y, scale_z;
        float rotateAngle_x, rotateAngle_y, rotateAngle_z;

        // load material
        void loadMTL(std::string);

private:
        std::vector<int> splitFaceV(std::string);
        std::string IsTimeToChangeMaterial(int currFace); // analyses if currFace is starting face of any material
        unsigned materialNum(std::string materialName); // look for material number with materialname
};

#endif // OBJECT_H
