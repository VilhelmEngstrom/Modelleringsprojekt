#include "Time.h"


Time::Time() {}

Time::~Time() {}

float Time::getDeltaTime() {
	return m_DeltaTime;
}

void Time::update() {
	// Update time
	m_CurrentFrame = (float)glfwGetTime();
	m_DeltaTime = m_CurrentFrame - m_LastFrame;
	m_LastFrame = m_CurrentFrame;
	
	
	m_PreviousDeltas.push_front(1 / m_DeltaTime);
	m_PreviousDeltas.pop_back();
}

void Time::displayFPS() {
	std::cout << std::accumulate(m_PreviousDeltas.begin(), m_PreviousDeltas.end(), 0) / MEAN_FACTORS << " fps" << '\r' << std::flush;
}


float Time::m_CurrentFrame = 0.0f;
float Time::m_DeltaTime = 0.0f;
float Time::m_LastFrame = 0.0f;

const unsigned short Time::MEAN_FACTORS = 500;

std::deque<float> init() {
	std::deque<float> tmp;
	for (int i = 0; i < Time::MEAN_FACTORS; i++) {
		tmp.push_back(0.0f);
	}

	return tmp;
}
std::deque<float> Time::m_PreviousDeltas(init());