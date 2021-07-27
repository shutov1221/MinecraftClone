#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>
#include <thread>
#include <random>

#include "ShaderCollection.h"
#include "Camera.h"
#include "Window.h"
#include "Texture.h"
#include "Events.h"
#include "Mesh.h"
#include "BlockProps.h"

#include "Renderer.h"
#include "BlockRenderer.h"
#include "ScreenRenderer.h"

#include "Sun.h"
#include "Sphere.h"

#include "Chunk.h"
#include "SuperChunk.h"
#include "ChunkManager.h"
#include "World.h"
#include "WorldTimer.h"
#include "Player.h"
#include "BlockWorldCollider.h" 

#include "SSAO.h"
#include "ShadowMapping.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

float deltaTime = 0.0f;
float deltaTimeFPS = 0.0f;
float lastFrame = 0.0f;
float lastFrame1 = 0.0f;

float camX = 0.0f;
float camY = 0.0f;
float camZ = 0.0f;

int frameCounter = 0;

int main() {
    Window* window = Window::Create(SCR_WIDTH, SCR_HEIGHT, "Window");
    Events events;
    events.Initialize();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    ShaderCollection::Create();
    WorldTimer::CreateClock();
    Shader* defaultShader = ShaderCollection::GetShader(ShaderType::MeshNonTransparentShader);
    Shader* sphereShader = loadShader("res/shaders/sphere_vertex.glsl", "res/shaders/sphere_fragment.glsl");

    Camera* camera = new Camera(glm::vec3(0.0f, 20.0f, 0.0f), 150.0f, glm::radians(70.0f), 0.1f, 1000.0f);
    Player* player = new Player(camera, glm::vec3(-0.0f, 50.5f, -0.0f), 2.0f, { 0.9f, 2.0f, 0.9f }, new BlockWorldCollider);

    World* world = World::CreateWorld(camera);
    BlockBase::Create();

    BlockRenderer* blockRenderer = new BlockRenderer(camera);
    ScreenRenderer* screenRenderer = new ScreenRenderer();

    Texture* grassTexture = load_texture("res/textures/atlas.png");

    Sun* sun = new Sun(glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, 800.0f, camera);
    Sphere* sphere = new Sphere(20.0f, glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 15, 15);

    ShadowMapping* shadowMapping = new ShadowMapping(sun);
    shadowMapping->Init();

    SSAO ssao(camera);
    ssao.Init();

    defaultShader->use();
    defaultShader->setInt("shadowMap", 0);
    defaultShader->setInt("blockTexture", 1);
    defaultShader->setInt("ssao", 2);

    bool fly = true;
    float playerSpeed = 40.0f;

    while (!Window::IsShouldClose())
    {
        WorldTimer::Update();
        camera->Update();
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            deltaTimeFPS = currentFrame - lastFrame1;
            lastFrame = currentFrame;
            frameCounter++;

            if (deltaTimeFPS >= 1.0 / 30.0)
            {
                std::string FPS = std::to_string((1.0 / deltaTimeFPS) * frameCounter);
                std::string ms = std::to_string((deltaTimeFPS / frameCounter) * 1000);
                std::string newTitle = "Cuba4 - " + FPS + "FPS / " + ms + "ms";
                Window::SetTitle(newTitle);

                frameCounter = 0;
                lastFrame1 = currentFrame;
            }

            if (Window::keyboard->IsKeyPressed(GLFW_KEY_ESCAPE)) {
                Window::SetShouldClose(true);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_W)) {
                player->Move(MoveDirection::FRONT, playerSpeed, fly);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_S)) {
                player->Move(MoveDirection::BACK, playerSpeed, fly);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_A)) {
                player->Move(MoveDirection::LEFT, playerSpeed, fly);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_D)) {
                player->Move(MoveDirection::RIGHT, playerSpeed, fly);
            }

            if (Window::keyboard->IsKeyPressed(GLFW_KEY_UP)) {
                //sun->position.x += deltaTime * 40.0f;
                sun->MoveAroundHemiSphere(deltaTime * 40.0f, 0.0f);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_DOWN)) {
                //sun->position.x -= deltaTime * 40.0f;
                sun->MoveAroundHemiSphere(-deltaTime * 40.0f, 0.0f);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_LEFT)) {
                //sun->position.z -= deltaTime * 40.0f;
                sun->MoveAroundHemiSphere(0.0f, -deltaTime * 40.0f);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_RIGHT)) {
                //sun->position.z += deltaTime * 40.0f;
                sun->MoveAroundHemiSphere(0.0f, deltaTime * 40.0f);
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
                //sun->position.y += deltaTime * 40.0f;
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_CAPS_LOCK)) {
                //sun->position.y -= deltaTime * 40.0f;
            }

            if (Window::keyboard->IsKeyReleased(GLFW_KEY_SPACE)) {
                player->Jump();
            }

            if (Window::keyboard->IsKeyPressed(GLFW_KEY_O)) {
                sun->viewSize += 1.0;
            }
            if (Window::keyboard->IsKeyPressed(GLFW_KEY_P)) {
                sun->viewSize -= 1.0;

                if (sun->viewSize < 1.0f) {
                    sun->viewSize = 1.0f;
                }

            }

            if (Window::keyboard->JustKeyPressed(GLFW_KEY_TAB)) {
                Window::LockCursor();
            }

            camX += -Window::mouse->dx / Window::GetWidth() * 2.0f;
            camY += -Window::mouse->dy / Window::GetHeight() * 2.0f;

            if (camY > glm::radians(90.0f)) {
                camY = glm::radians(90.0f);
            }

            if (camY < -glm::radians(90.0f)) {
                camY = -glm::radians(90.0f);
            }

            camera->Rotate(camY, camX, camZ);
        }

        screenRenderer->Clear();
        
        glClearColor(0.1f, 0.5f, 0.8f, 1.0f);
        blockRenderer->useShader(sphereShader);
        sphereShader->setMat4("cameraProjectionMatrix", camera->GetProjectionMatrix());
        sphereShader->setMat4("cameraViewMatrix", camera->GetViewMatrix());
        sphereShader->setMat4("cameraModelMatrix", camera->GetModelMatrix());

        world->Update();

        uint ssaoBlurText = ssao.CalculateSSAO(blockRenderer, screenRenderer);

        uint depthMap = shadowMapping->GetDepthMap(blockRenderer);

        glViewport(0, 0, Window::GetWidth(), Window::GetHeight());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        blockRenderer->useShader(defaultShader);

        defaultShader->setMat4("cameraProjectionMatrix", camera->GetProjectionMatrix());
        defaultShader->setMat4("cameraViewMatrix", camera->GetViewMatrix());
        defaultShader->setMat4("cameraModelMatrix", camera->GetModelMatrix());

        defaultShader->setMat4("lightProjectionMatrix", sun->GetProjectionMatrix());
        defaultShader->setMat4("lightViewMatrix", sun->GetViewMatrix());

        defaultShader->setVec3("lightPos", sun->GetPosition());
        defaultShader->setVec3("viewPos", camera->GetPosition());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glActiveTexture(GL_TEXTURE1);
        grassTexture->bind();
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, ssaoBlurText);

        World::Draw(blockRenderer);

        blockRenderer->useShader(sphereShader);
        sphere->SetPosition(sun->GetPosition());
        sphere->Draw(blockRenderer);
        if (!player->IsOnGround()) {
            //player->AddForce({ 0.0f, -9.807f, 0.0f }, ForceMode::Acceleration);
        }

        player->DrawBoundingBox(blockRenderer, {1.0f, 0.0f, 0.0f});
        player->Update();

        events.PullEvents();
    }

    delete sun;
    delete sphereShader;
    delete shadowMapping;
    delete grassTexture;
    delete camera;
    delete player;
    delete blockRenderer;
    delete screenRenderer;
    delete world;

    Window::Terminate();

    return 0;
}