#include "ShadowMapping.h"

ShadowMapping::ShadowMapping(Sun* sun) :
    sun(sun)
{
    depthShader = ShaderCollection::GetShader(ShaderType::DepthMapShader);

    screenHeight = Window::GetHeight();
    screenWidth = Window::GetWidth();

    shadowHeight = screenHeight * 8;
    shadowWidth = screenWidth * 8;
}

ShadowMapping::~ShadowMapping() {
    glDeleteTextures(1, &depthMap);
    glDeleteFramebuffers(1, &depthMapFBO);
}

void ShadowMapping::Init() {
    GenDepthBuffer();
    GenDepthTexture();
}

void ShadowMapping::Update() {
    if (screenHeight != Window::GetHeight() ||
        screenWidth != Window::GetWidth())
    {
        screenHeight = Window::GetHeight();
        screenWidth = Window::GetWidth();

        shadowHeight = screenHeight * 8;
        shadowWidth = screenWidth * 8;

        glDeleteFramebuffers(1, &depthMapFBO);
        glDeleteTextures(1, &depthMap);

        GenDepthBuffer();
        GenDepthTexture();
    }
}

uint ShadowMapping::GetDepthMap(Renderer* renderer) {
    Update();

    if (enabled) {
        CalculateDepthTexture(renderer);

        return depthMap;
    }
    return 0;
}

void ShadowMapping::Enable() {
    enabled = true;
}

void ShadowMapping::Disable() {
    enabled = false;
}

void ShadowMapping::SetShadowHeight(uint height) {
    shadowHeight = height;
}

void ShadowMapping::SetShadowWidth(uint width) {
    shadowWidth = width;
}

void ShadowMapping::CalculateDepthTexture(Renderer* renderer) {
    renderer->useShader(depthShader);
    depthShader->setMat4("lightProjectionMatrix", sun->GetProjectionMatrix());
    depthShader->setMat4("lightViewMatrix", sun->GetViewMatrix());
    depthShader->setMat4("model", sun->GetModelMatrix());

    glViewport(0, 0, shadowWidth, shadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    World::Draw(renderer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapping::GenDepthTexture() {
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapping::GenDepthBuffer() {
    glGenFramebuffers(1, &depthMapFBO);
}