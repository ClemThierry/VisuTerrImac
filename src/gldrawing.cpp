#include "../include/gldrawing.h"
#include "../include/create_object.h"
#include <stdio.h>

void glDrawRepere(float length) {
	// dessin du repère
	glBegin(GL_LINES);
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(length,0.,0.);
		glColor3f(0.,1.,0.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,length,0.);
		glColor3f(0.,0.,1.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,0.,length);
	glEnd();
}

Vect createVect(float x, float y, float z){
	Vect newVect;
	newVect.x = x;
	newVect.y = y;
	newVect.z = z;
	return newVect;
}

Vect prodVect(Vect v1, Vect v2){
	Vect newVect;
	newVect.x = v1.y*v2.z - v1.z*v2.y;
	newVect.y = v1.z*v2.x - v1.x*v2.z;
	newVect.z = v1.x*v2.y - v1.y*v2.x;
	return newVect;
}

void drawObject(){
   //Rotate
   //ChargeText
}