#pragma once
#include <iostream>
#include <math.h>

#if defined _WIN32 || defined _WIN_64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif

#include "dependencies/include/glew.h"

#ifndef MESH_DEBUG
#define MESH_DEBUG 1
#endif

#if MESH_DEBUG == 1
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

typedef unsigned int uint;

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

class Mesh{
    public:
        Mesh();
        virtual ~Mesh();

        uint getNumberOfVertices() const;
        uint getNumberOfIndices() const;

        // Return pointer to list of vertices
        Vertex* getVertices() const;
        // Return pointer to list of indices
        uint* getIndices() const;

        // Construct the mesh
        virtual void generateVertices() = 0;
        // Generate index list for reusing vertices
        virtual void generateIndices() = 0;

    protected:
        Vertex* vertices;
        uint* indices;

        uint nVertices, nIndices;
};
