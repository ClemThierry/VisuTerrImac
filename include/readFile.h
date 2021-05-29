#ifndef __READFILE_H
#define __READFILE_H
#include <string>

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

#endif