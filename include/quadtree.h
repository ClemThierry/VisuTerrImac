#include "../include/glm/glm.hpp"

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

    void render(glm::vec2 topleft, glm::vec2 bottomright, HeightMap *map);

    void clear();

    void build(glm::vec2 topleft, glm::vec2 bottomright, glm::mat4 camera);

    void build_rec(glm::vec2 topleft, glm::vec2 bottomright, glm::vec2 frustum[4], int level);

};
