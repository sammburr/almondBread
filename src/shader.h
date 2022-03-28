// Shader class is built entirely from template besides functions specified*

#ifndef __SHADER__
#define __SHADER__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <iostream>

// Creates a new shader program.
class Shader
{
private:
    unsigned int shaderProgram;

    unsigned int vertexShaderID;
    const char* vertexShaderSource;

    unsigned int fragmentShaderID;
    const char* fragmentShaderSource;

public:
    // Sets the vertex shader of this program.
    bool setVertexShader(std::string a_vertexShaderSource);
    bool setFragmentShader(std::string a_fragmentShaderSource);

    // *Custom function not from template
    void setInt(const char* a_uninformName, int a_int);
    // *Custom function not from template
    void setVec2(const char* a_uninformName, glm::vec2 a_vec2);
    // *Custom function not from template
    void setFloat(const char* a_uninformName, float a_float);

    int compile();
    void use();

private:
    int getUniformLocation(std::string a_uniformName);
    std::string loadShaderSource(std::string a_pathToShaderSourceFile);
    bool shaderCompiled(unsigned int a_id);
};

#endif