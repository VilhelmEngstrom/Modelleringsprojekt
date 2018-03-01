#include "BubbleSystem.h"





void BubbleSystem::addBubble(Sphere* s)
{
	
	float radius = (float)(rand() % 20 + 10) / 100;
	Vector pos = Vector((float)(rand() % 30 - 15)/10, 1.5f, (float)(rand() % 20 - 20) / 10);
	myBubblyBubbles.push_back(Bubble(radius, s, pos));
	++nrOfBubbles;
		
}
