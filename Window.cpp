#include "Window.h"


namespace graphics {

	Window& Window::getInstance(const std::string& name, int width, int height) {
		static Window instance(&name[0], width, height);
		return instance;
	}

	Window::Window(const char* name, int width, int height)
		: m_Width(width), m_Height(height), m_Title(name){
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

		glEnable(GL_DEPTH_TEST);


	}

	
	

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(m_Window);
	}


	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::enableBackfaceCulling() const {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	void Window::disableBackfaceCulling() const {
		glDisable(GL_CULL_FACE);
	}

	void Window::processInput(Camera* camera) const {
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_Window, true);

		float deltaTime = Time::getDeltaTime();

		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::FORWARD, deltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::BACKWARD, deltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::LEFT, deltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			camera->processKeyboardInput(CameraMovement::RIGHT, deltaTime);


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

	bool Window::mousePress(double& xpos, double& ypos){

		if (GLFW_PRESS == glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT)){
			glfwGetCursorPos(m_Window, &xpos, &ypos);
			xpos = (xpos - m_Width / 2)* 5/m_Width;
			ypos = (ypos - m_Height / 2)* -3/m_Height ;
			return true;
		}
		
		return false;
	}

	bool Window::isPressed(int keycode){	
		if (MAX_KEYS <= keycode) {
			std::cout << "Unknown key pressed\n";
			return false;
		}
		
		int newState = glfwGetKey(m_Window, keycode);
		bool isPressed = false;

		if (GLFW_RELEASE == newState && GLFW_PRESS == keyStates[keycode])
			isPressed = true;
		
		keyStates[keycode] = newState;

		return isPressed;
	}

	void Window::update() const {
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

	int Window::keyStates[MAX_KEYS] = { GLFW_RELEASE };

	
}