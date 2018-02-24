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

Vertex* Mesh::getVertices() const{
    return vertices;
}

uint* Mesh::getIndices() const{
    return indices;
}


void Mesh::generateRenderer(){
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

void Mesh::render(unsigned int texID) const{
    if(renderer == NULL){
        printf("No renderer has been generated\n");
        return;
    }

    // Render geometry
    renderer->render(texID);
}


void Mesh::setVertexValues(uint index, std::initializer_list<float> values){
    const auto& it = values.begin();
    vertices[index].position.x  = *it;
    vertices[index].position.y  = *(it+1);
    vertices[index].position.z  = *(it+2);
    vertices[index].normal.x    = *(it+3);
    vertices[index].normal.y    = *(it+4);
    vertices[index].normal.z    = *(it+5);
    vertices[index].texCoords.s = *(it+6);
    vertices[index].texCoords.t = *(it+7);
}
