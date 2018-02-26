#include "BubbleSystem.h"





void BubbleSystem::addBubble(Sphere* s)
{
	float radius = (rand() / (float)RAND_MAX * 0.2) + 0.1;
	Vector pos = Vector((rand() / (float)RAND_MAX * -1) + 1, 3, (rand() / (float)RAND_MAX * -1) + 1);
	
	myBubblyBubbles.push_back(Bubble(radius, s, pos));
	++nrOfBubbles;
		
}
