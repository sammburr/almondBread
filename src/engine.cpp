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

    //shader.setFragmentShader("C:/Users/Sam Burford/Desktop/Almond Bread/src/shaders/basicFragmentShader.glsl");
    shader.setFragmentShader(std::filesystem::current_path().append("src\\shaders\\basicMandelFragmentShader.glsl").string());
    shader.setVertexShader(std::filesystem::current_path().append("src\\shaders\\basicVertexShader.glsl").string());
    shader.compile();

    glm::vec3 v1 = glm::vec3( 1.0f,  1.0f,  0.0f);
    glm::vec3 v2 = glm::vec3( 1.0f, -1.0f,  0.0f);
    glm::vec3 v3 = glm::vec3(-1.0f, -1.0f,  0.0f);
    glm::vec3 v4 = glm::vec3(-1.0f,  1.0f,  0.0f);

    Square = quad(v1, v2, v3, v4);
    
    //tex.genTexture("C:\\Users\\Sam Burford\\Desktop\\Almond Bread\\src\\container.jpg");

}

void engine::ProcessInput()
{



}

void engine::ProcessUpdate()
{



}

void engine::ProcessDraw()
{

    shader.use();
    //shader.setInt("texture0", 0);
    Square.Draw();   

}

void engine::ProcessEnd()
{

    tex.freeTexture();
    Square.Clear();

}