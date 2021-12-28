// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_VECTOR_H
#define PB_VECTOR_H

class PbVector {
	public:
		PbVector(); // create a single PbVector(0, 0, 1)
		PbVector(double x, double y, double z);

		virtual ~PbVector() {}

		void normalize(); // normalize this PbVector, previous informations are lost

		// all below automatically update magnitude
		void set_x(double x);
		void set_y(double y);
		void set_z(double z);
		void set_xyz(double x, double y, double z);

        double get_x() {return v_x;}
        double get_y() {return v_y;}
        double get_z() {return v_z;}
		double getMagnitude() {return magnitude;}

        PbVector& operator= (const PbVector &v);

	protected:
		double v_x, v_y, v_z, magnitude;

		double calculateMagnitude();
};

#endif // PB_VECTOR_H
