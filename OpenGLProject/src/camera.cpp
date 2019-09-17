#include "camera.hpp"

#include <glm/gtx/string_cast.hpp>

#include "log.hpp"

Camera::Camera(GLfloat FOV,
               GLfloat width,
               GLfloat height,
               GLfloat nearPlane,
               GLfloat farPlane,
               glm::vec3 camPos)
{
    cameraPos = camPos;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    viewMatrix = glm::lookAt(cameraPos, cameraFront, cameraUp);
    projectionMatrix = glm::perspective(FOV, width / height, nearPlane, farPlane);

    LOG_DEBUG("viewMatrix:\n{}", glm::to_string(viewMatrix));
    LOG_DEBUG("projectionMatrix:\n{}", glm::to_string(projectionMatrix));
}

Camera::~Camera()
{
}