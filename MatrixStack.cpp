#include "MatrixStack.h"


MatrixStack::MatrixStack(){
    current = new Mat4();
    init();
}

MatrixStack::~MatrixStack(){
    flush();
}


// Stack operations

void MatrixStack::init(){
    current->previous = NULL;
    unit();
}

void MatrixStack::push(){
    Mat4* newMat = new Mat4;

    newMat->previous = current;
    std::copy(current->v, current->v+MAT4_SIZE, newMat->v);

    current = newMat;
}

void MatrixStack::pop(){
    if(!current){
        printf("Stack is empty");
        return;
    }

    Mat4* last = current;
    current = current->previous;
    delete last;
}


void MatrixStack::flush(){
    while(current){
        pop();
    }
}


// Getters

float* MatrixStack::getTopMatrix() const{
    return current ? current->v : NULL;
}


uint MatrixStack::getDepth() const{
    Mat4* it = current;

    uint depth = 0;
    while(it){
        depth++;
        it = it->previous;
    }

    return depth;
}


// Matrix tranforms

void MatrixStack::unit(){
    // Set diagonal to 1.0f
    for(int i = 0; i < MAT4_SIZE; i++)
        i % 5 == 0 ? current->v[i] = 1.0f : current->v[i] = 0.0f;
}

void MatrixStack::unit(float mat[]){
    for(int i = 0; i < MAT4_SIZE; i++)
        i % 5 == 0 ? mat[i] = 1.0f : mat[i] = 0.0f;
}

void MatrixStack::scale(float magnitude){
    float m[16];
    unit(m);

    // Multiply diagonal
    for(int i = 0; i < MAT4_SIZE; i += 5)
        m[i] = m[i] * magnitude;

    // Scale current matrix
    multiply(current->v, m, current->v);
}

void MatrixStack::translate(const Vec3& vec){
    float m[16];
    unit(m);
    m[12] = vec.x;
    m[13] = vec.y;
    m[14] = vec.z;

    multiply(current->v, m, current->v);
}

void MatrixStack::translate(float x, float y, float z){
    // Call translate with Vec3 argument
    translate({x,y,z});
}

void MatrixStack::rotate(RotationAxis axis, float angle){
    float m[16];
    unit(m);

    // Index 0 :  cos(angle)
    // Index 1 :  sin(angle)
    // Index 2 : -sin(angle)
    // Index 3 :  cos(angle)
    std::array<int, 4> indices;


    if(axis == RotationAxis::X)
        indices = {5, 6, 9, 10};
    else if(axis == RotationAxis::Y)
        indices = {0, 8, 2, 10};
    else
        indices = {0, 1, 4, 5};

    m[indices.at(0)] =  cos(angle);
    m[indices.at(1)] =  sin(angle);
    m[indices.at(2)] = -sin(angle);
    m[indices.at(3)] =  cos(angle);

    multiply(current->v, m, current->v);
}


// IO

void MatrixStack::print() const{
    Mat4* it = current;

    printf("Stack contents:\n\n");
    while(it){
        printMatrix(it->v);
        it = it->previous;
        printf("\n");
    }
}


// Protected

void MatrixStack::printMatrix(float* mat) const{
    for(int i = 0; i < 4; i++)
        printf("%4.2f %4.2f %4.2f %4.2f\n", mat[i+0], mat[i+4], mat[i+8],  mat[i+12]);
}

void MatrixStack::multiply(float m1[], float m2[], float out[]){
    float tempMat[MAT4_SIZE];
    // Multiply
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            tempMat[row+col*4] = m1[row] * m2[col*4] + m1[row+4] * m2[1+col*4] + m1[row+8] * m2[2+col*4] +
                                 m1[row+12] * m2[3+col*4];
        }
    }
    // Copy to out variable
    std::copy(tempMat, tempMat+16, out);
}

void MatrixStack::multiply(float m1[], float multiplier, float out[]){
    float tempMat[MAT4_SIZE];

    for(int i = 0; i < MAT4_SIZE; i++){
        tempMat[i] = m1[i] * multiplier;
    }

    std::copy(tempMat, tempMat+MAT4_SIZE, out);
}
