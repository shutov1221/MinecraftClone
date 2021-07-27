#include "SSAO.h"

SSAO::SSAO(Camera* camera) :
    camera(camera)
{
    screenHeight = Window::GetHeight();
    screenWidth = Window::GetWidth();

    std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
    this->randomFloats = randomFloats;
    ssaoKernel.resize(64);
    ssaoNoise.resize(16);

    shaderGeometryPass = ShaderCollection::GetShader(ShaderType::SSAOGeometryShader);
    shaderSSAO = ShaderCollection::GetShader(ShaderType::SSAOShader);
    shaderSSAOBlur = ShaderCollection::GetShader(ShaderType::SSAOBlurShader);

    gBuff = new GBuffer();
    gBuff->Create();

    enabled = true;
}

SSAO::~SSAO() {

    glDeleteFramebuffers(1, &ssaoFBO);
    glDeleteFramebuffers(1, &ssaoBlurFBO);
    glDeleteTextures(1, &ssaoColorBuffer);
    glDeleteTextures(1, &ssaoColorBufferBlur);

    delete gBuff;
}

void SSAO::Init() {
    fillKernel();

    GenColorBuffer();
    GenColorBufferBlur();
    GenNoiseTexture();

    shaderSSAO->use();
    shaderSSAO->setInt("gPosition", 0);
    shaderSSAO->setInt("gNormal", 1);
    shaderSSAO->setInt("texNoise", 2);
    shaderSSAO->setFloat("screenWidth", (float)screenWidth);
    shaderSSAO->setFloat("screnHeight", (float)screenHeight);

    shaderSSAOBlur->use();
    shaderSSAOBlur->setInt("ssaoInput", 0);

    shaderSSAOBlur->use();
    shaderGeometryPass->setInt("invertedNormals", 0);
}

void SSAO::Update() {
    if (screenHeight != Window::GetHeight() ||
        screenWidth != Window::GetWidth())
    {
        screenHeight = Window::GetHeight();
        screenWidth = Window::GetWidth();

        glDeleteFramebuffers(1, &ssaoFBO);
        glDeleteFramebuffers(1, &ssaoBlurFBO);

        glDeleteTextures(1, &ssaoColorBuffer);
        glDeleteTextures(1, &ssaoColorBufferBlur);

        GenColorBuffer();
        GenColorBufferBlur();
    }
}

void SSAO::GeometricPass(Renderer* geometry) {
    glBindFramebuffer(GL_FRAMEBUFFER, gBuff->Get_ID());

        geometry->Clear();
        geometry->useShader(shaderGeometryPass);
        World::Draw(geometry);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAO::SSAO_Pass(Renderer* screen) {
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
        glClear(GL_COLOR_BUFFER_BIT);

        screen->useShader(shaderSSAO);

        shaderSSAO->setFloat("screenWidth", (float)screenWidth);
        shaderSSAO->setFloat("screnHeight", (float)screenHeight);

        for (unsigned int i = 0; i < 64; ++i) {
            shaderSSAO->setVec3("samples[" + std::to_string(i) + "]", ssaoKernel[i]);
        }

        shaderSSAO->setMat4("projection", camera->GetProjectionMatrix());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gBuff->GetGPosition());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gBuff->GetGNormals());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, noiseTexture);

        screen->Render(nullptr, GL_TRIANGLE_STRIP);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAO::SSAO_Blur_Pass(Renderer* screen) {
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
        glClear(GL_COLOR_BUFFER_BIT);

        screen->useShader(shaderSSAOBlur);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);

        screen->Render(nullptr, GL_TRIANGLE_STRIP);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint SSAO::CalculateSSAO(Renderer* geometry, Renderer* screen) {
    
    gBuff->Update();
    Update();

    if (enabled) {
        GeometricPass(geometry);
        SSAO_Pass(screen);
        SSAO_Blur_Pass(screen);

        return ssaoColorBufferBlur;
    }

    return -1;
}

void SSAO::Enable() {
    enabled = true;
}

void SSAO::Disable() {
    enabled = false;
}

void SSAO::GenColorBuffer() {
    glGenFramebuffers(1, &ssaoFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);

        glGenTextures(1, &ssaoColorBuffer);
        glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, screenWidth, screenHeight, 0, GL_RED, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "SSAO Framebuffer not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAO::GenColorBufferBlur() {
    glGenFramebuffers(1, &ssaoBlurFBO);

    glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);

        glGenTextures(1, &ssaoColorBufferBlur);
        glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, screenWidth, screenHeight, 0, GL_RED, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAO::GenNoiseTexture() {
    for (unsigned int i = 0; i < 16; i++)
    {
        glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f);
        ssaoNoise[i] = noise;
    }

    glGenTextures(1, &noiseTexture);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void SSAO::fillKernel() {
    for (unsigned int i = 0; i < 64; ++i)
    {
        glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);
        float scale = float(i) / 64.0f;

        scale = lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        ssaoKernel[i] = sample;
    }
}
