/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef POINT_H
#define POINT_H

class Point {
	public:
        // constructors and destructor
		Point() {p_x = 0.0; p_y = 0.0; p_z = 0.0;}
		Point(double x, double y, double z) {p_x = x; p_y = y; p_z = z;}

		virtual ~Point() {}

        // setters
        void set_x(double x) {p_x = x;}
        void set_y(double y) {p_y = y;}
        void set_z(double z) {p_z = z;}
        void set_xyz(double x, double y, double z) {p_x = x; p_y = y; p_z = z;}

        // getters
        double get_x() {return p_x;}
        double get_y() {return p_y;}
        double get_z() {return p_z;}

        // operator =
		Point& operator= (const Point &p);

	protected:
        // coordinates
		double p_x, p_y, p_z;
};

#endif // POINT_H
