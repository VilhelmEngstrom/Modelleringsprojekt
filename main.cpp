#include <iostream>
#include "Window.h"
#include "Mesh.h"
#include "Sphere.h"
#include "MatrixStack.h"
#include "Shader.h"
#include "utility.h"
#include "Bubble.h"
#include "BubbleSystem.h"

#ifndef WIN_DEBUG
#define WIN_DEBUG 1
#endif

#ifndef STACK_DEBUG
#define STACK_DEBUG 0
#endif

// Fix aspect ratio
// Send stack to shader



int main(int argc, char** argv) {
	using namespace graphics;

#if STACK_DEBUG == 1


	MatrixStack matStack;
	//matStack.translate(1.0f, 2.0f, 1.0f);
	matStack.rotate(RotationAxis::X, M_PI);
	//matStack.scale(2.0f);

	matStack.print();



#endif

#if WIN_DEBUG == 1
	// Open a window
	Window win("Engine", 540, 540);
	// Create sphere, radius 1.0f, 30 vertical segments
	Sphere sphere(1.0f, 15);
	
	// random tid 
	srand(time(0));
	// definiera ett partikelsystem
	BubbleSystem bubbleSystem;


	// Specify, compile and pass shader program to OpenGL
	Shader shader("resources/shaders/basic.glsl");

	// Perspective projection matrix
	float perspective[16];
	utility::generatePerspectiveProjectionMatrix(perspective, 4, 3, 7, 1);

	// Add locations of uniforms (variables in shader to be set from C++-code)
	shader.addLocation("perspective");
	shader.addLocation("stack");

	// Create new matrix stack
	MatrixStack matStack;

	while (!win.shouldClose()) {
		// Erase everything from the previous frame
		win.clear();
		// Enable back face culling
		win.cullBackFace();

		// Use the shader
		shader.activate();

		// Adjust projection matrix if window has been resized
		utility::adjustAspect(perspective, win);
		// Pass perspective projection matrix to shader
		shader.passMat4("perspective", perspective);


		// Camera transfomations
		// Add new matrix to stack
		matStack.push();
		// Translate 5 units towards user
		matStack.translate({ 0.0f, 0.0f, -5.0f });
		
		
		// Kolla om vi aktiverar space
		if (win.spaceActive())
		{
			int randome = rand() % 1500;
			if(randome == 1)
				bubbleSystem.addBubble(&sphere); // lägg till ny bubbla i systemet
		}
		
		// rendera bubblorna i systemet om de "lever"
		for (int i = 0; i < bubbleSystem.getNumberOfBubbles(); ++i)
		{
			
			if (bubbleSystem.myBubblyBubbles[i].alive)
			{
				// Model transformations
				// Add new matrix to the stack
				matStack.push();

				bubbleSystem.myBubblyBubbles[i].update(win.addKeyInput());
				matStack.translate({ bubbleSystem.myBubblyBubbles[i].getPos().getX(),bubbleSystem.myBubblyBubbles[i].getPos().getY(),bubbleSystem.myBubblyBubbles[i].getPos().getZ() });

				// Scale the object
				matStack.scale(bubbleSystem.myBubblyBubbles[i].getRadius());
				//std::cout << bubbleSystem.myBubblyBubbles[i].getPos();

				// Pass topmost matrix in the stack to the shader
				shader.passMat4("stack", matStack.getTopMatrix());
				// Render the sphere
				sphere.render();

				// Remove topmost matrix from stack
				matStack.pop();
			}
			
			
		}
		
		// Remove topmost matric from stack
		matStack.pop();



		// Deactivate shader
		shader.deactivate();

		// Swap buffers and get poll events
		win.update();
	}
#endif

	return 0;
}