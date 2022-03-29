#include "engine.h"

#pragma execution_character_set( "utf-8" )

#define RED   71
#define GREEN 47

#pragma region BACKEND

engine::engine(int scr_width, int scr_height, const char* title)
{

    SCR_HEIGHT = scr_height;
    SCR_WIDTH  = scr_width;
    SCR_TITLE  = title;

    InitConsole();

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

    SetConsoleTextAttribute(hConsole, GREEN);
    std::cout << "(α) GLFW => terminated." << std::endl;
    SetConsoleTextAttribute(hConsole, 7);

}

void engine::InitConsole()
{

    SetConsoleOutputCP( CP_UTF8 );
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

}

bool engine::InitGLFW()
{

    if(glfwInit())
    {

        //glfw is init correctly
        SetConsoleTextAttribute(hConsole, GREEN);
        std::cout << "(α) GLFW => initialized." << std::endl;
        SetConsoleTextAttribute(hConsole, 7);

    }
    else
    {

        //glfw has failed to init
        SetConsoleTextAttribute(hConsole, RED);
        std::cout << "(β) GLFW => failed to initialized." << std::endl;
        SetConsoleTextAttribute(hConsole, 7);

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

        SetConsoleTextAttribute(hConsole, RED);
        std::cout << "(β) glad => failed to load OpenGL function pointers." << std::endl;
        SetConsoleTextAttribute(hConsole, 7);

        return false;       

    }
    else
    {

        SetConsoleTextAttribute(hConsole, GREEN);
        std::cout << "(α) glad => loaded OpenGL function pointers." << std::endl;
        SetConsoleTextAttribute(hConsole, 7);

    }

    return true;

}

bool engine::StartWindow()
{

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE, NULL, NULL);

    if (window == NULL)
    {

        SetConsoleTextAttribute(hConsole, RED);
        std::cout << "(β) GLFW => failed to create GLFWWindow context." << std::endl;
        SetConsoleTextAttribute(hConsole, 7);

        return false;

    }
    else
    {

        SetConsoleTextAttribute(hConsole, GREEN);
        std::cout << "(α) GLFW => succsefully created GLFWWindow context." << std::endl;
        SetConsoleTextAttribute(hConsole, 7);

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

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ProcessInput();

        ProcessUpdate();

        ProcessDraw();    

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    ProcessEnd();

}

#pragma endregion

void engine::ProcessBegin()
{

    shader0.setFragmentShader(std::filesystem::current_path().append("src\\shaders\\basicFragmentShader.glsl").string());
    shaderMandel.setFragmentShader(std::filesystem::current_path().append("src\\shaders\\basicMandelFragmentShader.glsl").string());
    shaderJulia.setFragmentShader(std::filesystem::current_path().append("src\\shaders\\basicJuliaFragmentShader.glsl").string());
    shader0.setVertexShader(std::filesystem::current_path().append("src\\shaders\\basicVertexShader.glsl").string());
    shaderMandel.setVertexShader(std::filesystem::current_path().append("src\\shaders\\basicVertexShader.glsl").string());
    shaderJulia.setVertexShader(std::filesystem::current_path().append("src\\shaders\\basicVertexShader.glsl").string());
    shader0.compile();
    shaderMandel.compile();
    shaderJulia.compile();

    SquareScreen1 = Quad(q1v1, q1v2, q1v3, q1v4, 1.0f, 1.0f);
    SquareScreen2 = Quad(q2v1, q2v2, q2v3, q2v4, 1.0f, 1.0f);
    SquareFract1 = Quad(f1, f2, f3, f4, 1.0f, 1.0f);
    SquareFract2 = Quad(f1, f2, f3, f4, 1.0f, 1.0f);

    renderSize = glm::vec2(800.0f,800.0f);
    displacment = glm::vec2(0.5f, 0.5f);
    scale = 10.0f;
    juliaPoint = glm::vec2(0.0f, 0.0f);
    maxIter = 10.0f;

    frameBuffer.Generate();
    frameBuffer.Bind();
    tex.genTexture(renderSize.x, renderSize.y);
    frameBuffer.AttachTexture(tex.getID());
    frameBuffer.UnBind();

}

