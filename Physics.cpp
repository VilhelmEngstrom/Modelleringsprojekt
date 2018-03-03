#include "Physics.h"


const float Physics::GRAVITY = -9.82f;
const float Physics::AIR_DENSITY = 1.225f;
const float Physics::AIR_RESISTANCE = 0.47f;
const float Physics::THICKNESS = 0.00006f;

const float Physics::SURFACE_TENSION = 0.025f;

const float Physics::STEP = 0.001f;

float Physics::realtime = 0.0f;



Vector Physics::calculate_drag_force(const Vector& velocity, float area)
{

	return ((-1)*velocity.sign()*velocity*velocity*AIR_DENSITY*AIR_RESISTANCE*area*(0.5));


}

Vector Physics::calculate_gravity_force(float mass)
{
	return Vector(0, mass*GRAVITY, 0);

}

Vector Physics::getPositionDelta(const Vector& currentAcc, Vector& currentVelocity, float mass, const Vector& totalForce)
{

	// ber�kna accelerationen
	Vector acc = currentAcc + (totalForce * (1 / mass));

	currentVelocity = currentVelocity + acc * STEP; // ber�kna ny hastighet

	
	Vector delta = currentVelocity * STEP; // Ber�kna skillnad i position
	return delta;

}

// Vad gör den här metoden?
// returns the effect off the force vector
Vector Physics::wind_effect_on_vertex(const Vector& vertexNormal, const Vector& windForce)
{
	vertexNormal.dotProduct(windForce);
	return vertexNormal;

}

void Physics::makeItWobble(Mesh* mesh, float radius, float area, const Vector& force)
{

	float innerPressure = 4 * SURFACE_TENSION/ radius;

	Vertex* pointer = mesh->getVertices();
	for (int i = 0 ; i < (int)mesh->getNumberOfVertices(); ++i)
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

Vector Physics::addNoice(const Vector& position)
{
	float a = -3.00f;
	float b = -3.00f;
	float c = 1.48f;
	float d = -0.27f;
	float e = 1.00f;
	float f = 1.00f;

	float i = a * position.getX() + b * position.getY();
	float j = c * position.getX() + d * position.getY();
	float k = e * position.getX() + f * position.getY();

	Vector vectorField = Vector(i, j, k);

	float scaling = 0.000001f;
	return scaling * vectorField;
}



Vector Physics::addWind(const Vector& external, const Vector& position)
{
	Vector wind(external.getX() / (1 + abs(-2*external.getX() - position.getX())), external.getY() / (1 + abs(-2*external.getY() - position.getY())), 0);
	wind = wind * 0.0005f;
	return wind;
}
