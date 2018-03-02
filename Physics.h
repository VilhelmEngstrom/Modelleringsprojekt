#pragma once

#include <cmath>
#include <ctime>
#include "Vector.h"
#include "Mesh.h"
#include "Window.h"

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
	static const float THICKNESS;
									   // Bubble properties
	static const float SURFACE_TENSION; // surface tension

										// Step size
	static const float STEP;

	

	static Vector calculate_drag_force(Vector velocity, float area);
	static Vector calculate_gravity_force(float mass);
	static Vector getPositionDelta(Vector& currentAcc, Vector& currentVelocity, float mass, const Vector& totalForce);
	static Vector wind_effect_on_vertex(Vector vertexNormal, Vector windForce);
	static void makeItWobble(Mesh* mesh,float radius, float area, const Vector& force);
	static Vector addNoice(Vector& position);
	static Vector addWind(const Vector& external,const Vector& position);

private:
		Physics() {}
		~Physics() {}
};




