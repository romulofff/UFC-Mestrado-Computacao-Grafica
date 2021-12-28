/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <QGLWidget>
#include <QString>
#include <QImage>
#include <QGLFunctions>

class Material {
	public:
        // constructors and destructor
		Material();
        Material(const char *materialName);

        void loadTexture();

        // getters
        float* getKa() {return ka;}
        float* getKd() {return kd;}
        float* getKs() {return ks;}

        float getShininess() {return sh;}
        float getNi() {return ni;}

        std::string getTextureFileName() {return textureFileName;}
        std::string getMaterialName() {return materialName;}

        bool getItHasTexture() {return itHasTexture;}
        GLuint getTexHandle() {return texHandle;}

        // setters
        void setKa(float r, float g, float b);
        void setKd(float r, float g, float b);
        void setKs(float r, float g, float b);

        void setSh(float);
        void setNi(float);
        void setAlpha(float);

        void setTextureFileName(std::string textureFileName);
        void setItHasTexture();

    private:
        // ambient, diffuse and specular components
        float ka[4], kd[4], ks[4];

        // shininess and refraction coefficient
        float sh, ni;

        std::string materialName;
        std::string textureFileName;
        QImage texture;

        GLuint texHandle;
        bool itHasTexture;
};

#endif // MATERIAL_H
