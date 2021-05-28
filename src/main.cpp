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
#include "../include/camera.h"

#define STEP_ANGLE	M_PI/90.
#define STEP_PROF	0.05

GLuint texture;

float latitude=0;
float longitude=0;
camera *cam;

void display(){
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	glPushMatrix();

		glm::mat4 perspective = cam->calculermatrice();
        glLoadMatrixf(glm::value_ptr(perspective));

		glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
		glRotatef(-(latitude/M_PI)*180,0.,0.,1.);
		glRotatef(-(longitude/M_PI)*180,1.,0.,0.);
		glDepthMask(GL_FALSE);
		drawSkyBox(texture);
		glDrawRepere(2.0);
		glDepthMask(GL_TRUE);
		//drawCube();
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
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
			//posY-=STEP_PROF;
      cam->avancer(0.1);
			break;
		case GLUT_KEY_DOWN :
			//posY+=STEP_PROF;
      cam->avancer(-0.1);
			break;
		case GLUT_KEY_LEFT :
			//posX-=STEP_PROF;
			break;
		case GLUT_KEY_RIGHT :
			//posX+=STEP_PROF;
			break;
		case GLUT_KEY_PAGE_UP :
			//posZ+=STEP_PROF;
			break;
		case GLUT_KEY_PAGE_DOWN :
			//posZ-=STEP_PROF;
			break;
		default:
			printf("Appui sur une touche spéciale\n");
	}
	glutPostRedisplay();
}

void init(){
	cam = new camera(M_PI/3, 0.3, 10000, 500, 500);
    //select clearing (background) color
    glClearColor(0.3,0.3,0.3,1.0);
    //initialize viewing values 
    glLoadIdentity();

	createCoordinates();//creation coordonnées de la map

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  float light_color[] = { 253.0f/255, 184.0/255, 19.0f/255, 1.0f };
  float light_pos[] = { 0.0f, 0.0f, 10.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
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
