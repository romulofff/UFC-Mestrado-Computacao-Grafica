/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "AffineSpace.h"

void multByScalar(double scalar, Point *point)
{
	point->set_x( scalar * point->get_x() );
	point->set_y( scalar * point->get_y() );
	point->set_z( scalar * point->get_z() );
}

void multByScalar(double scalar, Vector *vector)
{
	vector->set_x( scalar * vector->get_x() );
	vector->set_y( scalar * vector->get_y() );
	vector->set_z( scalar * vector->get_z() );
}

double dotProduct(Point p1, Point p2)
{
	return ( (p1.get_x() * p2.get_x()) + (p1.get_y() * p2.get_y()) + (p1.get_z() * p2.get_z()) );
}

double dotProduct(Vector v, Point p)
{
	return ( (v.get_x() * p.get_x()) + (v.get_y() * p.get_y()) + (v.get_z() * p.get_z()) );
}

double dotProduct(Vector v1, Vector v2)
{
	return ( (v1.get_x() * v2.get_x()) + (v1.get_y() * v2.get_y()) + (v1.get_z() * v2.get_z()) );
}

Vector crossProduct(Vector v1, Vector v2)
{
	double aux_x = (v1.get_y() * v2.get_z()) - (v2.get_y() * v1.get_z());
	double aux_y = (v1.get_z() * v2.get_x()) - (v2.get_z() * v1.get_x());
	double aux_z = (v1.get_x() * v2.get_y()) - (v2.get_x() * v1.get_y());

	Vector auxVector(aux_x, aux_y , aux_z);

	return auxVector;
}

Vector pointsSubtraction(Point endPoint, Point initPoint)
{
	double aux_x = endPoint.get_x() - initPoint.get_x();
	double aux_y = endPoint.get_y() - initPoint.get_y();
	double aux_z = endPoint.get_z() - initPoint.get_z();

	Vector auxVector(aux_x, aux_y , aux_z);

	return auxVector;
}
