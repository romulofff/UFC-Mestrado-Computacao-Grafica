// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_AFFINE_SPACE_H
#define PB_AFFINE_SPACE_H

#include "PbPoint.h"
#include "PbVector.h"

void multByScalar(double scalar, PbPoint *point);
void multByScalar(double scalar, PbVector *vector);

double dotProduct(PbPoint p1, PbPoint p2);
double dotProduct(PbVector v, PbPoint p);
double dotProduct(PbVector v1, PbVector v2);

PbVector crossProduct(PbVector v1, PbVector v2);

PbVector pointsSubtraction(PbPoint endPoint, PbPoint initPoint);

#endif // PB_AFFINE_SPACE_H
