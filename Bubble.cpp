#include "Bubble.h"



Bubble::~Bubble()
{
}

void Bubble::killBubble(double& xpos, double& ypos)
{
	

	if (xpos < (position + radius).getX() && xpos >(position - radius).getX() && ypos >(position - radius).getY() && ypos < (position + radius).getY())
		alive = false;
}

void Bubble::update(const Vector& externalForce)
{
	if (alive)
	{
		if (lifetime < life++)
			alive = false;
		else {
			gravity = Physics::calculate_gravity_force(mass);
			drag = Physics::calculate_drag_force(currentVelocity, area);
			noise = Physics::addNoice(position);
			external = Physics::addWind(externalForce, position);
			Vector bla(mass * 3 * sin(20 * position.getY()), abs(5 * mass*sin(20 * position.getY())), 0);

			totalForce = gravity + drag + external + noise + bla;
			//Physics::makeItWobble(sphere , radius , area, totalForce);

			position = position + Physics::getPositionDelta(currentAcc, currentVelocity, mass, totalForce);
		}


	}

}
