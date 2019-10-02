#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <btBulletDynamicsCommon.h>
#include <chrono>

#include "log.hpp"
#include "shader_loader.hpp"
#include "camera.hpp"
#include "light_renderer.hpp"
#include "mesh_renderer.hpp"
#include "texture_loader.hpp"


btDiscreteDynamicsWorld* dynamicsWorld;
Camera* camera;
LightRenderer* light;
MeshRenderer* sphere;
MeshRenderer* ground;

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

    auto previousTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)){
        // render our scene
        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();

        dynamicsWorld->stepSimulation(dt);
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
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));


    glEnable(GL_DEPTH_TEST);

    ShaderLoader shader;

    GLuint flatShaderProgram = shader.CreateProgram(
        "assets/shaders/flat_model.vs",
        "assets/shaders/flat_model.fs");

    GLuint texturedShaderProgram = shader.CreateProgram(
        "assets/shaders/textured_model.vs",
        "assets/shaders/textured_model.fs");

    TextureLoader tLoader;
    GLuint sphereTexture = tLoader.getTextureID("assets/textures/globe.jpg");
    GLuint groundTexture = tLoader.getTextureID("assets/textures/ground.jpg");

    camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 20.0f));
    
    light = new LightRenderer(MeshType::kSphere, camera);
    light->setProgram(flatShaderProgram);
    light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    btCollisionShape* sphereShape = new btSphereShape(1.0f);
    btDefaultMotionState* sphereMotionState = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10.0f, 0))
    );
    btScalar mass = 10.0;
    btVector3 sphereInertia(0, 0, 0);
    sphereShape->calculateLocalInertia(mass, sphereInertia);
    btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(
        mass,
        sphereMotionState,
        sphereShape,
        sphereInertia);
    btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    sphereRigidBody->setRestitution(1.0f);
    sphereRigidBody->setFriction(1.0f);
    dynamicsWorld->addRigidBody(sphereRigidBody);

    sphere = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody);
    sphere->setProgram(texturedShaderProgram);
    sphere->setTexture(sphereTexture);
    sphere->setScale(glm::vec3(1.0f));

    btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f, 0.5f, 4.0f));
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2.0f, 0))
    );
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
        0.0f,
        groundMotionState,
        groundShape,
        btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    groundRigidBody->setRestitution(1.0f);
    groundRigidBody->setFriction(0.9f);
    groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

    dynamicsWorld->addRigidBody(groundRigidBody);

    ground = new MeshRenderer(MeshType::kCube, camera, groundRigidBody);
    ground->setProgram(texturedShaderProgram);
    ground->setTexture(groundTexture);
    ground->setScale(glm::vec3(4.0f, 0.5f, 4.0f));
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClearColor(77.0/255.0, 166.0/255.0, 255.0/255.0, 1.0);
    glClearColor(1.0, 1.0, 0.0, 1.0);
    // light->draw();
    sphere->draw();
    ground->draw();
}