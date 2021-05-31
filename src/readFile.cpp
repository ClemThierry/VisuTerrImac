#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/readFile.h"
#include <errno.h>
#include <stdio.h>
#include <string>
#include <cstring>

infoTimac readTimac(){
    infoTimac newTimac;
    std::ifstream infile("config.timac");
    if(!infile.is_open()){
        printf("Erreur Reading Timac");
    }
    infile >> newTimac.filename;
    infile >> newTimac.xSize;
    infile >> newTimac.ySize;
    infile >> newTimac.zMin;
    infile >> newTimac.zMax;
    infile >> newTimac.zNear;
    infile >> newTimac.zFar;
    infile >> newTimac.fov;
    return newTimac;
}

IMG readMap(std::string filename){
    IMG newImage;
    std::ifstream infile(filename);
    if(!infile.is_open()){
        printf("\n Erreur Reading PBM");
    }
    std::string pgmExt;
    std::getline(infile, pgmExt);
    if(pgmExt.compare("P2")){
        printf("\n Erreur Not P2");
    }
    std::getline(infile, pgmExt);
    infile >> newImage.width;
    infile >> newImage.height;
    infile >> newImage.maxColorVal;
    newImage.data = new unsigned char[newImage.width*newImage.height];
    for (int i = 0; i < newImage.width*newImage.height; i++)
    {
        infile >> newImage.data[i];
    } 
    return newImage;
}