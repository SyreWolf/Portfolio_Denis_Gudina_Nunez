#ifndef BALA_H_
#define BALA_H_
#include <GL/glut.h>
#include "solido.h"

//Clase Bala, hereda de sólido
class Bala : public Solido {
	//Radio de la bala
	double r;
	//Comprueba si está en movimiento
	bool moving;
public:
	//Contructor por defecto
	Bala() : Solido(), r(0.1), moving(false) {}
	//Contructor por valor
	Bala(Vector3D p, Vector3D c, Vector3D v, double d = 1, bool m = false) :
		Solido(p, c, v),
		r(d),
		moving(m){}
	//Destructor
	~Bala();
	//Métodos de acceso del radio 
	double getR() { return r; }
	void setR(double d) { r = d; }
	//Métodos de acceso del comprobador de movimiento
	bool isMoving() { return moving; }
	void setMoving(bool m) { moving = m; }
	//Render
	void render();
	//Ostream &operator <<
	friend ostream &operator<<(ostream &os, const Bala &b);
};
//Declaracion ostream &operator <<
inline ostream &operator<<(ostream &os, const Bala &b) {
	os << static_cast<const Solido&>(b);
	os << b.r << endl;
	os << b.moving << endl;
	return os;
}

#endif