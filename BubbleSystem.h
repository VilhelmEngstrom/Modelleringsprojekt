#pragma once
#include "Bubble.h"
#include <cstdlib>
#include <forward_list>


class BubbleSystem
{
public:
	BubbleSystem() {}
	~BubbleSystem() {}

	void addBubble(Sphere* s);

	// Remove "dead" bubbles
	void clean();

	std::forward_list<Bubble> bubbles;
};

