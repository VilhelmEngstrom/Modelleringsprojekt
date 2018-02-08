#pragma once
#include <iostream>
#include <algorithm>
#include "dependencies/include/glew.h"

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

namespace graphics{
    class Object {
        typedef unsigned int uint;

        public:
            // Initialize with number of vertices, array of vertices and optinally
            // the number of dimentions (3D by default).
            // Primitives must be given as traingles. Drawing a
            // triangle requires 3 verts, a square 6 verts (2 triangles) and so on.
            // Creating a triangle:
            // float verts[9] = {
            // -1.0f, -1.0f, 0.0f,               // coords for vert 1
            //  1.0f, -1,0f, 0.0f,               // coords for vert 2
            //  0.0f,  1.0f, 0.0f               // coords for vert 3
            // };
            // Object o(3, verts);
            //
            // Creating a rectangle:
            // float verts[12] = {
            // -1.0f, -1.0f, 0.0f,               // coords for vert 1
            //  0.0f, -1.0f, 0.0f,               // coords for vert 2
            //  0.0f,  0.0f, 0.0f,               // coords for vert 3
            // -1.0f, -1.0f, 0.0f,               // vert 4
            //  0.0f,  0.0f, 0.0f,               // vert 5
            // -1.0f,  1.0f, 0.0f               // vert 6
            // };
            //Object o(6, verts);

            Object(uint nVerts, float* pos);
            Object(uint nVerts, float* pos, uint dim);
            ~Object();

            // Specify shader to be used for object (must be done once)
            void setShader(uint shader);

            // Set draw mode (GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW)
            void setDrawMode(const GLenum& mode);

            // Draw the object (in update loop)
            void draw() const;


        protected:
            float* vertexPositions;
            uint nVertices, dimension;
            uint vertexArrayID, vertexBuffer;
            uint shaderProgram;
            GLenum drawMode;

            // Initialize, called from ctor
            void init(float* pos);
            // Initialize specific fields, called from init(...)
            void initVertPos(float* pos);
            void initVertexArray();
            void initVertexBuffer();

    };
}
