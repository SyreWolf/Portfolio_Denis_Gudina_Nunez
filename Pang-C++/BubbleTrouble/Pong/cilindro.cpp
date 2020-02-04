#include "cilindro.h"

Cilindro::Cilindro(float bp, float hp) {
	quadratic = gluNewQuadric();
	b = bp;
	h = hp;
}
Cilindro::~Cilindro()
{
}

void Cilindro::render() {
	glPushMatrix();
	glColor3f(this->getCol().getX(), this->getCol().getY(), this->getCol().getZ());
	glTranslatef(this->getPos().getX(), this->getPos().getY(), this->getPos().getZ());
	gluCylinder(quadratic, b, b, h, 16, 16);
	glPopMatrix();
}
