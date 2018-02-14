#pragma once
#include "Shader.h"

#if defined _WIN32 || defined _WIN_64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif

#include "dependencies/include/glew.h"

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex{
    struct Vec3{
        float x,y,z;
    };
    struct Vec2{
        float s,t;
    };

    Vec3 position;
    Vec3 normal;
    Vec2 texCoords;
};

#endif

namespace graphics{
    class Renderer {
        public:
            explicit Renderer(Vertex* vertices, uint nVerts, uint* indices, uint nInds);
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
            void init();
            // Pass vertex array to OpenGL
            void setupVertexBuffer();
            // Pass index array to OpenGL
            void setupIndexBuffer();
            // Unbind vertex array object and vertex and index buffers
            void unbind();

    };
}
