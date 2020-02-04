//#pragma once
#ifndef VECTOR3D__
#define VECTOR3D__
#include <iostream>

using namespace std;

class Vector3D {
private:
	double x, y, z;
public:
	//Vector3D():x(0),y(0),z(0) {}
	Vector3D(double px=0, double y=0, double z = 0) :x(px), y(y), z(z) {}
	//Vector3D() :x(0), y(0), z(0) {}
	//Vector3D(double px) :x(px), y(0), z(0) {}
	//Vector3D(double px, double y) :x(px), y(y), z(0) {}
	//Vector3D(double px, double y, double z) :x(px), y(y), z(z) {}
	inline double getX() {return x;}
	inline double getY() {return y;}
	inline double getZ() {return z;}
	inline void setX(double d) { x = d; }
	inline void setY(double d) { y = d; }
	inline void setZ(double d) { z = d;	}
	Vector3D suma(Vector3D b);
	Vector3D operator+(Vector3D b);
	Vector3D operator-(Vector3D b);
	Vector3D resta(Vector3D b);
	Vector3D productoPorEscalar(double b);
	Vector3D operator*(double b);
	Vector3D operator/(double b);
	double productoEscalar(Vector3D v);
	double operator*(Vector3D v);
	friend ostream &operator<<(ostream &os, const Vector3D &v);
};
inline ostream &operator<<(ostream &os, const Vector3D &v) {
	os << v.x << "," << v.y << "," << v.z;
	return os;
}
#endif // !VECTOR3D__
