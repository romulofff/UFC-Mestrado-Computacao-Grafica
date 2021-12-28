// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbVector.h"
#include <cmath>

PbVector :: PbVector() 
{
	v_x = 0.0;
	v_y = 0.0;
	v_z = 1.0;

	magnitude = 1.0;	
}

PbVector :: PbVector(double x, double y, double z)
{
	v_x = x;
	v_y = y;
	v_z = z;

    magnitude = calculateMagnitude();
}

void PbVector :: normalize()
{
	v_x /= magnitude;
	v_y /= magnitude;
	v_z /= magnitude;

	magnitude = 1.0;
}

void PbVector :: set_x(double x)
{
	v_x = x;
	magnitude = calculateMagnitude();
}

void PbVector :: set_y(double y)
{
	v_y = y;
	magnitude = calculateMagnitude();
}

void PbVector :: set_z(double z) 
{
	v_z = z;
	magnitude = calculateMagnitude();
}

void PbVector :: set_xyz(double x, double y, double z)
{
	v_x = x;
	v_y = y;
	v_z = z;
	magnitude = calculateMagnitude();
}

double PbVector :: calculateMagnitude()
{
	return sqrt( (v_x * v_x) + (v_y * v_y) + (v_z * v_z) );
}

PbVector& PbVector :: operator= (const PbVector &v)
{
	if (this != &v) 
	{
		v_x = v.v_x;
		v_y = v.v_y;
		v_z = v.v_z;

		magnitude = v.magnitude;
	}

	return *this;
}
