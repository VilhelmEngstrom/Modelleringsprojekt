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


class Object {
    typedef unsigned int uint;


    public:
        // Initialize with number of vertices, array of vertices and optinally
        // the number of dimestions (3D by default)
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
