#include "Vector.h"

Vector::Vector(const Vector& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector::Vector(float d) {
	x = y = z = d;
}

Vector::Vector(Vec3 v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vec3 Vector::returnVec3()
{
	return { x,y,z };
}



Vector operator*(const Vector& v1, const Vector& v2) {

	return Vector(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}


float Vector::dotProduct(const Vector &v) const{
	return ((x*v.x) + (y*v.y) + (z*v.z));
}


float Vector::angle(const Vector& v) const
{
	return this->dotProduct(v) / (this->length()*v.length() );
} 

float Vector::length() const
{
	return sqrt(x * x + y * y + z * z);
}


Vector Vector::normalized()
{
return (1 / this->length() )*(*this);
} 

Vector Vector::crossProduct(const Vector& v) {


	float e1 = (y*v.z) - (z*v.y);
	float e2 = -((x*v.z) - (z*v.x));
	float e3 = (x*v.y) - (y*v.x);

	return Vector(e1, e2, e3);
}

Vector operator+(const Vector& v1, const Vector& v2) {

	return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector operator-(const Vector& v1, const Vector& v2) {

	return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}


Vector Vector::sign() const
{
	Vector newV(1.0, 1.0, 1.0);

	if (x < 0)
		newV.setX(-1.0);
	if (y < 0)
		newV.setY(-1.0);
	if (z < 0)
		newV.setZ(-1.0);

	return newV;
}


void Vector::setX(float d) {
	x = d;
}


void Vector::setY(float d) {
	y = d;
}

void Vector::setZ(float d) {
	z = d;
}

float Vector::getX() const {
	return x;
}

float Vector::getY() const {
	return y;
}

float Vector::getZ() const {

	return z;

}


std::ostream& operator<< (std::ostream& os, const Vector& v) {

	os << "Vector: [" << v.x << ", " << v.y << ", " << v.z << "]\n";

	return os;
}
