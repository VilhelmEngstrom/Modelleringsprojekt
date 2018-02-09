//
//  Vector.cpp
//  emma
//
//  Created by Emma Nilsson on 2018-02-02.
//  Copyright © 2018 Emma Nilsson. All rights reserved.
//

#include "Vector.h"

Vector::Vector(const Vector& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector::Vector(double d) {
    x = y = z = d;
}

Vector operator*(const Vector& v1, const Vector& v2) {

    return Vector(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

double Vector::dotProduct(const Vector &v) {
    return ( (x*v.x) + (y*v.y) + (z*v.z));
}

Vector Vector::crossProduct(const Vector& v) {
    
    double e1 = (y*v.z) - (z*v.y);
    double e2 = -((x*v.z)-(z*v.x));
    double e3 = (x*v.y) - (y*v.x);
    
    return Vector(e1, e2, e3);
}

void Vector::setX(double d) {
    x = d;
}

void Vector::setY(double d) {
    y = d;
}

void Vector::setZ(double d) {
    z = d;
}

double Vector::getX() {
    return x;
}

double Vector::getY() {
    return y;
}

double Vector::getZ() {
    return z;
}

std::ostream& operator<< (std::ostream& os, const Vector& v) {
    
    os << "Vector: ["  << v.x << ", " << v.y << ", " << v.z << "]\n";
    
    return os;
}
