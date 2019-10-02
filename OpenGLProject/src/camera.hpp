#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 cameraPos;
public:
    Camera(GLfloat FOV,
           GLfloat width,
           GLfloat height,
           GLfloat nearPlane,
           GLfloat farPlane,
           glm::vec3 camPos);
    ~Camera();

    inline glm::mat4 getViewMatrix() { return viewMatrix;}
    inline glm::mat4 getProjectionMatrix() { return projectionMatrix;}
    inline glm::vec3 getCameraPosition() { return cameraPos;}
    inline glm::mat4 getViewProjectionMatrix() { return projectionMatrix * viewMatrix;}
};
#endif