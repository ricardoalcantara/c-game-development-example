#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <GL/glew.h>
#include <string>

class ShaderLoader
{
private:
    std::string ReadShader(const char *filename);
    GLuint CreateShader(GLenum shaderType,
                        std::string source,
                        const char *shaderName);

public:
    ShaderLoader();
    ~ShaderLoader();

    GLuint CreateProgram(const char *vertexShaderFilename,
                         const char *fragmentShaderFilename);
};
#endif