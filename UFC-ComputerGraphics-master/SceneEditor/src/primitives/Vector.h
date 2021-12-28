/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
*	COMPUTACAO GRAFICA 1
*	PROFESSOR: CRETO AUGUSTO VIDAL
*
*	JONAS LIMA DA SILVA				344090
*	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
	public:
        // constructors and destructor
        Vector(); // create a unit vector(0, 0, 1)
		Vector(double x, double y, double z);

		virtual ~Vector() {}

        // normalize this Vector, previous informations are lost
        void normalize();

        // setters, all below automatically update magnitude
		void set_x(double x);
		void set_y(double y);
		void set_z(double z);
		void set_xyz(double x, double y, double z);

        // getters
        double get_x() {return v_x;}
        double get_y() {return v_y;}
        double get_z() {return v_z;}
		double getMagnitude() {return magnitude;}

        // operator =
        Vector& operator= (const Vector &v);

	protected:
        //coordinates
		double v_x, v_y, v_z, magnitude;

        // calculates the magnitude based on coordinates
		double calculateMagnitude();
};

#endif // VECTOR_H
