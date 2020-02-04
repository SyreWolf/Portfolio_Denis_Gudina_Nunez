#include "solido.h"
void Solido::update(double dt) {
	/*Si el tipo del objeto comprobado 
	es pelota realiza los movimiento de
	rebote de la pelota entre las posiciones 
	determinadas de anchura y altura del mapa*/
	if (type == "pelota") {
		pos = pos + vel * dt;
		Vector3D a = f / m;
		vel = vel + a * dt;

		if (pos.getX() > 14 || pos.getX() < -14) {
			double d = vel.getX()*-1;
			vel.setX(d);
		}
		if (pos.getY() < 1 || pos.getY() >= 18) {
			double d = vel.getY()*-1;
			vel.setY(d);
		}
	}
	/*Si el tipo del objeto comprobado
	es bala realiza un movimiento uniforme
	en la direccion de la coordenada y hasta
	la altura predeterminada para el mapa*/
	else if (type == "bala") {
		pos = pos + vel * dt;

		if (pos.getY() >= 18) {
			hit = true;
		}
	}
}
