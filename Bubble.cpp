#include "Bubble.h"



Bubble::~Bubble()
{
}

void Bubble::update(const Vector& externalForce)
{
	if (alive)
	{
		gravity = Physics::calculate_gravity_force(mass);
		drag = Physics::calculate_drag_force(currentVelocity, area);
		//noise = Physics::addNoice(position);
		external = Physics::addWind(externalForce, position);
		Vector bla(mass*3*sin(20 * position.getY()), abs(5*mass*sin(20 * position.getY())), 0);
		
		totalForce = gravity + drag + external + noise + bla;
		//Physics::makeItWobble(sphere , radius , area, totalForce);

		position = position + Physics::getPositionDelta(currentAcc, currentVelocity, mass, totalForce);
		
		++life; // Uppdatera livstiden
		if (life > lifetime)
			alive = false;
	}
	
}