#ifndef __QUAD__
#define __QUAD__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <iostream>
#include <Windows.h>

class Quad
{
private:
    unsigned int VBO, VAO, EBO;
    //vertices are in form
    // posx, posy, posz, texCoordx, texCoordy
    float vertices[20];

    unsigned int indices[6] = {

        0, 1, 3, // first tri
        1, 2, 3  // second tri

    };

public:
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
    glm::vec3 d;

    Quad(glm::vec3, glm::vec3, glm::vec3, glm::vec3, float, float);
    Quad();

    void Clear();
    void Draw();
};

#endif