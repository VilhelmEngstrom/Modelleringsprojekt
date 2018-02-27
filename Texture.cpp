#include "Texture.h"

// REALLY ugly but has to be done since stb_image can only be included in a single file.
// Putting this in a header causes redefinition whenever that header is included,
// this is a problem with the class, nothing I can do about it.
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "dependencies/include/stb_image.h"
#endif


graphics::Texture::Texture() : width(0), height(0), bitDepth(0), data(NULL) {}

graphics::Texture::Texture(const std::string& path) : width(0), height(0), bitDepth(0), data(NULL){
    loadTexture(&path[0]);
}


graphics::Texture::Texture(Texture&& tex) : width(std::move(tex.width)), height(std::move(tex.height)), bitDepth(std::move(tex.bitDepth)){
    data = tex.data;
    tex.data = NULL;
}

graphics::Texture::~Texture() {
    stbi_image_free(data);
}

graphics::Texture& graphics::Texture::operator=(Texture&& rhs){
    if(this != &rhs){
        stbi_image_free(data);

        width    = std::move(rhs.width);
        height   = std::move(rhs.height);
        bitDepth = std::move(rhs.bitDepth);

        data = rhs.data;
        rhs.data = NULL;
    }

    return *this;
}

int graphics::Texture::getWidth() const{
    return width;
}

int graphics::Texture::getHeight() const{
    return height;
}

int graphics::Texture::getBitDepth() const{
    return bitDepth;
}

unsigned char* graphics::Texture::getData(){
    return data;
}

const unsigned char* graphics::Texture::getData() const{
    return data;
}


void graphics::Texture::loadTexture(const char* cPath){
    data = stbi_load(cPath, &width, &height, &bitDepth, 0);
    if(!data){
        std::cout << "Failed to load texture " << cPath << "\n";
    }
}
