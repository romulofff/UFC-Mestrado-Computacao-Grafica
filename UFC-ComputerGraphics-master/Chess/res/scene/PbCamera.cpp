// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbCamera.h"
#include <cmath>

#include "PbAffineSpace.h"

PbCamera :: PbCamera(PbPoint camEye, PbPoint camLookAt)
{
	eye = camEye;
	lookAt = camLookAt;

	viewUp = camEye;
	viewUp.set_z(viewUp.get_z() + 1.0);

	this->createMatrix();
}

PbCamera :: PbCamera(PbPoint camEye, PbPoint camLookAt, PbPoint camViewUp)
{
	eye = camEye;
	lookAt = camLookAt;
	viewUp = camViewUp;

	this->createMatrix();
}

PbCamera :: PbCamera(double eye_x, double eye_y, double eye_z,
                     double lookAt_x, double lookAt_y, double lookAt_z)
{
    eye.set_x(eye_x);
    eye.set_y(eye_y);
    eye.set_z(eye_z);

    lookAt.set_x(lookAt_x);
    lookAt.set_y(lookAt_y);
    lookAt.set_z(lookAt_z);

    viewUp.set_x(eye_x);
    viewUp.set_y(eye_y);
    viewUp.set_z(eye_z + 1.0);

    this->createMatrix();
}

PbCamera :: PbCamera(double eye_x, double eye_y, double eye_z,
                     double lookAt_x, double lookAt_y, double lookAt_z,
                     double viewUp_x, double viewUp_y, double viewUp_z)
{
    eye.set_x(eye_x);
    eye.set_y(eye_y);
    eye.set_z(eye_z);

    lookAt.set_x(lookAt_x);
    lookAt.set_y(lookAt_y);
    lookAt.set_z(lookAt_z);

    viewUp.set_x(viewUp_x);
    viewUp.set_y(viewUp_y);
    viewUp.set_z(viewUp_z);

	this->createMatrix();
}

void PbCamera :: updateEye(PbPoint camEye)
{
	eye = camEye;
	this->createMatrix();
}

void PbCamera :: updateEye(double x, double y, double z)
{
    eye.set_x(x);
    eye.set_y(y);
    eye.set_z(z);

	this->createMatrix();
}

void PbCamera :: updateLookAt(PbPoint camLookAt)
{
	lookAt = camLookAt;
	this->createMatrix();
}

void PbCamera :: updateLookAt(double x, double y, double z)
{
    lookAt.set_x(x);
    lookAt.set_y(y);
    lookAt.set_z(z);

	this->createMatrix();
}

void PbCamera :: updateViewUp(PbPoint camViewUp)
{
	viewUp = camViewUp;
	this->createMatrix();
}

void PbCamera :: updateViewUp(double x, double y, double z)
{
    viewUp.set_x(x);
    viewUp.set_y(y);
    viewUp.set_z(z);

	this->createMatrix();
}

void PbCamera :: updateCamera(PbPoint camEye, PbPoint camLookAt)
{
	eye = camEye;
	lookAt = camLookAt;

	viewUp = camEye;
	viewUp.set_z(viewUp.get_z() + 1.0);

	this->createMatrix();
}

void PbCamera :: updateCamera(PbPoint camEye, PbPoint camLookAt, PbPoint camViewUp)
{
	eye = camEye;
	lookAt = camLookAt;
	viewUp = camViewUp;

	this->createMatrix();
}

void PbCamera :: updateCamera(double eye_x, double eye_y, double eye_z,
                              double lookAt_x, double lookAt_y, double lookAt_z)
{
    eye.set_x(eye_x);
    eye.set_y(eye_y);
    eye.set_z(eye_z);

    lookAt.set_x(lookAt_x);
    lookAt.set_y(lookAt_y);
    lookAt.set_z(lookAt_z);

    viewUp.set_x(eye_x);
    viewUp.set_y(eye_y);
    viewUp.set_z(eye_z + 1.0);

    this->createMatrix();
}

void PbCamera :: updateCamera(double eye_x, double eye_y, double eye_z,
                              double lookAt_x, double lookAt_y, double lookAt_z,
                              double viewUp_x, double viewUp_y, double viewUp_z)
{
    eye.set_x(eye_x);
    eye.set_y(eye_y);
    eye.set_z(eye_z);

    lookAt.set_x(lookAt_x);
    lookAt.set_y(lookAt_y);
    lookAt.set_z(lookAt_z);

    viewUp.set_x(viewUp_x);
    viewUp.set_y(viewUp_y);
    viewUp.set_z(viewUp_z);

    this->createMatrix();
}

void PbCamera :: createMatrix()
{
	PbVector i, j, k, auxVector;

    // vector of z axis
	k = pointsSubtraction(eye, lookAt);
	k.normalize();

    // vector of y axis
	auxVector = pointsSubtraction(viewUp, eye);

	i = crossProduct(auxVector, k);
	i.normalize();

    // vector of x axis
	j = crossProduct(k, i);

    // matrix of transformation
    matrix[0]  = i.get_x();
    matrix[1]  = j.get_x();
    matrix[2]  = k.get_x();
    matrix[3]  = 0.0;

    matrix[4]  = i.get_y();
    matrix[5]  = j.get_y();
    matrix[6]  = k.get_y();
    matrix[7]  = 0.0;

    matrix[8]  = i.get_z();
    matrix[9]  = j.get_z();
    matrix[10] = k.get_z();
    matrix[11] = 0.0;

    matrix[12] = -(dotProduct(i, eye));
    matrix[13] = -(dotProduct(j, eye));
    matrix[14] = -(dotProduct(k, eye));
    matrix[15] = 1.0;
}

PbCamera& PbCamera :: operator= (const PbCamera &cam)
{
	if (this != &cam)
	{
        for (int i = 0; i < 16; i++)
            matrix[i] = cam.matrix[i];

		eye = cam.eye;
		lookAt = cam.lookAt;
		viewUp = cam.viewUp;
	}

	return *this;
}
