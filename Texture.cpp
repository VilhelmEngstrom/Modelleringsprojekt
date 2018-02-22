#include "Texture.h"

graphics::Texture::Texture() : width(0), height(0), bpp(0), imType(0), imData(NULL){
    if(glewInit() != GLEW_OK){
        printf("Texture error: Could not initialize glew\n");
        exit(EXIT_FAILURE);
    }
}

graphics::Texture::Texture(const std::string& texFile) : width(0), height(0), bpp(0), imData(NULL){
    if(glewInit() != GLEW_OK){
        printf("Texture error: Could not initialize glew\n");
        exit(EXIT_FAILURE);
    }

    if(!loadTGA(&texFile[0]))
        printf("Error loading texture '%s'\n", &texFile[0]);
}

graphics::Texture::Texture(const Texture& tex) : width(tex.width), height(tex.height), bpp(tex.bpp), imType(tex.imType){
    unsigned int size = tex.bpp * tex.height + tex.width / 8;

    imData = new byte[size];
    std::copy(tex.imData, tex.imData + size, imData);
}

graphics::Texture::Texture(Texture&& tex) : width(std::move(tex.width)), height(std::move(tex.height)), bpp(std::move(tex.bpp)), imType(std::move(tex.imType)) {
    imData = tex.imData;
    tex.imData = NULL;
}

graphics::Texture::~Texture(){
    delete[] imData;
    imData = NULL;
}

graphics::Texture& graphics::Texture::operator=(const Texture& rhs){
    Texture copy = rhs;
    std::swap(*this, copy);
    return *this;
}

graphics::Texture& graphics::Texture::operator=(Texture&& rhs){
    if(this != &rhs){
        // Free up resource
        delete[] imData;

        // Move
        width      = std::move(rhs.width);
        height     = std::move(rhs.height);
        bpp        = std::move(rhs.bpp);
        imType     = std::move(rhs.imType);
        imData     = rhs.imData;
        rhs.imData = NULL;
    }

    return *this;
}

unsigned int graphics::Texture::getWidth() const{
    return width;
}

unsigned int graphics::Texture::getHeight() const{
    return height;
}

const byte* graphics::Texture::getImData() const{
    return imData;
}

byte* graphics::Texture::getImData(){
    return imData;
}

bool graphics::Texture::loadTGA(const char* filename){
    FILE* file;
    file = fopen(filename, "rb");

    if(!file){
        printf("Error opening file %s\n", filename);
        return false;
    }

    TGAHeader header;

    size_t readSuccess;

    readSuccess = fread(&header, sizeof(header), 1, file);

    if(!readSuccess){
        fprintf(stderr, "Could not read file %s\n", filename);
        closeFile(file);
        return false;
    }

    bool success = false;


    if(memcmp(&uncompressedTGAHeader, &header, sizeof(header))){
        success = loadUncompressedTGA(file);
    }
    else if(memcmp(&compressedTGAHeader, &header, sizeof(header))){
        success = loadCompressedTGA(file);

    }
    else{
        fprintf(stderr, "Unsupported image format\n");
        closeFile(file);
        return false;
    }

    closeFile(file);
    return success;
}

bool graphics::Texture::loadCompressedTGA(FILE* file){
    TGA tga;

    if(fread(tga.header, sizeof(tga.header), 1, file) == 0){
        fprintf(stderr, "Error reading file header\n");
        return false;
    }

    if(!setTexValues(tga))
        return false;


    imData = new byte[tga.imSize];


    // Allocation failure
    if(!imData){
        fprintf(stderr, "Memory allocation not possible\n");
        return false;
    }


    return readPixels(tga, file);

}


bool graphics::Texture::loadUncompressedTGA(FILE* file){
    TGA tga;

    if(!fread(tga.header, sizeof(tga.header), 1, file)){
        fprintf(stderr, "Could not read header\n");
        return false;
    }

    if(!setTexValues(tga))
        return false;


    imData = new byte[tga.imSize];

    // Allocation failure
    if(!imData){
        fprintf(stderr, "Memory allocation not possible\n");
        return false;
    }

    // Read image data
    size_t readSize = fread(imData, 1, tga.imSize, file);

    if(readSize != tga.imSize){
        fprintf(stderr, "Could not read the entire image\n");
        return false;
    }


    // Switch color channels, BGR -> RGB
    byte temp;
    for(unsigned int i; i < tga.imSize; i += tga.bytesPerPixel){
        temp = imData[i];
        imData[i] = imData[i+2];
        imData[i+2] = temp;
    }


    return true;
}

bool graphics::Texture::setTexValues(TGA& tga){
    // Width = highbyte * 256 + lowbyte
    width = tga.header[1] * 256 + tga.header[0];
    // Height = highbyte * 256 + lowbyte
    height = tga.header[3] * 256 + tga.header[2];
    bpp = tga.header[4];

    if(width <= 0 || height <= 0 || (bpp != 24 && bpp != 32)){
        fprintf(stderr, "Invalid texture info\n");
        return false;
    }

    // Set tga values
    tga.width = width;
    tga.height = height;
    tga.bpp = bpp;

    // Set image type
    imType = (bpp == 24 ? GL_RGB : GL_RGBA);

    tga.bytesPerPixel = tga.bpp / 8;
    tga.imSize =    tga.bytesPerPixel * tga.width * tga.height;

    return true;
}

void graphics::Texture::closeFile(FILE* file) const{
    if(file != NULL){
        fclose(file);
        file = NULL;
    }
}

bool graphics::Texture::readPixels(TGA& tga, FILE* file) const{
    unsigned int pixelCount = tga.height * tga.width;
    unsigned int currentPixel = 0;
    unsigned int currentByte = 0;

    byte* colorBuffer = new byte[tga.bytesPerPixel];

    byte chunkHeader;
    while(currentPixel < pixelCount){
        chunkHeader = 0;

        // RAW chunk
        if(chunkHeader < 128){
            chunkHeader++;

            for(short i = 0; i < chunkHeader; i++){
                if(fread(colorBuffer, 1, tga.bytesPerPixel, file) != tga.bytesPerPixel){
                    fprintf(stderr, "Error reading color data\n");
                    delete[] colorBuffer;
                    return false;
                }
                swapChannels(tga, colorBuffer, currentByte);
            }
        }

        // RLE header
        else{
            chunkHeader -= 127;
            if(fread(colorBuffer, 1, tga.bytesPerPixel, file) != tga.bytesPerPixel){
                fprintf(stderr, "Error reading color data\n");
                delete[] colorBuffer;
                return false;
            }

            for(short i = 0; i < chunkHeader; i++)
                swapChannels(tga, colorBuffer, currentByte);
        }

        currentByte += tga.bytesPerPixel;
        currentPixel++;

    }

    delete[] colorBuffer;
    return true;
}

void graphics::Texture::swapChannels(TGA& tga, byte* buffer, unsigned int cByte) const{
    imData[cByte] = buffer[2];
    imData[cByte+1] = buffer[1];
    imData[cByte+2] = buffer[0];

    if(tga.bytesPerPixel == 4)
        imData[cByte+3] = buffer[3];
}

TGAHeader graphics::Texture::uncompressedTGAHeader = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

TGAHeader graphics::Texture::compressedTGAHeader   = {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0};
