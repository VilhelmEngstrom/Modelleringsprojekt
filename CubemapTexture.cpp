#include "CubemapTexture.h"

graphics::CubemapTexture::CubemapTexture(
    const std::string& posXFile,
    const std::string& negXFile,
    const std::string& posYFile,
    const std::string& negYFile,
    const std::string& posZFile,
    const std::string& negZFile){

    filenames[0] = posXFile;
    filenames[1] = negXFile;
    filenames[2] = posYFile;
    filenames[3] = negYFile;
    filenames[4] = posZFile;
    filenames[5] = negZFile;

    create();
}

graphics::CubemapTexture::~CubemapTexture() {}

unsigned int graphics::CubemapTexture::getTexID() const{
    return texID;
}

void graphics::CubemapTexture::create(){

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    Texture tex;
    for(int i = 0; i < 6; i++){
        // Next texture
        tex = Texture(filenames.at(i));

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, tex.getWidth(), tex.getHeight(),
                                                            0, GL_RGB, GL_UNSIGNED_BYTE, tex.getImData());
    }


    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

}
