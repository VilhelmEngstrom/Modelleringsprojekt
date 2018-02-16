#include "Physics.h"


const float Physics::GRAVITY = -9.82f;
const float Physics::AIR_DENSITY = 1.225f;
const float Physics::AIR_RESISTANCE = 0.47f;

const float Physics::SURFACE_TENSION = 0.025f;

const float Physics::STEP = 0.002f;



Vector Physics::calculate_drag_force(Vector velocity, float area)
{
	return ((-1)*velocity.sign()*velocity*velocity*AIR_DENSITY*AIR_RESISTANCE*area*(0.5));

}

Vector Physics::calculate_gravity_force(float mass)
{
	return Vector(0, mass*GRAVITY, 0);

}

Vector Physics::get_position_delta(Vector& currentVelocity, float mass, const Vector drag, const Vector gravity, const Vector external)
{
	// Calculate total force
	Vector totalForce = drag + gravity + external;

	// beräkna accelerationen
	Vector acc = totalForce * (1 / mass);

	currentVelocity = currentVelocity + acc * STEP; // beräkna ny hastighet
	Vector delta = currentVelocity * STEP; // Beräkna skillnad i position	
	return delta;

}

// returns the effect off the force vector
Vector Physics::wind_effect_on_vertex(Vector vertexNormal, Vector windForce)
{
	vertexNormal.dotProduct(windForce);
	return vertexNormal;

}


// Vector3.Scale(-sign(currentVelocity), Vector3.Scale(currentVelocity, currentVelocity)) * airRes * Area * airdensity / 2;

