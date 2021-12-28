/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "Vector.h"
#include <cmath>

Vector :: Vector() 
{
	v_x = 0.0;
	v_y = 0.0;
	v_z = 1.0;

	magnitude = 1.0;	
}

Vector :: Vector(double x, double y, double z)
{
	v_x = x;
	v_y = y;
	v_z = z;

    magnitude = calculateMagnitude();
}

void Vector :: normalize()
{
	v_x /= magnitude;
	v_y /= magnitude;
	v_z /= magnitude;

	magnitude = 1.0;
}

void Vector :: set_x(double x)
{
	v_x = x;
	magnitude = calculateMagnitude();
}

void Vector :: set_y(double y)
{
	v_y = y;
	magnitude = calculateMagnitude();
}

void Vector :: set_z(double z) 
{
	v_z = z;
	magnitude = calculateMagnitude();
}

void Vector :: set_xyz(double x, double y, double z)
{
	v_x = x;
	v_y = y;
	v_z = z;
	magnitude = calculateMagnitude();
}

double Vector :: calculateMagnitude()
{
	return sqrt( (v_x * v_x) + (v_y * v_y) + (v_z * v_z) );
}

Vector& Vector :: operator= (const Vector &v)
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
