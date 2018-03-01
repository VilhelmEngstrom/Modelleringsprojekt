#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Physics.h"
class Bubble
{
public:

	Bubble(float r, Sphere* s, Vector pos = Vector(0))
		:position(pos), radius(r), sphere(s), currentVelocity(0), currentAcc(0) {
		mass =  M_PI * radius * radius * Physics::THICKNESS;
		area = r*r*3.14f;
		
		lifetime = rand() % 20000 + 60000;
		
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

		Vector gravity = Vector(0);
		Vector drag = Vector(0);
		Vector noise = Vector(0);
		Vector external = Vector(0);
		Vector totalForce = Vector(0);
		bool alive = true;
		int life = 0;
		int lifetime;


};

