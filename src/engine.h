#ifndef __ENGINE__
#define __ENGINE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <iostream>
#include <Windows.h>
#include <memory>
#include <chrono>
#include <thread>
#include <filesystem>

#include "quad.h"
#include "shader.h"
#include "texture.h"
#include "frameBuffer.h"

class engine
{
private:

    #pragma region BACKEND

    // Set up windows console for colouring and UTF-8 encoding
    void InitConsole();
    // Startup and check GLFW
    bool InitGLFW();
    // Startup and check GLAD
    bool InitGlad();
    // Starup and verify GLFW window context
    bool StartWindow();
    // Start processing the window context loop and setup callbacks
    void ProcessBeginWindow();

    // Process once before main loop begins.
    void ProcessBegin();
    // Process input here.
    void ProcessInput();
    // Process logic every tick here.
    void ProcessUpdate();
    // Draw here.
    void ProcessDraw();
    // Terminate and clear memory here.
    void ProcessEnd();

    HANDLE hConsole;
    GLFWwindow* window;
    glm::ivec2 windowSize;

    #pragma endregion

    /*  DEFINE GLOBAL CLASS VARS HERE */

    glm::vec3 f1 = glm::vec3( 1.0f,  1.0f,  0.0f);
    glm::vec3 f2 = glm::vec3( 1.0f, -1.0f,  0.0f);
    glm::vec3 f3 = glm::vec3(-1.0f, -1.0f,  0.0f);
    glm::vec3 f4 = glm::vec3(-1.0f,  1.0f,  0.0f);

    glm::vec3 q1v1 = glm::vec3( 1.0f,  1.0f,  0.0f);
    glm::vec3 q1v2 = glm::vec3( 1.0f,  0.0f,  0.0f);
    glm::vec3 q1v3 = glm::vec3( 0.0f,  0.0f,  0.0f);
    glm::vec3 q1v4 = glm::vec3( 0.0f,  1.0f,  0.0f);

    glm::vec3 q2v1 = glm::vec3( -1.0f,  1.0f,  0.0f);
    glm::vec3 q2v2 = glm::vec3( -1.0f,  0.0f,  0.0f);
    glm::vec3 q2v3 = glm::vec3( 0.0f,  0.0f,  0.0f);
    glm::vec3 q2v4 = glm::vec3( 0.0f,  1.0f,  0.0f);

    glm::vec2 renderSize;
    float scale;
    glm::vec2 displacment;
    glm::vec2 juliaPoint;
    float maxIter;

    Quad SquareScreen1; 
    Quad SquareScreen2;
    Quad SquareFract1;
    Quad SquareFract2;

    Shader shader0;
    Shader shaderJulia;
    Shader shaderMandel;

    Texture tex;

    FrameBuffer frameBuffer;


    /*                                */

public:

    engine(int, int, const char*); // Constructor
    ~engine();                     // Destructor

    int SCR_WIDTH;
    int SCR_HEIGHT;
    const char* SCR_TITLE;

    double FrameRate = 999;

};

#endif