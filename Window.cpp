#include "Window.h"

// For window resizing, cannot be class member
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

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

}

bool Window::shouldClose() const{
    return glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE);
}

void Window::clear() const{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() const{
    clear();
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}


void windowResize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
