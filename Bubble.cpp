#include "Bubble.h"



Bubble::~Bubble()
{
}

void Bubble::update()
{
	Vector gravity = Physics::calculate_gravity_force(mass);
	Vector drag = Physics::calculate_drag_force(currentVelocity, area);
	position = position + Physics::get_position_delta(currentVelocity, mass, drag, gravity);
}