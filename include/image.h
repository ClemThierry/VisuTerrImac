#ifndef __IMAGE_H
#define __IMAGE_H

typedef struct Img
{
    int height;
    int width;
    unsigned char* data;
    int maxColorVal = 255;
} IMG;

#endif