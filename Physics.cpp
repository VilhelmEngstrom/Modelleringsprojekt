#include "Physics.h"


const float Physics::GRAVITY = -9.82;
const float Physics::AIR_DENSITY = 1.225;
const float Physics::AIR_RESISTANCE = 0.47;

const float Physics::SURFACE_TENSION = 0.025f;

Physics::Physics()
{
}


Physics::~Physics()
{
}

Vector Physics::calculate_drag_force(Vector velocity, float area)
{
	return ( (-1)*velocity.sign()*velocity*velocity*AIR_DENSITY*AIR_RESISTANCE*area*(0.5) );

}

Vector Physics::calculate_gravity_force(float mass)
{
	return Vector(0, mass*GRAVITY ,0);

}


// Vector3.Scale(-sign(currentVelocity), Vector3.Scale(currentVelocity, currentVelocity)) * airRes * Area * airdensity / 2;