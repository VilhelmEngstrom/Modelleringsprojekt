#include "BubbleSystem.h"





void BubbleSystem::addBubble(Sphere* s)
{
	
	float radius = (float)(rand() % 20 + 10) / 100;
	Vector pos = Vector((float)(rand() % 30 - 15)/10, 1.5f, (float)(rand() % 20 - 20) / 10);
	// Create and add bubble (avoid copying by using emplace instead of push)
	bubbles.emplace_front(Bubble(radius, s, pos));
}

void BubbleSystem::clean() {
	bubbles.remove_if([](const auto& bubble) {
		return !bubble.alive;
	});
}
