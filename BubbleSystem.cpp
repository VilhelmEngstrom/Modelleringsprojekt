#include "BubbleSystem.h"





void BubbleSystem::addBubble(Sphere* s)
{
	//srand(time(0)); //just seed the generator
	float radius = (rand() / (float)RAND_MAX * 0.15f) + 0.1f;
	Vector pos = Vector((rand() / (float)RAND_MAX * -2.0f) + 2.0f, 2.0f, (rand() / (float)RAND_MAX * -2.0f) + 2.0f);
	myBubblyBubbles.push_back(Bubble(radius, s, pos));
	++nrOfBubbles;
		
}
