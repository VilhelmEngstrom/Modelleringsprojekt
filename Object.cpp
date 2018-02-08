#include "Object.h"

graphics::Object::Object(uint nVerts, float* pos) : nVertices(nVerts), dimension(3){
    init(pos);
}

graphics::Object::Object(uint nVerts, float* pos, uint dim) : nVertices(nVerts){
    if(dim < 2 || dim > 3){
        std::cout << "Unknown dimension\n";
        exit(EXIT_FAILURE);
    }
    dimension = dim;
    init(pos);
}


graphics::Object::~Object(){
    delete[] vertexPositions;
}

void graphics::Object::setShader(uint shader){
    shaderProgram = shader;
}

void graphics::Object::setDrawMode(const GLenum& mode){
    drawMode = mode;
}


void graphics::Object::draw() const{
    if(!shaderProgram){
        std::cout << "No shader attached\n";
        return;
    }

    glUseProgram(shaderProgram);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, nVertices);
    glDisableVertexAttribArray(0);
}


void graphics::Object::init(float* pos){
    // Initialize glew
    if(glewInit() != GLEW_OK){
        std::cout << "Could not initialize GLEW\n";
        exit(EXIT_FAILURE);
    }

    drawMode = GL_STATIC_DRAW;
    shaderProgram = 0;

    initVertPos(pos);
    initVertexArray();
    initVertexBuffer();
}

void graphics::Object::initVertPos(float* pos){
    vertexPositions = new float[nVertices * dimension];
    std::copy(pos, pos + nVertices * dimension, vertexPositions);
}

void graphics::Object::initVertexArray(){
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
}

void graphics::Object::initVertexBuffer(){
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices * dimension * sizeof(float), vertexPositions, drawMode);
}
