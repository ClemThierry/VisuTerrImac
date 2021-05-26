#ifndef READFILE_H
#define READFILE_H
#include <string>

struct infoTimac
{
    std::string filename;
    int xSize;
    int ySize;
    int zNear;
    int zFar;
    int zMin;
    int zMax;
    int fov;
};

infoTimac readTimac();

#endif