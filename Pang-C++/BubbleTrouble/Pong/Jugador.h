#ifndef JUGADOR_H_
#define JUGADOR_H_
#include <GL/glut.h>
#include "solido.h"

//Clase Jugador, hereda de Solido
class Jugador :public Solido
{
	//Variables para el lado, la puntuacion y la comprobacion de vida
	double s;
	int score;
	bool muerto;
public:
	//Constructor por defecto
	Jugador() : Solido(), s(1), muerto(false) {}
	//Constructor por valores
	Jugador(Vector3D p, Vector3D c, Vector3D v, double d = 1, bool m = false) :
		Solido(p, c, v),
		s(d),
		muerto(m){}
	//Destructor
	~Jugador();
	/*Metodos de acceso para el lado,
	la puntuacion y el estado de vivo o muerto*/
	void setScore(int s) { score = s; }
	int getScore() { return score; }
	double getS() { return s; }
	void setS(double d) { s = d; }
	double isMuerto() { return muerto; }
	void setMuerto(bool m) { muerto = m; }
	//Render
	void render();
	//Ostream &operator <<
	friend ostream &operator<<(ostream &os, const Jugador &j);
};
//Declaracion ostream &operator <<
inline ostream &operator<<(ostream &os, const Jugador &j) {
	os << static_cast<const Solido&>(j);
	os << j.s << endl;
	return os;
}
#endif