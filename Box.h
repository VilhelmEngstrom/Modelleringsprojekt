#pragma once
#include <initializer_list>
#include <math.h>
#include "Mesh.h"

#ifndef BOX_H
#define BOX_H

class Box : public Mesh{
    public:
        explicit Box(float sideLength);
        Box(const Box& b);
        ~Box();

        Box& operator=(const Box& rhs);

        void generateVertices() override;
        void generateIndices() override;

    private:
        float side;

        void create();

};

#endif
