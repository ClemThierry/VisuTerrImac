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

Vect createVect(float x, float y, float z);

Vect prodVect(Vect v1, Vect v2);

void drawObject(GLuint texture_id,float objH,float x, float y, float z, float yaw);

#endif