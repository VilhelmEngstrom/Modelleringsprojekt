#include "Renderer.h"


graphics::Renderer::Renderer(const Mesh& mesh)
: vertexArray(NULL), indexArray(NULL), nVertices(mesh.getNumberOfVertices()), nIndices(mesh.getNumberOfIndices()){
    init(mesh);
}

graphics::Renderer::~Renderer(){

}


void graphics::Renderer::render() const{
    if(!shaderProgram){
        printf("No shader has been set\n");
        return;
    }
    // Use shader
    glUseProgram(shaderProgram);
    // Bind the VAO
    glBindVertexArray(vertexArrayObj);
    // Draw
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, (void*)0);
     // Unbind VAO and shader
    glBindVertexArray(0);
    glUseProgram(0);
}


void graphics::Renderer::setShader(const std::string& shaderFile){
    shaderProgram = Shader::compile(shaderFile);
}

void graphics::Renderer::init(const Mesh& mesh){
    vertexArray = mesh.getVertices();
    indexArray = mesh.getIndices();

    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);

    setupVertexBuffer();
    setupIndexBuffer();

    unbind();
}

void graphics::Renderer::setupVertexBuffer(){
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

    // Positions
    glEnableVertexAttribArray(0);
    // Normals
    glEnableVertexAttribArray(1);
    // Textures
    glEnableVertexAttribArray(2);

    // Offsets in index array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
}

void graphics::Renderer::setupIndexBuffer(){
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(uint), indexArray, GL_STATIC_DRAW);
}

void graphics::Renderer::unbind(){
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
