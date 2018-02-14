#pragma once
#include "Mesh.h"
#include "Shader.h"

#if defined _WIN32 || defined _WIN_64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif

#include "dependencies/include/glew.h"

namespace graphics{
    class Renderer {
        public:
            // Takes any class derived from Mesh as argument
            explicit Renderer(const Mesh& mesh);
            ~Renderer();

            // Draw the object
            void render() const;

            // Set the shader, argument is the path to the shader file
            void setShader(const std::string& shaderFile);

        protected:
            uint vertexArrayObj, vertexBuffer, indexBuffer;
            Vertex* vertexArray;
            uint* indexArray;

            uint nVertices, nIndices;
            uint shaderProgram;

            // Initialize
            void init(const Mesh& mesh);
            // Pass vertex array to OpenGL
            void setupVertexBuffer();
            // Pass index array to OpenGL
            void setupIndexBuffer();
            // Unbind vertex array object and vertex and index buffers
            void unbind();

    };
}
