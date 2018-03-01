#pragma once
#include <vector>
#include "Bubble.h"
#include <cstdlib>


class BubbleSystem
{
public:
	BubbleSystem() {}
	~BubbleSystem() {}

	void addBubble(Sphere* s);
	std::vector<Bubble> myBubblyBubbles;
	int getNumberOfBubbles() { return nrOfBubbles; }

private:
	
	int nrOfBubbles = 0;
};

