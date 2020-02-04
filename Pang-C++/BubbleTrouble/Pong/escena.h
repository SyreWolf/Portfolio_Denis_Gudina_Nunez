#ifndef ESCENA_H_
#define ESCENA_H_
#include <vector>
#include <Windows.h>
#include <MMSystem.h>
#include "Bala.h"
#include "Jugador.h"
#include "Pelota.h"
#include "pared.h"

using namespace std;

//Clase Escena modificada
class Escena
{
	//No vamos a usar este array, se comenta
	//vector<Solido*> solidos;
	//El jugador, la bala, vectores de paredes y pelotas
	vector<Pared*> paredes;
	vector<Pelota*> pelotas;
	Jugador* jugador;
	Bala* bala;
public:
	//Constructor vacio
	Escena();
	//Destructor
	~Escena();
	//Metodos de acceso que no se van a usar
	/*vector<Solido*> getSolidos() { return solidos; }
	void setSolidos(vector<Solido*> e) { solidos = e; }*/
	//Metodos de acceso para paredes, pelotas, la bala y el jugador
	vector<Pared*> getParedes() { return paredes; }
	void setParedes(vector<Pared*> p) { paredes = p; }
	vector<Pelota*> getPelotas() { return pelotas; }
	void setPelotas(vector<Pelota*> ps) { pelotas = ps; }
	Bala* getBala() { return bala; }
	void setBala(Bala* b) { bala = b; }
	Jugador* getJugador() { return jugador; }
	void setJugador(Jugador* j) { jugador = j; }
	//Render
	void render();
	//Update de movimiento
	void update(double dt);
	//Update de las colisiones
	void updatecolliders();
	//No se usa
	/*void addSolidos(Solido* e) {
		solidos.push_back(e);
	}*/
	//Metodos para añadir paredes y pelotas a los vectores
	void add(Pared* pa) {
		paredes.push_back(pa);
	}
	void add(Pelota* p) {
		pelotas.push_back(p);
	}
	//Interseccion entre la bala y las pelotas
	void intersectBalaPelota(Bala* b, Pelota* p);
	//Interseccion entre el jugador y las pelotas
	void intersectJugadorPelota(Jugador* j, Pelota* p);
};

#endif
