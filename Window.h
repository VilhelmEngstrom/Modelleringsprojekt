#pragma once
#include <iostream>
#include "dependencies/include/glew.h"
#include "dependencies/include/glfw3.h"
#include "Vector.h"

#ifndef GL_DEBUG
#define GL_DEBUG 0
#endif
#if GL_DEBUG == 1
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif


namespace graphics{
    class Window{
        public:
            Window(const char* name, int width, int height);
            ~Window();

            // Returns whether the close button or the escape key has been triggered
            bool shouldClose() const;

            // Clear window
            void clear() const;

            // Cull back faces
            void cullBackFace() const;

            // Updates the window by clearing it and swapping buffers
            void update() const;

            // Get window pointer, for size adjustment
            GLFWwindow* getWindow() const;

			// check if keyinput is used
			Vector addKeyInput() const;

			bool spaceActive();

        protected:
            GLFWwindow* m_window;
            int m_width, m_height;
            const char* m_title;

            // Initialize window
            void init();
    };

    // For window resizing, cannot be class member
    void windowResize(GLFWwindow* window, int width, int height);
}