void engine::ProcessInput()
{

    if(glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    {

        renderSize = renderSize + 5.0f;
        SquareScreen1.Clear();
        SquareScreen2.Clear();
        SquareScreen1 = Quad(q1v1, q1v2, q1v3, q1v4, renderSize.x/windowSize.x, renderSize.y/windowSize.y);
        SquareScreen2 = Quad(q2v1, q2v2, q2v3, q2v4, renderSize.x/windowSize.x, renderSize.y/windowSize.y);


    }
    else if(glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {

        renderSize = renderSize - 5.0f;
        SquareScreen1.Clear();
        SquareScreen2.Clear();
        SquareScreen1 = Quad(q1v1, q1v2, q1v3, q1v4, renderSize.x/windowSize.x, renderSize.y/windowSize.y);
        SquareScreen2 = Quad(q2v1, q2v2, q2v3, q2v4, renderSize.x/windowSize.x, renderSize.y/windowSize.y);

    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {

        displacment.y = displacment.y + 0.01f;

    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {

        displacment.y = displacment.y - 0.01f;

    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {

        displacment.x = displacment.x + 0.01f;

    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {

        displacment.x = displacment.x - 0.01f;

    }

    if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
    {

        scale = scale + 0.01f;

    }
    else if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
    {

        scale = scale - 0.01f;

    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {

        juliaPoint.y = juliaPoint.y + 0.01f;

    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {

        juliaPoint.y = juliaPoint.y - 0.01f;

    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {

        juliaPoint.x = juliaPoint.x + 0.01f;

    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {

        juliaPoint.x = juliaPoint.x - 0.01f;

    }

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {

        maxIter = maxIter + 10.0f;

    }
    else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {

        maxIter = maxIter - 10.0f;

    }

}

void engine::ProcessUpdate()
{



}

void engine::ProcessDraw()
{

    frameBuffer.Bind();
    tex.updateTexture(renderSize.x, renderSize.y);
    frameBuffer.AttachTexture(tex.getID());

    glViewport(0, 0, renderSize.x, renderSize.y);

    shaderJulia.use();
    shaderJulia.setVec2("screenSize", renderSize);
    shaderJulia.setFloat("scale", scale);
    shaderJulia.setVec2("displacment", displacment);
    shaderJulia.setVec2("juliaPoint", juliaPoint);
    shaderJulia.setFloat("MAX_ITERS", maxIter);
    SquareFract1.Draw();

    frameBuffer.UnBind();
    glViewport(0, 0, windowSize.x, windowSize.y);
    shader0.use();
    shader0.setInt("texture0", 0);
    SquareScreen1.Draw();

    frameBuffer.Bind();
    glViewport(0, 0, renderSize.x, renderSize.y);

    tex.updateTexture(renderSize.x, renderSize.y);
    frameBuffer.AttachTexture(tex.getID());

    shaderMandel.use();
    shaderMandel.setVec2("screenSize", renderSize);
    shaderMandel.setFloat("scale", scale);
    shaderMandel.setVec2("displacment", displacment);
    shaderJulia.setVec2("juliaPoint", juliaPoint);
    shaderMandel.setFloat("MAX_ITERS", maxIter);
    SquareFract2.Draw();  

    frameBuffer.UnBind();
    glViewport(0, 0, windowSize.x, windowSize.y);
    shader0.use();
    shader0.setInt("texture0", 0);
    SquareScreen2.Draw();

}

void engine::ProcessEnd()
{

    tex.freeTexture();
    SquareFract1.Clear();
    SquareFract2.Clear();
    SquareScreen1.Clear();
    SquareScreen2.Clear();

}