#ifndef __TEXTURE__
#define __TEXTURE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Texture
{
private:
    const GLubyte* texture_data;
    unsigned int texture;
    const char* imageSource;
    
public:
    void genTexture(unsigned int a_width, unsigned int a_height);
    void updateTexture(unsigned int a_width, unsigned int a_height);
    void genTexture(const char* a_pathToImage);
    unsigned int getID();
    void freeTexture();

};

#endif