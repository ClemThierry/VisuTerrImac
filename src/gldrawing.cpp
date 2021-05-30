#include "../include/gldrawing.h"
#include <stdio.h>
#include <math.h>

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

void drawObject(GLuint texture_id,float objH,float x, float y, float z, float yaw){
   	glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texture_id);

	glPushMatrix();
		glTranslatef(x,y,z+objH-1);
		glRotatef(yaw/M_PI*180+90,0.,0.,1.);
		glBegin(GL_QUADS);
            glTexCoord2f(0,1);
            glVertex3f(-objH,0.,-objH);
                
            glTexCoord2f(1,1);
            glVertex3f(objH,0.,-objH);
                
            glTexCoord2f(1,0);
            glVertex3f(objH,0.,objH);

            glTexCoord2f(0,0);
            glVertex3f(-objH,0.,objH);
        glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_TEXTURE_2D);
}