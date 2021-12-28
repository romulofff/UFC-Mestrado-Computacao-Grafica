// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_POINT_H
#define PB_POINT_H

class PbPoint {
	public:
		PbPoint() {p_x = 0.0; p_y = 0.0; p_z = 0.0;}
		PbPoint(double x, double y, double z) {p_x = x; p_y = y; p_z = z;}

		virtual ~PbPoint() {}

        void set_x(double x) {p_x = x;}
        void set_y(double y) {p_y = y;}
        void set_z(double z) {p_z = z;}
        void set_xyz(double x, double y, double z) {p_x = x; p_y = y; p_z = z;}

        double get_x() {return p_x;}
        double get_y() {return p_y;}
        double get_z() {return p_z;}

		PbPoint& operator= (const PbPoint &p);

	protected:
		double p_x, p_y, p_z;
};

#endif // PB_POINT_H
