#include "CubemapTexture.h"

graphics::CubemapTexture::CubemapTexture(std::array<std::string, 6> files) : faces(files){
    loadCubemap();
}

graphics::CubemapTexture::~CubemapTexture() {}

unsigned int graphics::CubemapTexture::getTexID() const{
    return texID;
}

void graphics::CubemapTexture::loadCubemap(){

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    Texture tex;
    for(unsigned int i = 0; i < faces.size(); i++){
        tex = Texture(faces.at(i));

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, tex.getWidth(), tex.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, tex.getData());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
