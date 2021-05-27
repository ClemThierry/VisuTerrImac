#ifndef __GL_DRAWING_H
#define __GL_DRAWING_H

#include <GL/gl.h>

typedef struct vect
{
    float x;
    float y;
    float z;
} Vect;


// Fonction de dessin d'un repere. L'axe x est rouge, l'axe y vert et l'axe z bleu.
void glDrawRepere(float length);

void drawCube();

Vect createVect(float x, float y, float z);

Vect prodVect(Vect v1, Vect v2);

//Draw Square (with triangle)

//Draw Terrain

#endif