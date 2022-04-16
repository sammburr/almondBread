#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


void Texture::genTexture(const char* a_pathToImage)
{

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(a_pathToImage, &width, &height, &nrChannels, 0);
    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else
    {

        std::cout << "Failed to load texture" << std::endl;

    }
    stbi_image_free(data);

}

void Texture::genTexture(unsigned int a_width, unsigned int a_height)
{

    texture_data = new GLubyte[a_width*a_height*3]();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, a_width, a_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


}

void Texture::updateTexture(unsigned int a_width, unsigned int a_height)
{

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, a_width, a_height, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

}

void Texture::freeTexture()
{

    glDeleteTextures(1, &texture);

}

unsigned int Texture::getID()
{

    return texture;

}