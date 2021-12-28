// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_LIGHT_SOURCE_H
#define PB_LIGHT_SOURCE_H

class PbLightSource {
    public:
        PbLightSource();
        virtual ~PbLightSource();

        virtual void enableLight(); // creates a light using OpenGL

        void setAmbient(float *ambientComponent);
        void setDiffuse(float *diffuseComponent);
        void setSpecular(float *specularComponent);
        void setPosition(float *positionComponent);

        void setAmbient(float r, float g, float b, float a = 1.0f);
        void setDiffuse(float r, float g, float b, float a = 1.0f);
        void setSpecular(float r, float g, float b, float a = 1.0f);
        void setPosition(float x, float y, float z, float w = 0.0f);

        void setConstantAttenuation(float constAtt) {constantAttenuation = constAtt;}
        void setLinearAttenuation(float linearAtt) {linearAttenuation = linearAtt;}
        void setQuadraticAttenuation(float quadAtt) {quadraticAttenuation = quadAtt;}

        float* getAmbient() {return ambient;}
        float* getDiffuse() {return diffuse;}
        float* getSpecular() {return specular;}
        float* getPosition() {return position;}

        float get_x() {return position[0];}
        float get_y() {return position[1];}
        float get_z() {return position[2];}

        float getConstantAttenuation() {return constantAttenuation;}
        float getLinearAttenuation() {return linearAttenuation;}
        float getQuadraticAttenuation() {return quadraticAttenuation;}

    protected:
        float ambient[4], diffuse[4], specular[4], position[4];
        float constantAttenuation, linearAttenuation, quadraticAttenuation;
        static unsigned int lightId; // starts 0
};

#endif // PB_LIGHT_SOURCE_H
