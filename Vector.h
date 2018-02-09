//
//  Vector.hpp
//  emma
//
//  Created by Emma Nilsson on 2018-02-02.
//  Copyright © 2018 Emma Nilsson. All rights reserved.
//
#pragma once
#include <iostream>

class Vector {
    public:
        Vector()
            :x(0), y(0), z(0) {}
        Vector(double inX, double inY, double inZ)
            :x(inX), y(inY), z(inZ) {}
        Vector(const Vector& v);
        Vector(double d);
    
        //elementwise multiplication
        friend Vector operator*(const Vector& v1, const Vector& v2);
    
        //dot product
        double dotProduct(const Vector& v);
    
        //cross product
        Vector crossProduct(const Vector& v);
    
        //set variables
        void setX(double d);
        void setY(double d);
        void setZ(double d);
    
        double getX();
        double getY();
        double getZ();
    
    
    private:
        double x, y, z;
        friend std::ostream& operator<< (std::ostream& os, const Vector& v);
    
};


