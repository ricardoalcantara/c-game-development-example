#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.hpp"
#include "shader_loader.hpp"
#include "camera.hpp"
#include "light_renderer.hpp"

Camera* camera;
LightRenderer* light;

void renderScene();
void initGame();

static void glfwError(int id, const char* description)
{
    LOG_ERROR("glfwError: {}", description);
}


int main(int argc, char const *argv[])
{
    glfwSetErrorCallback(&glfwError);

    LOG_INFO("Hello OpenGL =D");
    glfwInit();
    LOG_DEBUG("glfw initialized");
    GLFWwindow* window = glfwCreateWindow(800, 600, " Hello OpenGL ", NULL, NULL);
    if (!window)
    {
        LOG_ERROR("window was not created");
        glfwTerminate();
        LOG_DEBUG("glfw terminated");
        exit(EXIT_FAILURE);

    }
    LOG_DEBUG("window created");

    glfwMakeContextCurrent(window);
    LOG_DEBUG("window made current context");

    glewInit();
    LOG_DEBUG("glew initialized");
    
    initGame();

    while (!glfwWindowShouldClose(window)){
        // render our scene
        renderScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    LOG_DEBUG("glfw terminated");

    delete camera;
    delete light;
    return 0;
}

void initGame()
{
    glEnable(GL_DEPTH_TEST);

    ShaderLoader shader;

    GLuint flatShaderProgram = shader.CreateProgram(
        "assets/shaders/flat_model.vs",
        "assets/shaders/flat_model.fs");
    

    camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));
    
    light = new LightRenderer(MeshType::kTriangle, camera);
    light->setProgram(flatShaderProgram);
    light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(77.0/255.0, 166.0/255.0, 255.0/255.0, 1.0);
    light->draw();
}