#pragma once
#include <iostream>

#include "dependencies/include/glfw3.h"



class Window{
    public:
        Window(const char* name, int width, int height);
        ~Window();

        // Returns whether the close button has been clicked
        bool closed() const;

        // Updates the window by clearing it and swapping buffers
        void update() const;

    protected:
        GLFWwindow* m_window;
        int m_width, m_height;
        const char* m_title;

        void init();
};
