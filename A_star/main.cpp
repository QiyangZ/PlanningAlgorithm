#include<iostream>
#include<vector>
#include<algorithm>

#include<unordered_set>
#include<queue>
#include<stack>

using namespace std;

// The points on grid map
struct Point
{
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    /*Return the distance between two points.*/
    int distance(const Point& p) {
        return abs(p.x - x) + abs(p.y - y);
    }
};

// Point, include more information(f, g, h...)
struct Node
{
    Point p;
    int f, g, h;
    Node* parent;
    Node (Point p, int g, int h, Node* parent = nullptr) 
    : p(p), g(g), h(h), f(g + h), parent(parent) {}
}; // without declaration, these parameters are public in Struct(in class, private)

class QueueCompare {
    public:
    bool operator()(Node* left, Node* right) {
        return left->f > right->f;
    }
};

class NodeCompare {
    public:
    bool operator() (Node* n1, Node* n2) {
        return n1->f < n2->f;
    }
};

stack<Point> aStarPath(const vector<vector<int>>& map, Point& start, Point& goal) {
    int row = map.size();
    int col = map[0].size();

    // priority_queue<Node*, vector<Node*>, MyCompare> openList; // define a min-heap
    // unordered_set<Node*> closeList; // define a hash map, max. efficiency for search
    vector<Node*> openList;
    vector<Node*> closeList;
    openList.push_back(new Node(start, start.distance(start), start.distance(goal)));
    stack<Point> path; // define a stack to store path point, no need to reverse.
    while (!openList.empty()) {
        sort(openList.begin(), openList.end(),NodeCompare{});
        Node* cur = *openList.begin();
        openList.erase(openList.begin());
        closeList.push_back(cur);
        //1. cur is goal:
        if(cur->p.x == goal.x && cur->p.y == goal.y) {
            while (cur != nullptr) {
                path.push(cur->p);
                cur = cur->parent;
            }
            return path;
        }
        
        //2. cur is not goal:
        int x = cur->p.x;
        int y = cur->p.y;
        vector<Point> neighbors = {
            {x - 1, y + 1}, {x, y + 1}, {x + 1, y + 1},
            {x - 1, y},                 {x + 1, y},
            {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}
        };

        // traverse the surrounding points:
        for (auto n : neighbors) {
            if (n.x < 0 || n.x >= row || n.y < 0 || n.y >= col || map[n.x][n.y] == 1) continue;
            bool inCloseList = false;
            for (auto c : closeList) {
                if (c->p.x == n.x && c->p.y == n.y) {
                    inCloseList = true;
                    break; // end for loop in close list
                }
            }
            if (inCloseList) continue;

            bool inOpenList = false;
            for (auto o : openList) {
                if (o->p.x == n.x && o->p.y == n.y) {
                    inOpenList = true;
                    // update f:
                    int g = n.distance(cur -> p) + cur -> g; // distance between neighbor and cur Node, plus, 
                                                             // g of cur. The distance between start and the neighbor
                    int h = n.distance(goal);
                    int f = g + h;
                    if (f < o->f) {
                        o -> f = f;
                        o -> parent = cur;
                    }
                    break; // end for loop in close list
                }
            }
            // if this neighbor not in openlist, then add to open list:
            if (!inOpenList) {
                int g = n.distance(cur -> p) + cur -> g;
                int h = n.distance(goal);
                // int f = g + h;
                openList.push_back(new Node(n, g, h, cur));
            }

        }

    }

    return path;

}



int main () {
    // grid map:
    vector<vector<int>> map = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
    };

    //define start and end point:
    Point start = Point(0, 0);
    Point goal = Point(4, 4);

    stack<Point> result = aStarPath(map, start, goal);
    while (!result.empty()) {
        Point pathPoint = result.top();
        result.pop();
        cout << '(' << pathPoint.x << ", " << pathPoint.y << ')' << endl;
    }
    return 0;
}