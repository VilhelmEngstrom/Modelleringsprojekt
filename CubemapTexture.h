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
            // Initalize with paths to the texture files
            CubemapTexture(std::array<std::string, 6> files);
            ~CubemapTexture();

            // Get the cubemap's texture id
            unsigned int getTexID() const;
        private:
            // Filenames
            std::array<std::string, 6> faces;
            // Texture id
            unsigned int texID;

            // Load the invividual textures and pass the to OpenGL
            void loadCubemap();
    };
}

#endif
