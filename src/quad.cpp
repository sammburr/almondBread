#include "quad.h"

Quad::Quad()
{
    for (unsigned int i = 0; i < 20; i++)
    {
        vertices[i] = 0.0f;
    }
    
}

Quad::Quad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4)
{

    vertices[0] = v1.x;
    vertices[1] = v1.y;
    vertices[2] = v1.z;
    vertices[3] = 1.0f;
    vertices[4] = 1.0f;

    vertices[5] = v2.x;
    vertices[6] = v2.y;
    vertices[7] = v2.z;
    vertices[8] = 1.0f;
    vertices[9] = 0.0f;

    vertices[10] = v3.x;
    vertices[11] = v3.y;
    vertices[12] = v3.z;
    vertices[13] = 0.0f;
    vertices[14] = 0.0f;

    vertices[15] = v4.x;
    vertices[16] = v4.y;
    vertices[17] = v4.z;
    vertices[18] = 0.0f;
    vertices[19] = 1.0f;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

// A Destructor cannot be used, because for some reason it is called when still in scope of engine class...
// This provides same purpose, need to remeber to call it.
void Quad::Clear()
{

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}

void Quad::Draw()
{

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}