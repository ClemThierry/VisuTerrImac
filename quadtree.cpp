#include <iostream>
#include <cmath>
using namespace std;
  
// Used to hold details of a point
struct Point
{
    int x;
    int y;
    Point(int valeur_x, int valeur_y)
    {
        x = valeur_x;
        y = valeur_y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};

// The objects that we want stored in the quadtree
struct Node
{
    Point pos;
    int elevation;
    Node(Point valeur_pos, int valeur_elevation)
    {
        pos = valeur_pos;
        elevation = valeur_elevation;
    }
    Node()
    {
        elevation = 0;
    }
};

// The main quadtree class
class Quad
{
    // Hold details of the boundary of this node
    Point topLeft;
    Point topRight;
    Point botRight;
    Point botLeft;
  
    // Contains details of node
    Node *n;
  
    // Children of this tree
    Quad *topLeftTree;
    Quad *topRightTree;
    Quad *botLeftTree;
    Quad *botRightTree;

  public:
    Quad()
    {
        topLeft = Point(0, 0);
        topRight = Point(0, 0);
        botRight = Point(0, 0);
        botLeft = Point(0, 0);
        n = NULL;
        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;
    }
    Quad(Point topL, Point topR, Point botR, Point botL)
    {
        n = NULL;

        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;

        topLeft = topL;
        topRight = topR;
        botRight = botR;
        botLeft = botL;
    }
    void insert(Node*);             //le noeud du milieu du quad
    Node* search(Point);
    bool in_quadtree(Point);
};

// Check if current quadtree contains the point
bool Quad::in_quadtree(Point p)
{
    return (p.x >= topLeft.x &&
        p.x <= botRight.x &&
        p.y >= topLeft.y &&
        p.y <= botRight.y);
}

// Insert a node into the quadtree
void Quad::insert(Node *node)
{
    if (node == NULL)
        return;
  
    // Current quad cannot contain it
    if (!in_quadtree(node->pos))
        return;
  
    if (isLeaf())
    {
        if (n == NULL){
            n = node;
        }
        return;
    }
  
    if ((topLeft.x + botRight.x) / 2 >= node->pos.x)            //le noeud sera placé à gauche
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(node);
        }
  
        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                    Point(topLeft.x,
                        (topLeft.y + botRight.y) / 2),
                    Point((topLeft.x + botRight.x) / 2,
                        botRight.y));
            botLeftTree->insert(node);
        }
    }
    else                                                        //le noeud sera placé à droite
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        topLeft.y),
                    Point(botRight.x,
                        (topLeft.y + botRight.y) / 2));
            topRightTree->insert(node);
        }
  
        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2),
                    Point(botRight.x, botRight.y));
            botRightTree->insert(node);
        }
    }
}

bool Quad::isLeaf(){
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    return (abs(topLeft.x - botRight.x) <= 1 &&
            abs(topLeft.y - botRight.y) <= 1);
}
