#include <iostream>
#include "dependencies/include/glew.h"
#include "Window.h"


#define GL_DEBUG 1

#if GL_DEBUG == 1
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif


int main(int argc, char** argv){

    Window win("Engine", 960, 540);

    if(glewInit() != GLEW_OK)
        std::cout << "Could not initialize GLEW\n";


    while(!win.shouldClose())
        win.update();
    return 0;
}
