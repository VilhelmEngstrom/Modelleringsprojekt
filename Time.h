#pragma once
#include <iostream>
#include <numeric>
#include <deque>
#include "dependencies/include/glfw3.h"

class Time{
	public:
		~Time();
		

		static float getDeltaTime();
		static void update();

		static void displayFPS();

		static const unsigned short MEAN_FACTORS;
	private:
		Time();
		static std::deque<float> m_PreviousDeltas;

		static float m_CurrentFrame, m_DeltaTime, m_LastFrame;

};

