// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbMaterial.h"
#include <string>
#include <fstream>

PbMaterial :: PbMaterial()
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
}

PbMaterial :: PbMaterial(const char *materialName)
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

    this->loadMaterial(materialName);
}

void PbMaterial :: loadMaterial(const char *materialName)
{
	float r, g, b, alpha, x;
    std::string type, trash;

	std::ifstream fin;
    fin.open(materialName, std::ifstream::in);

    while (fin >> type)
    {
        if (type == "Ka")
        {
            fin >> r >> g >> b;
			
			ka[0] = r;
			ka[1] = g;
			ka[2] = b;
		}
        else if (type == "Kd")
        {
            fin >> r >> g >> b;
			
			kd[0] = r;
			kd[1] = g;
			kd[2] = b;
		}
        else if (type == "Ks")
        {
            fin >> r >> g >> b;
			
			ks[0] = r;
			ks[1] = g;
			ks[2] = b;
		}
        else if (type == "Ns")
        {
            fin >> x;
			sh = x;
        }
        else if (type == "Ni")
		{
			fin >> x;
			ni = x;
		}
		else if (type == "d" || type == "Tr")
		{
			fin >> alpha;

			ka[3] = alpha;
			kd[3] = alpha;
			ks[3] = alpha;
		}
        else
		{
			getline(fin, trash);
        }
    }
}
