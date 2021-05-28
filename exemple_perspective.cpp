#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <camera.h>

void dessinercube(float width, glm::vec3 pos);

int main()
{
    float PI=3.1416;

    // crée la fenêtre
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activation de la fenêtre
    window.setActive(true);

    // chargement des ressources, initialisation des états OpenGL, ...
    glEnable(GL_DEPTH_TEST);

    // la boucle principale
    bool running = true;
    int width, height;

    camera cam(PI/2, 0.1, 5.0, 800, 600);

    while (running)
    {

        cam.avancer(1);
        
        // gestion des évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // on stoppe le programme
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // on ajuste le viewport lorsque la fenêtre est redimensionnée
                glViewport(0, 0, event.size.width, event.size.height);

                //on sauvergarde les dimensions
                width = event.size.width;
                height = event.size.height;

                cam.setdimension(width, height);
            }
            else if (event.type == sf::Event::MouseMoved)           //essai couleurs fond
            {
                float rouge = (float)event.mouseMove.x/width;
                float bleu = (float)event.mouseMove.y/height;
                glClearColor(rouge,bleu,0,1);
            }
        }

        // effacement les tampons de couleur/profondeur
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // dessin...

        glm::mat4 perspective = cam.calculermatrice();
        glLoadMatrixf(glm::value_ptr(perspective));

        dessinercube(1.2, glm::vec3(20.0f,0.0f,0.0f));

        // termine la trame courante (en interne, échange les deux tampons de rendu)
        window.display();
    }

    // libération des ressources...

    return 0;
}

void dessinercube(float width, glm::vec3 pos){

    float coord[3*24] = {
            // Face front (z = -width/2) (E,F,G,H)
            -width/2.0f,-width/2.0f,-width/2.0f,	// E
            width/2.0f,-width/2.0f,-width/2.0f,		// F
            width/2.0f,width/2.0f,-width/2.0f,		// G
            -width/2.0f,width/2.0f,-width/2.0f,		// H
            // Face back (z = width/2) (A,B,C,D)
            -width/2.0f,-width/2.0f,width/2.0f,		// A
            width/2.0f,-width/2.0f,width/2.0f,		// B
            width/2.0f,width/2.0f,width/2.0f,		// C
            -width/2.0f,width/2.0f,width/2.0f,		// D
            // Face left (x = -width/2) (E,A,D,H)
            -width/2.0f,-width/2.0f,-width/2.0f,	// E
            -width/2.0f,-width/2.0f,width/2.0f,		// A
            -width/2.0f,width/2.0f,width/2.0f,		// D
            -width/2.0f,width/2.0f,-width/2.0f,		// H
            // Face right (x = +width/2) (B,F,G,C)
            width/2.0f,-width/2.0f,width/2.0f,		// B
            width/2.0f,-width/2.0f,-width/2.0f,		// F
            width/2.0f,width/2.0f,-width/2.0f,		// G
            width/2.0f,width/2.0f,width/2.0f,		// C
            // Face top (y = +width/2) (D,C,G,H)
            -width/2.0f,width/2.0f,width/2.0f,		// D
            width/2.0f,width/2.0f,width/2.0f,		// C
            width/2.0f,width/2.0f,-width/2.0f,		// G
            -width/2.0f,width/2.0f,-width/2.0f,		// H
            // Face down (y = -width/2) (A,B,F,E)
            -width/2.0f,-width/2.0f,width/2.0f,		// A
            width/2.0f,-width/2.0f,width/2.0f,		// B
            width/2.0f,-width/2.0f,-width/2.0f,		// F
            -width/2.0f,-width/2.0f,-width/2.0f		// E
        };

    float couleurs[3*6] = {
        1,0,0,
        0,1,0,
        0,0,1,
        1,0,0,
        0,1,0,
        0,0,1
    };

    glBegin(GL_QUADS);

    for(int i=0 ; i<24 ; i++){
        int j=3*i;
        int c=i/4;
        glColor3f(couleurs[c], couleurs[c+1], couleurs[c+2]);
        glVertex3f(coord[j]+pos.x, coord[j+1]+pos.y, coord[j+2]+pos.z);
    }

    glEnd();

}