#pragma once
#include <GL/glut.h>
#include "solido.h"

class Cubo:public Solido
{
	double s;
public:
	Cubo(): Solido(), s(0.25)	{}
	Cubo(Vector3D p, Vector3D c=Vector3D(1,0,0), Vector3D v=Vector3D(), double d=0.25):
		Solido(p,c,v),
		s(d) {}
	~Cubo();
	/* Metodos de acceso */
	double getS() {	return s;}
	void setS(double d) {s = d;	}
	void render();
	friend ostream &operator<<(ostream &os, const Cubo &c);
};
inline ostream &operator<<(ostream &os, const Cubo &c) {
	os << static_cast<const Solido&>(c);
	os << c.s << endl;
	return os;
}