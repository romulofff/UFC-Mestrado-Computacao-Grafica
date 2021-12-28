/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "LightSource.h"

#include <iostream>

#ifdef __APPLE__
    #include "gl.h"
#else
    #include "GL/gl.h"
#endif

unsigned int LightSource :: lightId = 0;

LightSource :: LightSource()
{
    ambient[0] = 0.0f;
    ambient[1] = 0.0f;
    ambient[2] = 0.0f;
    ambient[3] = 1.0f;

    diffuse[0] = 1.0f;
    diffuse[1] = 1.0f;
    diffuse[2] = 1.0f;
    diffuse[3] = 1.0f;

    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;
    specular[3] = 1.0f;

    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 1.0f;
    position[3] = 0.0f;

    constantAttenuation = 1.0f;
    linearAttenuation = 0.0f;
    quadraticAttenuation = 0.0f;
}

LightSource :: ~LightSource()
{
    --lightId;
    glDisable(GL_LIGHT0 + lightId);
}

void LightSource :: enableLight()
{
    if (lightId > 7)
    {
        std::cout << "Cannot create more than 8 light sources.\n";
    }
    else
    {
        // create light in openGL
        glEnable(GL_LIGHT0 + lightId);

        glLightfv(GL_LIGHT0 + lightId, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0 + lightId, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0 + lightId, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT0 + lightId, GL_POSITION, position);

        glLightf(GL_LIGHT0 + lightId, GL_CONSTANT_ATTENUATION, constantAttenuation);
        glLightf(GL_LIGHT0 + lightId, GL_LINEAR_ATTENUATION, linearAttenuation);
        glLightf(GL_LIGHT0 + lightId, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);

        ++lightId;
    }
}

void LightSource :: setAmbient(float *ambientComponent)
{
    ambient[0] = *(ambientComponent);
    ambient[1] = *(ambientComponent + 1);
    ambient[2] = *(ambientComponent + 2);
    ambient[3] = *(ambientComponent + 3);

    glLightfv(GL_LIGHT0 + lightId, GL_AMBIENT, ambient);
}

void LightSource :: setDiffuse(float *diffuseComponent)
{
    diffuse[0] = *(diffuseComponent);
    diffuse[1] = *(diffuseComponent + 1);
    diffuse[2] = *(diffuseComponent + 2);
    diffuse[3] = *(diffuseComponent + 3);

    glLightfv(GL_LIGHT0 + lightId, GL_DIFFUSE, diffuse);
}

void LightSource :: setSpecular(float *specularComponent)
{
    specular[0] = *(specularComponent);
    specular[1] = *(specularComponent + 1);
    specular[2] = *(specularComponent + 2);
    specular[3] = *(specularComponent + 3);

    glLightfv(GL_LIGHT0 + lightId, GL_SPECULAR, specular);
}

void LightSource :: setPosition(float *positionComponent)
{
    position[0] = *(positionComponent);
    position[1] = *(positionComponent + 1);
    position[2] = *(positionComponent + 2);
    position[3] = *(positionComponent + 3);

    glLightfv(GL_LIGHT0 + lightId, GL_POSITION, position);
}

void LightSource :: setAmbient(float r, float g, float b, float a)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;

    glLightfv(GL_LIGHT0 + lightId, GL_AMBIENT, ambient);
}

void LightSource :: setDiffuse(float r, float g, float b, float a)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;

    glLightfv(GL_LIGHT0 + lightId, GL_DIFFUSE, diffuse);
}

void LightSource :: setSpecular(float r, float g, float b, float a)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;

    glLightfv(GL_LIGHT0 + lightId, GL_SPECULAR, specular);
}

void LightSource :: setPosition(float x, float y, float z, float w)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = w;

    glLightfv(GL_LIGHT0 + lightId, GL_POSITION, position);
}

void LightSource :: setConstantAttenuation(float constAtt)
{
    constantAttenuation = constAtt;
    glLightf(GL_LIGHT0 + lightId, GL_CONSTANT_ATTENUATION, constantAttenuation);
}

void LightSource :: setLinearAttenuation(float linearAtt)
{
    linearAttenuation = linearAtt;
    glLightf(GL_LIGHT0 + lightId, GL_LINEAR_ATTENUATION, linearAttenuation);
}

void LightSource :: setQuadraticAttenuation(float quadAtt)
{
    quadraticAttenuation = quadAtt;
    glLightf(GL_LIGHT0 + lightId, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
}
