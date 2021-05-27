#include "create_object.h"
// #include "./include/ReadPGM"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int vertex_number;
float* vertex_coord;
float* normal_coord;
unsigned int triangle_number;
unsigned int* triangle_index;



void createCoordinates() {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets consistituant les triangles (triangle_index)
	// CUBE
	vertex_number = 24;
	triangle_number = 12;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
	
	// CONSTRUIRE LES TABLEAUX
	float width = 1.0;
	float coord[3*24] = {
		// Face front (z = -width/2) (E,F,G,H)
		-width/2.0f,-width/2.0f,-width/2.0f,	// E
		width/2.0f,-width/2.0f,-width/2.0f,		// F
		width/2.0f,width/2.0f,-width/2.0f,		// G
		-width/2.0f,width/2.0f,-width/2.0f,		// H
		// Face back (z = width/2) (A,B,C,D)
		-width/2.0f,-width/2.0f,width/2.0f,		// A
		width/2.0f,-width/2.0f,width/2.0f,		// B
		width/2.0f,width/2.0f,width/2.0f,		// C
		-width/2.0f,width/2.0f,width/2.0f,		// D
		// Face left (x = -width/2) (E,A,D,H)
		-width/2.0f,-width/2.0f,-width/2.0f,	// E
		-width/2.0f,-width/2.0f,width/2.0f,		// A
		-width/2.0f,width/2.0f,width/2.0f,		// D
		-width/2.0f,width/2.0f,-width/2.0f,		// H
		// Face right (x = +width/2) (B,F,G,C)
		width/2.0f,-width/2.0f,width/2.0f,		// B
		width/2.0f,-width/2.0f,-width/2.0f,		// F
		width/2.0f,width/2.0f,-width/2.0f,		// G
		width/2.0f,width/2.0f,width/2.0f,		// C
		// Face top (y = +width/2) (D,C,G,H)
		-width/2.0f,width/2.0f,width/2.0f,		// D
		width/2.0f,width/2.0f,width/2.0f,		// C
		width/2.0f,width/2.0f,-width/2.0f,		// G
		-width/2.0f,width/2.0f,-width/2.0f,		// H
		// Face down (y = -width/2) (A,B,F,E)
		-width/2.0f,-width/2.0f,width/2.0f,		// A
		width/2.0f,-width/2.0f,width/2.0f,		// B
		width/2.0f,-width/2.0f,-width/2.0f,		// F
		-width/2.0f,-width/2.0f,-width/2.0f		// E
	};
	float normals[3*24] = {
		// Face back (z = -width/2) (E,F,G,H)
		0.0f,0.0f,-1.0f,	0.0f,0.0f,-1.0f,	0.0f,0.0f,-1.0f,	0.0f,0.0f,-1.0f,
		// Face front (z = width/2) (A,B,C,D)
		0.0f,0.0f,1.0f,		0.0f,0.0f,1.0f,		0.0f,0.0f,1.0f,		0.0f,0.0f,1.0f,
		// Face left (x = -width/2) (E,A,D,H)
		-1.0,0.0,0.0,		-1.0,0.0,0.0,		-1.0,0.0,0.0,		-1.0,0.0,0.0,
		// Face right (x = +width/2) (B,F,G,C)
		1.0,0.0,0.0,		1.0,0.0,0.0,		1.0,0.0,0.0,		1.0,0.0,0.0,
		// Face top (y = +width/2) (D,C,G,H)
		0.0,1.0,0.0,		0.0,1.0,0.0,		0.0,1.0,0.0,		0.0,1.0,0.0,
		// Face down (y = -width/2) (A,B,F,E)
		0.0,-1.0,0.0,		0.0,-1.0,0.0,		0.0,-1.0,0.0,		0.0,-1.0,0.0
	};
	memcpy(vertex_coord,coord,3*vertex_number*sizeof(float));
	memcpy(normal_coord,normals,3*vertex_number*sizeof(float));
	unsigned int indexes[3*12] = {
		// Face front (z = -width/2) (E,F,G,H)
		0,1,2,		0,2,3,
		// Face back (z = width/2) (A,B,C,D)
		4,5,6,		4,6,7,
		// Face left (x = -width/2) (E,A,D,H)
		8,9,10,		8,10,11,
		// Face right (x = +width/2) (B,F,G,C)
		12,13,14,		12,14,15,
		// Face top (y = +width/2) (D,C,G,H)
		16,17,18,		16,18,19,
		// Face down (y = -width/2) (A,B,F,E)
		20,21,22,		20,22,23
	};
	memcpy(triangle_index,indexes,3*triangle_number*sizeof(float));
	
}
