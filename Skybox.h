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

            void render() const;

        private:
            std::vector<float> vertexPositions;

            unsigned int VAO, VBO;
            unsigned int cMapTexID;

            void generateVertexPositions();
            void generateRenderingData();
    };
}
#endif
