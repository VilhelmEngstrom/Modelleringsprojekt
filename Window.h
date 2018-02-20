#pragma once
#include <iostream>
#if defined _WIN32 || defined _WIN64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif
#include "dependencies/include/glew.h"
#include "dependencies/include/glfw3.h"

#ifndef WINDOW_H
#define WINDOW_H
namespace graphics{

    class Window{
        public:
            Window(const char* name, int width, int height);
            Window(const Window&) = delete;
            ~Window();

            Window operator=(const Window&) = delete;

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

        private:
            GLFWwindow* m_window;
            int m_width, m_height;
            const char* m_title;

            // Initialize window
            void init();
    };


    // For window resizing, cannot be class member
    void windowResize(GLFWwindow* window, int width, int height);

}
#endif
