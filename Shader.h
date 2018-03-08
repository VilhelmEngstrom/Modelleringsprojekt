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

#include "dependencies/include/glm/glm.hpp"
#include "dependencies/include/glm/gtc/matrix_transform.hpp"
#include "dependencies/include/glm/gtc/type_ptr.hpp"

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

            void use() const;
            static void detachAll();

            // Pass scalar to shader, handle is the name of the variable in
            // the shader
            void passScalar(const std::string& handle, int scalar);
            void passScalar(const std::string& handle, float scalar);

			void passVec3(const std::string& handle, const glm::vec3& vec);

            // Pass Mat4 to shader, handle is the name of the uniform in the shader,
            // matrix is a poirnter to the Mat4 (a float[16])
            void passMat4(const std::string& handle, float* matrix);
            void passMat4(const std::string& handle, const glm::mat4& matrix);

        private:
            unsigned int shaderProgramID;
			std::map<std::string, int> uniformLocations;

            enum class ShaderType {
                NONE=-1, VERTEX, FRAGMENT
            };

			// Get the location of the uniform, either from uniformLocations or from the 
			// shader. In the latter case, the pair is added to the map for future use
			int getUniformLocation(const std::string& handle);


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
