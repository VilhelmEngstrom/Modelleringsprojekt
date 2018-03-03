#include "Time.h"


Time::Time() {}

Time::~Time() {}

float Time::getDeltaTime() {
	return deltaTime;
}

void Time::update() {
	currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Time::displayFPS() {
	std::cout << std::left << std::setw(4) << std::accumulate(previousFPS.begin(), previousFPS.end(), 0) / MEAN_FACTORS 
			  << std::setw(6) << " FPS" << "Uptime: " << uptime() << '\r' << std::flush;
	// Update previous FPSs
	previousFPS.push_front(1 / deltaTime);
	previousFPS.pop_back();
}


float Time::uptime() {
	return (float)glfwGetTime() - START_TIME;
}


float Time::currentFrame = 0.0f;
float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;

const unsigned short Time::MEAN_FACTORS = 250;
const float Time::START_TIME = (float)glfwGetTime();

std::deque<float> init() {
	std::deque<float> tmp;
	for (int i = 0; i < Time::MEAN_FACTORS; i++) {
		tmp.push_back(0.0f);
	}

	return tmp;
}
std::deque<float> Time::previousFPS(init());