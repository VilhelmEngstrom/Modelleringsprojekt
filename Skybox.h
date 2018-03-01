#pragma once
#include <iostream>
#include <vector>
#include "CubemapTexture.h"

#if defined _WIN32 || defined _WIN64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif
#include "dependencies/include/glew.h"


#ifndef SKYBOX_H
#define SKYBOX_H
namespace graphics{
    class Skybox{
        public:
            Skybox();
            explicit Skybox(const CubemapTexture& texture);
            ~Skybox();

            // Render skybox
            void render() const;

        private:
            std::vector<float> vertexPositions;

            // Vertex array and vertex buffer objects
            unsigned int VAO, VBO;
            // Cubemap texture
            unsigned int cMapTexID;

            // Create cube, hardcoded postions that fit OpenGL
            void generateVertexPositions();
            // Generate and bind vertex array and buffer data
            void generateRenderingData();
    };
}
#endif
