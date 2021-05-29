#ifndef __READFILE_H
#define __READFILE_H
#include <string>
#include "../include/image.h"

struct infoTimac
{
    std::string filename;
    float xSize;
    float ySize;
    float zNear;
    float zFar;
    float zMin;
    float zMax;
    float fov;
};

infoTimac readTimac();
IMG readMap(std::string filename);

#endif