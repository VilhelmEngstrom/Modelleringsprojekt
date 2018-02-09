//
//  Matrix.cpp
//  emma
//
//  Created by Emma Nilsson on 2018-02-02.
//  Copyright © 2018 Emma Nilsson. All rights reserved.
//

#include "Matrix3.h"

Matrix3::Matrix3() {
    a11 = a22 = a33 = 1;
    a12 = a13 = a21 = a23 = a31 = a32 = 0;
}

Matrix3::Matrix3(const Matrix3& m) {
    a11 = m.a11;
    a12 = m.a12;
    a13 = m.a13;
    a21 = m.a21;
    a22 = m.a22;
    a23 = m.a23;
    a31 = m.a31;
    a32 = m.a32;
    a33 = m.a33;
}

Matrix3::Matrix3(double d) {
    a11 = a12 = a13 = d;
    a21 = a22 = a23 = d;
    a31 = a32 = a33 = d;
}

Matrix3::Matrix3(int matrix[], int size) {
    
    if (size == 9) {
        a11 = matrix[0];
        a12 = matrix[1];
        a13 = matrix[2];
        a21 = matrix[3];
        a22 = matrix[4];
        a23 = matrix[5];
        a31 = matrix[6];
        a32 = matrix[7];
        a33 = matrix[8];
    }
    else Matrix3();
}

Matrix3 operator*(const Matrix3& m1, const Matrix3& m2){
    Matrix3 aCopy(m1);
    
    aCopy.a11 = aCopy.a11 * m2.a11;
    aCopy.a12 = aCopy.a12 * m2.a12;
    aCopy.a13 = aCopy.a13 * m2.a13;
    aCopy.a21 = aCopy.a21 * m2.a21;
    aCopy.a22 = aCopy.a22 * m2.a22;
    aCopy.a23 = aCopy.a23 * m2.a23;
    aCopy.a31 = aCopy.a31 * m2.a31;
    aCopy.a32 = aCopy.a32 * m2.a32;
    aCopy.a33 = aCopy.a33 * m2.a33;
    
    return aCopy;
}

Matrix3 Matrix3::multiply(const Matrix3& m) {
    Matrix3 aCopy(*this);
    
    double newA11 = (aCopy.a11 * m.a11) + (aCopy.a12 * m.a21) + (aCopy.a13 * m.a31);
    double newA12 = (aCopy.a11 * m.a12) + (aCopy.a12 * m.a22) + (aCopy.a13 * m.a32);
    double newA13 = (aCopy.a11 * m.a13) + (aCopy.a12 * m.a23) + (aCopy.a13 * m.a33);
    double newA21 = (aCopy.a21 * m.a11) + (aCopy.a22 * m.a21) + (aCopy.a23 * m.a31);
    double newA22 = (aCopy.a21 * m.a12) + (aCopy.a22 * m.a22) + (aCopy.a23 * m.a32);
    double newA23 = (aCopy.a21 * m.a13) + (aCopy.a22 * m.a23) + (aCopy.a23 * m.a33);
    double newA31 = (aCopy.a31 * m.a11) + (aCopy.a32 * m.a21) + (aCopy.a33 * m.a31);
    double newA32 = (aCopy.a31 * m.a12) + (aCopy.a32 * m.a22) + (aCopy.a33 * m.a32);
    double newA33 = (aCopy.a31 * m.a13) + (aCopy.a32 * m.a23) + (aCopy.a33 * m.a33);
    
    aCopy.a11 = newA11;
    aCopy.a12 = newA12;
    aCopy.a13 = newA13;
    aCopy.a21 = newA21;
    aCopy.a22 = newA22;
    aCopy.a23 = newA23;
    aCopy.a31 = newA31;
    aCopy.a32 = newA32;
    aCopy.a33 = newA33;
    
    return aCopy;
}

Vector Matrix3::multiply(const Vector& v) {
    Vector aCopy(v);
    
    double x = (a11 * aCopy.getX()) + (a12 * aCopy.getY()) + (a13 * aCopy.getZ());
    double y = (a21 * aCopy.getX()) + (a22 * aCopy.getY()) + (a23 * aCopy.getZ());
    double z = (a31 * aCopy.getX()) + (a32 * aCopy.getY()) + (a33 * aCopy.getZ());
    
    aCopy.setX(x);
    aCopy.setY(y);
    aCopy.setZ(z);
    
    return aCopy;
}

std::ostream& operator<< (std::ostream& os, const Matrix3& m) {
    
    os << "Matrix = \n[" << m.a11 << " " << m.a12 << " " << m.a13 << "\n";
    os << " " << m.a21 << " " << m.a22 << " " << m.a23 << "\n";
    os << " " << m.a31 << " " << m.a32 << " " << m.a33 << "]\n";
    
    return os;
}
