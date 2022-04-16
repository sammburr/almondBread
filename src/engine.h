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

#include "screen.h"

#include "quad.h"
#include "shader.h"
#include "texture.h"
#include "frameBuffer.h"
#include "console.h"

class engine
{
private:

    #pragma region BACKEND

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

    Console console = Console("engine.cpp");
    GLFWwindow* window;
    glm::ivec2 windowSize;

    #pragma endregion


public:

    engine(int, int, const char*); // Constructor
    ~engine();                     // Destructor

    int SCR_WIDTH;
    int SCR_HEIGHT;
    const char* SCR_TITLE;

};

#endif