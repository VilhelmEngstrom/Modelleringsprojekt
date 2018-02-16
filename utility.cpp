#include "utility.h"


void utility::generatePerspectiveProjectionMatrix(float* matrix, float f, float zNear, float zFar, float aspectRatio){
    if(!aspectRatio){
        printf("Aspect ration cannot be zero\n");
        return;
    }
    if(zNear >= zFar){
        printf("zNear must be smaller than zFar\n");
        return;
    }


    for(int i = 0; i < MAT4_SIZE; i++)
        matrix[i] = 0;

    matrix[0]  = f/aspectRatio;
    matrix[5]  = f;
    matrix[10] = (zFar + zNear) / (zNear-zFar);
    matrix[11] = -1;
    matrix[14] = 2 * zFar * zNear / (zNear - zFar);
}
