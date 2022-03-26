#ifndef __QUAD__
#define __QUAD__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <iostream>
#include <Windows.h>

class quad
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
    quad(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    quad();

    void Clear();
    void Draw();
};

#endif