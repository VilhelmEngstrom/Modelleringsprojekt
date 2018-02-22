#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>


#if defined _WIN32 || defined _WIN64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif
#include "dependencies/include/glew.h"


typedef unsigned char byte;

#ifndef TGAHEADER_H
#define TGAHEADER_H

// TGA file header for determining type
typedef struct{
    byte Header[12];
} TGAHeader;

#endif


#ifndef TGA_H
#define TGA_H

typedef struct{
    byte header[6];
    // Bytes per pixel (3 or 4)
    unsigned int bytesPerPixel;
    // Amount of memory required
    unsigned int imSize;
    unsigned int imType;
    unsigned int height;
    unsigned int width;
    // Bits per pixel (24 or 32)
    unsigned int bpp;
} TGA;

#endif

#ifndef TEXTURE_H
#define TEXTURE_H

namespace graphics{
    class Texture {
        public:
            Texture();
            explicit Texture(const std::string& texFile);
            Texture(const Texture& tex);
            // Move ctor
            Texture(Texture&& tex);
            ~Texture();

            Texture& operator=(const Texture& rhs);
            // Move operator=
            Texture& operator=(Texture&& rhs);

            unsigned int getWidth() const;
            unsigned int getHeight() const;
            const byte* getImData() const;
            byte* getImData();

        private:
            unsigned int width;
            unsigned int height;
            unsigned int bpp;
            unsigned int imType;
            byte* imData;

            static TGAHeader uncompressedTGAHeader, compressedTGAHeader;

            bool loadTGA(const char* filename);

            bool loadCompressedTGA(FILE* file);
            bool loadUncompressedTGA(FILE* file);

            bool setTexValues(TGA& tga);

            void closeFile(FILE* file) const;

            bool readPixels(TGA& tga, FILE* file) const;

            void swapChannels(TGA& tga, byte* buffer, unsigned int cByte) const;
    };
}

#endif
