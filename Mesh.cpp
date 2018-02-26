#include "Mesh.h"

Mesh::Mesh() : vertices(NULL), indices(NULL), renderer(NULL){
    if(glewInit() != GLEW_OK){
        std::cout << "Could not initialize GLEW\n";
        exit(EXIT_FAILURE);
    }
}

Mesh::~Mesh() {
    delete renderer;
    delete[] vertices;
    delete[] indices;
}

uint Mesh::getNumberOfVertices() const{
    return nVertices;
}

uint Mesh::getNumberOfIndices() const{
    return nIndices;
}

Vertex* Mesh::getVertices() {
    return vertices;
}

uint* Mesh::getIndices() const{
    return indices;
}


void Mesh::genRenderer(){
    renderer = new graphics::Renderer(vertices, nVertices, indices, nIndices);
}

void Mesh::render() const{
    if(renderer == NULL){
        printf("No renderer has been generated\n");
        return;
    }

    // Render geometry
    renderer->render();
}
