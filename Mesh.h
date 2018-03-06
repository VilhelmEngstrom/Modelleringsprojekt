#pragma once
#include <iostream>
#include <initializer_list>
#include "Shader.h"
#include "Renderer.h"

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

#ifndef MESH_H
#define MESH_H

class Mesh{
    public:
        Mesh();
        virtual ~Mesh();

        unsigned int getNumberOfVertices() const;
        unsigned int getNumberOfIndices() const;

        // Return pointer to list of vertices
        Vertex* getVertices() const;
        // Return pointer to list of indices
        unsigned int* getIndices() const;
       
        // Render object (uses Renderer*)
        void render() const;

        void render(unsigned int texID) const;

    protected:
        Vertex* vertices;
        unsigned int* indices;
        unsigned int nVertices, nIndices;

        graphics::Renderer* renderer;

		// Construct the mesh
		virtual void generateVertices() = 0;
		// Generate index list for reusing vertices
		virtual void generateIndices() = 0;


        // initialize renderer
        void generateRenderer();

        void setVertexValues(unsigned int index, std::initializer_list<float> values);
};

#endif
