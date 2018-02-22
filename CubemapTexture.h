#pragma once
#include <string>
#include <array>
#include <stdio.h>
#include "Texture.h"





#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H

namespace graphics{
    class CubemapTexture{
        public:
            CubemapTexture(
                const std::string& posXFile,
                const std::string& negXFile,
                const std::string& posYFile,
                const std::string& negYFile,
                const std::string& posZFile,
                const std::string& negZFile);

            ~CubemapTexture();

            unsigned int getTexID() const;

        private:
            std::array<std::string, 6> filenames;

            unsigned int texID;

            void create();

    };
}

#endif
