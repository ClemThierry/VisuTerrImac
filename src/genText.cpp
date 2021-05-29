#include "../include/genText.h"
#include "../include/stb_image.h"

GLuint chargeTexture(char* filepath){
    int imageW, imageH;
    unsigned char* imagePixels = stbi_load(filepath, &imageW, &imageH, nullptr, 4);
    if (!imagePixels)
    {
        printf("Error Image Not Found");
    }
    
    GLuint textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,imageW,imageH,0,GL_RGBA,GL_UNSIGNED_BYTE,imagePixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    free(imagePixels);
    return textureID;
}