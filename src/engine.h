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

    #pragma endregion

    /*  DEFINE GLOBAL CLASS VARS HERE */

    glm::vec2 renderSize;
    float scale;
    glm::vec2 displacment;
    glm::vec2 juliaPoint;
    float maxIter;

    Quad Square0; 
    Quad Square1;

    Shader shader0;
    Shader shader1;

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