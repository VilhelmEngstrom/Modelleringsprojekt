#include "Sphere.h"

Sphere::Sphere(float rad, unsigned int segs) : radius(rad), verticalSegs(segs > 3 ? segs : 3){
    init();
    create();
    generateRenderer();
}

Sphere::Sphere(const Sphere& s) : radius(s.radius), verticalSegs(s.verticalSegs), flatSegs(s.flatSegs){
    nVertices = s.nVertices;
    nIndices = s.nIndices;

    vertices = new Vertex[nVertices];
    indices = new unsigned int[nIndices];

    std::copy(s.vertices, s.vertices+s.nVertices, vertices);
    std::copy(s.indices, s.indices+s.nIndices, indices);

    generateRenderer();
}

Sphere::~Sphere() {}

Sphere& Sphere::operator=(const Sphere& rhs){
    Sphere copy = rhs;
    std::swap(*this, copy);
    return *this;
}

float Sphere::getRadius() const{
    return radius;
}


void Sphere::init(){
    // Number flat segments
    flatSegs = 2 * verticalSegs;
    // Number of vertices and indices
    nVertices = 2 + (verticalSegs-1) * (flatSegs+1);
    nIndices =  3 * (2 * flatSegs + (verticalSegs-2) * flatSegs*2);
    // Allocate
    vertices = new Vertex[nVertices];
    indices = new unsigned int[nIndices];
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
    unsigned int index;

    for(unsigned int i = 0; i < verticalSegs-1; ++i){
        // theta in interval [0 , 3.14]
        theta = (double)(i+1)/verticalSegs*M_PI;
        y = (float)cos(theta);
        sinTheta = (float)sin(theta);
        for(unsigned int j = 0; j <= flatSegs; ++j){
            // phi in interval [0, 2*3.14]
            phi = (double)j/flatSegs*2.0*M_PI;
            x = sinTheta* (float)sin(phi);
            z = sinTheta* (float)cos(phi);
            index = 1 + i * (flatSegs+1) + j;
            setVertexValues(index, {radius*x, radius*y, radius*z, x, y, z, (float)j/flatSegs, 1 - (float)(i+1)/verticalSegs});
        }
    }
}

void Sphere::generateIndices(){
    // Top
    for(unsigned int i = 0; i < flatSegs; i++){
        setIndexValues(3*i, {0, i+1, i+2});
    }

    // Middle
    unsigned int offset, val;
    for(unsigned int i = 0; i < verticalSegs-2; i++){
        for(unsigned int j = 0; j < flatSegs; j++){
            offset = 3*(flatSegs+2*(i*flatSegs+j));
            val = 1 + i*(flatSegs+1) + j;
            setIndexValues(offset, {val, val+flatSegs+1, val+1, val+1, val+flatSegs+1, val+flatSegs+2});
        }
    }

    // Bottom
    offset = 3 * (flatSegs + 2 * (verticalSegs-2) * flatSegs);
    for(unsigned int i = 0; i < flatSegs; i++){
        setIndexValues(offset+3*i, {nVertices-1, nVertices-2-i, nVertices-3-i});
    }

}

void Sphere::setIndexValues(unsigned int index, std::initializer_list<unsigned int> values){
    for(int i = 0; i < (values.end() - values.begin()); i++){
        indices[index+i] = *(values.begin()+i);
    }
}
