#pragma once
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <array>

#ifndef MAT4_SIZE
#define MAT4_SIZE 16
#endif

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#ifndef VEC3_H
#define VEC3_H

struct Vec3{
    float x,y,z;
};

#endif

#ifndef ROTAXIS_H
#define ROTAXIS_H

enum class RotationAxis{
    X,Y,Z
};

#endif

#ifndef MATRIXNODE_H
#define MATRIXNODE_H

struct MatrixNode{

    // Matrix follows pattern
    //
    // v[0] v[4]  v[8]  v[12]
    // v[1] v[5]  v[9]  v[13]
    // v[2] v[6]  v[10] v[14]
    // v[3] v[7]  v[11] v[15]

    float v[MAT4_SIZE];
    MatrixNode* previous;
};

#endif

class MatrixStack{
    typedef MatrixNode Mat4;

    public:
        MatrixStack();
        ~MatrixStack();

        // Stack operations
        // Initialize
        void init();

        // Add new matrix
        void push();

        // Remove topmost matrix
        void pop();

        // Empty stack
        void flush();


        // Getters
        float* getTopMatrix() const;

        // Get number of matrices in stack
        uint getDepth() const;

        // Matrix transforms
        // Make current matrix a unit
        void unit();

        // Make mat a unit
        static void unit(float mat[]);

        // Uniform scaling
        void scale(float magnitude);

        // Translate
        void translate(const Vec3& vec);
        void translate(float x, float y, float z);

        // Rotate. angle in radians. Use macro M_PI for pi
        // axis is given by RotationAxis::X, RotationAxis::Y or RotationAxis::Z
        // eg:
        // rotate(RotationAxis::X, M_PI); will rotate the object
        // 3.14 rads around the x axis
        void rotate(RotationAxis axis, float angle);

        // IO
        // Print every matrix on the stack
        void print() const;

        // Topmost matrix
        Mat4* current;
    protected:
        // Print single matrix
        void printMatrix(float* mat) const;

        // Multiply m1 with m2, store in out (out = m1 * m2)
        static void multiply(float m1[], float m2[], float out[]);
        // Multiply matrix with scalar
        static void multiply(float mat1[], float multiplier, float out[]);
};
