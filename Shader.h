#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include "dependencies/include/glew.h"
// Disable deprecation of fread(...) in MSVC
#if defined _WIN32 || defined _WIN64
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#endif
#include <stdio.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#ifndef GL_DEBUG
#define GL_DEBUG 1
#endif
#if GL_DEBUG == 1
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

struct ShaderSource{
    std::string vertexSource;
    std::string fragmentSource;
};


namespace graphics{
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
}
