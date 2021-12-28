/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef AFFINE_SPACE_H
#define AFFINE_SPACE_H

#include "Point.h"
#include "Vector.h"

void multByScalar(double scalar, Point *point);
void multByScalar(double scalar, Vector *vector);

double dotProduct(Point p1, Point p2);
double dotProduct(Vector v, Point p);
double dotProduct(Vector v1, Vector v2);

Vector crossProduct(Vector v1, Vector v2);

Vector pointsSubtraction(Point endPoint, Point initPoint);

#endif // AFFINE_SPACE_H
