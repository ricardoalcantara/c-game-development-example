#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>
#include <GL/glew.h>

class TextureLoader
{
public:
    TextureLoader();
    ~TextureLoader();

    GLuint getTextureID(std::string texFileName);
};
#endif