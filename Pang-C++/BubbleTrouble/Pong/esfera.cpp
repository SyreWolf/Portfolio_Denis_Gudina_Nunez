#include "esfera.h"

Esfera::~Esfera()
{
}
void Esfera::render() {
	glPushMatrix();
	glTranslatef(this->getPos().getX(), (*this).getPos().getY(), getPos().getZ());
	//glRotatef(t * 5, 0.0, 1.0, 0.0);
	glColor3f(getCol().getX(), getCol().getY(), getCol().getZ());
	glutSolidSphere(r,10,10);
	glPopMatrix();
}
