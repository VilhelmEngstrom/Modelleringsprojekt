#pragma once
#include <iostream>
#include <string>

#ifndef TEXTURE_H
#define TEXTURE_H

namespace graphics{
    class Texture{
        public:
            // Initialize empty texture object
            Texture();
            // Read texture from file stored in path
            explicit Texture(const std::string& path);
            // Copying would be very resource heavy and not really necessary
            Texture(const Texture& tex) = delete;
            // Move ctor
            Texture(Texture&& tex);
            ~Texture();

            // Copying souldn't be needed
            Texture& operator=(const Texture& rhs) = delete;
            // Move assignment operator, crucial
            Texture& operator=(Texture&& rhs);

            // Getters
            int getWidth() const;
            int getHeight() const;
            int getBitDepth() const;
            unsigned char* getData();
            const unsigned char* getData() const;

        private:
            // Width, height and bits per pixel for the image
            int width, height, bitDepth;
            // Image data
            unsigned char* data;

            // Load the image using stbi_load
            void loadTexture(const char* cPath);
    };
}

#endif
