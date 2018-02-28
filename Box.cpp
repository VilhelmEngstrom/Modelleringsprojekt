#include "Box.h"


Box::Box(float sideLength) : side(sideLength){
    create();
}

Box::Box(const Box& b){
    nVertices = b.nVertices;
    nIndices = b.nIndices;

    vertices = new Vertex[nVertices];
    indices = new unsigned int[nIndices];

    std::copy(b.vertices, b.vertices+b.nVertices, vertices);
    std::copy(b.indices, b.indices+b.nIndices, indices);

    generateRenderer();
}

Box::~Box() {}

Box& Box::operator=(const Box& rhs){
    Box copy = rhs;
    std::swap(*this, copy);
    return *this;
}

void Box::create(){
    // 24 normals => 24 vertices
    nVertices = 24;
    // 2 triangles per face, 3 vertices per triangle, 6 faces
    nIndices = 36;

    vertices = new Vertex[nVertices];
    indices = new unsigned int[nIndices];

    generateVertices();
    generateIndices();

    generateRenderer();
}

void Box::generateVertices(){
    float halfSide = side/2;

    // Vertices for each square:
    // vert 0    vert 3
    //
    // vert 1    vert 2

    // Triangle 1 for each face:
    // vert 0 -> vert 1 -> vert 2
    //
    //Triangle 2 for each face:
    // vert 0 -> vert 2 -> vert 3

    // Square facing positive z-direction
    //                       posx      posy        posz   nx  ny  nz  s  t
    setVertexValues(0,  {-halfSide,  halfSide,  halfSide,  0,  0,  1, 0, 0});
    setVertexValues(1,  {-halfSide, -halfSide,  halfSide,  0,  0,  1, 0, 1});
    setVertexValues(2,  { halfSide, -halfSide,  halfSide,  0,  0,  1, 1, 1});
    setVertexValues(3,  { halfSide,  halfSide,  halfSide,  0,  0,  1, 1, 0});

    // Square facing in positive x-direction
    setVertexValues(4,  { halfSide,  halfSide,  halfSide,  1,  0,  0, 0, 0});
    setVertexValues(5,  { halfSide, -halfSide,  halfSide,  1,  0,  0, 0, 1});
    setVertexValues(6,  { halfSide, -halfSide, -halfSide,  1,  0,  0, 1, 1});
    setVertexValues(7,  { halfSide,  halfSide, -halfSide,  1,  0,  0, 1, 0});

    // Square facing negative z-direction
    setVertexValues(8,  { halfSide,  halfSide, -halfSide,  0,  0, -1, 0, 0});
    setVertexValues(9,  { halfSide, -halfSide, -halfSide,  0,  0, -1, 0, 1});
    setVertexValues(10, {-halfSide, -halfSide, -halfSide,  0,  0, -1, 1, 1});
    setVertexValues(11, {-halfSide,  halfSide, -halfSide,  0,  0, -1, 1, 0});

    // Square facing negative x-direction
    setVertexValues(12, {-halfSide,  halfSide, -halfSide, -1,  0,  0, 0, 0});
    setVertexValues(13, {-halfSide, -halfSide, -halfSide, -1,  0,  0, 0, 1});
    setVertexValues(14, {-halfSide, -halfSide,  halfSide, -1,  0,  0, 1, 1});
    setVertexValues(15, {-halfSide,  halfSide,  halfSide, -1,  0,  0, 1, 0});

    // Square facing positive y-direction
    setVertexValues(16, {-halfSide,  halfSide, -halfSide,  0,  1,  0, 0, 0});
    setVertexValues(17, {-halfSide,  halfSide,  halfSide,  0,  1,  0, 0, 1});
    setVertexValues(18, { halfSide,  halfSide,  halfSide,  0,  1,  0, 1, 1});
    setVertexValues(19, { halfSide,  halfSide, -halfSide,  0,  1,  0, 1, 0});

    // Square facing negative y-direction
    setVertexValues(20, {-halfSide, -halfSide,  halfSide,  0, -1,  0, 0, 0});
    setVertexValues(21, {-halfSide, -halfSide, -halfSide,  0, -1,  0, 0, 1});
    setVertexValues(22, { halfSide, -halfSide, -halfSide,  0, -1,  0, 1, 1});
    setVertexValues(23, { halfSide, -halfSide,  halfSide,  0, -1,  0, 1, 0});
}

void Box::generateIndices(){
    // Index for box face
    unsigned int face = -1;
    // Vertex number
    unsigned int vertexNo = 0;

    for(unsigned int i = 0; i < nIndices; i++){
        // Next face
        if(i % 6 == 0)
            ++face;

        // First triangle
        if(((int)floor(i/3) % 2 == 0)){
            indices[i] = - 2 * face + vertexNo++;
        }
        // Second triangle
        else{
            indices[i] = indices[i-3] + (i % 3 == 0 ? 0 : 1);

        }
    }
}
