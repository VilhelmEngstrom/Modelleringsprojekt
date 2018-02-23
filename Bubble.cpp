#include "Bubble.h"



Bubble::~Bubble()
{
}

void Bubble::update(const Vector& externalForce)
{
	Vector gravity = Physics::calculate_gravity_force(mass);
	Vector drag = Physics::calculate_drag_force(currentVelocity, area);
	Vector external = externalForce * mass * 100;
	Vector totalForce = gravity + drag + external;
	Physics::makeItWobble(sphere , radius , area, totalForce);
	position = position + Physics::get_position_delta(currentAcc, currentVelocity, mass, drag, gravity,external);
	
}