// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbObject.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

#ifdef __APPLE__
    #include "gl.h"
#else
    #include "GL/gl.h"
#endif

PbObject :: PbObject()
{
    drawable = false;
    material = NULL;
}

PbObject :: PbObject(std::string objName)
{
    material = NULL;

    this->loadObject(objName);

    drawable = true;
}

PbObject :: ~PbObject()
{
    delete material;
}

void PbObject :: loadObject(std::string objName)
{
    int v1, v2, v3;
    double x, y, z;
    std::string type, trash, name;

    std::ifstream fin;
    fin.open(objName.c_str(), std::ifstream::in);

    while (fin >> type)
    {
        if (type == "v")
        {
            fin >> x >> y >> z;

            PbVertex newVertex(x, y, z);
            vertexVector.push_back(newVertex);
        }
        else if (type == "vt")
        {
            fin >> x >> y;

            PbVertex newTextureVertex(x, y, 0.0);
            textureVertexVector.push_back(newTextureVertex);
        }
        else if (type == "f")
        {
            fin >> v1 >> v2 >> v3;

            PbFace newFace(&(vertexVector[v1-1]), &(vertexVector[v2-1]), &(vertexVector[v3-1]));
            faceList.push_back(newFace);
            vertexVector[v1-1].incrementNormal(newFace.getNormal());
            vertexVector[v2-1].incrementNormal(newFace.getNormal());
            vertexVector[v3-1].incrementNormal(newFace.getNormal());
        }
        else if (type == "mtllib")
        {
            fin >> name;

            material = new PbMaterial(("../../assets/" + name).c_str());
        }
        else
        {
            getline(fin, trash);
        }
    }
}

void PbObject :: draw()
{
    std::vector<PbVertex*> vertices;
    std::list<PbFace> :: iterator faceIt;

    glMaterialfv(GL_FRONT, GL_AMBIENT, material->getKa());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material->getKd());
    glMaterialfv(GL_FRONT, GL_SPECULAR, material->getKs());
    glMaterialf(GL_FRONT, GL_SHININESS, material->getShininess());

    for (faceIt = faceList.begin(); faceIt != faceList.end(); ++faceIt)
    {
        vertices = faceIt->getVertexVector();
        std::vector<PbVertex*> :: iterator vertIt;

        // normal por vertices
        glBegin(GL_POLYGON);
            for (vertIt = vertices.begin(); vertIt != vertices.end(); ++vertIt)
            {
                glNormal3f((*vertIt)->getNormal_x(), (*vertIt)->getNormal_y(), (*vertIt)->getNormal_z());
                glVertex3f((*vertIt)->get_x(), (*vertIt)->get_y(), (*vertIt)->get_z());
            }
        glEnd();
    }
}

void PbObject :: drawVerticesNormals(float size)
{
    std::vector<PbVertex*> vertices;
    std::list<PbFace> :: iterator faceIt;

    float redColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, redColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, redColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, redColor);
    glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);

    for (faceIt = faceList.begin(); faceIt != faceList.end(); ++faceIt)
    {
        vertices = faceIt->getVertexVector();
        std::vector<PbVertex*> :: iterator vertIt;

        glBegin(GL_LINES);
            for (vertIt = vertices.begin(); vertIt != vertices.end(); ++vertIt)
            {
                (*vertIt)->normalize();
                glVertex3f((*vertIt)->get_x(),
                           (*vertIt)->get_y(),
                           (*vertIt)->get_z());
                glVertex3f((*vertIt)->get_x() + (*vertIt)->getNormal_x() * size,
                           (*vertIt)->get_y() + (*vertIt)->getNormal_y() * size,
                           (*vertIt)->get_z() + (*vertIt)->getNormal_z() * size);
            }
        glEnd();
    }
}

PbObject& PbObject :: operator= (const PbObject &o)
{
    if (this != &o)
    {
        vertexVector = o.vertexVector;
        textureVertexVector = o.textureVertexVector;
        faceList = o.faceList;

        drawable = o.drawable;
        identifier = o.identifier;
    }

    return *this;
}
