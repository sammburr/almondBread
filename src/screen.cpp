#include "screen.h"


Screen::Screen(Texture _tex, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, glm::vec3 _v4, float tilingX, float tilingY, glm::vec2 _renderSize, glm::vec2 _windowSize)
{

    v1 = _v1;
    v2 = _v2;
    v3 = _v3;
    v4 = _v4;

    renderSize = _renderSize;
    windowSize = _windowSize;

    frame.Clear();
    frame = Quad(v1, v2, v3, v4, tilingX, tilingY);

    fb.Generate();
    tex = _tex;

    sp.setVertexShader(std::filesystem::current_path().append("src\\shaders\\basicVertexShader.glsl").string());
    sp.setFragmentShader(std::filesystem::current_path().append("src\\shaders\\basicFragmentShader.glsl").string());
    sp.compile();

}

Screen::Screen()
{


    
}

void Screen::Update(glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, glm::vec3 _v4, float tilingX, float tilingY, glm::vec2 _renderSize, glm::vec2 _windowSize)
{

    v1 = _v1;
    v2 = _v2;
    v3 = _v3;
    v4 = _v4;

    renderSize = _renderSize;
    windowSize = _windowSize;

    frame.Clear();
    frame = Quad(v1, v2, v3, v4, tilingX, tilingY);

    tex.updateTexture(renderSize.x, renderSize.y);
}

void Screen::Bind()
{

    fb.Bind();
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    fb.AttachTexture(tex.getID());
    glViewport(0, 0, renderSize.x, renderSize.y);

}

void Screen::UnBind()
{

    fb.UnBind();

}

void Screen::Draw()
{

    glViewport(0, 0, windowSize.x, windowSize.y);
    sp.use();
    sp.setInt("texture0", 0);
    frame.Draw();

}

void Screen::Clear()
{

    tex.freeTexture();
    frame.Clear();

}