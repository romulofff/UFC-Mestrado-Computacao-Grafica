// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_MATERIAL_H
#define PB_MATERIAL_H

class PbMaterial {
	public:
		PbMaterial();
        PbMaterial(const char *materialName);

        void loadMaterial(const char *materialName);

		float* getKa() {return ka;}
		float* getKd() {return kd;}
		float* getKs() {return ks;}

		float getShininess() {return sh;}
        float getNi() {return ni;}

	private:
		float ka[4], kd[4], ks[4]; 
		float sh, ni;
};

#endif // PB_MATERIAL_H
