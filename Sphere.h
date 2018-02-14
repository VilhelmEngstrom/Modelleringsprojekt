#pragma once
#include <iostream>
#include <initializer_list>
#include <math.h>
#include "Mesh.h"
#include "Renderer.h"

#ifndef M_PI
#define M_PI 3.1415926535
#endif

class Sphere : public Mesh{
    public:
        // Initialize with radius and number of vertical segments
        Sphere(float rad, uint segs);
        ~Sphere();

    protected:
        float radius;
        uint verticalSegs, flatSegs;

        void init();
        // Create the sphere, the methods below it
        void create();

        // Sweep the surface, based on spherical coordinates
        void generateVertices() override;
        // Index the vertices
        void generateIndices() override;

        // Initialize values
        void setVertexValues(uint index, std::initializer_list<float> values);
        void setIndexValues(uint index, std::initializer_list<uint> values);
};
