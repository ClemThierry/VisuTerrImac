#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "../include/main.h"
#include "../include/gldrawing.h"

float longitude = 40.;
float latitude = 40.;
float angle = M_PI/2.;

float posX = 0.;
float posY = 0.;
float posZ = 0.;

void display(){

	Vect pVise = createVect(posX+cos(longitude)*sin(latitude),posY+sin(longitude)*sin(latitude),posZ+cos(latitude));
	Vect vise = createVect(cos(longitude)*sin(latitude),sin(longitude)*sin(latitude),cos(latitude));
	Vect vectL = createVect(cos(longitude + angle),sin(longitude + angle),0.);
	Vect vectUp = prodVect(vise,vectL);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	glPushMatrix();
    
		gluLookAt(posX,posY,posZ,pVise.x,pVise.y,pVise.z,vectUp.x,vectUp.y,vectUp.z);
		glColor3f(1.0,0.0,0.0);
		glDrawRepere(5.0);

		glEnable(GL_LIGHT0);
    
	glPopMatrix();

	glFinish();

	glutSwapBuffers();
}

static void kbdFunc(unsigned char c, int x, int y) {
	switch(c) {
		case 27 :
			exit(0);
			break;
		case 'D' : case 'd' : 
			latitude -= STEP_ANGLE;
			break;
		case 'E' : case 'e' : 
			latitude += STEP_ANGLE;
			break;
		case 'F' : case 'f' : 
			longitude -= STEP_ANGLE;
			break;
		case 'S' : case 's' : 
			longitude += STEP_ANGLE;
			break;
		default:
			printf("Appui sur la touche %c\n",c);
	}
	glutPostRedisplay();
}

static void kbdSpFunc(int c, int x, int y) {
	switch(c) {
		case GLUT_KEY_UP :
			posY+=STEP_PROF;
			break;
		case GLUT_KEY_DOWN :
			posY-=STEP_PROF;
			break;
		case GLUT_KEY_LEFT :
			posX-=STEP_PROF;
			break;
		case GLUT_KEY_RIGHT :
			posX+=STEP_PROF;
			break;
		case GLUT_KEY_PAGE_UP :
			posZ+=STEP_PROF;
			break;
		case GLUT_KEY_PAGE_DOWN :
			posZ-=STEP_PROF;
			break;
		default:
			printf("Appui sur une touche spéciale\n");
	}
	glutPostRedisplay();
}

void init(){
    //select clearing (background) color
    glClearColor(0.3,0.3,0.3,0.0);
    //initialize viewing values 
	glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    //Initialise GLUT with command-line parameters. 
    glutInit(&argc, argv);
    
    //Set Display Mode
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    
    //Set the window size
    glutInitWindowSize(500,500);
    
    //Set the window position
    glutInitWindowPosition(0,0);
    
    //Create the window
    glutCreateWindow("VisuTerrIMAC");
    
    //Call init (initialise GLUT
    init();
    
    //Call "display" function
    glutDisplayFunc(display);

	glutKeyboardFunc(kbdFunc);
	glutSpecialFunc(kbdSpFunc);
    
    //Enter the GLUT event loop
    glutMainLoop();

    return 0;
}