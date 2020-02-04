#ifndef SOLIDO_H_
#define SOLIDO_H_

#include <GL/glut.h>
#include "vector3d.h"

class Solido {
	Vector3D pos;
	Vector3D vel;
	Vector3D col;
	Vector3D f;
	double m;
	/*Se añaden las variables tipo y controlador de colision
	a las variables que habia de manera inicial*/
	string type;
	bool hit;
public:
	/* Constructores */
	Solido() :
		pos(Vector3D()),
		vel(),
		col(1, 1, 0),
		f(),
	    m(1),
	    type("none"),
		hit(false){}
	Solido(Vector3D p, Vector3D c = Vector3D(1, 0, 0), Vector3D v = Vector3D(), Vector3D f = Vector3D(), double m = 1, string t = "none", bool h = false) :
		pos(Vector3D(p.getX(), p.getY(), p.getZ())),
		vel(p.getX(), p.getY(), p.getZ()),
		col(c),f(f),m(m),type(t),hit(h) {}

	/* Metodos de acceso */
	Vector3D getPos() {return pos;	}
	void setPos(Vector3D v) {pos = v;}
	Vector3D getVel() {	return vel;}
	void setVel(Vector3D v) {vel = v;}
	Vector3D getCol() {return col;}
	void setCol(Vector3D v) {col = v;}
	Vector3D getF() { return f; }
	void setF(Vector3D v) { f = v; }
	double getM() { return m; }
	void setM(double d) { m = d; }
	/*Se añaden los metodos de acceso 
	para el tipo y el controlador de colision*/
	string getType() { return type; }
	void setType(string t) { type = t; }
	bool isHit() { return hit; }
	void setHit(bool h) { hit = h; }

	void acumulaFuerza(Vector3D fv) { f = f + fv; }

	void update(double dt);
	virtual void render() = 0;
	friend ostream &operator<<(ostream &os, const Solido &c);
};
inline ostream &operator<<(ostream &os, const Solido &c) {
	os << c.pos << endl;
	os << c.vel << endl;
	os << c.col << endl;
	os << c.f << endl;
	os << c.m << endl;
	return os;
}
#endif