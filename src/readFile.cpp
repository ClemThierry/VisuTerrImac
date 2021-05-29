#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/readFile.h"

infoTimac readTimac(){
    infoTimac newTimac;
    std::ifstream infile("config.timac");
    if(!infile.is_open()){
        printf("Erreur");
    }
    std::getline(infile,newTimac.filename);
    infile >> newTimac.xSize;
    infile >> newTimac.ySize;
    infile >> newTimac.zMin;
    infile >> newTimac.zMax;
    infile >> newTimac.zNear;
    infile >> newTimac.zFar;
    infile >> newTimac.fov;
    return newTimac;
}