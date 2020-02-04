#include "vector3d.h"

Vector3D Vector3D::suma(Vector3D b) {
	Vector3D r;
	r.x = x + b.x;
	r.y = y + b.y;
	r.z = z + b.z;
	return r;
}
Vector3D Vector3D::operator+(Vector3D b) {
	Vector3D r;
	r.x = x + b.x;
	r.y = y + b.y;
	r.z = z + b.z;
	return r;
}
Vector3D Vector3D::resta(Vector3D b) {
	Vector3D r;
	r.x = x - b.x;
	r.y = y - b.y;
	r.z = z - b.z;
	return r;
}
Vector3D Vector3D::operator-(Vector3D b) {
	Vector3D r;
	r.x = x - b.x;
	r.y = y - b.y;
	r.z = z - b.z;
	return r;
}
Vector3D Vector3D::productoPorEscalar(double b) {
	Vector3D r;
	r.x = x * b;
	r.y = y * b;
	r.z = z * b;
	return r;
}
Vector3D Vector3D::operator*(double b) {
	Vector3D r;
	r.x = x * b;
	r.y = y * b;
	r.z = z * b;
	return r;
}
Vector3D Vector3D::operator/(double m) {
	Vector3D r;
	r.x = x / m;
	r.y = y / m;
	r.z = z / m;
	return r;
}
double Vector3D::productoEscalar(Vector3D v) {
	double r;
	r = x * v.x + y * v.y + z * v.z;
	return r;
}
double Vector3D::operator*(Vector3D v) {
	double r;
	r = x * v.x + y * v.y + z * v.z;
	return r;
}