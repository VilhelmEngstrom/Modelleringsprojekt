#include "Window.h"

graphics::Window::Window(const char* name, int width, int height) : m_width(width), m_height(height), m_title(name){
    init();
}

graphics::Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}


void graphics::Window::init(){
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW\n";
        return;
    }

    // OpenGL 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

    if(!m_window){
        std::cout << "Could not initialize GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowSizeCallback(m_window, windowResize);

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

}

bool graphics::Window::shouldClose() const{
    return glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE);
}


void graphics::Window::clear() const{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void graphics::Window::cullBackFace() const{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void graphics::Window::update() const{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void graphics::windowResize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);

}
