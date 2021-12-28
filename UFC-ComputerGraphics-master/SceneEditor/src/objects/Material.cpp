/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "Material.h"
#include <iostream>

Material :: Material()
{
	ka[0] = 0.2f;
	ka[1] = 0.2f;
	ka[2] = 0.2f;
	ka[3] = 1.0f;

	kd[0] = 0.8f;
	kd[1] = 0.8f;
	kd[2] = 0.8f;
	kd[3] = 1.0f;

	ks[0] = 1.0f;
	ks[1] = 1.0f;
	ks[2] = 1.0f;
	ks[3] = 1.0f;

	sh = 0.0f;
	ni = 1.0f;

    itHasTexture = false;
}

Material :: Material(const char *materialName)
{
	ka[0] = 0.2f;
	ka[1] = 0.2f;
	ka[2] = 0.2f;
	ka[3] = 1.0f;

	kd[0] = 0.8f;
	kd[1] = 0.8f;
	kd[2] = 0.8f;
	kd[3] = 1.0f;

	ks[0] = 1.0f;
	ks[1] = 1.0f;
	ks[2] = 1.0f;
	ks[3] = 1.0f;

	sh = 0.0f;
	ni = 1.0f;

    this->materialName = materialName;
    itHasTexture = false;
}

void Material :: setKa(float r, float g, float b)
{
    ka[0] = r;
    ka[1] = g;
    ka[2] = b;
}

void Material :: setKd(float r, float g, float b)
{
    kd[0] = r;
    kd[1] = g;
    kd[2] = b;
}

void Material :: setKs(float r, float g, float b)
{
    ks[0] = r;
    ks[1] = g;
    ks[2] = b;
}

void Material :: setAlpha(float alpha)
{
    ka[3] = alpha;
    kd[3] = alpha;
    ks[3] = alpha;
}

void Material :: setSh(float sh)
{
    this->sh = sh;
}

void Material :: setNi(float ni)
{
    this->ni = ni;
}

void Material :: setTextureFileName(std::string textureFileName)
{
    this->textureFileName = textureFileName;
}

void Material :: setItHasTexture()
{
    this->itHasTexture = true;
}

void Material :: loadTexture()
{
    // load image using Qt (tutorial http://www.youtube.com/watch?v=GONCD1DQ_PQ)

    if( !texture.load(textureFileName.c_str()) )
    {
        std::cerr << "Could not read the image file\n";
        return;
    }

    texture = QGLWidget::convertToGLFormat(texture);

    int w = texture.width();
    int h = texture.height();

    // generate the texture
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) texture.bits());
}
