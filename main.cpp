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




int main(int argc, char** argv) {
	using namespace graphics;

	// ***************
	// Window & camera
	// ***************

	// Create the window, this must e done thorugh getInstance as the class
	// uses the singleton design pattern (all ctors are either private or deleted)
	Window& win = Window::getInstance("glm test", 960, 540);
	// Enable blending for transparancy
	win.enableBlend();

	// Create a camera and place it in the scene
	Camera camera(glm::vec3(0.0f, 0.0f, -10.0f));

	// ********************
	//    Skybox setup
	// ********************

	// Path to folder containing skybox images
	std::string location = "resources/textures/skybox/";
	// Skybox images
	std::array<std::string, 6> faces = { location + "right.jpg", location + "left.jpg", location + "top.jpg",
		location + "bottom.jpg", location + "front.jpg", location + "back.jpg" };
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



	// definiera ett partikelsystem
	BubbleSystem bubbleSystem;
	float deltaTime;
	

	while (!win.shouldClose()) {
		
		// Time
		deltaTime = Time::getDeltaTime();
		Time::update();
		Time::displayFPS();

		
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
			
			#if false
			model.translate({ 0.0f, 0.0f, -3.0f });
			sphereShader.passMat4("model", model.getTopMatrix());
			sphere.render();

			#endif		
			#if true

			// Kolla om vi aktiverar space
			if (win.isPressed(GLFW_KEY_SPACE))
				bubbleSystem.addBubble(&sphere); // l�gg till ny bubbla i systemet

			// rendera bubblorna i systemet om de "lever"
			for (int i = 0; i < bubbleSystem.getNumberOfBubbles(); ++i){

				if (bubbleSystem.myBubblyBubbles[i].alive){
					// Model transformations
					// Add new matrix to the stack
					model.push();

						
						while (Physics::realtime < deltaTime) {
							bubbleSystem.myBubblyBubbles[i].update(win.addKeyInput());
							Physics::realtime += Physics::STEP;
						}
						Physics::realtime = 0.0f;
					
						// Liten optimering
						const auto& pos = bubbleSystem.myBubblyBubbles[i].getPos();
						

						model.translate({pos.getX(), pos.getY(), pos.getZ()});

						// Scale the object
						model.scale(bubbleSystem.myBubblyBubbles[i].getRadius());

						// Pass topmost matrix in the stack to the shader
						sphereShader.passMat4("model", model.getTopMatrix());
						// Render the sphere
						sphere.render();

					// Remove topmost matrix from stack
					model.pop();
				}


			}
			#endif
		model.pop();

		// Detach all shaders
		Shader::detachAll();

		// Swap buffers and poll events
		win.update();


	}
	

	return 0;
}
