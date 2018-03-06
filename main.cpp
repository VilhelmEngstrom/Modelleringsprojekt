#include <iostream>
#include "Window.h"
#include "Mesh.h"
#include "Sphere.h"
#include "MatrixStack.h"
#include "Shader.h"
#include "CubemapTexture.h"
#include "Camera.h"
#include "Skybox.h"
#include "Bubble.h"
#include "BubbleSystem.h"
#include "Time.h"


// glm
#include "dependencies/include/glm/glm.hpp"
#include "dependencies/include/glm/gtc/matrix_transform.hpp"
#include "dependencies/include/glm/gtc/type_ptr.hpp"



#ifdef RELEASE_BUILD_WINDOWS
#include <windows.h>
#endif


int main(int argc, char** argv) {
	#ifdef RELEASE_BUILD_WINDOWS

	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

	#endif

	using namespace graphics;

	// ***************
	// Window & camera
	// ***************

	// Create the window, this must be done thorugh getInstance as the class
	// uses the singleton design pattern (all ctors are either private or deleted)
	Window& win = Window::getInstance("Soap Bubbles", 960, 540);
	// Enable blending for transparency
	win.enableBlend();

	// Create a camera and place it in the scene
	Camera camera(glm::vec3(0.0f, 0.0f, -10.0f));

	// ********************
	//    Skybox setup
	// ********************

	// Path to folder containing skybox images
	std::string location = "resources/textures/skybox/";
	// Skybox images
	std::array<std::string, 6> faces = { location + "posx.jpg", location + "negx.jpg", location + "posy.jpg",
		location + "negy.jpg", location + "posz.jpg", location + "negz.jpg" };
	// Create the skybox texture
	CubemapTexture tex(faces);
	// Create skybox, passing its texture
	Skybox skybox(tex);

	Shader skyboxShader("resources/shaders/skybox.glsl");

	// Pass uniform to skybox shader
	skyboxShader.use();
	skyboxShader.passScalar("skybox", 0);





	// *************
	//    Sphere
	// *************

	// Create sphere
	Sphere sphere(1.0f, 30);
	Shader sphereShader("resources/shaders/bubble.glsl");


	sphereShader.use();

	// Pass fresnel values to the sphere's shader
	//									    power scale bias
	sphereShader.passVec3("fresnelValues", {2.0f, 2.0f, 0.1f});

	// Color ratios for refraction
	// Refraction ratio for soapy water
	float refractionRatio = 1.0f / 1.34f;
	// Values in vector correspond to rgb. Results are best when values are between 0 and 1
	sphereShader.passVec3("colorRatios", {1.0f, refractionRatio, 1.0f});


	// **************
	//  Allocations
	// **************
	// Model view
	MatrixStack model;
	glm::mat4 view, projection;
	float deltaTime;



	// definiera ett partikelsystem
	BubbleSystem bubbleSystem;
	std::srand(std::time(NULL));
	

	while (!win.shouldClose()) {
		
		// Time
		deltaTime = Time::getDeltaTime();
		Time::update();

		#ifndef RELEASE_BUILD_WINDOWS

		Time::displayFPS();
		
		#endif
		
		win.clear();
		win.processInput(&camera);

		// Update projectin matrix
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)win.getWidth() / (float)win.getHeight(), 0.1f, 100.0f);


		// *************
		//    Skybox
		// *************

		skyboxShader.use();

		// The view matrix
		view = glm::mat4(glm::mat3(camera.getViewMatrix()));

		// Pass view and projectin
		skyboxShader.passMat4("view", view);
		skyboxShader.passMat4("projection", projection);

		skybox.render();

		// *************
		//    Bubble
		// *************

		sphereShader.use();
		// Pass view and projection
		
		sphereShader.passMat4("projection", projection);

		model.push();
			model.translate({ 0.0f, 0.0f, -2.0f });

			// Kolla om vi aktiverar space
			if (win.isPressed(GLFW_KEY_SPACE))
				bubbleSystem.addBubble(&sphere); // l�gg till ny bubbla i systemet

			// rendera bubblorna i systemet om de "lever"
			for (auto& bubble : bubbleSystem.bubbles){

				if (bubble.alive){
					// Model transformations
					// Add new matrix to the stack
					model.push();

						
						while (Physics::realtime < deltaTime) {
							bubble.update(win.addKeyInput());
							Physics::realtime += Physics::STEP;
						}
						Physics::realtime = 0.0f;
											
						model.translate(bubble.getPos().returnVec3());

						// Scale the object
						model.scale(bubble.getRadius());

						// Pass topmost matrix in the stack to the shader
						sphereShader.passMat4("model", model.top());
						// Render the sphere
						sphere.render();

					// Remove topmost matrix from stack
					model.pop();
				}
			}
			// Remove "dead" bubbles
			bubbleSystem.clean();

		model.pop();

		// Detach all shaders
		Shader::detachAll();

		// Swap buffers and poll events
		win.update();


	}


	#ifdef RELEASE_BUILD_WINDOWS
	
	FreeConsole();

	#endif
	

	return 0;
}
