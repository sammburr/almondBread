#include "engine.h"

#pragma region BACKEND

engine::engine(int scr_width, int scr_height, const char* title)
{

    SCR_HEIGHT = scr_height;
    SCR_WIDTH  = scr_width;
    SCR_TITLE  = title;

    if(!InitGLFW())
    {

        return;
    }

    StartWindow();

    if(!InitGlad())
        return;

    ProcessBeginWindow();

    return;

}

engine::~engine()
{

    glfwTerminate();

    console.LogSuccsess("GLFW => terminated.");

}

bool engine::InitGLFW()
{

    if(glfwInit())
    {

        //glfw is init correctly
        console.LogSuccsess("GLFW => initialized.");

    }
    else
    {

        //glfw has failed to init
        console.LogError("GLFW => failed to initialized.");

        return false;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;

}

bool engine::InitGlad()
{

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {

        console.LogError("glad => failed to load OpenGL function pointers.");

        return false;       

    }
    else
    {

        console.LogSuccsess("glad => loaded OpenGL function pointers.");

    }

    return true;

}

bool engine::StartWindow()
{

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE, NULL, NULL);

    if (window == NULL)
    {

        console.LogError("GLFW => failed to create GLFWWindow context.");

        return false;

    }
    else
    {

        console.LogSuccsess("GLFW => succsefully created GLFWWindow context.");

    }

    glfwMakeContextCurrent(window);
    return true;

}

void engine::ProcessBeginWindow()
{

    ProcessBegin();

    while(!glfwWindowShouldClose(window))
    {

        glfwGetWindowSize(window, &windowSize.x, &windowSize.y);
        SCR_WIDTH = windowSize.x;
        SCR_HEIGHT = windowSize.y;

        ProcessInput();

        ProcessUpdate();

        ProcessDraw();    

        glfwPollEvents();

    }

    ProcessEnd();

}

#pragma endregion

#pragma region GLOBALS

/*  DEFINE GLOBAL CLASS VARS HERE */

glm::vec3 f1 = glm::vec3( 1.0f,  1.0f,  0.0f);  // TL
glm::vec3 f2 = glm::vec3( 1.0f, -1.0f,  0.0f);  // BL
glm::vec3 f3 = glm::vec3(-1.0f, -1.0f,  0.0f);  // BR
glm::vec3 f4 = glm::vec3(-1.0f,  1.0f,  0.0f);  // TR

glm::vec3 q1v1 = glm::vec3( -1.0f,  1.0f,  0.0f); // TL
glm::vec3 q1v2 = glm::vec3( -1.0f,  0.0f,  0.0f); // BL
glm::vec3 q1v3 = glm::vec3( 0.0f,  0.0f,  0.0f); // BR
glm::vec3 q1v4 = glm::vec3( 0.0f,  1.0f,  0.0f); // TR

glm::vec3 q2v1 = q1v1 + glm::vec3(1.0f,0.0f,0.0f);
glm::vec3 q2v2 = q1v2 + glm::vec3(1.0f,0.0f,0.0f);
glm::vec3 q2v3 = q1v3 + glm::vec3(1.0f,0.0f,0.0f);
glm::vec3 q2v4 = q1v4 + glm::vec3(1.0f,0.0f,0.0f);

glm::vec2 renderSize;
bool hasUpdated = false;

float scale;
glm::vec2 displacment;
glm::vec2 juliaPoint;
float maxIter;

Quad SquareFract;

Shader shader0;
Shader shaderJulia;
Shader shaderMandel;

Texture tex;

FrameBuffer frameBuffer;

Screen screen0;
Screen screen1;

int scr_width0;
int scr_height0;

/*                                */

#pragma endregion

void engine::ProcessBegin()
{

    shaderMandel.setFragmentShader(std::filesystem::current_path().append("src\\shaders\\basicMandelFragmentShader.glsl").string());
    shaderJulia.setFragmentShader(std::filesystem::current_path().append("src\\shaders\\basicJuliaFragmentShader.glsl").string());

    shaderMandel.setVertexShader(std::filesystem::current_path().append("src\\shaders\\basicVertexShader.glsl").string());
    shaderJulia.setVertexShader(std::filesystem::current_path().append("src\\shaders\\basicVertexShader.glsl").string());

    shaderMandel.compile();
    shaderJulia.compile();

    SquareFract = Quad(f1, f2, f3, f4, 1.0f, 1.0f);

    renderSize = glm::vec2(800.0f,800.0f);
    displacment = glm::vec2(0.5f, 0.5f);
    scale = 10.0f;
    juliaPoint = glm::vec2(0.0f, 0.0f);
    maxIter = 10.0f;

    tex.genTexture(renderSize.x, renderSize.y);
    screen0 = Screen(tex, q1v1, q1v2, q1v3, q1v4, 1.0f, 1.0f, renderSize, windowSize);
    screen1 = Screen(tex, q2v1, q2v2, q2v3, q2v4, 1.0f, 1.0f, renderSize, windowSize);

}

