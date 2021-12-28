// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbVertex.h"

PbVertex :: PbVertex()
{
	p_x = 0.0;
	p_y = 0.0;
	p_z = 0.0;

	normal.set_xyz(0.0, 0.0, 0.0);
}

PbVertex :: PbVertex(double x, double y, double z)
{
	p_x = x;
	p_y = y;
	p_z = z;

	normal.set_xyz(0.0, 0.0, 0.0);
}

void PbVertex :: setNormal(double n_x, double n_y, double n_z)
{
    normal.set_xyz(n_x, n_y, n_z);
    normal.normalize();
}

void PbVertex :: incrementNormal(PbVector n)
{
    normal.set_xyz(normal.get_x() + n.get_x(), normal.get_y() + n.get_y(), normal.get_z() + n.get_z());
}

void PbVertex :: incrementNormal(double n_x, double n_y, double n_z)
{
    normal.set_xyz(normal.get_x() + n_x, normal.get_y() + n_y, normal.get_z() + n_z);
}
