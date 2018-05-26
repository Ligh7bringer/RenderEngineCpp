#ifndef RENDERENGINE_WATER_FRAME_BUFFERS_H
#define RENDERENGINE_WATER_FRAME_BUFFERS_H


class WaterFrameBuffers {
public:
    WaterFrameBuffers();
    void cleanUp();

    void unbindCurrentFrameBuffer();
    void bindReflectionFrameBuffer();
    void bindRefractionFrameBuffer();

    ~WaterFrameBuffers();

    unsigned int getReflectionTexture() const;

    unsigned int getRefractionTexture() const;

    unsigned int getRefractionDepthTexture() const;

private:
    const int REFLECTION_WIDTH = 320;
    const int REFLECTION_HEIGHT = 180;
    const int REFRACTION_WIDTH = 1280;
    const int REFRACTION_HEIGHT = 720;

    unsigned int _reflectionFrameBuffer;
    unsigned int _reflectionTexture;
    unsigned int _reflectionDepthBuffer;

    unsigned int _refractionFrameBuffer;
    unsigned int _refractionTexture;
    unsigned int _refractionDepthTexture;

    void initReflectionBuffer();
    void initRefractionBuffer();
    unsigned int createFrameBuffer();
    void bindFrameBuffer(unsigned int framebuffer, int width, int height);
    unsigned int createTextureAttachment(int width, int height);
    unsigned int createDepthTextureAttachment(int width, int height);
    unsigned int createDepthBufferAttachment(int width, int height);
};


#endif //RENDERENGINE_WATER_FRAME_BUFFERS_H
