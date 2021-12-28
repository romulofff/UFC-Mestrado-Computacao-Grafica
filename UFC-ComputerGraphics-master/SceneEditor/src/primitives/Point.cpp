/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "Point.h"

Point& Point :: operator= (const Point &p)
{
	if (this != &p)
	{
		p_x = p.p_x;
		p_y = p.p_y;
		p_z = p.p_z;
	}

	return *this;
}
