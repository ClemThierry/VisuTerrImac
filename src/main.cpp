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
#include "../include/quadtree.h"
#include "../include/heightmap.h"

GLuint texture;

float yaw = 0.;
float tilt = 0.;
camera *cam;
const unsigned char mapdata[] = {
  255, 128, 255,
  255, 128, 255,
  255, 128, 255
};
glm::vec2 minp(-10.0f, -10.0f);
glm::vec2 maxp(10.0f, 10.0f);
HeightMap map(maxp - minp, mapdata, 3, 3, 255);

void display(){

    Quad qt;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();

    glPushMatrix();

        glm::mat4 perspective = cam->calculermatrice();
        glLoadMatrixf(glm::value_ptr(perspective));

        qt.build(minp, maxp, perspective);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE);
        drawSkyBox(texture);
        glDrawRepere(2.0);
        glDepthMask(GL_TRUE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        qt.render(minp, maxp, &map);
    
    glPopMatrix();

    glFinish();

    glutSwapBuffers();
}

static void kbdFunc(unsigned char c, int x, int y) {
	switch(c) {
		case 27 :
			exit(0);
			break;
		case 'Z' : case 'z' : 
			if(tilt < 0.5)tilt+= STEP_ANGLE;
			break;
		case 'S' : case 's' : 
			if(tilt > -0.5) tilt-= STEP_ANGLE;
			break;
		case 'F' : case 'f' : 
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		case 'P' : case 'p' : 
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;
		default:
			printf("Appui sur la touche %c\n",c);
	}
  cam->setangle(yaw,tilt);
	glutPostRedisplay();
}

static void kbdSpFunc(int c, int x, int y) {
	switch(c) {
		case GLUT_KEY_UP :
      cam->avancer(0.1);
			break;
		case GLUT_KEY_DOWN :
      cam->avancer(-0.1);
			break;
		case GLUT_KEY_LEFT :
			yaw+=0.1;
			break;
		case GLUT_KEY_RIGHT :
			yaw-=0.1;
			break;
		case GLUT_KEY_PAGE_UP :
			//posZ+=1;
			break;
		case GLUT_KEY_PAGE_DOWN :
			//posZ-=1;
			break;
		default:
			printf("Appui sur une touche spéciale\n");
	}
	cam->setangle(yaw,tilt);
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
