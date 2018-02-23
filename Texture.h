#pragma once
#include <iostream>
#include <string>

#ifndef TEXTURE_H
#define TEXTURE_H

namespace graphics{
    class Texture{
        public:
            Texture();
            explicit Texture(const std::string& path);
            Texture(const Texture& tex) = delete;
            Texture(Texture&& tex);
            ~Texture();

            Texture& operator=(const Texture& rhs) = delete;
            Texture& operator=(Texture&& rhs);

            int getWidth() const;
            int getHeight() const;
            int getBitDepth() const;
            unsigned char* getData();
            const unsigned char* getData() const;

        private:
            int width, height, bitDepth;
            unsigned char* data;

            void loadTexture(const char* cPath);
    };
}

#endif
