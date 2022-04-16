#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include <iostream>
#include <fstream>
#include <string>

// Sets the vertex shader of this program.
bool Shader::setVertexShader(std::string a_pathToShaderSourceFile)
{
    std::string shaderSource = this->loadShaderSource(a_pathToShaderSourceFile);
    this->vertexShaderSource = shaderSource.c_str();

    // Create the new vertex shader.
    this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    // Add the shader code to the shader.
    glShaderSource(this->vertexShaderID, 1, &this->vertexShaderSource, NULL);
    glCompileShader(this->vertexShaderID);

    if(!this->shaderCompiled(this->vertexShaderID))
        return false;

    return true;
}

bool Shader::setFragmentShader(std::string a_pathToShaderSourceFile)
{
    std::string shaderSource = this->loadShaderSource(a_pathToShaderSourceFile);
    this->fragmentShaderSource = shaderSource.c_str();

    // Create the new vertex shader.
    this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Add the shader code to the shader.
    glShaderSource(this->fragmentShaderID, 1, &this->fragmentShaderSource, NULL);
    glCompileShader(this->fragmentShaderID);

    if(!this->shaderCompiled(this->fragmentShaderID))
        return false;

    return true;
}

void Shader::setInt(const char* a_uniformName, int a_int)
{

    glUniform1i(glGetUniformLocation(shaderProgram, a_uniformName), a_int);

}

void Shader::setFloat(const char* a_uniformName, float a_float)
{

    glUniform1f(glGetUniformLocation(shaderProgram, a_uniformName), a_float);

}

void Shader::setDouble(const char* a_uniformName, double a_double)
{

    glUniform1d(glGetUniformLocation(shaderProgram, a_uniformName), a_double);

}

void Shader::setVec2(const char* a_uninformName, glm::vec2 a_vec2)
{

    glUniform2f(glGetUniformLocation(shaderProgram, a_uninformName), a_vec2.x, a_vec2.y);

}

void Shader::setVec2d(const char* a_uninformName, glm::dvec2 a_vec2d)
{

    glUniform2f(glGetUniformLocation(shaderProgram, a_uninformName), a_vec2d.x, a_vec2d.y);

}

int Shader::compile()
{
    this->shaderProgram = glCreateProgram();

    // Attach the vertex and fragment shader.
    glAttachShader(this->shaderProgram, this->vertexShaderID);
    glAttachShader(this->shaderProgram, this->fragmentShaderID);
    
    // Compile the shader.
    glLinkProgram(this->shaderProgram);

    int compiled;
    char infoLog[512];

    // Get the compile status.
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &compiled);

    if(!compiled)
    {
        glGetShaderInfoLog(this->shaderProgram, 512, NULL, infoLog);
        console.LogError("Could not complie shader program:");
        console.LogError(infoLog);
    
        return -1;
    }

    //console.LogSuccsess("Complied shader program");

    // Delete the shaders.
    glDeleteShader(this->vertexShaderID);
    glDeleteShader(this->fragmentShaderID);

    return this->shaderProgram;
}

int Shader::getUniformLocation(std::string a_uniformName)
{
    int m_location = glGetUniformLocation(this->shaderProgram, a_uniformName.c_str());

    return m_location;
}

void Shader::use()
{
    glUseProgram(this->shaderProgram);
}

std::string Shader::loadShaderSource(std::string a_pathToShaderSourceFile)
{
    std::ifstream fileReader;
    fileReader.open(a_pathToShaderSourceFile, std::ios::binary);

    // Make sure to check that the file is open.
    if(fileReader.is_open())
    {
        //console.LogSuccsess("Opened file.");
        // Set the 'cursor' at the beginning of the file.
        fileReader.seekg(0, std::ios::beg);

        std::string line;
        std::string output;
        while (std::getline(fileReader, line))
        {
            output.append(line);
            output.append("\n");
        }

        // Add a null terminator at the end of the string.
        output.append("\0");

        return output;
    }
    else
    {
        console.LogError("Could not open file.");
    }

    return "";
}

bool Shader::shaderCompiled(unsigned int a_id)
{
    int compiled;
    char infoLog[512];

    // Get the compile status.
    glGetShaderiv(a_id, GL_COMPILE_STATUS, &compiled);

    if(!compiled)
    {
        glGetShaderInfoLog(a_id, 512, NULL, infoLog);
        console.LogError("Could not compile shader:");
        console.LogError(infoLog);
    
        return false;
    }

    //console.LogSuccsess("Compiled shader");

    return true;
}