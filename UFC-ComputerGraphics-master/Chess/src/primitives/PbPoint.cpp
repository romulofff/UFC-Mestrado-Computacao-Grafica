// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbPoint.h"

PbPoint& PbPoint :: operator= (const PbPoint &p)
{
	if (this != &p)
	{
		p_x = p.p_x;
		p_y = p.p_y;
		p_z = p.p_z;
	}

	return *this;
}
