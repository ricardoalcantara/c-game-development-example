#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "log.hpp"

int main(int argc, char const *argv[])
{
    glm::vec3 vec{0.0, 0.0, 0.0};
    glfwInit();
    LOG_INFO("Hello OpenGL =D");
    GLFWwindow* window = glfwCreateWindow(800, 600, " Hello OpenGL ", NULL, NULL);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)){
        // render our scene
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
