#pragma once
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

struct Problem {
    vector<vector<int>> initial_state;
    vector<vector<int>> goal_state = {{1, 2, 3},{4, 5, 6},{7, 8, 0}};
    //either add totalexpanded nodes here and maxfrontier size here or put in struct node; put it in problem cuz main uses problem p
    int totalExpandedNodes;
    int maxNumberOfNodesInQueue;

    Problem() { 
        initial_state = {{1, 0, 3},{4, 2, 6},{7, 5, 8}}; 
        totalExpandedNodes = 0;
        maxNumberOfNodesInQueue = 1;
    }

    Problem(vector<vector<int>> init) { 
        initial_state = init; 
        totalExpandedNodes = 0;
        maxNumberOfNodesInQueue = 0;
    }

    void up();
    void down();
    void left();
    void right();

    //Logic: let x = an instance where a big number comes before a small number.
    //If x is even, the puzzle is solvable. Otherwise not.
    bool isSolvable(const vector<vector<int>> s);


    //utilize goal state coordinates to calculate each distance
    double euclideanDist(vector<vector<int>> currState);
    int misplacedTileDist(vector<vector<int>> currState);
};

struct Node {
    public:
        Problem problem;
        Node* parent;
        Node* left;
        Node* right;
        int gCost; // cost from the start
        int hCost; // heuristic goal
        int fCost; // g(n) + h(n)
        int depth; //use for depth function 
        bool operator<(const Node& other) const {
            return gCost > other.gCost; // Reverse for min-heap behavior
            }

        //ctor
        Node() {
            parent = nullptr; left = nullptr; right = nullptr;
            gCost = 0; hCost = 0; fCost = 0;
            problem = Problem({{0,0,0},{0,0,0},{0,0,0}});
            depth = 0;
        }

        Node(Problem p) {
            parent = nullptr; left = nullptr; right = nullptr;
            gCost = 0; hCost = 0; fCost = 0;
            problem = p;
            depth = 0;
        }

        ~Node() {}

        //functions
        bool compareGCost(const Node* a, const Node* b) {return a->gCost < b->gCost;};
        bool compareHCost(const Node* a, const Node* b) {return a->hCost < b->hCost;};
        int getGCost() {return this->gCost;};
        int getHCost() {return this->hCost;};
        int getFCost() {return this->gCost + this->hCost;};
};

struct Tree {
    Node* root;

    //ctor
    Tree() : root(nullptr) {}

    // functions
    void addNode(int);
    void removeNode(int);
    void drawPath();
    int getNodeCount();
    int getExpandedNodes();
    int getMaxFrontierSize();
};

struct State{
    vector<vector<int>> board;
    int x; //x position of the blank (9)
    int y; //y position of the blank (9)

    char move; // can be up, down, left, or right
    State* parent; //to print out the path.

};

struct CompareByCost {
    bool operator()(const Node& a, const Node& b) const {
        return (a.gCost > b.gCost);
    }
};

void printState(const vector<vector<int>>& s);

//global funcs
Node UniformCostSearch(Problem& p);
Node AStarSearchMT(Problem& p);
Node AStarSearchED(Problem& p);
string stateToString(const vector<vector<int>>& state);
// bool inFrontier(priority_queue<Node, vector<Node>, CompareByCost> frontier, const vector<vector<int>>& state);
// bool inExplored(const vector<vector<vector<int>>>& explored, const vector<vector<int>>& state);
//put helper funcs here like infrontier or inexplored
//i think if u cant switch in up down left or right func and it returns same state, then dont add to frontier so we need to check for that