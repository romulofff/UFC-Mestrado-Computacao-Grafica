/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "Object.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <stdlib.h>
#include <QDir>

#ifdef __APPLE__
    #include "gl.h"
#else
    #include "GL/gl.h"
#endif

#define FIRST_ID 130130

unsigned int Object :: latestId = FIRST_ID;

Object :: Object()
{
    material = NULL;
    name = "";

    translate_x = 0.0;
    translate_y = 0.0;
    translate_z = 0.0;

    scale_x = 1.0;
    scale_y = 1.0;
    scale_z = 1.0;

    rotateAngle_x = 0.0;
    rotateAngle_y = 0.0;
    rotateAngle_z = 0.0;

    drawable = false;
    identifier = latestId;

    ++latestId;
}

Object :: Object(std::string objName)
{
    material = NULL;
    name = "";

    setObjDirectory(objName);

    this->loadObject(objName);

    drawable = true;
    identifier = latestId;

    translate_x = 0.0;
    translate_y = 0.0;
    translate_z = 0.0;

    scale_x = 1.0;
    scale_y = 1.0;
    scale_z = 1.0;

    rotateAngle_x = 0.0;
    rotateAngle_y = 0.0;
    rotateAngle_z = 0.0;

    ++latestId;
}

Object :: ~Object()
{
    delete material;
}

void Object :: loadObject(std::string objName)
{
    double x, y, z;
    std::string type, tmp;
    std::string v1, v2, v3, v4;
    std::vector<int> f1, f2, f3, f4;
    std::vector<int>::iterator it1, it2, it3, it4;

    /* reading order ( [] is optional):
     * mtllib
     * [o]
     * v
     * [vt]
     * [vn]
     * f
     * [usemtl]
     * [s]
     *
     * Some OBJ files don't have vt or vn lines, but always those are before f lines.
     * So the number of vt/vn line indicates us if we need to add texture/normals to our object.
     **/

    std::ifstream fin;
    fin.open(objName.c_str(), std::ifstream::in);

    vtCount = 0;
    vnCount = 0;
    int faceCount;

    std::string line;
    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        ss >> type;

        if (type == "#") // comments
        {
            // ignore
        }
        else if (type == "mtllib")
        {
            ss >> tmp;
            //materialFileName = tmp;
            materialFileName = objDirectory + "/" + tmp; // this name will be used to open mtl file
            faceCount = 0;
        }
        else if (type == "o")
        {
            ss >> name;
            //objectsName.push_back(name);
        }
        else if (type == "v") // vertices
        {
            ss >> x >> y >> z;
            Vertex newVertex(x, y, z);
            vertexVector.push_back(newVertex);
        }
        else if (type == "vt") // vertice-texture
        {
            ss >> x >> y;
            Vertex newTextureVertex(x, y, 0.0);
            textureVertexVector.push_back(newTextureVertex);
            vtCount++;
        }
        else if (type == "vn") // normals
        {
            ss >> x >> y >> z;
            vnCount++;
            //std::cout << type << " "<< x << " " << y << " " << z << std::endl;
            //Vertex newTextureVertex(x, y, 0.0);
            //textureVertexVector.push_back(newTextureVertex);
        }
        else if (type == "f") // faces
        {
            faceCount++;
            if (ss >> v1 >> v2 >> v3 >> v4) // 4 vertices
            {
                f1 = splitFaceV(v1);
                f2 = splitFaceV(v2);
                f3 = splitFaceV(v3);
                f4 = splitFaceV(v4);

                // VERTEX component
                it1 = f1.begin();
                it2 = f2.begin();
                it3 = f3.begin();
                it4 = f4.begin();

                // create new Face
                Face newFace(&(vertexVector[*it1-1]), &(vertexVector[*it2-1]), &(vertexVector[*it3-1]), &(vertexVector[*it4-1]));

                vertexVector[*it1-1].incrementNormal(newFace.getNormal());
                vertexVector[*it2-1].incrementNormal(newFace.getNormal());
                vertexVector[*it3-1].incrementNormal(newFace.getNormal());
                vertexVector[*it4-1].incrementNormal(newFace.getNormal());

                // TEXTURE component
                if (vtCount > 0)
                {
                    it1++; it2++; it3++; it4++;
                    newFace.setUVCoordinates(
                            textureVertexVector[*it1-1].get_x(), textureVertexVector[*it1-1].get_y(),
                            textureVertexVector[*it2-1].get_x(), textureVertexVector[*it2-1].get_y(),
                            textureVertexVector[*it3-1].get_x(), textureVertexVector[*it3-1].get_y(),
                            textureVertexVector[*it4-1].get_x(), textureVertexVector[*it4-1].get_y()
                    );
                }

                // push to faceList
                faceList.push_back(newFace);

            }
            else // 3 vertice - ignore v4
            {
                // v = "vertex/texture_coordinate/normal" to [vertex, texture_coordinate, normal]

                // split face components (x/x/x)
                f1 = splitFaceV(v1);
                f2 = splitFaceV(v2);
                f3 = splitFaceV(v3);

                // VERTEX component
                it1 = f1.begin();
                it2 = f2.begin();
                it3 = f3.begin();

                //if (k++ < 790) {

                // create new Face
                Face newFace(&(vertexVector[*it1-1]), &(vertexVector[*it2-1]), &(vertexVector[*it3-1]));

                // change normals
                vertexVector[*it1-1].incrementNormal(newFace.getNormal());
                vertexVector[*it2-1].incrementNormal(newFace.getNormal());
                vertexVector[*it3-1].incrementNormal(newFace.getNormal());

                // TEXTURE component
                if (vtCount > 0)
                {
                    it1++; it2++; it3++;
                    newFace.setUVCoordinates(
                            textureVertexVector[*it1-1].get_x(), textureVertexVector[*it1-1].get_y(),
                            textureVertexVector[*it2-1].get_x(), textureVertexVector[*it2-1].get_y(),
                            textureVertexVector[*it3-1].get_x(), textureVertexVector[*it3-1].get_y()
                    );
                }

                faceList.push_back(newFace);
            }
        }
        else if (type == "usemtl")
        {
            // explained at Object.h line 16
            ss >> tmp;

            usemtl umtl;
            umtl.materialName = tmp;
            umtl.startFace = faceCount;
            usemtlVector.push_back(umtl);
        }
        else if (type == "s")
        {
            ss >> tmp;
            //std::cout << type << " " << tmp << std::endl;
        }
    }

    // now we read MTL file
    loadMTL(materialFileName);

}

