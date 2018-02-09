#include "Physics.h"


const float Physics::GRAVITY = -9.82;
const float Physics::AIR_DENSITY = 1.225;
const float Physics::AIR_RESISTANCE = 0.47;

const float Physics::SURFACE_TENSION = 0.025;

const float Physics::STEP = 0.002;

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

Vector Physics::get_position_delta( Vector& currentVelocity, float mass, const Vector drag, const Vector gravity, const Vector external = Vector(0) )
{
	// Calculate total force
	Vector totalForce = drag + gravity + external;

	// beräkna accelerationen
	Vector acc = totalForce*(1/mass); 

	currentVelocity = currentVelocity + acc * STEP; // beräkna ny hastighet
	Vector delta = currentVelocity * STEP + (acc*STEP*STEP) / 2; // Beräkna skillnad i position											
	
}

// returns the effect off the force vector
Vector Physics::wind_effect_on_vertex(Vector vertexNormal, Vector windForce)
{
	vertexNormal.dotProduct(windForce);

}


Vector Physics::get_new_radius(const float mass, const float innerpressure, const float area, const Vector force)
{
	float pressure = force.length * (1 / mass);
	Vector new_radius = 4 * SURFACE_TENSION * 1/(innerpressure - pressure);
}