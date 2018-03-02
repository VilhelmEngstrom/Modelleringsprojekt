#include "Time.h"


Time::Time() {}

Time::~Time() {}

float Time::getDeltaTime() {
	return deltaTime;
}

void Time::update() {
	// Update time
	currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
	
	previousFPS.push_front(1 / deltaTime);
	previousFPS.pop_back();
}

void Time::displayFPS() {
	std::cout << std::left << std::setw(4) << std::accumulate(previousFPS.begin(), previousFPS.end(), 0) / MEAN_FACTORS 
			  << " fps" << '\r' << std::flush;
}


float Time::currentFrame = 0.0f;
float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;

const unsigned short Time::MEAN_FACTORS = 400;

std::deque<float> init() {
	std::deque<float> tmp;
	for (int i = 0; i < Time::MEAN_FACTORS; i++) {
		tmp.push_back(0.0f);
	}

	return tmp;
}
std::deque<float> Time::previousFPS(init());