void Object :: loadMTL(std::string materialNameFile)
{
    /**
     * Materials in MTL file are arranged alphabetically.
     * Not always the first material should be renderized, so we have to
     * store "usemtl" line from OBJ to know which material have to be shown.
     */
    float r, g, b, alpha, x;
    std::string type, tmp;
    int countLastMtl = -1;

    std::ifstream fin;
    fin.open(materialNameFile.c_str(), std::ifstream::in);

    while (fin >> type)
    {
        if (type == "newmtl")
        {
            countLastMtl++;
            fin >> tmp;
            // create a new Material
            Material newMaterial(tmp.c_str());
            materialVector.push_back(newMaterial);
        }
        else if (type == "Ka")
        {
            fin >> r >> g >> b;
            materialVector[countLastMtl].setKa(r, g, b);
        }
        else if (type == "Kd")
        {
            fin >> r >> g >> b;
            materialVector[countLastMtl].setKd(r, g, b);
        }
        else if (type == "Ks")
        {
            fin >> r >> g >> b;
            materialVector[countLastMtl].setKs(r, g, b);
        }
        else if (type == "Ns")
        {
            fin >> x;
            materialVector[countLastMtl].setSh(x);
        }
        else if (type == "Ni")
        {
            fin >> x;
            materialVector[countLastMtl].setNi(x);
        }
        else if (type == "d" || type == "Tr")
        {
            fin >> alpha;
            materialVector[countLastMtl].setAlpha(alpha);
        }
        else if (type == "map_Kd")
        {
            fin >> tmp;
            materialVector[countLastMtl].setItHasTexture();
            materialVector[countLastMtl].setTextureFileName(this->getObjDirectory() + "/" + tmp);
        }
        else
        {
            getline(fin, tmp);
        }
    }
}

