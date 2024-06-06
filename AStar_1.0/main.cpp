#include "Node.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>


class MySort {
    public:
    bool operator() (Node* n1, Node* n2) {
        return n1 -> f < n2 -> f;
    }
}; 

int mydistance(int x, int y, Node& node) {
    return (abs(x - node.x) + abs(y - node.y));
}

std::stack<Node*> aStarAlgorithm(std::vector<std::vector<int>>& gridMap, Node& start, Node& goal){
    using namespace std;
    stack<Node*> pathss;

    // priority_queue<Node*, vector<Node*>, MyCompare> openList; // the points, who are to be traversaled; prio. queue for sort
    // priority_queue cannot traversal, so use vector
    vector<Node*> openList;
    vector<Node*> closeList;
    // unordered_set<Node*> closeList; // the points, who are alredy traversaled; un. set for find

    openList.push_back(new Node(start.x, start.y, 0, start.distance(goal), nullptr));
    while(!openList.empty()) {
        
        sort(openList.begin(), openList.end(), MySort{});
        Node* cur = *openList.begin(); 
        openList.erase(openList.begin());
        closeList.push_back(cur);

        // 1. if cur is goal:
        // if (cur -> x == goal.x && cur ->y  == goal.y) return pathss; nonono!!
        
        if (cur -> x == goal.x && cur ->y  == goal.y) {
            while(cur != nullptr) {
                pathss.push(cur);
                cur = cur -> parent;
            }
            return pathss;
            // break;
        }

        // 2. if cur is not goal:
        int x = cur -> x;
        int y = cur -> y;
        
        vector<vector<int>> neighbors = {
            {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1},
            {x - 1, y},                 {x + 1, y},
            {x - 1, y + 1}, {x, y + 1}, {x + 1, y + 1}
        };
        
        for (auto n : neighbors) {
            
            bool inCloseList = false;
            for (auto c : closeList) {
                if (c-> x == n[0] && c-> y == n[1]) {
                    inCloseList = true;
                    break; // end for loop in close list
                }
            }
            
            if (n[0] < 0 || n[0] >= gridMap.size() || n[1] < 0 || n[1] >= gridMap[0].size() 
            || inCloseList || gridMap[n[0]][n[1]] == 1) {
                continue;
            }

            //n is in openlist or not:
            bool inOpenList = false;
            for (auto o : openList) {
                if(n[0] == o -> x && n[1] == o -> y) {
                    inOpenList = true;
                    // update f and parent
                    
                    int g = o -> distance(*cur) + cur -> g;
                    int h = o -> distance(goal);
                    int newf = g + h;
                    if (newf < o -> f) {
                        o -> f = newf;
                        o -> parent = cur;
                    }
                    break;
                }
            }

            if (!inOpenList) {
                int g = mydistance(n[0], n[1], *cur) + cur -> g;
                int h = mydistance(n[0], n[1], goal);
                // Node toAdd = Node(n[0], n[1], g, h, cur);
                openList.push_back(new Node(n[0], n[1], g, h, cur));
            }


        }

    }
    return pathss;
}



int main () {
    using namespace std;
    // grid map:
    vector<vector<int>> map = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
    };

    //define start and end point:
    Node start = Node(0, 0);
    Node goal = Node(4, 4);
    
    stack<Node*> result = aStarAlgorithm(map, start, goal);
    
    while (!result.empty()) {
        Node* pathPoint = result.top();
        result.pop();
        cout << '(' << pathPoint->x << ", " << pathPoint->y << ')' << endl;
    }
    return 0;
}