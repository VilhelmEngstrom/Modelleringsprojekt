#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Physics.h"
class Bubble
{
public:

	Bubble(float m, Sphere* s, Vector pos = Vector(0))
		:mass(m), position(pos), sphere(s), currentVelocity(0) {
		area = s->getRadius()*s->getRadius()*3.14f;
	}
	~Bubble();

	void update();
	Vector get_pos() const { return position; }


private:
		float mass;
		Vector position;
		Sphere* sphere;
		Vector currentVelocity;
		float area;
		


};

