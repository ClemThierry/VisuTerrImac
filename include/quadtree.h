#ifndef __QUATREE_H
#define __QUATREE_H
#include "../include/glm/glm.hpp"
#include <GL/gl.h>

class HeightMap;

// The objects that we want stored in the quadtree
struct Node
{

};

// The main quadtree class
class Quad
{

    // Contains details of node
    Node n;
  
    // Children of this tree 
    Quad * children[4];

  public:
    Quad()                      //constructeur
    {
        children[0]  = NULL;
        children[1] = NULL;
        children[2]  = NULL;
        children[3] = NULL;
    }

    ~Quad(){                    //destructeur
        clear();
    }

    void render(glm::vec2 topleft, glm::vec2 bottomright, HeightMap *map, GLuint texture_id);

    void clear();

    void build(glm::vec2 topleft, glm::vec2 bottomright, glm::mat4 camera,glm::vec3 camPos);

    void build_rec(glm::vec2 topleft, glm::vec2 bottomright, glm::vec2 frustum[4], int level,glm::vec3 camPos);

};

#endif