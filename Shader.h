#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "dependencies/include/glew.h"

#define GLEW_STATIC
#define GL_DEBUG 1

#if GL_DEBUG == 1
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif


struct ShaderSource{
    std::string vertexSource;
    std::string fragmentSource;
};


class Shader{
    public:
        Shader();
        ~Shader();

        // Compile and link shaders, return 0 if this fails
        static unsigned int compile(const std::string& shaderPath);
        static unsigned int compile(const std::string& vertexPath, const std::string& fragmentPath);

    protected:
        enum class ShaderType {
            NONE=-1, VERTEX, FRAGMENT
        };
        
        // Compile shader, return shader IDs
        static unsigned int compileSource(const char* shaderSource, const ShaderType& type);

        // Link the program, returns 0 if linking failed
        static unsigned int linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID);

        // C syntax for efficiency
        // Read shader source code from a single file
        static ShaderSource loadSource(const std::string& shaderPath);
        // Read shader source code from separate files
        static ShaderSource loadSource(const std::string& vertexPath, const std::string& fragmentPath);


};