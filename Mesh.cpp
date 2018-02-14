#include "Mesh.h"

Mesh::Mesh() : vertices(NULL), indices(NULL){
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

Vertex* Mesh::getVertices() const{
    return vertices;
}

uint* Mesh::getIndices() const{
    return indices;
}

void Mesh::genRenderer(){
    renderer = new graphics::Renderer(vertices, nVertices, indices, nIndices);
}

void Mesh::setShader(const std::string& shaderFile) const{
    if(renderer == NULL){
        printf("Renderer has been generated, cannot set shader\n");
        return;
    }
    renderer->setShader(shaderFile);
}

void Mesh::render() const{
    if(renderer == NULL){
        printf("Renderer has been generated\n");
        return;
    }
    renderer->render();
}
