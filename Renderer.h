#pragma once
#include <stdio.h>

#if defined _WIN32 || defined _WIN_64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif

#include "dependencies/include/glew.h"

#ifndef VEC3_H
#define VEC3_H

struct Vec3{
    float x,y,z;
};

#endif

#ifndef VEC2_H
#define VEC2_H

struct Vec2{
    float s,t;
};

#endif

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex{
    Vec3 position;
    Vec3 normal;
    Vec2 texCoords;
};

#endif

typedef unsigned int uint;

namespace graphics{
    class Renderer {
        public:
            explicit Renderer(Vertex* vertices, uint nVerts, uint* indices, uint nInds);
            ~Renderer();

            // Draw the object
            void render() const;

        protected:
            uint vertexArrayObj, vertexBuffer, indexBuffer;
            Vertex* vertexArray;
            uint* indexArray;

            uint nVertices, nIndices;


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
