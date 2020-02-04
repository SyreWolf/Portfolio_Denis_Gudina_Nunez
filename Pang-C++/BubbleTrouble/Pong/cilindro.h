#pragma once
#include <vector>
#include <GL/glut.h>
#include "solido.h"

using namespace std;

class Cilindro: public Solido{
	GLUquadricObj *quadratic;
	double b;
	double h;
public:
	Cilindro(float bp, float hp);
	~Cilindro();
	double getB() { return b; }
	double getH() { return h; }
	void setG(double d) { b = d; }
	void setH(double d) { h = d; }
	void render();
	friend ostream &operator<<(ostream &os, const Cilindro &c);
};
inline ostream &operator<<(ostream &os, const Cilindro &c) {
	os << static_cast<const Solido&>(c);
	os << c.b << endl;
	os << c.h << endl;
	return os;
}

