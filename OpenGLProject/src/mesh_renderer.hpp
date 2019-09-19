#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    MeshRenderer(MeshType modelType, Camera* _camera);
    ~MeshRenderer();

    void draw();

    inline void setPosition(glm::vec3 _position) { position = _position; }
    inline void setScale(glm::vec3 _scale) { scale = _scale; }
    inline void setProgram(GLuint _program) { program = _program; }
    inline void setTexture(GLuint _textureID) { texture = _textureID; }
};

MeshRenderer::MeshRenderer(MeshType modelType, Camera* _camera)
{
    camera = _camera;

    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);

    switch (modelType)
    {
    case kTriangle:
        Mesh::setTriData(vertices, indices);
        break;
    case kQuad:
        Mesh::setQuadData(vertices, indices);
        break;
    case kCube:
        Mesh::setCubeData(vertices, indices);
        break;
    case kSphere:
        Mesh::setSphereData(vertices, indices);
        break;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (offsetof(Vertex, Vertex::texture_coordinates)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::draw()
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 viewProjection = camera->getViewProjectionMatrix();
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = translationMatrix * scaleMatrix;

    glUseProgram(program);

    GLuint vpLoc = glGetUniformLocation(program, "view_projection");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(viewProjection));

    GLuint modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,  0);

    glBindVertexArray(0);
    glUseProgram(0);
}
#endif