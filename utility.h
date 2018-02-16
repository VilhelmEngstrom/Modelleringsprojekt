#pragma once
#include <stdio.h>
#include <math.h>

#ifndef MAT4_SIZE
#define MAT4_SIZE 16
#endif

#ifndef UTILITY_H
#define UTILITY_H

namespace utility{

    // Generate a perspective projection matrix, stored in argument matrix
    void generatePerspectiveProjectionMatrix(float* matrix, float fov, float zNear, float zFar, float aspect);



}

#endif
