#ifndef __SCREEN__
#define __SCREEN__

#include <glad/glad.h>
#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>
#include <filesystem>

#include "quad.h"
#include "frameBuffer.h"
#include "texture.h"
#include "shader.h"

class Screen
{
private:

    glm::vec2 renderSize;
    glm::vec2 windowSize;

    Quad frame;
    FrameBuffer fb;
    Texture tex;
    Shader sp;
    

public:

    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    glm::vec3 v4;

    Screen(Texture _tex, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, glm::vec3 _v4, float _tilingX, float _tilingY, glm::vec2 _renderSize, glm::vec2 _windowSize);
    Screen();
    void Update(glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, glm::vec3 _v4, float _tilingX, float _tilingY, glm::vec2 _renderSize, glm::vec2 _windowSize);
    void Bind();
    void UnBind();
    void Draw();
    void Clear();

};

#endif