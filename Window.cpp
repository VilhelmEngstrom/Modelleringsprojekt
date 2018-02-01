#include "Window.h"

void windowResize(GLFWwindow* window, int width, int height);

Window::Window(const char* name, int width, int height) : m_width(width), m_height(height), m_title(name){
    init();
}

Window::~Window() {
    glfwTerminate();
}


void Window::init(){
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW\n";
        return;
    }

    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

    if(!m_window){
        std::cout << "Could not initialize GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowSizeCallback(m_window, windowResize);

}

bool Window::closed() const{
    return glfwWindowShouldClose(m_window);
}

void Window::update() const{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}


void windowResize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
