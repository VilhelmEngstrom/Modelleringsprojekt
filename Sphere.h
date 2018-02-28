#pragma once
#include <iostream>
#include <initializer_list>
#include <math.h>
#include "Mesh.h"
#include "Renderer.h"

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#ifndef SPHERE_H
#define SPHERE_H

class Sphere : public Mesh{
    public:
        // Initialize with radius and number of vertical segments
        Sphere(float rad, unsigned int segs);
        Sphere(const Sphere& s);
        ~Sphere();

        Sphere& operator=(const Sphere& rhs);
    private:
        float radius;
        unsigned int verticalSegs, flatSegs;

        void init();
        // Create the sphere, the methods below it
        void create();

        // Sweep the surface, based on spherical coordinates
        void generateVertices() override;
        // Index the vertices
        void generateIndices() override;

        // Initialize values
        void setIndexValues(unsigned int index, std::initializer_list<unsigned int> values);
};

#endif
