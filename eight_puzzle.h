#pragma once
#include <vector>
#include <iostream>

using namespace std;

struct Problem {
    vector<vector<int>> initial_state;
    vector<vector<int>> goal_state = {{1, 2, 3},{4, 5, 6},{7, 8, 0}};

    Problem() { initial_state = {{1, 0, 3},{4, 2, 6},{7, 5, 8}}; }

    Problem(vector<vector<int>> init) { initial_state = init; }

    void up();
    void down();
    void left();
    void right();

    //Logic: let x = an instance where a big number comes before a small number.
    //If x is even, the puzzle is solvable. Otherwise not.
    bool isSolvable(const vector<vector<int>> s);
};

struct Node {
        Problem problem;
        Node* parent;
        Node* left;
        Node* right;
        int gCost; // cost from the start
        int hCost; // heuristic goal
        int fCost; // g(n) + h(n)

        //ctor
        Node() {
            parent = nullptr; left = nullptr; right = nullptr;
            gCost = 0; hCost = 0; fCost = 0;
            problem = Problem({{0,0,0},{0,0,0},{0,0,0}});
        }

        Node(Problem p) {
            parent = nullptr; left = nullptr; right = nullptr;
            gCost = 0; hCost = 0; fCost = 0;
            problem = p;
        }

        ~Node() {}

        //functions
        bool compareGCost(const Node* a, const Node* b) {return a->gCost < b->gCost;};
        bool compareHCost(const Node* a, const Node* b) {return a->hCost < b->hCost;};
        int getGCost() {return this->gCost;};
        int getHCost() {return this->hCost;};
        int getFCost() {return this->fCost;};
};

struct Tree {
    Node* root;

    //ctor
    Tree() : root(nullptr) {}

    // functions
    void addNode(int);
    void removeNode(int);
    void drawPath();
    int depth();
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

void printState(const vector<vector<int>> s){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(s[i][j] == 0){cout << "X";}
            else{cout << s[i][j];}
        }
        cout << endl;
    }
}