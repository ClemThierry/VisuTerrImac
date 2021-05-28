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
	float hauteur[5][5]= {
		{0.1, 0.0, 0.2, 0.1, 0.0},
		{0.2, 0.1, 0.2, 0.1, 0.0},
		{0.1, 0.0, 0.2, 0.3, 0.0},
		{0.0, 0.0, 0.2, 0.1, 0.1},
		{0.1, 0.3, 0.2, 0.0, 0.0}
	};
	int nb_pt_per_side = 5;
    int nb_div = nb_pt_per_side - 1;
    vertex_number = nb_pt_per_side*nb_pt_per_side;
    // 2 triange par carré 
    triangle_number = 2*nb_div*nb_div;

    vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
    normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
    triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);

    unsigned int idx = 0;
    unsigned int idxn = 0;
    float width = 1.0;
    for(int i=0;i<nb_pt_per_side;i++) {
        for(int j=0;j<nb_pt_per_side;j++) {
            vertex_coord[idx++]  = - width/2.0 + j*width/(float)nb_div;
            vertex_coord[idx++]  = hauteur[i][j];
            vertex_coord[idx++]  = width/2.0 - i*width/(float)nb_div; 
            normal_coord[idxn++] = 0.0;
            normal_coord[idxn++] = 1.0;
            normal_coord[idxn++] = 0.0;
        }
    }

    unsigned int idxt = 0;
    for(int i=0;i<nb_div;i++) {
        for(int j=0;j<nb_div;j++) {
            triangle_index[idxt++] = i*nb_pt_per_side + j;
            triangle_index[idxt++] = i*nb_pt_per_side + j + 1;
            triangle_index[idxt++] = (i+1)*nb_pt_per_side + j + 1;
            triangle_index[idxt++] = i*nb_pt_per_side + j;
            triangle_index[idxt++] = (i+1)*nb_pt_per_side + j + 1;
            triangle_index[idxt++] = (i+1)*nb_pt_per_side + j;
        }
    }
	
}
