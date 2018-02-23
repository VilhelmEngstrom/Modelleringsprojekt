#include "Window.h"

graphics::Window::Window(const char* name, int width, int height) : m_Width(width), m_Height(height), m_Title(name){
    init();
}

graphics::Window::~Window() {
    glfwDestroyWindow(m_Window);
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

    // To fix compilation on OS X
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

    if(!m_Window){
        std::cout << "Could not initialize GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowSizeCallback(m_Window, windowResize);

    glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

}

bool graphics::Window::shouldClose() const{
    return glfwWindowShouldClose(m_Window) || glfwGetKey(m_Window, GLFW_KEY_ESCAPE);
}


void graphics::Window::clear() const{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void graphics::Window::cullBackFace() const{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void graphics::Window::update() const{
    // Ugly, shouldn't be called every frame...
    glfwGetWindowSize(m_Window, &m_Width, &m_Height);


    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

int graphics::Window::getWidth() const{
    return m_Width;
}

int graphics::Window::getHeight() const{
    return m_Height;
}

void graphics::windowResize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
