/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"

class Camera {
    public:
        // constructors and destructor

		Camera(Point camEye, Point camLookAt);
        Camera(Point camEye, Point camLookAt, Point camViewUp);

        Camera(double eye_x, double eye_y, double eye_z,
                 double lookAt_x, double lookAt_y, double lookAt_z);
		Camera(double eye_x, double eye_y, double eye_z, 
                 double lookAt_x, double lookAt_y, double lookAt_z,
                 double viewUp_x, double viewUp_y, double viewUp_z);

        virtual ~Camera() {}


        // funtions to atualize the values of the cam

		void updateEye(Point camEye);
		void updateEye(double x, double y, double z);

		void updateLookAt(Point camLookAt);
		void updateLookAt(double x, double y, double z);

		void updateViewUp(Point camViewUp);
		void updateViewUp(double x, double y, double z);

		void updateCamera(Point camEye, Point camLookAt);
		void updateCamera(Point camEye, Point camLookAt, Point camViewUp);
        void updateCamera(double eye_x, double eye_y, double eye_z,
                          double lookAt_x, double lookAt_y, double lookAt_z);
        void updateCamera(double eye_x, double eye_y, double eye_z,
                          double lookAt_x, double lookAt_y, double lookAt_z,
                          double viewUp_x, double viewUp_y, double viewUp_z);


        // getters

        double getEye_x() {return eye.get_x();}
        double getEye_y() {return eye.get_y();}
        double getEye_z() {return eye.get_z();}

        double getLookAt_x() {return lookAt.get_x();}
        double getLookAt_y() {return lookAt.get_y();}
        double getLookAt_z() {return lookAt.get_z();}

        double getViewUp_x() {return viewUp.get_x();}
        double getViewUp_y() {return viewUp.get_y();}
        double getViewUp_z() {return viewUp.get_z();}

        double* getMatrix() {return matrix;}

        // operator =
		Camera& operator= (const Camera &cam);


    private:
        // camera content
        double matrix[16];
        Point eye, lookAt, viewUp;

        // calculate the camera matrix
        void createMatrix();
};

#endif // CAMERA_H
