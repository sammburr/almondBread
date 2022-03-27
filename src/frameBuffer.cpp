#include "frameBuffer.h"

void FrameBuffer::Generate()
{

    glGenFramebuffers(1, &FB);
    glBindFramebuffer(GL_FRAMEBUFFER, FB);

    unsigned int drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBuffer::AttachTexture(unsigned int a_texture_id)
{

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, a_texture_id, 0);

}

void FrameBuffer::Bind()
{

    glBindFramebuffer(GL_FRAMEBUFFER, FB);

}

void FrameBuffer::UnBind()
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}