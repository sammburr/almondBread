#ifndef __FRAMEBUFFER__
#define __FRAMEBUFFER__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class FrameBuffer
{
private:
    unsigned int FB;
public:
    void Generate();
    void AttachTexture(unsigned int);
    void Bind();
    void UnBind();
};

#endif