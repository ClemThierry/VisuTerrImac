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

void drawCube(){
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 0.5, 0.5, -0.5);
      glVertex3f(-0.5, 0.5, -0.5);
      glVertex3f(-0.5, 0.5,  0.5);
      glVertex3f( 0.5, 0.5,  0.5);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glVertex3f( 0.5, -0.5, -0.5);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.5,  0.5, 0.5);
      glVertex3f(-0.5, 0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f( 0.5, -0.5, 0.5);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 0.5, -0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glVertex3f(-0.5, 0.5, -0.5);
      glVertex3f( 0.5, 0.5, -0.5);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-0.5, 0.5, 0.5);
      glVertex3f(-0.5,0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glVertex3f(-0.5, -0.5, 0.5);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(0.5, 0.5, -0.5);
      glVertex3f(0.5, 0.5,0.5);
      glVertex3f(0.5,-0.5, 0.5);
      glVertex3f(0.5, -0.5, -0.5);
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

void drawTerrain(){
	float white[3] = {1.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertex_coord);
	glNormalPointer(GL_FLOAT,0,normal_coord);
	glDrawElements(GL_TRIANGLES,3*triangle_number,GL_UNSIGNED_INT,triangle_index);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}