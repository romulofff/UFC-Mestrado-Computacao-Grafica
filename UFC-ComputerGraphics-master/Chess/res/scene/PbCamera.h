// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_CAMERA_H
#define PB_CAMERA_H

#include "PbPoint.h"

class PbCamera {
    public:
		PbCamera(PbPoint camEye, PbPoint camLookAt);
		PbCamera(PbPoint camEye, PbPoint camLookAt, PbPoint camViewUp);

        PbCamera(double eye_x, double eye_y, double eye_z,
                 double lookAt_x, double lookAt_y, double lookAt_z);
		PbCamera(double eye_x, double eye_y, double eye_z, 
                 double lookAt_x, double lookAt_y, double lookAt_z,
                 double viewUp_x, double viewUp_y, double viewUp_z);

        virtual ~PbCamera() {}

		void updateEye(PbPoint camEye);
		void updateEye(double x, double y, double z);

		void updateLookAt(PbPoint camLookAt);
		void updateLookAt(double x, double y, double z);

		void updateViewUp(PbPoint camViewUp);
		void updateViewUp(double x, double y, double z);

		void updateCamera(PbPoint camEye, PbPoint camLookAt);
		void updateCamera(PbPoint camEye, PbPoint camLookAt, PbPoint camViewUp);
        void updateCamera(double eye_x, double eye_y, double eye_z,
                          double lookAt_x, double lookAt_y, double lookAt_z);
        void updateCamera(double eye_x, double eye_y, double eye_z,
                          double lookAt_x, double lookAt_y, double lookAt_z,
                          double viewUp_x, double viewUp_y, double viewUp_z);

        double getEye_x() {return eye.get_x();}
        double getEye_y() {return eye.get_y();}
        double getEye_z() {return eye.get_z();}

        double getLookAt_x() {return lookAt.get_x();}
        double getLookAt_y() {return lookAt.get_y();}
        double getLookAt_z() {return lookAt.get_z();}

        double* getMatrix() {return matrix;}

		PbCamera& operator= (const PbCamera &cam);

	private:
        double matrix[16];
        PbPoint eye, lookAt, viewUp;

        void createMatrix();
};

#endif // PB_CAMERA_H
