#ifndef READPGM_H
#define READPGM_H

#include <stdio.h>

// Structure for storing the
// image data
typedef struct PGMImage {
	char pgmType[3];
	unsigned int width;
	unsigned int height;
	unsigned int maxValue;
	unsigned char** data; 

} PGMImage;

void ignoreComments(FILE* fp);
bool openPGM(PGMImage* pgm, const char* filename);
void printImageDetails(PGMImage* pgm, const char* filename);

#endif