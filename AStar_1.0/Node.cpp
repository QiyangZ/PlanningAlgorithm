#include "Node.h"
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <queue>

int Node::distance(Node& node){
    return (abs(x - node.x) + abs(y - node.y));
}
Node::Node(int x, int y) : x(x), y(y), g(0), h(0), f(g + h), parent(nullptr) {};
Node::Node (int x, int y, int g, int h, Node* parent = nullptr) :
    x(x), y(y), g(g), h(h), f(g + h), parent(parent) {};


