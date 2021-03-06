// C Programe to read a PGMB image
// and print its parameters
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/ReadPGM.h"
// Function to ignore any comments
// in file

void ignoreComments(FILE *fp)
{
	int ch;
	char line[100];

	// Ignore any blank lines
	while ((ch = fgetc(fp)) != EOF && isspace(ch))
		;

	// Recursively ignore comments
	// in a PGM image commented lines
	// start with a '#'
	if (ch == '#')
	{
		if(fgets(line, sizeof(line), fp))
		{
			ignoreComments(fp);
		}
		
	}
	else
		fseek(fp, -1, SEEK_CUR);
}

// Function to open the input a PGM
// file and process it
bool openPGM(PGMImage *pgm, const char *filename)
{
	// Open the image file in the
	// 'read binary' mode
	FILE *pgmfile = fopen(filename, "rb");

	// If file does not exist,
	// then return
	if (pgmfile == NULL)
	{
		printf("fopen failed, errno = %d\n", errno);
		//printf("File does not exist\n");
		return false;
	}

	ignoreComments(pgmfile);
	if(fscanf(pgmfile, "%s", pgm->pgmType))
	{
		// Check for correct PGM Binary
		// file type
		if (strcmp(pgm->pgmType, "P6"))
		{
			fprintf(stderr,"Wrong file type!\n");
			exit(EXIT_FAILURE);
		}

		ignoreComments(pgmfile);
	}

	// Read the image dimensions
	if(fscanf(pgmfile, "%d %d",&(pgm->width),&(pgm->height)))
	{
		ignoreComments(pgmfile);
	}

	

	// Read maximum gray value
	if(fscanf(pgmfile, "%d", &(pgm->maxValue))){
		ignoreComments(pgmfile);
	}
	

	// Allocating memory to store
	// img info in defined struct
	pgm->data = (unsigned char **)malloc(pgm->height * sizeof(unsigned char *));

	// Storing the pixel info in
	// the struct
	if (pgm->pgmType[1] == '6')
	{

		fgetc(pgmfile);

		for (int i = 0; i < (int)pgm->height; i++)
		{
			pgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));

			// If memory allocation
			// is failed
			if (pgm->data[i] == NULL)
			{
				fprintf(stderr,
						"malloc failed\n");
				exit(1);
			}

			// Read the gray values and
			// write on allocated memory
			
			size_t result;
			result = fread(pgm->data[i], sizeof(unsigned char), pgm->width, pgmfile);
			if(result != pgm->width){
				fputs("Reading error",stderr); exit (3);
			}
		}
	}

	// Close the file
	fclose(pgmfile);

	return true;
}

// Function to print the file details
void printImageDetails(PGMImage *pgm, const char *filename)
{
	FILE *pgmfile = fopen(filename, "rb");

	// Retreiving the file extension
	char *ext = (char *)strrchr(filename, '.');

	if (!ext)
		printf("No extension found in file %s", filename);
	else
		printf("File format : %s\n",
			   ext + 1);

	printf("PGM File type : %s\n", pgm->pgmType);

	// Print type of PGM file, in ascii
	// and binary format
	if (!strcmp(pgm->pgmType, "P2"))
		printf("PGM File Format: ASCII\n");
	else if (!strcmp(pgm->pgmType, "P5"))
		printf("PGM File Format: Binary\n");

	printf("Width of img : %d px\n", pgm->width);
	printf("Height of img : %d px\n", pgm->height);
	printf("Max Gray value : %d\n", pgm->maxValue);

//Test de ce que contient data
	for (int i = 0; i < (int)pgm->height/(int)pgm->height+2; i++)
	{
		for (int j = 0; j < (int)pgm->width; j++)
		{
			printf("data[%i][%i] = %i \n",i,j, pgm->data[i][j]);
		}	
		
	}
	fclose(pgmfile);
}



