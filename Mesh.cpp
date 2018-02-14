#include "Mesh.h"

Mesh::Mesh() : vertices(NULL), indices(NULL) {
    if(glewInit() != GLEW_OK){
        std::cout << "Could not initialize GLEW\n";
        exit(EXIT_FAILURE);
    }
}

Mesh::~Mesh() {
    delete[] vertices;
    delete[] indices;
}

uint Mesh::getNumberOfVertices() const{
    return nVertices;
}

uint Mesh::getNumberOfIndices() const{
    return nIndices;
}

Vertex* Mesh::getVertices() const{
    return vertices;
}
uint* Mesh::getIndices() const{
    return indices;
}
