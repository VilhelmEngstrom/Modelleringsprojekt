#pragma once

#include "Vector.h"
#include "Mesh.h"

#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
	float s, t;
};

#endif

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex {
	Vec3 position;
	Vec3 normal;
	Vec2 texCoords;
};

#endif

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

	

	static Vector calculate_drag_force(Vector velocity, float area);
	static Vector calculate_gravity_force(float mass);
	static Vector get_position_delta(Vector& currentAcc, Vector& currentVelocity, float mass, const Vector drag, const Vector gravity, const Vector external = Vector(0));
	static Vector wind_effect_on_vertex(Vector vertexNormal, Vector windForce);
	static void makeItWobble(Mesh* mesh,float radius, float area, const Vector& force);

private:
		Physics() {}
		~Physics() {}
};




