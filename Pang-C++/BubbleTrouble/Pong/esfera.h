#pragma once
#include <GL/glut.h>
#include "solido.h"
class Esfera: public Solido{
	double r; 
public:
	Esfera() : Solido(), r(0.25) {}
	Esfera(Vector3D p, Vector3D c = Vector3D(1, 0, 0), Vector3D v = Vector3D(), double d = 0.25) :
		Solido(p, c, v),
		r(d) {}
	~Esfera();
	/* Metodos de acceso */
	double getR() { return r; }
	void setR(double d) { r = d; }
	void render();
	friend ostream &operator<<(ostream &os, const Esfera &c);
};
inline ostream &operator<<(ostream &os, const Esfera &c) {
	os << static_cast<const Solido&>(c);
	os << c.r << endl;
	return os;
}