#pragma once
#include <vector>

using namespace std;

class Node {
    public:
        Node* parent;
        Node* left;
        Node* right;
        int value;

        //ctor
        Node() : parent(nullptr), left(nullptr), right(nullptr), value(0) {}
        Node(int num) : parent(nullptr), left(nullptr), right(nullptr), value(num) {}
        ~Node() {}
};

class Tree {
    public:
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

class Problem {
    vector<vector<int>> initial_state;
    vector<vector<int>> goal_state : {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    Problem(vector<vector<int>> init) {
        initial_state = init;
    }

    Problem() {
        initial_state = {
            {1, 0, 3},
            {4, 2, 6},
            {7, 5, 8}
        };
    };

    void up();
    void down();
    void left();
    void right();
    
};
