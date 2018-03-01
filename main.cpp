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

	// Create a camera and place it in the scene
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

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
	sphereShader.passVec3("fresnelValues", { 0.4f, 2.5f, 0.0f });

	// Color ratios for refraction
	// Refraction ratio for soapy water
	float refractionRatio = 1.0f / 1.34f;
	// Values in vector correspond to rgb. Results are best when values are between 0 and 1
	sphereShader.passVec3("colorRatios", { refractionRatio, refractionRatio, 1.0f });


	// **************
	//  Allocations
	// **************
	// Model view
	MatrixStack model;
	glm::mat4 view, projection;






	// random tid 
	srand((unsigned int)time(0));
	// definiera ett partikelsystem
	BubbleSystem bubbleSystem;
	

	

	while (!win.shouldClose()) {
		
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
		sphereShader.passMat4("view", view);
		sphereShader.passMat4("projection", projection);

		model.push();
		model.translate({ 0.0f, 0.0f, -2.0f });


			// Kolla om vi aktiverar space
			if (win.spaceActive()){
				int randome = rand() % 1500;
				if (randome == 1)
					bubbleSystem.addBubble(&sphere); // l�gg till ny bubbla i systemet
			}

			// rendera bubblorna i systemet om de "lever"
			for (int i = 0; i < bubbleSystem.getNumberOfBubbles(); ++i){

				if (bubbleSystem.myBubblyBubbles[i].alive){
					// Model transformations
					// Add new matrix to the stack
					model.push();

						bubbleSystem.myBubblyBubbles[i].update(win.addKeyInput());
						model.translate({ bubbleSystem.myBubblyBubbles[i].getPos().getX(),bubbleSystem.myBubblyBubbles[i].getPos().getY(),bubbleSystem.myBubblyBubbles[i].getPos().getZ() });

						// Scale the object
						model.scale(bubbleSystem.myBubblyBubbles[i].getRadius());
						//std::cout << bubbleSystem.myBubblyBubbles[i].getPos();

						// Pass topmost matrix in the stack to the shader
						sphereShader.passMat4("model", model.getTopMatrix());
						// Render the sphere
						sphere.render();

					// Remove topmost matrix from stack
					model.pop();
				}


			}

		model.pop();

		// Detach all shaders
		Shader::detachAll();

		// Swap buffers and get poll events
		win.update();


	}


	return 0;
}