#include "cubo.h"
Cubo::~Cubo()
{
}
void Cubo::render() {
	glPushMatrix();
	glTranslatef(this->getPos().getX(), (*this).getPos().getY(), getPos().getZ());
	//glRotatef(t * 5, 0.0, 1.0, 0.0);
	glColor3f(getCol().getX(), getCol().getY(), getCol().getZ());
	glutSolidCube(s);
	glPopMatrix();
}
