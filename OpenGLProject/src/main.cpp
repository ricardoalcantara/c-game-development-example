#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.hpp"

int main(int argc, char const *argv[])
{
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
