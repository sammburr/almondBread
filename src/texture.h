#ifndef __TEXTURE__
#define __TEXTURE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Texture
{
private:
    unsigned int texture;

    const char* imageSource;
    
public:
    //CURRENTLY NOT FUNCTIONAL
    //void genTexture(int a_textureSpot, const char* a_pathToImage);
    void genTexture(unsigned int a_width, unsigned int a_height);
    void genTexture(const char* a_pathToImage);
    unsigned int getID();
    void freeTexture();

};

#endif