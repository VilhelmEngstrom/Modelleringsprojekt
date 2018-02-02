#pragma once
#include <iostream>

#include "dependencies/include/glfw3.h"



class Window{
    public:
        Window(const char* name, int width, int height);
        ~Window();

        // Returns whether the close button or the escape key has been triggered
        bool shouldClose() const;

        // Updates the window by clearing it and swapping buffers
        void update() const;

        // Clears window
        void clear() const;

    protected:
        GLFWwindow* m_window;
        int m_width, m_height;
        const char* m_title;

        // Initialize window
        void init();
};
