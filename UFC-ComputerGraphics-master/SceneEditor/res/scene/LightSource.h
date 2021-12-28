/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

class LightSource {
    public:
        LightSource();
        virtual ~LightSource();

        // creates a light using OpenGL
        virtual void enableLight();

        // setters
        void setAmbient(float *ambientComponent);
        void setDiffuse(float *diffuseComponent);
        void setSpecular(float *specularComponent);
        void setPosition(float *positionComponent);

        void setAmbient(float r, float g, float b, float a = 1.0f);
        void setDiffuse(float r, float g, float b, float a = 1.0f);
        void setSpecular(float r, float g, float b, float a = 1.0f);
        void setPosition(float x, float y, float z, float w = 0.0f);

        void setConstantAttenuation(float constAtt);
        void setLinearAttenuation(float linearAtt);
        void setQuadraticAttenuation(float quadAtt);

        // getters
        float* getAmbient() {return ambient;}
        float* getDiffuse() {return diffuse;}
        float* getSpecular() {return specular;}
        float* getPosition() {return position;}

        float getConstantAttenuation() {return constantAttenuation;}
        float getLinearAttenuation() {return linearAttenuation;}
        float getQuadraticAttenuation() {return quadraticAttenuation;}

    protected:
        float ambient[4], diffuse[4], specular[4], position[4];
        float constantAttenuation, linearAttenuation, quadraticAttenuation;
        static unsigned int lightId; // the number of lights created, starts 0
};

#endif // LIGHT_SOURCE_H
