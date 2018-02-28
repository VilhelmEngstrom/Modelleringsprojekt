#include <iostream>
#include "Window.h"
#include "Mesh.h"
#include "Sphere.h"
#include "MatrixStack.h"
#include "Shader.h"
#include "CubemapTexture.h"
#include "Camera.h"
#include "Skybox.h"


#include "dependencies/include/glm/glm.hpp"
#include "dependencies/include/glm/gtc/matrix_transform.hpp"
#include "dependencies/include/glm/gtc/type_ptr.hpp"



#ifndef GLM_DEBUG
#define GLM_DEBUG 1
#endif

#ifndef STACK_DEBUG
#define STACK_DEBUG 0
#endif

// Mouse input


int main(int argc, char** argv){
    using namespace graphics;








    #if GLM_DEBUG == 1

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Window& win = Window::getInstance("glm test", 960, 540);

    

    std::string location = "resources/textures/skybox/";
    std::array<std::string, 6> faces = {location + "right.jpg", location + "left.jpg", location + "top.jpg",
                                        location + "bottom.jpg", location + "front.jpg", location + "back.jpg"};

    CubemapTexture tex(faces);
    Skybox skybox(tex);

    Shader skyboxShader("resources/shaders/skybox.glsl");

    skyboxShader.use();
    skyboxShader.passScalar("skybox", 0);


    glm::mat4 view, projection;

    Sphere sphere(1.0f, 30);
    Shader sphereShader("resources/shaders/bubble.glsl");

    MatrixStack model;

    while(!win.shouldClose()){
        win.clear();
        win.processInput(&camera);

        projection = glm::perspective(glm::radians(camera.getZoom()), (float)win.getWidth()/(float)win.getHeight(), 0.1f, 100.0f);

        // *************
        //    Skybox
        // *************

        skyboxShader.use();

        view = glm::mat4(glm::mat3(camera.getViewMatrix()));

        skyboxShader.passMat4("view", view);
        skyboxShader.passMat4("projection", projection);

        skybox.render();

        // *************
        //    Bubble
        // *************

        sphereShader.use();
        sphereShader.passMat4("view", view);
        sphereShader.passMat4("projection", projection);

        model.push();
            model.translate({-1.0f, 0.3f, -8.0f});

            sphereShader.passMat4("model", model.getTopMatrix());
            // Render the sphere
            sphere.render();
        model.pop();






        Shader::detachAll();

        win.update();
    }






    #endif


    #if STACK_DEBUG == 1

    // Open a window
    Window win("Engine", 540, 540);
    // Create sphere, radius 1.0f, 30 vertical segments
    Sphere sphere(1.0f,30);
    // Specify, compile and pass shader program to OpenGL
    Shader shader("resources/shaders/basic.glsl");

    Sphere s2 = Sphere(1.0f, 30);


    // Perspective projection matrix
    float perspective[16];
    utility::generatePerspectiveProjectionMatrix(perspective, 4, 3, 7, 1);

    // Add locations of uniforms (variables in shader to be set from C++-code)
    shader.addLocation("perspective");
    shader.addLocation("stack");

    // Create new matrix stack
    MatrixStack matStack;



    // ******
    // Skybox
    // ******

    Box skybox(2.0f);
    std::string location = "resources/textures/skybox/";

    CubemapTexture tex(location + "right.tga", location + "left.tga", location + "up.tga",
                       location + "down.tga", location + "back.tga", location + "front.tga");

    //unsigned int texID = tex.getTexID();
    Shader skyboxShader("resources/shaders/skybox.glsl");
    skyboxShader.addLocation("view");
    skyboxShader.addLocation("perspective");


    float viewMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -5.0f, 1.0f
    };





    unsigned int texID = tex.getTexID();







    while(!win.shouldClose()){
        // Erase everything from the previous frame
        win.clear();
        // Enable back face culling
        win.cullBackFace();

        // Use the shader
        shader.use();

        // Adjust projection matrix if window has been resized
        utility::adjustAspect(perspective, win);
        // Pass perspective projection matrix to shader
        shader.passMat4("perspective", perspective);

        // Camera transfomations
        // Add new matrix to stack
        matStack.push();
            // Translate 5 units towards user
            matStack.translate({0.0f, 0.0f, -5.0f});

            // Model transformations
            // Add new matrix to the stack
            matStack.push();
                // Scale the object
                matStack.scale(0.5f);
                // Translate to the right
                matStack.translate({1.0f,0.0f,0.0f});
                // Pass topmost matrix in the stack to the shader
                shader.passMat4("stack", matStack.getTopMatrix());
                // Render the sphere
                sphere.render();

                matStack.translate(-2.0f, 0.0f, 0.0f);
                shader.passMat4("stack", matStack.getTopMatrix());
                //s2.render();

            // Remove topmost matrix from stack
            matStack.pop();
        // Remove topmost matric from stack
        matStack.pop();





        skyboxShader.use();


        skyboxShader.passMat4("view", viewMatrix);
        skyboxShader.passMat4("perspective", perspective);



        skybox.render(texID);





        Shader::detach();

        // Swap buffers and get poll events
        win.update();
    }

    #endif
    return 0;
}
