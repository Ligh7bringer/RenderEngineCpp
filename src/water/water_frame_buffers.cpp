#include "water_frame_buffers.h"

#include <glad/glad.h>

#include <engine/window_manager.h>
#include <utilities/gl_error.h>

WaterFrameBuffers::WaterFrameBuffers() {
    initReflectionBuffer();
    initRefractionBuffer();
}

void WaterFrameBuffers::initReflectionBuffer() {
    _reflectionFrameBuffer = createFrameBuffer();
    _reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    _reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::initRefractionBuffer() {
    _refractionFrameBuffer = createFrameBuffer();
    _refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    _refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    unbindCurrentFrameBuffer();
}

unsigned int WaterFrameBuffers::createFrameBuffer() {
    unsigned int frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    return frameBuffer;
}

unsigned int WaterFrameBuffers::createTextureAttachment(int width, int height) {
    check_gl_error();

    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

    check_gl_error();

    return tex;
}

unsigned int WaterFrameBuffers::createDepthTextureAttachment(int width, int height) {
    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex, 0);
    return tex;
}

unsigned int WaterFrameBuffers::createDepthBufferAttachment(int width, int height) {
    unsigned int depthBuffer;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    return depthBuffer;
}

void WaterFrameBuffers::bindFrameBuffer(unsigned int framebuffer, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, width, height);
}

void WaterFrameBuffers::unbindCurrentFrameBuffer() {
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   auto windowSize = WindowManager::getWindowSize();
   glViewport(0, 0, static_cast<GLsizei>(windowSize.x), static_cast<GLsizei>(windowSize.y));
}

void WaterFrameBuffers::bindReflectionFrameBuffer() {
    bindFrameBuffer(_reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFrameBuffers::bindRefractionFrameBuffer() {
    bindFrameBuffer(_refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

WaterFrameBuffers::~WaterFrameBuffers() {
//    glDeleteFramebuffers(1, &_reflectionFrameBuffer);
//    glDeleteTextures(1, &_reflectionTexture);
//    glDeleteRenderbuffers(1, &_reflectionDepthBuffer);
//    glDeleteFramebuffers(1, &_refractionFrameBuffer);
//    glDeleteTextures(1, &_refractionTexture);
//    glDeleteTextures(1, &_refractionDepthTexture);
}

unsigned int WaterFrameBuffers::getReflectionTexture() const {
    return _reflectionTexture;
}

unsigned int WaterFrameBuffers::getRefractionTexture() const {
    return _refractionTexture;
}

unsigned int WaterFrameBuffers::getRefractionDepthTexture() const {
    return _refractionDepthTexture;
}