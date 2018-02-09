#include <iostream>
#include "dependencies/include/glew.h"
#include "Window.h"
#include "Object.h"


#ifndef GL_DEBUG
#define GL_DEBUG 1
#endif
#if GL_DEBUG == 1
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif


int main(int argc, char** argv){
    using namespace graphics;

    Window win("Engine", 960, 540);

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,
         0.0f,  0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         0.0f,  0.0f, 0.0f,
        -1.0f,  0.0f, 0.0f
    };

    Object obj(6, vertices);

    obj.setShader("resources/shaders/basic.shader");



    while(!win.shouldClose()){
        win.clear();
        obj.draw();
        win.update();
    }
    return 0;
}
