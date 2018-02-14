#pragma once
#include <iostream>
#include <initializer_list>
#include "Mesh.h"

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