void Object :: draw()
{
    std::vector<Vertex*> vertices;
    std::list<Face> :: iterator faceIt;

    int i, f = 0; // index for UV coordinates;

    unsigned materialn = 0;

    for (faceIt = faceList.begin(); faceIt != faceList.end(); ++faceIt, f++)
    {
        // CHANGE MATERIAL AND LOAD TEXTURE (if it exists)
        // if usemtl doesn't exist in MTL file, load first material
        if ( IsTimeToChangeMaterial(f) != "" || usemtlVector.size() == 0 ) // "" means "no material"
        {
            materialn = materialNum(IsTimeToChangeMaterial(f));

            if (materialVector[materialn].getItHasTexture())
            {
                materialVector[materialn].loadTexture();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, materialVector[materialn].getTexHandle());
                glDisable(GL_COLOR_MATERIAL);
            }
            else
            {
                glDisable(GL_TEXTURE_2D);
            }

            // set material properties
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialVector[materialn].getKa());
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialVector[materialn].getKd());
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialVector[materialn].getKs());
            glMaterialf(GL_FRONT, GL_SHININESS, materialVector[materialn].getShininess());

        }

        vertices = faceIt->getVertexVector();
        std::vector<Vertex*> :: iterator vertIt;

        // draw the object in openGL widget
        glBegin(GL_POLYGON);
            for (vertIt = vertices.begin(), i = 0; vertIt != vertices.end(); ++vertIt, i++) // for each  vertex
            {
                if (materialVector[materialn].getItHasTexture())
                    glTexCoord2f(faceIt->getU(i), faceIt->getV(i));

                glNormal3f((*vertIt)->getNormal_x(), (*vertIt)->getNormal_y(), (*vertIt)->getNormal_z());
                glVertex3f((*vertIt)->get_x(), (*vertIt)->get_y(), (*vertIt)->get_z());
            }
        glEnd();

    }
}

void Object :: drawVerticesNormals()
{
    std::vector<Vertex*> vertices;
    std::list<Face> :: iterator faceIt;

    for (faceIt = faceList.begin(); faceIt != faceList.end(); ++faceIt)
    {
        vertices = faceIt->getVertexVector();
        std::vector<Vertex*> :: iterator vertIt;

        glBegin(GL_LINES);
            for (vertIt = vertices.begin(); vertIt != vertices.end(); ++vertIt)
            {
                (*vertIt)->normalize();
                glVertex3f((*vertIt)->get_x(),
                           (*vertIt)->get_y(),
                           (*vertIt)->get_z());
                glVertex3f((*vertIt)->get_x() + (*vertIt)->getNormal_x(),
                           (*vertIt)->get_y() + (*vertIt)->getNormal_y(),
                           (*vertIt)->get_z() + (*vertIt)->getNormal_z());
            }
        glEnd();
    }
}

std::vector<int> Object :: splitFaceV(std::string f)
{
    // f = "vertex/texture_coordinate/normal" to [vertex, texture_coordinate, normal]

    std::vector<int> face;

    do {
        if (f.find("/") != std::string::npos) // if found "/"
        {
            face.push_back(atoi( f.substr(0, f.find("/")).c_str() )); // add element
            f = f.substr(f.find("/")+1); // remove first part before /
        }
        else
        {
            face.push_back(atoi(f.c_str()));
            f = "";
        }
    } while (f != "");

    // then we have a vector with three parts of f
    return face;
}

void Object :: setObjDirectory(std::string objDir)
{
    objDirectory = objDir.substr(0, objDir.find_last_of("/"));
}

std::string Object :: IsTimeToChangeMaterial(int currFace)
{
    for (unsigned i = 0; i < usemtlVector.size(); i++)
        if (currFace == usemtlVector[i].startFace)
            return usemtlVector[i].materialName;
    return "";
}

unsigned Object :: materialNum(std::string materialName)
{
    for (unsigned i = 0; i < materialVector.size(); i++)
        if (materialVector[i].getMaterialName() == materialName)
            return i;
    return 0;
}

Object& Object :: operator= (const Object &o)
{
    if (this != &o)
    {
        vertexVector = o.vertexVector;
        textureVertexVector = o.textureVertexVector;
        materialVector = o.materialVector;
        usemtlVector = o.usemtlVector;
        faceList = o.faceList;

        texture = o.texture;
        texHandle = o.texHandle;
        material = o.material;
        vtCount = o.vtCount;
        vnCount = o.vnCount;

        name = o.name;
        materialFileName = o.materialFileName;
        objDirectory = o.objDirectory;

        drawable = o.drawable;
        pickable = o.pickable;
        identifier = o.identifier;
        latestId = o.latestId;

        translate_x = o.translate_x;
        translate_y = o.translate_y;
        translate_z = o.translate_z;

        scale_x = o.scale_x;
        scale_y = o.scale_y;
        scale_z = o.scale_z;

        rotateAngle_x = o.rotateAngle_x;
        rotateAngle_y = o.rotateAngle_y;
        rotateAngle_z = o.rotateAngle_z;
    }

    return *this;
}
