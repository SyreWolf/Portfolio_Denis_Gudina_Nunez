#ifndef PELOTA_H_
#define PELOTA_H_
#include <GL/glut.h>
#include "solido.h"

//Clase Pelota, hereda de Solido
class Pelota : public Solido {
	//Variable para el radio y el nivel de la pelota
	double r;
	int level;
public:
	//Contructor por defecto
	Pelota() : Solido(), r(1), level(3) {}
	//Constructor por valor
	Pelota(Vector3D p, Vector3D c, Vector3D v, double d = 1, int l = 3) :
		Solido(p, c, v),
		r(d),
		level(l){}
	~Pelota();
	/*Metodos de acceso para el nivel de pelota,
	y el lado*/
	void setLevel(int l) { level = l; }
	int getLevel() { return level; }
	double getR() { return r; }
	void setR(double d) { r = d; }
	//Render
	void render();
	//Ostream &operator <<
	friend ostream &operator<<(ostream &os, const Pelota &p);
};
//Declaracion ostream &operator <<
inline ostream &operator<<(ostream &os, const Pelota &p) {
	os << static_cast<const Solido&>(p);
	os << p.r << endl;
	os << p.level << endl;
	return os;
}
#endif