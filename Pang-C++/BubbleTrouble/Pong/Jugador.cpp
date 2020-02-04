#include "Jugador.h"
//Destructor Jugador
Jugador::~Jugador()
{
}
//Render Jugador
void Jugador::render() {
	glPushMatrix();
	glTranslatef(this->getPos().getX(), this->getPos().getY(), this->getPos().getZ());
	//glRotatef(t * 5, 0.0, 1.0, 0.0);
	glColor3f(getCol().getX(), getCol().getY(), getCol().getZ());
	glutSolidCube(s);
	glPopMatrix();
}
