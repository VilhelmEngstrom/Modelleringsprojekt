#pragma once

#include "Vector.h"

class Physics
{
public:

	// World properties
	static const float GRAVITY;
	static const float AIR_DENSITY; // luftdensitet ( density of the fluid )
	static const float AIR_RESISTANCE; // luftmotståndskonstant ( drag coeff )

	// Bubble properties
	static const float SURFACE_TENSION; // surface tension

	// Step size
	static const float STEP; 

	Physics();
	~Physics();

	Vector calculate_drag_force(Vector velocity, float area );
	Vector calculate_gravity_force(float mass);
	Vector get_position_delta(Vector& currentVelocity, float mass, const Vector drag, const Vector gravity, const Vector external = Vector(0));
	Vector wind_effect_on_vertex(Vector vertexNormal, Vector windForce);
};

