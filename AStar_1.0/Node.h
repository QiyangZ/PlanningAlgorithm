#ifndef NODE_H
#define NODE_H

#include<stack>
#include<vector>

class Node {
    // private:
    
    
    

    public:
    int x;
    int y; // the coordonate of this point
    int f, g, h; // f = g + h;
    Node* parent;

    int distance(Node& node);
    Node(int x, int y);
    Node (int x, int y, int g, int h, Node* parent);
    
};
#endif