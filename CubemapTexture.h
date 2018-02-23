#pragma once
#include <iostream>
#include <string>
#include <array>
#include <stdio.h>
#include "Texture.h"


#if defined _WIN32 || defined _WIN64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif
#include "dependencies/include/glew.h"


#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H

namespace graphics{
    class CubemapTexture{
        public:
            CubemapTexture(std::array<std::string, 6> files);

            ~CubemapTexture();

            unsigned int getTexID() const;

        private:

            std::array<std::string, 6> faces;

            int width, height, bitDepth;
            unsigned int texID;

            void loadCubemap();

    };
}

#endif
