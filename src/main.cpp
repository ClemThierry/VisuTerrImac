#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "../include/main.h"
#include "../include/gldrawing.h"
#include "../include/skybox.h"
#include "../include/create_object.h"

#define STEP_ANGLE	M_PI/90.
#define STEP_PROF	0.05

GLuint texture;

float latitude = 0.;
float longitude = M_PI/2.;
float angle = M_PI/2.;

float posX = 0.;
float posY = 0.;
float posZ = 0.;

void display(){

	Vect pVise = createVect(posX+cos(latitude)*sin(longitude),posY+sin(latitude)*sin(longitude),posZ+cos(longitude));
	Vect vise = createVect(cos(latitude)*sin(longitude),sin(latitude)*sin(longitude),cos(longitude));
	Vect vectL = createVect(cos(latitude + angle),sin(latitude + angle),0.);
	Vect vectUp = prodVect(vise,vectL);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	glPushMatrix();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHT0);
		glDrawRepere(2.0);
		glRotatef(-(latitude/M_PI)*180,0.,0.,1.);
		glRotatef(-(longitude/M_PI)*180,1.,0.,0.);
		glDepthMask(GL_FALSE);
		drawSkyBox(texture);
		glDepthMask(GL_TRUE);
		gluLookAt(posX,posY,posZ,pVise.x,pVise.y,pVise.z,vectUp.x,vectUp.y,vectUp.z);
		//drawCube();
		drawTerrain();
    
	glPopMatrix();

	glFinish();

	glutSwapBuffers();
}

static void kbdFunc(unsigned char c, int x, int y) {
	switch(c) {
		case 27 :
			exit(0);
			break;
		case 'S' : case 's' : 
			longitude+= STEP_ANGLE;
			break;
		case 'Z' : case 'z' : 
			longitude -= STEP_ANGLE;
			break;
		case 'D' : case 'd' : 
			latitude -= STEP_ANGLE;
			break;
		case 'Q' : case 'q' : 
			latitude += STEP_ANGLE;
			break;
		default:
			printf("Appui sur la touche %c\n",c);
	}
	glutPostRedisplay();
}

static void kbdSpFunc(int c, int x, int y) {
	switch(c) {
		case GLUT_KEY_UP :
			posY-=STEP_PROF;
			break;
		case GLUT_KEY_DOWN :
			posY+=STEP_PROF;
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
    glClearColor(0.3,0.3,0.3,1.0);
    //initialize viewing values 
    glLoadIdentity();
    gluPerspective(60.,1.,0.01,10000.);

	createCoordinates();//creation coordonnées de la map
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
	texture = genSkybox();
    
    //Call "display" function
    glutDisplayFunc(display);

	glutKeyboardFunc(kbdFunc);
	glutSpecialFunc(kbdSpFunc);
    
    //Enter the GLUT event loop
    glutMainLoop();

    return 0;
}