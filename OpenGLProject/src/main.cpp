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
#include "text_renderer.hpp"


btDiscreteDynamicsWorld* dynamicsWorld;
Camera* camera;
LightRenderer* light;
MeshRenderer* sphere;
MeshRenderer* ground;
MeshRenderer* enemy;
TextRenderer* label;

bool grounded = false;

void renderScene();
void initGame();

static void glfwError(int id, const char* description)
{
    LOG_ERROR("glfwError: {}", description);
}

void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int modd)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    LOG_DEBUG("pressed key {} - {}", key, action);
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        if (grounded == true)
        {
            grounded = false;
            LOG_INFO("pressed up key");
            sphere->rigidBody->applyImpulse(
                btVector3(0.0f, 100.0f, 0.0f),
                btVector3(0.0f, 0.0f, 0.0f)
            );
        }
    }
}

void myTickCallback(btDynamicsWorld *dynamicWorlds, btScalar timeStep)
{
    grounded = false;

    btTransform t(enemy->rigidBody->getWorldTransform());
    t.setOrigin(t.getOrigin() + btVector3( -15.0f, 0, 0) * timeStep);

    if (t.getOrigin().x() <= -18.0f)
    {
        t.setOrigin(btVector3(18.0f, 0, 0));
    }

    enemy->rigidBody->setWorldTransform(t);
    enemy->rigidBody->getMotionState()->setWorldTransform(t);

}

int main(int argc, char const *argv[])
{
    glfwSetErrorCallback(&glfwError);

    LOG_INFO("Hello OpenGL =D");
    glfwInit();
    LOG_DEBUG("glfw initialized");
    GLFWwindow* window = glfwCreateWindow(800, 600, " Hello OpenGL ", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, updateKeyboard);

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

    delete sphere;
    delete light;
    delete ground;
    delete enemy;
    delete label;
    delete camera;
    delete dynamicsWorld;

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
    dynamicsWorld->setInternalTickCallback(myTickCallback);

    glEnable(GL_DEPTH_TEST);

    ShaderLoader shader;

    GLuint flatShaderProgram = shader.CreateProgram(
        "assets/shaders/flat_model.vs",
        "assets/shaders/flat_model.fs");
    GLuint texturedShaderProgram = shader.CreateProgram(
        "assets/shaders/textured_model.vs",
        "assets/shaders/textured_model.fs");
    GLuint litTexturedShaderProgram = shader.CreateProgram(
        "assets/shaders/lit_textured_model.vs",
        "assets/shaders/lit_textured_model.fs");
    GLuint textShaderProgram = shader.CreateProgram(
        "assets/shaders/text.vs",
        "assets/shaders/text.fs");

    TextureLoader tLoader;
    GLuint sphereTexture = tLoader.getTextureID("assets/textures/globe.jpg");
    GLuint groundTexture = tLoader.getTextureID("assets/textures/ground.jpg");

    camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 20.0f));
    
    light = new LightRenderer(MeshType::kSphere, camera, 0.1f, 0.5f);
    light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
	light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

    btCollisionShape* sphereShape = new btSphereShape(1.0f);
    btDefaultMotionState* sphereMotionState = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 5.0f, 0))
    );
    btScalar mass = 13.0;
    btVector3 sphereInertia(0, 0, 0);
    sphereShape->calculateLocalInertia(mass, sphereInertia);
    btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(
        mass,
        sphereMotionState,
        sphereShape,
        sphereInertia);
    btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    sphereRigidBody->setRestitution(0.0f);
    sphereRigidBody->setFriction(1.0f);
    sphereRigidBody->setActivationState(DISABLE_DEACTIVATION);

    dynamicsWorld->addRigidBody(sphereRigidBody);

    sphere = new MeshRenderer(MeshType::kSphere, "hero", camera, sphereRigidBody, light);
    sphere->setProgram(litTexturedShaderProgram);
    sphere->setTexture(sphereTexture);
    sphere->setScale(glm::vec3(1.0f));
    sphereRigidBody->setUserPointer(sphere);
    //
    btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f, 0.5f, 4.0f));
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1.0f, 0))
    );
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
        0.0f,
        groundMotionState,
        groundShape,
        btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    groundRigidBody->setRestitution(0.0f);
    groundRigidBody->setFriction(1.0f);
    groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

    dynamicsWorld->addRigidBody(groundRigidBody);

    ground = new MeshRenderer(MeshType::kCube, "ground", camera, groundRigidBody, light);
    ground->setProgram(litTexturedShaderProgram);
    ground->setTexture(groundTexture);
    ground->setScale(glm::vec3(4.0f, 0.5f, 4.0f));
    groundRigidBody->setUserPointer(ground);
    //
    btCollisionShape* enemyShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
    btDefaultMotionState* enemyMotionState = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(18.0f, 1.0f, 0))
    );
    btRigidBody::btRigidBodyConstructionInfo enemyRigidBodyCI(
        0.0f,
        enemyMotionState,
        enemyShape,
        btVector3(0, 0, 0));
    btRigidBody* enemyRigidBody = new btRigidBody(enemyRigidBodyCI);
    enemyRigidBody->setRestitution(0.0f);
    enemyRigidBody->setFriction(1.0f);
    // enemyRigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
    enemyRigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

    dynamicsWorld->addRigidBody(enemyRigidBody);

    enemy = new MeshRenderer(MeshType::kCube, "enemy", camera, enemyRigidBody, light);
    enemy->setProgram(litTexturedShaderProgram);
    enemy->setTexture(groundTexture);
    enemy->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
    enemyRigidBody->setUserPointer(enemy);

    label = new TextRenderer(
        "Score: 0",
        "assets/fonts/gooddog.ttf",
        64,
        glm::vec3(1.0f, 0.0f, 0.0f),
        textShaderProgram
    );
    label->setPosition(glm::vec2(320.0f, 500.0f));
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(77.0/255.0, 166.0/255.0, 255.0/255.0, 1.0);
    // glClearColor(1.0, 1.0, 0.0, 1.0);

    light->draw();
    sphere->draw();
    ground->draw();
    enemy->draw();

    label->draw();
}