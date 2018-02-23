#pragma once
#pragma once
#include <iostream>
#include <cmath>
#include <math.h> 

#ifndef VEC3_H
#define VEC3_H

struct Vec3 {
	float x, y, z;
};

#endif

class Vector {
public:
	Vector()
		:x(0), y(0), z(0) {}
	Vector(float inX, float inY, float inZ)
		:x(inX), y(inY), z(inZ) {}
	Vector(const Vector& v);
	Vector(float d);
	Vector(Vec3 v);
	Vec3 returnVec3();

	//elementwise multiplication
	friend Vector operator*(const Vector& v1, const Vector& v2);

	// plus
	friend Vector operator+(const Vector& v1, const Vector& v2);

	// minus
	friend Vector operator-(const Vector& v1, const Vector& v2);

	//dot product
	float dotProduct(const Vector& v) const;

	float angle(const Vector& v) const;

	float length() const ;

	Vector normalized();

	//cross product
	Vector crossProduct(const Vector& v);

	// sign of vector
	Vector sign();

	//set variables
	void setX(float d);
	void setY(float d);
	void setZ(float d);

	float getX() const;
	float getY() const;
	float getZ() const;

private:
	float x, y, z;
	friend std::ostream& operator<< (std::ostream& os, const Vector& v);

};



