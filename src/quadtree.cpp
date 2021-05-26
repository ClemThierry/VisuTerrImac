#include <quadtree.h>
#include <cmath>

void Quad::render(glm::vec2 topleft, glm::vec2 bottomright, HeightMap *map)
{
    if(children[0] == NULL ){        //test if it is a leaf
        //code for a leaf (rendu)
    }
    else{                           //node

        const glm::vec2 half = (topleft + bottomright) * 0.5f;

        const glm::vec2 tl[4] = {
            topleft,
            glm::vec2(half.x, topleft.y),
            glm::vec2(topleft.x, half.y),
            half
        };

        const glm::vec2 br[4] = {
            half,
            glm::vec2(bottomright.x, half.y),
            glm::vec2(half.x, bottomright.y),
            bottomright
        };

        for(int i=0 ; i<4 ; i++){
            children[i]->render(tl[i], br[i], map);        // nord-ouest -> nord-est -> sud-ouest -> sud-est
        }
    }
}

void Quad::clear(){                     //delete children
    for(int i=0 ; i<4 ; i++){
        if(children[i] != NULL){        //the child exists
            delete children[i];
            children[i] = NULL;
        }
    }
}

void Quad::build(glm::vec2 topleft, glm::vec2 bottomright, glm::vec2 frustum[4]) {
    build_rec(topleft, bottomright, frustum, 0);
}

bool collision(glm::vec2 topleft, glm::vec2 bottomright, glm::vec2 frustum[4]) {

    // obtenir le tableau des 4 points du rectangle abcd dans l'ordre géométrique (comme si on faisait le tour du rectangle)
    glm::vec2 rectangle[4] = {
        topleft,
        glm::vec2(bottomright.x, topleft.y),
        bottomright,
        glm::vec2(topleft.x, bottomright.y)
    };
    
    // calculer la collision enre deux polygones a 4 cotés

    //travail sur le rectangle
    for(int a=0 ; a<4 ; a++)
    {
        int b = (a+1)%4;                                            //modulo 4 car c'est une boucle (à la fin on fait de 3 à 0 et pas de 3 à 4)

        glm::vec2 ab = rectangle[b] - rectangle[a];
        glm::vec2 normal = glm::vec2(-ab.y , ab.x);                 //normale à ab

        //extrémités du projeté du rectangle
        float min=INFINITY, max=-INFINITY;
        for(int i=0 ; i<4 ; i++){
            glm::vec2 v = rectangle[i] - rectangle[a];
            float x = glm::dot(normal, v);

            if(min>x){
                min = x;
            }
            if(x>max){
                max = x;
            }
        }

        //extrémités du projeté du frustum
        float min2=INFINITY, max2=-INFINITY;
        for(int i=0 ; i<4 ; i++){
            glm::vec2 v = frustum[i] - rectangle[a];
            float x = glm::dot(normal, v);

            if(min2>x){
                min2 = x;
            }
            if(x>max2){
                max2 = x;
            }
        }

        //vérification pour savoir si les polygones se touchent
        //si nos deux projetés ne se touchent pas, alors les deux figures ne se touchent pas
        bool se_touchent = max2 >= min && max >= min2;

        if(!se_touchent){
            return False;
        }
    }

    //travail sur le frustum
    for(int a=0 ; a<4 ; a++)
    {
        int b = (a+1)%4;                                            //modulo 4 car c'est une boucle (à la fin on fait de 3 à 0 et pas de 3 à 4)

        glm::vec2 ab = frustum[b] - frustum[a];                     // /!\ maintenant on est sur les points a et b du frustum
        glm::vec2 normal = glm::vec2(-ab.y , ab.x);                 //normale à ab

        //extrémités du projeté du rectangle
        float min=INFINITY, max=-INFINITY;
        for(int i=0 ; i<4 ; i++){
            glm::vec2 v = rectangle[i] - frustum[a];
            float x = glm::dot(normal, v);

            if(min>x){
                min = x;
            }
            if(x>max){
                max = x;
            }
        }

        //extrémités du projeté du frustum
        float min2=INFINITY, max2=-INFINITY;
        for(int i=0 ; i<4 ; i++){
            glm::vec2 v = frustum[i] - frustum[a];
            float x = glm::dot(normal, v);

            if(min2>x){
                min2 = x;
            }
            if(x>max2){
                max2 = x;
            }
        }

        //vérification pour savoir si les polygones se touchent
        //si nos deux projetés ne se touchent pas, alors les deux figures ne se touchent pas
        bool se_touchent = max2 >= min && max >= min2;

        if(!se_touchent){
            return False;
        }
    }

    return True;

}

void Quad::build_rec(glm::vec2 topleft, glm::vec2 bottomright, glm::vec2 frustum[4], int level){
    if(level == 10 || !collision(topleft, bottomright, frustum) ){            //condition d'arret : on a atteint la profondeur/subdivision maximale ou pas de collision
        return;
    }
    else{                      //on crée des enfants

        const glm::vec2 half = (topleft + bottomright) * 0.5f;

        const glm::vec2 tl[4] = {
            topleft,
            glm::vec2(half.x, topleft.y),
            glm::vec2(topleft.x, half.y),
            half
        };

        const glm::vec2 br[4] = {
            half,
            glm::vec2(bottomright.x, half.y),
            glm::vec2(half.x, bottomright.y),
            bottomright
        };

        for(int i=0 ; i<4 ; i++){
            children[i] = new Quad();
            children[i]->build_rec(tl[i], br[i], frustum, level+1);
        }
    }
}