void engine::ProcessInput()
{

    if(glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    {

        if(windowSize.x > windowSize.y)
        {

            renderSize.x = (renderSize.x/windowSize.x >= 1.0f) ? renderSize.x : renderSize.x + 1.0f;
            renderSize.y = (renderSize.x/windowSize.x >= 1.0f) ? renderSize.y : renderSize.y + 1.0f;

        }
        else
        {

            renderSize.x = (renderSize.y/windowSize.y >= 1.0f) ? renderSize.x : renderSize.x + 1.0f;
            renderSize.y = (renderSize.y/windowSize.y >= 1.0f) ? renderSize.y : renderSize.y + 1.0f;

        }

        console.Log(renderSize.x);
        console.Log(renderSize.y);

        hasUpdated = true;

    }
    else if(glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {

        renderSize.x = (renderSize.x <= 5.0f) ? 10.0f : renderSize.x - 5.0f;
        renderSize.y = (renderSize.y <= 5.0f) ? 10.0f : renderSize.y - 5.0f;
    
        hasUpdated = true;

    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {

        displacment.y = displacment.y  + (0.1f/scale);

        hasUpdated = true;

    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {

        displacment.y = displacment.y - (0.1f/scale);

        hasUpdated = true;

    }


    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {

        displacment.x = displacment.x + (0.1f/scale);

        hasUpdated = true;

    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {

        displacment.x = displacment.x - (0.1f/scale);

        hasUpdated = true;

    }

    if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
    {

        scale = scale * 1.1;

        hasUpdated = true;

    }
    else if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
    {

        scale = scale / 1.1;

        hasUpdated = true;

    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {

        juliaPoint.y = juliaPoint.y + 0.01f;

        hasUpdated = true;

    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {

        juliaPoint.y = juliaPoint.y - 0.01f;

        hasUpdated = true;

    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {

        juliaPoint.x = juliaPoint.x + 0.01f;

        hasUpdated = true;

    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {

        juliaPoint.x = juliaPoint.x - 0.01f;

        hasUpdated = true;

    }

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {

        maxIter = maxIter + 10.0f;

        hasUpdated = true;

    }
    else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {

        maxIter = maxIter - 10.0f;

        hasUpdated = true;

    }

}

void engine::ProcessUpdate()
{

    if(hasUpdated || SCR_HEIGHT != scr_height0 || SCR_WIDTH != scr_width0)
    {

        hasUpdated = true;
        console.Log("updated");

    }

    scr_height0 = SCR_HEIGHT;
    scr_width0 = SCR_WIDTH;

}

void engine::ProcessDraw()
{

    float renderScale;
    if(windowSize.x > windowSize.y)
    {

        renderScale = (renderSize.x/windowSize.x >= 1.0f) ? 1.0f : renderSize.x/windowSize.x;

    }
    else
    {

        renderScale = (renderSize.y/windowSize.y >= 1.0f) ? 1.0f : renderSize.y/windowSize.y;

    }

    glm::vec3 scale_offset = glm::vec3(0.0f, 1.0f - (float)(windowSize.x)/(windowSize.y), 0.0f);
    glm::vec3 offset = glm::vec3(1.0f, 0.0f, 0.0f);

    if(hasUpdated)
    {
        screen0.Update(q1v1, q1v2 + scale_offset, q1v3 + scale_offset, q1v4, renderScale, renderScale, renderSize, windowSize);
        screen1.Update(screen0.v1 + offset, screen0.v2 + offset, screen0.v3 + offset, screen0.v4 + offset, renderScale, renderScale, renderSize, windowSize);
    

        screen1.Bind();

        shaderMandel.use();    
        shaderMandel.setVec2("screenSize", renderSize);
        shaderMandel.setFloat("scale", scale);
        shaderMandel.setVec2("displacment", displacment);
        shaderJulia.setVec2("juliaPoint", juliaPoint);
        shaderMandel.setFloat("MAX_ITERS", maxIter);
        SquareFract.Draw();  

        screen1.UnBind();
        screen1.Draw();

        screen0.Bind();

        shaderJulia.use();
        shaderJulia.setVec2("screenSize", renderSize);
        shaderJulia.setFloat("scale", scale);
        shaderJulia.setVec2("displacment", displacment);
        shaderJulia.setVec2("juliaPoint", juliaPoint);
        shaderJulia.setFloat("MAX_ITERS", maxIter);
        SquareFract.Draw();

        screen0.UnBind();
        screen0.Draw();

        hasUpdated = false;
        glfwSwapBuffers(window);
    }

}

void engine::ProcessEnd()
{

    SquareFract.Clear();

}