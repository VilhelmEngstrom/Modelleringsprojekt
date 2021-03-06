#pragma once
#include <iostream>
#include <iomanip>
#include <numeric>
#include <deque>
#include "dependencies/include/glfw3.h"

class Time{
	public:
		~Time();
		// Get time since last frame
		static float getDeltaTime();
		// Update the time
		static void update();

		// Prints the average FPS for the last 250 frames
		static void displayFPS();

		static float uptime();

		// Number of factors to take the mean of for FPS
		static const unsigned short MEAN_FACTORS;
		
		static const float START_TIME;
	private:
		Time();
		// Holds previous FPSs
		static std::deque<float> previousFPS;

		static float currentFrame, deltaTime, lastFrame;

};

