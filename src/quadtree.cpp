#include <quadtree.h>

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