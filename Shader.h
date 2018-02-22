#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <map>

#if defined _WIN32 || defined _WIN64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif
#include "dependencies/include/glew.h"

#ifndef SHADERSOURCE_H
#define SHADERSOURCE_H

struct ShaderSource{
    std::string vertexSource;
    std::string fragmentSource;
};

#endif

#ifndef SHADER_H
#define SHADER_H

namespace graphics{
    class Shader{
        public:
            explicit Shader(const std::string& shaderFile);
            Shader(const Shader&) = delete;
            ~Shader();

            Shader operator=(const Shader&) = delete;

            void activate() const;
            void deactivate() const;

            // Add uniform from shader, handle is the name of the variable in the
            // shader
            void addLocation(const std::string& handle);

            // Pass scalar to shader, handle is the name of the variable in
            // the shader
            void passScalar(const std::string& handle, int uniform) const;
            void passScalar(const std::string& handle, float uniform) const;

            // Pass Mat4 to shader, handle is the name of the uniform in the shader,
            // matrix is a poirnter to the Mat4 (a float[16])
            void passMat4(const std::string& handle, float* matrix) const;

        private:
            unsigned int shaderProgramID;

            // Stores uniform locations, accessed by the string key.
            // Eg: locations.at(stack) yields the int associated with the
            // uniform 'stack' in the shader
            std::map<std::string, int> locations;

            enum class ShaderType {
                NONE=-1, VERTEX, FRAGMENT
            };


            // Compile and link shaders, return 0 if this fails
            static unsigned int compile(const std::string& shaderPath);
            static unsigned int compile(const std::string& vertexPath, const std::string& fragmentPath);

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

#endif
