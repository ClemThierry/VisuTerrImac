#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "../include/main.h"

GLuint texture;
GLuint sol;
GLuint arbre;
const int maxArbres = 25;
int nbArbres = 10;
float tabArbres[maxArbres*3];
float arbresH = 6.;

infoTimac info;
IMG imgdata;

float yaw = 0.;
float tilt = 0.;
bool ajust = false;
camera *cam;

glm::vec2 minp;
glm::vec2 maxp;
HeightMap map;

void display(){
    if (ajust)
    {
      cam->setHeight(map);
    }

    Quad qt;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glm::mat4 proj = cam->projection();
    glLoadMatrixf(glm::value_ptr(proj));

    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();

    glPushMatrix();

        glm::mat4 vue = cam->vue();
        glLoadMatrixf(glm::value_ptr(vue));
        float light_pos[] = { 0.0f, 100.0f, 10.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

        qt.build(minp, maxp, proj * vue);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE);
        drawSkyBox(texture);
        glDrawRepere(2.0);
        glDepthMask(GL_TRUE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        qt.render(minp, maxp, &map, sol);
        for (int i = 0; i < nbArbres*3; i+=3)
        {
          drawObject(arbre,arbresH,tabArbres[i],tabArbres[i+1],tabArbres[i+2], yaw);
        }
    
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
			if(tilt < M_PI/2)tilt+= STEP_ANGLE;
			break;
		case 'S' : case 's' : 
			if(tilt > -M_PI/2) tilt-= STEP_ANGLE;
			break;
		case 'F' : case 'f' : 
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		case 'P' : case 'p' : 
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;
    case 'H' : case 'h' : 
      ajust = !ajust;
			break;
    case '1':
      if (nbArbres+1<maxArbres) nbArbres++;
      break;
    case '2':
      if (nbArbres>0) nbArbres--;
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
		default:
			printf("Appui sur une touche spéciale\n");
	}
	cam->setangle(yaw,tilt);
	glutPostRedisplay();
}

void init(){
	cam = new camera(info.fov/180*M_PI, info.zNear, info.zFar, 500, 500);
  cam->setHeight(map);

  for (int i = 0; i < maxArbres*3; i+=3)
  {
    float posXarb = std::rand()%((int)info.xSize/2)+0;
    float posYarb = std::rand()%((int)info.ySize/2)+0;
    float posZarb = map.get_height({posXarb,posYarb});
    tabArbres[i] = posXarb;
    tabArbres[i+1] = posYarb;
    tabArbres[i+2] = posZarb;
  }
  
  //select clearing (background) color
  glClearColor(0.3,0.3,0.3,1.0);
  //initialize viewing values 
  glLoadIdentity();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  float light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float light_ambient[] = { 0.0f, 0.0f, 1.0f };
  float light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
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
    info = readTimac();
    maxp = {info.xSize/2,info.ySize/2};
    minp = {-info.xSize/2,-info.ySize/2};
    imgdata = readMap(info.filename);
    map = HeightMap(maxp - minp, imgdata.data, imgdata.width, imgdata.height, imgdata.maxColorVal, info.zMin, info.zMax);
    //Call init (initialise GLUT
    init();
	  texture = genSkybox();
    sol = chargeTexture("./maps/text/rock.png");
    arbre = chargeTexture("./maps/text/tree.png");
    
    //Call "display" function
    glutDisplayFunc(display);

	  glutKeyboardFunc(kbdFunc);
	  glutSpecialFunc(kbdSpFunc);
    
    //Enter the GLUT event loop
    glutMainLoop();

    return 0;
}