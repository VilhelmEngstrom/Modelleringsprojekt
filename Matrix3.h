//
//  Matrix.h
//  emma
//
//  Created by Emma Nilsson on 2018-02-02.
//  Copyright © 2018 Emma Nilsson. All rights reserved.
//
#pragma once
#include <iostream>
#include "Vector.h"

class Matrix3 {
    public:
        //default constructor creates a unit matrix
        Matrix3();
    
        //constructors
        Matrix3(const Matrix3& m);
        Matrix3(double d);
        Matrix3(int matrix[], int size);
    
        //elementwise multiplication
        friend Matrix3 operator*(const Matrix3& m1, const Matrix3& m2);
    
        Matrix3 multiply(const Matrix3& m);
        Vector multiply(const Vector& v);
    
    
    
    private:
        double a11, a12, a13;
        double a21, a22, a23;
        double a31, a32, a33;
    
        friend std::ostream& operator<< (std::ostream& os, const Matrix3& m);
    
};
