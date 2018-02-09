//
//  Vector.hpp
//  emma
//
//  Created by Emma Nilsson on 2018-02-02.
//  Copyright © 2018 Emma Nilsson. All rights reserved.
//
#pragma once
#include <iostream>
#include <cmath>
#include <math.h>       /* acos */

class Vector {
    public:
        Vector()
            :x(0), y(0), z(0) {}
        Vector(float inX, float inY, float inZ)
            :x(inX), y(inY), z(inZ) {}
        Vector(const Vector& v);
        Vector(float d);
    
        //elementwise multiplication
        friend Vector operator*(const Vector& v1, const Vector& v2);

		// plus
		friend Vector operator+(const Vector& v1, const Vector& v2);

		// minus
		friend Vector operator-(const Vector& v1, const Vector& v2);
    
        //dot product
		float dotProduct(const Vector& v);

		float angle(const Vector& v);

		float length();

		Vector normalized(); 
    
        //cross product
        Vector crossProduct(const Vector& v);

		// sign of vector
		Vector sign();
    
        //set variables
        void setX(float d);
        void setY(float d);
        void setZ(float d);
    
		float getX() const;
		float getY() const;
		float getZ() const;
    
    private:
		float x, y, z;
        friend std::ostream& operator<< (std::ostream& os, const Vector& v);
    
};


