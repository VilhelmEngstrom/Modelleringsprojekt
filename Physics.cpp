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

Vector Physics::get_position_delta(Vector& currentAcc, Vector& currentVelocity, float mass, const Vector drag, const Vector gravity, const Vector external)
{
	// Calculate total force
	Vector totalForce = drag + gravity + external;

	// beräkna accelerationen
	Vector acc = currentAcc + (totalForce * (1 / mass));

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

void Physics::makeItWobble(Mesh* mesh, float radius, float area,const Vector& force)
{
	
	float innerPressure = 4 * SURFACE_TENSION/ radius;
	
	Vertex* pointer = mesh->getVertices();
	for (int i = 0 ; i < mesh->getNumberOfVertices(); ++i)
	{
		Vector normal(pointer->normal);
		Vector appliedForce;
		normal = normal.normalized();

		if (force.angle(normal) < 0)
		{
			appliedForce = Vector(0);
		}
		else
		{
			appliedForce = force.angle(normal)*force;
			//std::cout << i << appliedForce;
		}
			
		float outsidePressure = appliedForce.length() / area;
		float newRadius = 4 * SURFACE_TENSION / (innerPressure - outsidePressure);
		float oldRadius = Vector(pointer->position).length();
		float scale = newRadius- oldRadius;
		
		
		Vector temp = Vector(pointer->position);
		temp = temp;
		pointer->position = temp.returnVec3();
		

		++pointer;
		
	}
}

// Vector3.Scale(-sign(currentVelocity), Vector3.Scale(currentVelocity, currentVelocity)) * airRes * Area * airdensity / 2;

