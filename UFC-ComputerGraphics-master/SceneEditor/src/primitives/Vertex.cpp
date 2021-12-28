/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "Vertex.h"

Vertex :: Vertex()
{
	p_x = 0.0;
	p_y = 0.0;
	p_z = 0.0;

	normal.set_xyz(0.0, 0.0, 0.0);
}

Vertex :: Vertex(double x, double y, double z)
{
	p_x = x;
	p_y = y;
	p_z = z;

	normal.set_xyz(0.0, 0.0, 0.0);
}

void Vertex :: setNormal(double n_x, double n_y, double n_z)
{
    normal.set_xyz(n_x, n_y, n_z);
    normal.normalize();
}

void Vertex :: incrementNormal(Vector n)
{
    normal.set_xyz(normal.get_x() + n.get_x(), normal.get_y() + n.get_y(), normal.get_z() + n.get_z());
}

void Vertex :: incrementNormal(double n_x, double n_y, double n_z)
{
    normal.set_xyz(normal.get_x() + n_x, normal.get_y() + n_y, normal.get_z() + n_z);
}
