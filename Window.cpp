#include "Window.h"


namespace graphics {

	Window& Window::getInstance(const std::string& name, int width, int height) {
		static Window instance(&name[0], width, height);
		return instance;
	}

	Window::Window(const char* name, int width, int height)
		: m_Width(width), m_Height(height), m_Title(name), m_CurrentFrame(0.0f), m_DeltaTime(0.0f), m_LastFrame(0.0f) {
		init();
	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}


	void Window::init() {
		if (!glfwInit()) {
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

		if (!m_Window) {
			std::cout << "Could not initialize GLFW window\n";
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);

		// Load OpenGL extensions
		glewExperimental = GL_TRUE;
		if (GLEW_OK != glewInit()) {
			std::cout << "Error initalizing glew\n";
			return;
		}

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);


		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);

	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(m_Window);
	}


	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::cullBackFace() const {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	void Window::processInput(Camera* camera) const {
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_Window, true);

		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::FORWARD, m_DeltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::BACKWARD, m_DeltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::LEFT, m_DeltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::RIGHT, m_DeltaTime);


	}

	Vector Window::addKeyInput() const{
		Vector force(0);
		if(glfwGetKey(m_Window, GLFW_KEY_UP))
			force.setY(1);
		if(glfwGetKey(m_Window, GLFW_KEY_RIGHT))
			force.setX(1);
		if(glfwGetKey(m_Window, GLFW_KEY_DOWN))
			force.setY(-1);
		if(glfwGetKey(m_Window, GLFW_KEY_LEFT))
			force.setX(-1);

		return force;
	}

	bool Window::spaceActive(){
		if(glfwGetKey(m_Window, GLFW_KEY_SPACE))
			return true;

		return false;
	}

	void Window::update() const {

		m_CurrentFrame = (float)glfwGetTime();
		m_DeltaTime = m_CurrentFrame - m_LastFrame;
		m_LastFrame = m_CurrentFrame;

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	int Window::getWidth() const {
		return m_Width;
	}

	int Window::getHeight() const {
		return m_Height;
	}

	void Window::enableBlend() const {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::disableBlend() const {
		glDisable(GL_BLEND);
	}

	void Window::window_resize(GLFWwindow* window, int width, int height) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
		glViewport(0, 0, width, height);
	}

}
