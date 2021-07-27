#include "GBuffer.h"

GBuffer::GBuffer()
{
    screenHeight = Window::GetHeight();
    screenWidth = Window::GetWidth();

    gBuffer = 0;
    gPosition = 0;
    gNormal = 0;
    rboDepth = 0;
    gAlbedo = 0;
}

GBuffer::~GBuffer() 
{
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gAlbedo);
    glDeleteRenderbuffers(1, &rboDepth);
    glDeleteFramebuffers(1, &gBuffer);
}

void GBuffer::Create() {

    glGenFramebuffers(1, &gBuffer);
    GenTextures();
}

void GBuffer::GenTextures() {

    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

        GenGPositionTexture();
        GenGNormalsTexture();
        GenGAlbedoTexture();

        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        glDrawBuffers(3, attachments);

        GenGDepthTexture();

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "Framebuffer not complete!" << std::endl;
        }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::Update() {
    if (screenHeight != Window::GetHeight() ||
        screenWidth != Window::GetWidth())
    {
        screenHeight = Window::GetHeight();
        screenWidth = Window::GetWidth();

        glDeleteTextures(1, &gPosition);
        glDeleteTextures(1, &gNormal);
        glDeleteTextures(1, &gAlbedo);

       // unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
       // glDeleteBuffers(3, attachments);

        glDeleteRenderbuffers(1, &rboDepth);

        GenTextures();
    }
}

uint GBuffer::Get_ID() {
    return gBuffer;
}

uint GBuffer::GetGPosition() {
    return gPosition;
}

uint GBuffer::GetGAlbedo() {
    return gAlbedo;
}

uint GBuffer::GetGNormals() {
    return gNormal;
}

uint GBuffer::GetGDepth() {
    return rboDepth;
}

void GBuffer::GenGPositionTexture() {
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
}

void GBuffer::GenGNormalsTexture() {
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
}

void GBuffer::GenGAlbedoTexture() {
    glGenTextures(1, &gAlbedo);
    glBindTexture(GL_TEXTURE_2D, gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
}

void GBuffer::GenGDepthTexture() {
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
}
