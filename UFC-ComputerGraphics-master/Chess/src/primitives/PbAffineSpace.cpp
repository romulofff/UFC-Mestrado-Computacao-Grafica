// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbAffineSpace.h"

void multByScalar(double scalar, PbPoint *point)
{
	point->set_x( scalar * point->get_x() );
	point->set_y( scalar * point->get_y() );
	point->set_z( scalar * point->get_z() );
}

void multByScalar(double scalar, PbVector *vector)
{
	vector->set_x( scalar * vector->get_x() );
	vector->set_y( scalar * vector->get_y() );
	vector->set_z( scalar * vector->get_z() );
}

double dotProduct(PbPoint p1, PbPoint p2)
{
	return ( (p1.get_x() * p2.get_x()) + (p1.get_y() * p2.get_y()) + (p1.get_z() * p2.get_z()) );
}

double dotProduct(PbVector v, PbPoint p)
{
	return ( (v.get_x() * p.get_x()) + (v.get_y() * p.get_y()) + (v.get_z() * p.get_z()) );
}

double dotProduct(PbVector v1, PbVector v2)
{
	return ( (v1.get_x() * v2.get_x()) + (v1.get_y() * v2.get_y()) + (v1.get_z() * v2.get_z()) );
}

PbVector crossProduct(PbVector v1, PbVector v2)
{
	double aux_x = (v1.get_y() * v2.get_z()) - (v2.get_y() * v1.get_z());
	double aux_y = (v1.get_z() * v2.get_x()) - (v2.get_z() * v1.get_x());
	double aux_z = (v1.get_x() * v2.get_y()) - (v2.get_x() * v1.get_y());

	PbVector auxVector(aux_x, aux_y , aux_z);

	return auxVector;
}

PbVector pointsSubtraction(PbPoint endPoint, PbPoint initPoint)
{
	double aux_x = endPoint.get_x() - initPoint.get_x();
	double aux_y = endPoint.get_y() - initPoint.get_y();
	double aux_z = endPoint.get_z() - initPoint.get_z();

	PbVector auxVector(aux_x, aux_y , aux_z);

	return auxVector;
}
