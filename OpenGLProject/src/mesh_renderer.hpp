#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <btBulletDynamicsCommon.h>

#include "camera.hpp"
#include "light_renderer.hpp"

#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H
class MeshRenderer
{
private:
    Camera* camera;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    glm::mat4 modelMatrix;

    glm::vec3 position, scale;
    GLuint vao, vbo, ebo, program, texture;
public:
    btRigidBody* rigidBody;
    std::string name = "";

public:
    MeshRenderer(MeshType modelType, std::string _name, Camera* _camera, btRigidBody* _rigidBody);
    ~MeshRenderer();

    void draw();

    inline void setPosition(glm::vec3 _position) { position = _position; }
    inline void setScale(glm::vec3 _scale) { scale = _scale; }
    inline void setProgram(GLuint _program) { program = _program; }
    inline void setTexture(GLuint _textureID) { texture = _textureID; }
};
#endif