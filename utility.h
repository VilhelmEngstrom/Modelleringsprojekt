#pragma once
#include <stdio.h>
#include <math.h>
#include "Window.h"

#ifndef UTILITY_H
#define UTILITY_H

namespace utility{
    const unsigned short MAT4_SIZE = 16;

    // Generate a perspective projection matrix, stored in argument matrix
    void generatePerspectiveProjectionMatrix(float* matrix, float fov, float zNear, float zFar, float aspect);

    // Adjust perspective projection matrix if window has been resized
    void adjustAspect(float* matrix, const graphics::Window& win);

}

#endif
