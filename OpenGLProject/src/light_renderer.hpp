#ifndef LIGHT_RENDERER_H
#define LIGHT_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.hpp"
#include "shader_loader.hpp"
#include "camera.hpp"

class LightRenderer
{
private:
    Camera* camera;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    glm::vec3 position, color;
    GLuint vbo, ebo, vao, program;

public:
    LightRenderer(MeshType meshType, Camera* camera);
    ~LightRenderer();

    void draw();
    inline void setPosition(glm::vec3 _position) { position = _position; }
    inline void setColor(glm::vec3 _color) { color = _color; }
    inline void setProgram(GLuint _program) { program = _program; }
    inline glm::vec3 getPosition() { return position; }
    inline glm::vec3 colorPosition() { return color; }
};
#endif