#include "mesh_renderer.hpp"


MeshRenderer::MeshRenderer(MeshType modelType, Camera* _camera, btRigidBody* _rigidBody)
{
    camera = _camera;
    rigidBody = _rigidBody;

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
    btTransform t;
    rigidBody->getMotionState()->getWorldTransform(t);
    btQuaternion rotation = t.getRotation();
    btVector3 translate = t.getOrigin();
    glm::mat4 rotationMatrix = glm::rotate(
        glm::mat4(1.0f),
        rotation.getAngle(),
        glm::vec3(
            rotation.getAxis().getX(),
            rotation.getAxis().getY(),
            rotation.getAxis().getZ()
        )
    );

    glm::mat4 translationMatrix = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(
            translate.getX(),
            translate.getY(),
            translate.getZ()
        )
    );

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    glm::mat4 viewProjection = camera->getViewProjectionMatrix();
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

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