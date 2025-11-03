#pragma once
#include <vector>
#include <queue>

using namespace std;

struct Problem {
    vector<vector<int>> initial_state;
    vector<vector<int>> goal_state = {{1, 2, 3},{4, 5, 6},{7, 8, 0}};
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
        maxNumberOfNodesInQueue = 1;
    }

    ~Problem() {}

    void up();
    void down();
    void left();
    void right();

    //Logic: let x = an instance where a big number comes before a small number.
    //If x is even, the puzzle is solvable. Otherwise not.
    bool isSolvable(const vector<vector<int>> s);

    double euclideanDist(vector<vector<int>> currState);
    int misplacedTileDist(vector<vector<int>> currState);
};

struct Node {
    Problem problem;
    Node* parent; //Used for path tracing for report
    int gCost; //Cost from the start
    int hCost; //Heuristic goal
    int fCost; //g(n) + h(n)
    int depth; //Depth of solution 
    bool operator<(const Node& other) const {
        return gCost > other.gCost; // Reverse for min-heap behavior
        }

    Node() {
        parent = nullptr;
        gCost = 0; hCost = 0; fCost = 0;
        problem = Problem({{0,0,0},{0,0,0},{0,0,0}});
        depth = 0;
    }

    Node(Problem p) {
        parent = nullptr;
        gCost = 0; hCost = 0; fCost = 0;
        problem = p;
        depth = 0;
    }

    ~Node() {}
};

struct CompareByCost { //Struct used for priority queue comparison and insertion based on gCost
    bool operator()(const Node* a, const Node* b) const {
        return (a->gCost > b->gCost);
    }
};

struct CompareByFCost { //Struct used for priority queue comparison and insertion based on fCost
    bool operator()(const Node* a, const Node* b) const {
        return (a->fCost > b->fCost);
    }
};

//Global funcs
Node* UniformCostSearch(Problem& p);
Node* AStarSearchMT(Problem& p);
Node* AStarSearchED(Problem& p);
string stateToString(const vector<vector<int>>& state); //Used as a helper function to convert each state to string for hashing and making it easier to check for dupes
void printState(const vector<vector<int>>& s); //Used for printing the path for report