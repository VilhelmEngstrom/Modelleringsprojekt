#include "Window.h"

graphics::Window::Window(const char* name, int width, int height)
: m_Width(width), m_Height(height), m_Title(name), m_CurrentFrame(0.0f), m_DeltaTime(0.0f), m_LastFrame(0.0f){
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
    return glfwWindowShouldClose(m_Window);
}


void graphics::Window::clear() const{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void graphics::Window::cullBackFace() const{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void graphics::Window::processInput(Camera* camera) const{
    if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);

    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboardInput(CameraMovement::FORWARD, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboardInput(CameraMovement::BACKWARD, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboardInput(CameraMovement::LEFT,m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboardInput(CameraMovement::RIGHT, m_DeltaTime);


}

void graphics::Window::update() const{
    // Ugly, shouldn't be called every frame...
    glfwGetWindowSize(m_Window, &m_Width, &m_Height);

    m_CurrentFrame = glfwGetTime();
    m_DeltaTime = m_CurrentFrame - m_LastFrame;
    m_LastFrame = m_CurrentFrame;

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
