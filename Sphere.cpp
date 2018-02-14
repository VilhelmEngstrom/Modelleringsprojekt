#include "Sphere.h"

Sphere::Sphere(float rad, uint segs) : radius(rad), verticalSegs(segs > 3 ? segs : 3){
    init();
    create();
    genRenderer();
}

Sphere::~Sphere() {}

void Sphere::init(){
    // Number flat segments
    flatSegs = 2 * verticalSegs;
    // Number of vertices and indices
    nVertices = 2 + (verticalSegs-1) * (flatSegs+1);
    nIndices =  3 * (2 * flatSegs + (verticalSegs-2) * flatSegs*2);
    // Allocate
    vertices = new Vertex[nVertices];
    indices = new uint[nIndices];
}

void Sphere::create(){
    // Initalize the first (top) vertex, y points upwards
    setVertexValues(0, {0.0f, radius, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f});
    // Sweep the surface
    generateVertices();
    // Initialize last (bottom) vertex
    setVertexValues(nVertices-1, {0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.0f});

    // Associate indices with correct vertices
    generateIndices();
}

void Sphere::generateVertices(){
    double theta, phi;
    float x, y, z;
    float sinTheta;
    uint index;

    for(uint i = 0; i < verticalSegs-1; ++i){
        // theta in interval [0 , 3.14]
        theta = (double)(i+1)/verticalSegs*M_PI;
        y = cos(theta);
        sinTheta = sin(theta);
        for(uint j = 0; j <= flatSegs; ++j){
            // phi in interval [0, 2*3.14]
            phi = (double)j/flatSegs*2.0*M_PI;
            x = sinTheta*sin(phi);
            z = sinTheta*cos(phi);
            index = 1 + i * (flatSegs+1) + j;
            setVertexValues(index, {radius*x, radius*y, radius*z, x, y, z, (float)j/flatSegs, 1 - (float)(i+1)/verticalSegs});
        }
    }
}

void Sphere::generateIndices(){
    // Top
    for(uint i = 0; i < flatSegs; i++){
        setIndexValues(3*i, {0, i+1, i+2});
    }

    // Middle
    uint offset, val;
    for(uint i = 0; i < verticalSegs-2; i++){
        for(uint j = 0; j < flatSegs; j++){
            offset = 3*(flatSegs+2*(i*flatSegs+j));
            val = 1 + i*(flatSegs+1) + j;
            setIndexValues(offset, {val, val+flatSegs+1, val+1, val+1, val+flatSegs+1, val+flatSegs+2});
        }
    }

    // Bottom
    offset = 3 * (flatSegs + 2 * (verticalSegs-2) * flatSegs);
    for(uint i = 0; i < flatSegs; i++){
        setIndexValues(offset+3*i, {nVertices-1, nVertices-2-i, nVertices-3-i});
    }

}

void Sphere::setVertexValues(uint index, std::initializer_list<float> values){
    auto it = values.begin();
    vertices[index].position.x  = *it;
    vertices[index].position.y  = *(it+1);
    vertices[index].position.z  = *(it+2);
    vertices[index].normal.x    = *(it+3);
    vertices[index].normal.y    = *(it+4);
    vertices[index].normal.z    = *(it+5);
    vertices[index].texCoords.s = *(it+6);
    vertices[index].texCoords.t = *(it+7);
}

void Sphere::setIndexValues(uint index, std::initializer_list<uint> values){
    for(int i = 0; i < (values.end() - values.begin()); i++){
        indices[index+i] = *(values.begin()+i);
    }
}
