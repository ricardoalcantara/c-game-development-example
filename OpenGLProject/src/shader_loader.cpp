#include "shader_loader.hpp"

// #include<iostream>
#include<fstream>
#include<vector>

#include "log.hpp"

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

// Private
std::string ShaderLoader::ReadShader(const char *filename)
{
    std::string shaderCode;
    std::ifstream file(filename, std::ios::in);

    if (!file.good())
    {
        LOG_ERROR("Can't read file {}", filename);
        std::terminate();
    }

    file.seekg(0, std::ios::end);
    shaderCode.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&shaderCode[0], shaderCode.size());
    file.close();

    // LOG_DEBUG("Read Shader: {} - {}", filename, shaderCode);
    return shaderCode;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType,
                        std::string source,
                        const char *shaderName)
{
    int compile_result = 0;

    GLuint shader = glCreateShader(shaderType);
    const char* shader_code_ptr = source.c_str();
    const int shader_code_size = source.size();
    glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

    if (compile_result == GL_FALSE)
    {
        int info_log_length = 0;
        std::vector<char> shader_log(info_log_length);

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
        LOG_ERROR("Error Compiling Shader: {} -> {}", shaderName, shader_log[0]);

        return 0;
    }
    // LOG_DEBUG("Created Shader: {} - {}", shaderName, source);

    return shader;
}

// Public
GLuint ShaderLoader::CreateProgram(const char *vertexShaderFilename,
                         const char *fragmentShaderFilename)
{
    std::string vertex_shader_code = ReadShader(vertexShaderFilename);
    std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

    GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "Vertex Shader");
    GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "Fragment Shader");

    int link_result = 0;

    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &link_result);

    if (link_result == GL_FALSE)
    {
        int info_log_length = 0;
        std::vector<char> program_log(info_log_length);

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
        glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);

        LOG_ERROR("Shader Loader: LINK ERROR {}", program_log[0]);

        return 0;
    }

    return program;
}