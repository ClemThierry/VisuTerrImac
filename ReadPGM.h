#ifndef READPGM_H
#define READPGM_H

// Structure for storing the
// image data
typedef struct PGMImage {
	char pgmType[3];
	unsigned char** data; //convertir en tableau à double entrées (x,y --> coordonnées des points)
	unsigned int width;
	unsigned int height;
	unsigned int maxValue;
} PGMImage;

void ignoreComments(FILE* fp);
bool openPGM(PGMImage* pgm, const char* filename);
void printImageDetails(PGMImage* pgm, const char* filename);

#endif