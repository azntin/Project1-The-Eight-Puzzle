#include <iostream>
#include <vector>
#include "eight_puzzle.h"

using namespace std;

int main() {
    int puzzleChoice;
    int algoChoice;
    Problem p;

    cout << "Welcome to 8 puzzle solver." << endl; // add student ID here ?
    cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle." << endl;
    cin >> puzzleChoice;

    if (puzzleChoice == 1) {
        p = Problem(); //default puzzle
    }
    if (puzzleChoice == 2) { 
        cout << "Enter your puzzle, use a zero to represent the blank." << endl;
        cout << "The puzzle will be filled in row-major order, meaning it fills each column of every row." << endl;
        int input;
        vector<vector<int>> userPuzzle(3, vector<int>(3, 0));

        for (int i = 0; i < 3; ++i) { //takes input and fills puzzle correctly
            for (int j = 0; j < 3; ++j) {
                cin >> input;
                userPuzzle[i][j] = input;
            }
        }
        p = Problem(userPuzzle);
    }
    cout << "Enter your choice of algorithm" << endl;
    cout << "Uniform Cost Search " << endl;
    cout << "A* with the Misplaced Tile heuristic" << endl;
    cout << "A* with the Euclidean distance heuristic" << endl;
    cin >> algoChoice;

    Node goalNode;
    if (algoChoice == 1) {
        goalNode = UniformCostSearch(p);
    }
    else if (algoChoice == 2) {
        goalNode = AStarSearchMT(p);
    }
    else if (algoChoice == 3) {
        goalNode = AStarSearchED(p);
    }

    //call correspodning function based on algochoice and that fnction can call 
    //func drawPath to show expanding the node and best choice... stuff from project


    cout << "Goal!!!" << endl; //maybe remove this because there are some cases where 
    //8 puzzle cant be solved?

    //for these three statements, maybe do it in the function itself and not here?
    // cout << "To solve this problem the search algorithm expanded a total of XXX (correct numbers should appear here) nodes." << endl;
    cout << "To solve this problem the search algorithm expanded a total of " << p.totalExpandedNodes << " nodes." << endl;
    // cout << "The maximum number of nodes in the queue at any one time: YYY." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << p.maxNumberOfNodesInQueue << "." << endl;
    cout << "The depth of the goal node was " << goalNode.depth << '.' << endl;  

    return 0;
}
