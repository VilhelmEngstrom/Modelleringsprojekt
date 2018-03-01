#pragma once
#include <iostream>
#include <string>
#if defined _WIN32 || defined _WIN64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif
#include "dependencies/include/glew.h"
#include "dependencies/include/glfw3.h"

#include "Camera.h"
#include "Vector.h"

#ifndef WINDOW_H
#define WINDOW_H
namespace graphics{
    class Window{
        public:
			static Window& getInstance(const std::string& name, int width, int height);

            Window(const Window&) = delete;
            ~Window();

            Window operator=(const Window&) = delete;

            // Returns whether the close button or the escape key has been triggered
            bool shouldClose() const;

            // Clear window
            void clear() const;

            // Cull back faces
            void cullBackFace() const;

            void processInput(Camera* camera) const;

            // check if keyinput is used
            Vector addKeyInput() const;

            bool spaceActive();

            // Updates the window by clearing it and swapping buffers
            void update() const;

            int getWidth() const;
            int getHeight() const;

        private:
            GLFWwindow* m_Window;
            int m_Width, m_Height;
            const char* m_Title;

            mutable float m_CurrentFrame, m_DeltaTime, m_LastFrame;

            Window(const char* name, int width, int height);

            // Initialize window
            void init();

			static void window_resize(GLFWwindow* window, int width, int height);
    };




}
#endif
