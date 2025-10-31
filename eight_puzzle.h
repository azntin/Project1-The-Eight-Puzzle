#pragma once
#include <vector>
#include <iostream>

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
    }

    void up();
    void down();
    void left();
    void right();

    //Logic: let x = an instance where a big number comes before a small number.
    //If x is even, the puzzle is solvable. Otherwise not.
    bool isSolvable(const vector<vector<int>> s){
        vector<int> vec;
        int currPos;
        int bigBeforeSmall = 0;

        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                currPos = s[i][j];
                if(currPos != 0){
                    vec.push_back(currPos);
                }
            }
        }

        for(int i = 0; i < vec.size(); ++i){
            for(int j = i+1; j < vec.size(); ++j){
                if(vec.at(i) > vec.at(j)){
                    bigBeforeSmall ++;
                }
            }
        }
        return (bigBeforeSmall % 2 == 0);
    };
  
    
};
