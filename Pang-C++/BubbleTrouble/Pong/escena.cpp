#include "escena.h"
//Constructor
Escena::Escena()
{
}
//Destructor de la escena que limpia todas las variables
Escena::~Escena()
{
	delete jugador;
	delete bala;
	for (Pared* pa : paredes)
		delete pa;
	paredes.resize(0);

	for (Pelota* p : pelotas)
		delete p;
	pelotas.resize(0);
}
//Render de las variables de escena
void Escena::render() {
	/*for (int i = 0; i < cubos.size(); i++) {
		//(*cubos[i]).render();
		cubos[i]->render();
	}
	for (Esfera* e : esferas) {
		e->render();
	}
	for (Cilindro* c : cilindros) c->render();*/
	jugador->render();
	bala->render();
	for (Pared* pa : paredes)
		pa->render();
	for (Pelota* p : pelotas)
		p->render();

}
/*Update, comprueba primero las colisiones y luego
hace un update de la posicion de los objetos*/
void Escena::update(double dt) {
	updatecolliders();
	bala->update(dt);
	if (bala->isHit()) {
		bala->setPos(Vector3D(0, -20, 0));
		bala->setCol(Vector3D(0, 0, 0));
		bala->setVel(Vector3D(0, 0, 0));
		bala->setMoving(false);
		bala->setHit(false);
	}
	for (Pelota* p : pelotas) {
		p->update(dt);
	}
	/*for (Solido* s : solidos) {
		s->update(dt);
	}*/
}
/*Comprueba si la bala colisiona con la pelota,
teniendo en cuenta si la suma entre los radios es mayor
o menor que la distancia actual entre ellos. Si es menor
han chocado, si no, no han chocado. Si chocan se crean dos
pelotas nuevas en caso de que el nivel sea mayor que 1
y se indica las colisiones*/
void Escena::intersectBalaPelota(Bala* b, Pelota* p) {
	if ((b->getR() + p->getR()) >= (sqrt(pow((b->getPos()).getX() - (p->getPos()).getX(), 2) + pow((b->getPos()).getY() - (p->getPos()).getY(), 2)))) {
		if (p->getLevel() > 1) {
			Pelota* r = new Pelota();
			r->setPos(Vector3D(p->getPos().getX() + 1.5, p->getPos().getY(), 0));
			r->setLevel(p->getLevel() - 1);
			r->setCol(Vector3D(1, 0, 1));
			r->setF(Vector3D(0, -0.98, 0));
			r->setF(Vector3D(0, -0.98, 0));
			r->setR(p->getR()-0.25);
			r->setVel(Vector3D(1, 0, 0));
			r->setHit(false);
			r->setType("pelota");
			add(r);

			r = new Pelota();
			r->setPos(Vector3D(p->getPos().getX() - 1.5, p->getPos().getY(), 0));
			r->setLevel(p->getLevel() - 1);
			r->setCol(Vector3D(0, 1, 1));
			r->setF(Vector3D(0, -0.98, 0));
			r->setF(Vector3D(0, -0.98, 0));
			r->setR(p->getR() - 0.25);
			r->setVel(Vector3D(-1, 0, 0));
			r->setHit(false);
			r->setType("pelota");
			add(r);


			b->setHit(true);
			p->setHit(true);
		}
		else {

			b->setHit(true);
			p->setHit(true);
		}
	}
}

/*Comprueba si el jugador colisiona con la pelota,
teniendo en cuenta si la suma entre bounding box del 
jugador y el radio de la pelota es mayor o menor que 
la distancia actual entre ellos. Si es menor han chocado, 
si no, no han chocado. Si chocan se indican las colisiones*/
void Escena::intersectJugadorPelota(Jugador* j, Pelota* p) {
	if (j->isHit()) {
		if (((j->getS() + (j->getS() / 3)) + p->getR()) >= (sqrt(pow((j->getPos()).getX() - (p->getPos()).getX(), 2) + pow((j->getPos()).getY() - (p->getPos()).getY(), 2)))) {
			j->setHit(false);
		}
	}
	else {
		if (((j->getS() + (j->getS() / 3)) + p->getR()) >= (sqrt(pow((j->getPos()).getX() - (p->getPos()).getX(), 2) + pow((j->getPos()).getY() - (p->getPos()).getY(), 2)))) {
			j->setHit(true);
		}
	}

}

/*Se utilizan los metodos de colision implementados
para comprobar con todas las colisiones de las pelotas*/
void Escena::updatecolliders() {
	for (int i = 0; i < pelotas.size(); i++) {
		intersectBalaPelota(bala, pelotas[i]);
		intersectJugadorPelota(jugador, pelotas[i]);
		if (pelotas[i]->isHit()) {
			//Sonido para la eliminacion de las pelotas
			PlaySound(TEXT("Explosion.wav"), NULL, SND_ASYNC);
			jugador->setScore(jugador->getScore() + 100);
			delete pelotas[i];
			pelotas.erase(pelotas.begin() + i);
			cout << pelotas.size() << " pelotas en juego\n" << endl;
		}    
		if (jugador->isHit()) {
			jugador->setMuerto(true);
		}
	}
}