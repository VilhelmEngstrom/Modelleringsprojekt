#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Physics.h"
class Bubble
{
public:

	Bubble(float m,float r, Sphere* s, Vector pos = Vector(0))
		:mass(m), position(pos), radius(r), sphere(s), currentVelocity(0), currentAcc(0) {
		area = r*r*3.14f;
	}
	~Bubble();

	void update(const Vector& externalForce);
	Vector getPos() const { return position; }
	float getRadius() const { return radius; }

	
	

private:
		float mass;
		Vector position;
		float radius;
		Vector currentVelocity;
		Vector currentAcc;
		float area;
		Sphere* sphere;
		


};

